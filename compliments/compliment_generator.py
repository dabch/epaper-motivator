#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys

STRING_DECL = "const char c{}[] PROGMEM = \"\\x05\"\"{}\\x04\";"
ARRAY_DECL = "const char *const compliments_progmem[] = {{{}}};"
COUNT_DECL = "const int COMPLIMENT_COUNT = {};"

DEBUG = False

def main():
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} [line length] [max line count]")
        return
    line_len = int(sys.argv[1])
    line_count = int(sys.argv[2])
    if line_len <= 0:
        print("Invalid line length")
        print(f"Usage: {sys.argv[0]} [line length] [max line count]")
        return
    if line_count <= 0:
        print("Invalid line count")
        print(f"Usage: {sys.argv[0]} [line length] [max line count]")
        return

    print("// ---------------- BEGIN GENERATED COMPLIMENTS -------------")
    print(f"// line length: {line_len}")
    print("// ---------------- - - - - - - - - - - - - - - -------------")

    count = 0

    struct_elems_list = []
    
    while True:
        try:
            compliment = input()
        except EOFError:
            break
        line_idx = 0
        lines = [""]
        if len(compliment.strip()) <= 0 or compliment.startswith('#'):
            continue
        words = compliment.strip().split(" ")
        while len(words) > 0:
            if DEBUG:
                print("===")
                print(words[0])
                print(line_idx)
                print(lines)
                print(lines[line_idx])

            if (len(lines[line_idx]) + len(words[0])) <= line_len:
                lines[line_idx] += words[0] + " " 
                words = words[1:]
            elif len(words[0]) > line_len:
                part_1 = words[0][:line_len - len(lines[line_idx]) - 1]
                part_2 = words[0][line_len - len(lines[line_idx]) - 1:]
                lines[line_idx] += part_1 + "-"
                words = [part_2] + words[1:]
                line_idx += 1
                lines.append("")
            else:
                lines[line_idx] = lines[line_idx].strip()
                lines.append("")
                line_idx += 1

        if len(lines) > line_count:
            print(f"ERROR: compliment too long ({len(lines)} lines), please adjust manually: \"{compliment}\"", file=sys.stderr)
        compliment = "\\n".join(lines).strip()
        if len(lines) <= 4:
            compliment = '\\n' + compliment
        if len(lines) <= 2:
            compliment = '\\n' + compliment

        compliment = compliment.replace("ö", "\\x94\"\"")
        compliment = compliment.replace("ü", "\\x81\"\"")
        compliment = compliment.replace("ä", "\\x84\"\"")
        compliment = compliment.replace("Ä", "\\x8e\"\"")
        compliment = compliment.replace("Ö", "\\x99\"\"")
        compliment = compliment.replace("Ü", "\\x9a\"\"")
        compliment = compliment.replace("ß", "\\xe0\"\"")

        print(STRING_DECL.format(count, compliment))
        count += 1

    print(ARRAY_DECL.format(', '.join([f"c{i}" for i in range(count)])))

    print(COUNT_DECL.format(count))
                

if __name__ == "__main__":
    main()

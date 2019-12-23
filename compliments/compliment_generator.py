#!/usr/bin/env python3
import sys

STRING_DECL = "const char c{}_{}[] PROGMEM = \"{}\";"
#STRUCT_DECL = "const compliment_t c{} PROGMEM = {{{}, c{}a}};"
ARRAY_DECL = "const char* const c{}a[] = {{{}}};"
#ARRAY_DECL = "const char* const c{}a[] PROGMEM = {{{}}};"
ARRAY_ELEMENT_DECL = "c{}_{}"

MAP_DECL = "const compliment_t compliment_table[] = {{{}}};"
#MAP_DECL = "const compliment_t compliment_table[] PROGMEM = {{{}}};"
MAP_ELEMENT_DECL = "{{{}, c{}a}}"

def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} [line length]")
        return
    line_len = int(sys.argv[1])
    if line_len <= 0:
        print("Invalid line length")
        print(f"Usage: {sys.argv[0]} [line length]")
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

        line = 0
        words = compliment.split(" ")
        current = ""
        while len(words) > 0:
            if (len(current) + len(words[0])) <= line_len:
                current += words[0] + " "
                words = words[1:]
            elif len(words[0]) > line_len:
                part_1 = words[0][:line_len - len(current)]
                part_2 = words[0][line_len - len(current):]
                current += part_1 + " "
                words = [part_2] + words[1:]
                print(STRING_DECL.format(count, line, current.strip()))
                line += 1
                current = ""
            else:
                print(STRING_DECL.format(count, line, current.strip()))
                line += 1
                current = ""
        print(STRING_DECL.format(count, line, current.strip()))
        line += 1

        array_elements_list = [ARRAY_ELEMENT_DECL.format(count, i) for i in range(line)]
        array_elements = ", ".join(array_elements_list)
        
        print(ARRAY_DECL.format(count, array_elements))
        #struct_elems = struct_elems.append(MAP_ELEMENT_DECL.format(line, count))
        struct_elems_list.append(MAP_ELEMENT_DECL.format(line, count))
        count += 1
        print()

    if count <= 0:
        return

    #table_elements_list = [MAP_ELEMENT_DECL.format(i) for i in range(count)]
    struct_elems = ", ".join(struct_elems_list)
    print(MAP_DECL.format(struct_elems))

    print(f"const int COMPLIMENT_COUNT = {count};")
            
    print("// ---------------- END GENERATED COMPLIMENTS -------------")

if __name__ == "__main__":
    main()

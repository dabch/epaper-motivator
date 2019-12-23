upload: compile
	arduino-cli upload -b arduino:avr:pro -p /dev/ttyUSB1 -i build/sketch.hex

compile: src/*
	[ -d build ] || mkdir -p build
	arduino-cli compile -b arduino:avr:pro -o build/sketch.hex src/lea-motivator.cpp


clean:
	rm -r build

    

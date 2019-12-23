upload: compile
	arduino-cli upload -b arduino:avr:pro -p /dev/ttyUSB1 -i lea-motivator.ino.arduino.avr.pro.with_bootloader.hex

compile: lea-motivator.ino src/*
	arduino-cli compile -b arduino:avr:pro lea-motivator.ino

    

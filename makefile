all:eOrgan-108328017.c
	sdcc -c Keypad4x4.c
	sdcc eOrgan-108328017.c Keypad4x4.rel 
	sdar -o myIO.lib -rc Keypad4x4.rel 
	sdcc myIO.lib eOrgan-108328017.c
	packihx eOrgan-108328017.ihx > eOrgan-108328017.hex
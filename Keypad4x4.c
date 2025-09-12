#include<8051.h>

unsigned int keypad4x4(unsigned int num)
{
	unsigned int datas[] = {0b01110111, 0b10110111, 0b11010111, 0b11100111,	 // 0 1 2 3
							0b01111011, 0b10111011, 0b11011011, 0b11101011,	 // 4 5 6 7
							0b01111101, 0b10111101, 0b11011101, 0b11101101,	 // 8 9 A B
							0b01111110, 0b10111110, 0b11011110, 0b11101110}; // C D E F

	for (int i = 0; i < 16; i++)
	{
		if (num == datas[i])
			return i;
	}

	return 0;
}
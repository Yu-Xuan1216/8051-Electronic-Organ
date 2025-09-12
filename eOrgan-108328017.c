#include <8051.h>
#include "Keypad4x4.h"
#define tick 15536
#define record_size 30

unsigned int tone = 0;		 // 紀錄當下是哪個音
char interrupts = 0; //計算有幾次 interrupt
unsigned int count = 0;		// 錄了多少音
int beat = 0;	// 放音當下的音

const unsigned melody[] = {1908, 1805, 1700, 1608, // C 		C# 		D 		D#
						   1515, 1432, 1351, 1275, // E 		F 		F# 		G
						   1205, 1136, 1121, 1012, // G# 		A 		A# 		B
						   954, 850};			   // highC 	highD

__xdata unsigned int record[record_size] = {0}; // 儲存錄音資訊

void delay(int t) //	延遲函數開始
{
	int i, j;
	for (i = 0; i < t; i++)
		for (j = 0; j < 800; j++);
}


void timer0_i1sr(void) __interrupt(1) __using(1) //發出聲音
{
	int note = 65535 - melody[tone];
	TH0 = note >> 8;   // the first 4 bits of the note
	TL0 = note & 0xff; // the last 4 bits of the note
	P0 = ~P0;		   // high wave and low wave
}

void timer1_isr(void) __interrupt(3) __using(2) // count time
{
	TH1 = tick >> 8;
	TL1 = tick & 0xff;
	if (interrupts > 20)	// 1 second have 20 interrupts, 13 次 interrupt 要加一拍
	{ 
		beat += 1;
		interrupts = 0;
	}
	else
		interrupts += 1;
	if (beat>count || beat>=record_size)
		beat = -1;
}

void recordmusic(int key)
{
	P2 = 0x40; // 按E 七段顯示0: 錄音
	tone = key;
	record[count] = tone;
}

void playmusic()
{
	P2 = 0x79; // 按F 七段顯示1: 放音
	tone = record[beat];
}

// P0: 喇叭
// P1: Keypad
// P2: 七段

void main(void)
{
	IE = 0x8A;
	TMOD = 0x11; // set timer mode
	TCON = 0x50; // open timer1 and timer0
	P0 = 0;		 // P0: 喇叭

	unsigned char tmp;
	unsigned int data[4] = {0xfe, 0xfd, 0xfb, 0xf7};
	unsigned int record_tmp = 2; //紀錄目前狀態為錄音 or 放音
	unsigned int key = 0;

	while (1)
	{
		for (int i = 0; i < 4; i++)
		{
			P1 = data[i]; // P1: keypad
			tmp = P1;
			while (((tmp & 0xf0) != 0xf0)) // 檢查是否有按鍵按下
			{
				delay(3); //延遲, 判斷是否為彈跳訊號
				tmp = P1;
				if (((tmp & 0xf0) != 0xf0)) //如果仍然有0的情況, 則表示非彈跳訊號
				{
					key = keypad4x4(P1);
					if (key == 14)
					{
						record_tmp = 0; // 錄音
						count = -1;		// 錄了多少音
						for(int i = 0; i<record_size ; i++)
							record[i] = -1;
					}
					else if (key == 15)
					{
						record_tmp = 1; // 放音
						beat = 0;
					}

					if (record_tmp == 0) // 錄音
					{
						recordmusic(key);
						count++;
					}
				}

				do
				{
					tmp = P1;					//讀回按鍵值
				} while ((tmp & 0xf0) != 0xf0); // 直到前4 bits皆為1為止 (代表按鍵已放開)
					
			}
		}
		if (record_tmp == 1) //放音
		{
			playmusic();
		}
	}
}
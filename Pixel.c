/*
 * Pixel.c
 *
 *  Created on: -----
 *      Author: -----
 */

#include "Pixel.h"



//Table for pixel dots.
//				 dots[X][Y][COLOR]
volatile uint8_t dots[8][8][3]={0};

// Here the setup operations for the LED matrix will be performed
void setup()
{
	// Resetting the screen at start is a MUST to operation (Set RSTn to 1).
	*control = 0;
	*channel = 0;

	// Sleep 500 ms
	usleep(500);
	*control&= 0b00000;
	// RSTn bit = 1
	*control |= 0b00001;
	// SDA bit = 1
	*control |= 0b10000;


	//Write code that sets 6-bit values in register of DM163 chip. Recommended that every bit in that register is set to 1. 6-bits and 24 "bytes", so some kind of loop structure could be nice.
	//24*6 bits needs to be transmitted
	for (uint8_t i = 0; i < 24*6; ++i)
	{
		// Set clock signal to LOW
		*control &= ~(0b01000);
		// Set clock signal to HIGH
		*control |= (0b01000);
	}
	// Set clock signal to LOW
	*control &= ~(0b01000);

	//Final thing in this function is to set SB-bit to 1 to enable transmission to 8-bit register.
	*control |= (0b00100);
}

//Change value of one pixel at led matrix. This function is only used for changing values of dots array
void SetPixel(uint8_t x,uint8_t y, uint8_t r, uint8_t g, uint8_t b){

	//Hint: you can invert Y-axis quite easily with 7-y
	dots[x][y][0]=b;
	//Write rest of two lines of code required to make this function work properly (green and red colors to array).
	dots[x][y][1]=g;
	dots[x][y][2]=r;

}


//Put new data to led matrix. Hint: This function is supposed to send 24-bytes and parameter x is for channel x-coordinate.
void run(uint8_t x){



	//Write code that writes data to led matrix driver (8-bit data). Use values from dots array
	//Hint: use nested loops (loops inside loops)
	//Hint2: loop iterations are 8,3,8 (pixels,color,8-bitdata)
	for (int pixel = 0; pixel < 8; ++pixel)
	{
		for (int color = 0; color < 3; ++color)
		{
			for (int data_counter = 0; data_counter < 8; ++data_counter)
			{
				uint8_t data = dots[x][pixel][color];
				if (data & 0x80)
					*control |= 0x10;
				else
					*control &= ~0x10;
				*control &= ~0x08;
				data <<= 1;
				*control |= 0x08;
			}
		}
	}
	latch();
	*control &= ~0x08;
}

//Latch signal. See colorsshield.pdf or DM163.pdf in project folder on how latching works
void latch()
{
	*control |= 0b00010;
	*control &= ~0b00010;
}


//Set one line (channel) as active, one at a time.
void open_line(uint8_t x){
	switch (x)
	{
		case 0:
			*channel |= 0b00000001;
			break;
		case 1:
			*channel |= 0b00000010;
			break;
		case 2:
			*channel |= 0b00000100;
			break;
		case 3:
			*channel |= 0b00001000;
			break;
		case 4:
			*channel |= 0b00010000;
			break;
		case 5:
			*channel |= 0b00100000;
			break;
		case 6:
			*channel |= 0b01000000;
			break;
		case 7:
			*channel |= 0b10000000;
			break;
		default:
			*channel = 0;
	}
}




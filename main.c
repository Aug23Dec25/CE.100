/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 *
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

// Main program for exercise

//****************************************************
//By default, every output used in this exercise is 0
//****************************************************
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xgpiops.h"
#include "xttcps.h"
#include "xscugic.h"
#include "xparameters.h"
#include "Pixel.h"
#include "Interrupt_setup.h"
#include <stdbool.h>
#include "game_logic.h"

//********************************************************************
//***************TRY TO READ COMMENTS*********************************
//********************************************************************

//***Hint: Use sleep(x)  or usleep(x) if you want some delays.****
//***To call assembler code found in blinker.S, call it using: blinker();***


//Comment this if you want to disable all interrupts
#define enable_interrupts




/***************************************************************************************
Name: Duc Nguyen
Student number: 151945124

Name: Quang Nguyen
Student number:

Name:
Student number:

Tick boxes that you have coded

Led-matrix driver		Game		    Assembler
	[x]					[x]					[]

Brief description:

*****************************************************************************************/



volatile uint8_t channel_index = 0;
volatile uint8_t alien_x = 0, alien_y = 0, alien_direction = 1;
volatile uint8_t ship_x = 0, ship_direction = 0;
volatile uint8_t bullet_x, bullet_y, bullet_direction = 1;
volatile uint8_t score=0;


int main()
{
	//**DO NOT REMOVE THIS****
	    init_platform();
	//************************


#ifdef	enable_interrupts
	    init_interrupts();
#endif


	    //setup screen

	    setup();





	    Xil_ExceptionEnable();



	    //Try to avoid writing any code in the main loop.
		while(1){


		}


		cleanup_platform();
		return 0;
}


//Timer interrupt handler for led matrix update. Frequency is 800 Hz
void TickHandler(void *CallBackRef){
	//Don't remove this
	uint32_t StatusEvent;

	// Exceptions must be disabled when updating screen
	Xil_ExceptionDisable();



	//****Write code here ****

	if(channel_index > 7)
	{
		channel_index = 0;
	}

	open_line(100);

	run(channel_index);
	open_line(channel_index);
	channel_index++;





	//****END OF OWN CODE*****************

	//*********clear timer interrupt status. DO NOT REMOVE********
	StatusEvent = XTtcPs_GetInterruptStatus((XTtcPs *)CallBackRef);
	XTtcPs_ClearInterruptStatus((XTtcPs *)CallBackRef, StatusEvent);
	//*************************************************************
	//enable exceptions
	Xil_ExceptionEnable();
}


//Timer interrupt for moving alien, shooting... Frequency is 10 Hz by default
void TickHandler1(void *CallBackRef)
{

	//Don't remove this
	uint32_t StatusEvent;

	//****Write code here ****
    // Draw the ship at its current position
    make_ship(ship_x);

    // Move and draw the alien
    make_alien(alien_x, 0, alien_direction);
    alien_x += alien_direction;

    // Reverse alien direction if it hits the edges
    if (alien_x >= 8 || alien_x < 0) {
        alien_direction *= -1;
        alien_x += alien_direction;
    }

    // Handle the bullet's movement
    if (bullet_y < 8 && bullet_y >= 0) {
        bullet_y -= bullet_direction;
        make_bullet(bullet_x, bullet_y);

        // Check if the bullet hits the alien
        if (bullet_x == alien_x && bullet_y == alien_y) {
            score++;
            display_score(score);
        }
    }

    // Check for victory condition
    if (score == 3)
    {
        display_victory();
    }


	//****END OF OWN CODE*****************
	//clear timer interrupt status. DO NOT REMOVE
	StatusEvent = XTtcPs_GetInterruptStatus((XTtcPs *)CallBackRef);
	XTtcPs_ClearInterruptStatus((XTtcPs *)CallBackRef, StatusEvent);
}


//Interrupt handler for switches and buttons.
//Reading Status will tell which button or switch was used
//Bank information is useless in this exercise
void ButtonHandler(void *CallBackRef, u32 Bank, u32 Status){
	//****Write code here ****

	//Hint: Status==0x01 ->btn0, Status==0x02->btn1, Status==0x04->btn2, Status==0x08-> btn3, Status==0x10->SW0, Status==0x20 -> SW1

    if (Status == 0x01) { // BTN0: Fire a bullet
        bullet_x = ship_x + 1; // Set bullet to the ship's middle position
        bullet_y = 7;          // Place bullet at the top of the ship
    }
    else if (Status == 0x02) { // BTN1: Move ship right
        move_ship_right(); // Shift the ship one column to the right
    }
    else if (Status == 0x04) { // BTN2: Move ship left
        move_ship_left(); // Shift the ship one column to the left
    }
    else if (Status == 0x08) { // BTN3: Reset game state
        alien_x = 0;
        alien_y = 0;
        alien_direction = 1;
        ship_x = 0;
        score = 0;
        reset_scoreboard(); // Clear the matrix and reset all variables
    }






	//****END OF OWN CODE*****************
}

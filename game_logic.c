#include "game_logic.h"


void move_alien(uint8_t alien_x, uint8_t alien_y, uint8_t direction)
{
	// Clear the current position of alien
	SetPixel(alien_x, alien_y, 0, 0, 0);
	sleep(1);

	if (direction + alien_x >= 0 && direction + alien_x <= 7)
	{
		alien_x += direction;
	}

	// Draw the new alien's position
	SetPixel(alien_x, alien_y, 255, 0, 0);
}











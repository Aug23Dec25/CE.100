#include "game_logic.h"

// External variables
extern uint8_t ship_x;
extern uint8_t bullet_direction;
extern uint8_t bullet_y;
extern uint8_t won_flag;

/**
 * @brief Draws the alien at the specified position and clears its previous position.
 * @param x Alien's current x-coordinate.
 * @param y Alien's current y-coordinate.
 * @param direction Alien's movement direction (1 for right, -1 for left).
 */
void make_alien(uint8_t x, uint8_t y, uint8_t direction)
{
	if (won_flag == 1) return;
    SetPixel(x, y, 104, 187, 89); // Draw the alien (green pixel)

    // Clear the alien's previous position
    uint8_t prev_x = x - direction;
    if (prev_x >= 0 && prev_x <= 7) {
        SetPixel(prev_x, y, 0, 0, 0); // Clear the pixel
    }
}

/**
 * @brief Draws the ship at its current position on the LED matrix.
 * @param ship_x The current x-coordinate of the ship's leftmost pixel.
 */
void make_ship(uint8_t ship_x)
{
	if (won_flag == 1) return;
    // Draw the ship (sky-blue color)
    for (uint8_t i = 0; i < 3; i++) {
        SetPixel(ship_x + i, 6, 56, 149, 211);
    }
    SetPixel(ship_x + 1, 5, 56, 149, 211); // Top point of the ship
}

/**
 * @brief Moves the ship one position to the right, ensuring it stays within bounds.
 */
void move_ship_right()
{
	if (won_flag == 1) return;
    // Clear the ship's current position
    for (uint8_t i = 0; i < 3; i++) {
        SetPixel(ship_x + i, 6, 0, 0, 0);
    }
    SetPixel(ship_x + 1, 5, 0, 0, 0); // Clear the top point

    // Move the ship right if within bounds
    if (ship_x < 5) {
        ship_x++;
    }

    // Redraw the ship
    make_ship(ship_x);
}

/**
 * @brief Moves the ship one position to the left, ensuring it stays within bounds.
 */
void move_ship_left()
{
	if (won_flag == 1) return;
    // Clear the ship's current position
    for (uint8_t i = 0; i < 3; i++) {
        SetPixel(ship_x + i, 6, 0, 0, 0);
    }
    SetPixel(ship_x + 1, 5, 0, 0, 0); // Clear the top point

    // Move the ship left if within bounds
    if (ship_x > 0) {
        ship_x--;
    }

    // Redraw the ship
    make_ship(ship_x);
}

/**
 * @brief Draws a bullet at its current position and clears its previous position.
 * @param x Bullet's current x-coordinate.
 * @param y Bullet's current y-coordinate.
 */
void make_bullet(uint8_t x, uint8_t y) {
    static uint8_t prev_x = 8; // Track the previous x position
    static uint8_t prev_y = 8; // Track the previous y position

    // Clear the bullet's previous position
    if (prev_x < 8 && prev_y < 8) {
        SetPixel(prev_x, prev_y, 0, 0, 0);
    }

    // Draw the bullet at its new position
    if (y < 8 && y >= 0) {
        SetPixel(x, y, 255, 0, 0); // Red bullet
    }

    // Update previous bullet position
    prev_x = x;
    prev_y = y;
}

/**
 * @brief Displays the player's score as white pixels on the bottom row.
 * @param score The player's current score.
 */
void display_score(uint8_t score) {
    // Clear the score area
    for (uint8_t i = 0; i < 8; i++) {
        SetPixel(i, 7, 0, 0, 0);
    }

    // Draw the score
    for (uint8_t i = 0; i < score; i++) {
        SetPixel(i, 7, 255, 255, 255); // White score pixels
    }
}

/**
 * @brief Displays a simple smiley face when the player wins.
 */
void display_victory()
{
	won_flag = 1;
    uint8_t smiley[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            if (smiley[i][j] == 1) {
                SetPixel(j, i, 255, 255, 0); // Yellow for smiley
            } else {
                SetPixel(j, i, 0, 0, 0); // Clear pixel
            }
        }
    }

}

/**
 * @brief Resets the entire LED matrix to a blank state.
 */
void reset_scoreboard() {
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            SetPixel(i, j, 0, 0, 0); // Clear all pixels
        }
    }
}

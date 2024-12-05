#ifndef SRC_GAMELOGIC_H_   // Include guard to prevent multiple inclusions
#define SRC_GAMELOGIC_H_

#include "Pixel.h"  // Include Pixel.h for SetPixel functionality

// -------------------------------------
// Function Declarations
// -------------------------------------

/**
 * @brief Draws the alien at the specified position and clears its previous position.
 * @param x Alien's current x-coordinate.
 * @param y Alien's current y-coordinate.
 * @param direction Alien's movement direction (1 for right, -1 for left).
 */
void make_alien(uint8_t x, uint8_t y, uint8_t direction);

/**
 * @brief Activates the LED board by resetting the entire matrix.
 */
void activate_board();

/**
 * @brief Draws the ship at its current position on the LED matrix.
 * @param ship_x The current x-coordinate of the ship's leftmost pixel.
 */
void make_ship(uint8_t ship_x);

/**
 * @brief Moves the ship one position to the left, ensuring it stays within bounds.
 */
void move_ship_left();

/**
 * @brief Moves the ship one position to the right, ensuring it stays within bounds.
 */
void move_ship_right();

/**
 * @brief Draws a bullet at its current position and clears its previous position.
 * @param x Bullet's current x-coordinate.
 * @param y Bullet's current y-coordinate.
 */
void make_bullet(uint8_t x, uint8_t y);

/**
 * @brief Displays the player's score as white pixels on the bottom row.
 * @param score The player's current score.
 */
void display_score(uint8_t score);

/**
 * @brief Displays a victory smiley face when the player wins.
 */
void display_victory();

/**
 * @brief Resets the entire LED matrix to a blank state.
 */
void reset_scoreboard();

#endif // SRC_GAMELOGIC_H_

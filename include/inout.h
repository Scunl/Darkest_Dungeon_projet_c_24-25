#ifndef INOUT_H
#define INOUT_H

#include "data.h"

/**
 * Displays the list of characters with their stats
 * @param characters List of characters to display
 */
void display_characters(const Character* characters);

/**
 * Displays available character classes
 * @param classes Array of available classes
 * @param size Number of classes to display
 */
void display_classes(const Class classes[NBCLASS], int size);

/**
 * Displays character's accessories
 * @param inventory Array of accessories to display
 */
void display_accessories(const Accessory* inventory);

/**
 * Displays the main menu with current round number
 * @param round_number Current round number
 */
void display_menu(int round_number);

/**
 * Displays character's status (HP, Stress, etc.)
 * @param character Character whose status to display
 */
void display_character_status(const Character* character);

#endif

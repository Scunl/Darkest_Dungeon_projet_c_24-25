#ifndef ENGINE_H
#define ENGINE_H

#include "data.h"

Enemy *createEnemy(const char name[MAX_NAME_LENGTH], int level, int attack,
                   int defense, int hp, int stress);
/* Function prototypes */
/**
 * Selects a character from source list and moves it to destination list
 * @param source Pointer to source character list
 * @param size Number of characters in source list
 * @param destination Pointer to destination character list
 * @return 1 if successful, 0 if failed
 */
int select_character(Character **source, int size, Character **destination);

/**
 * Counts the number of characters in a list
 * @param list Head of character list
 * @return Number of characters in the list
 */
int count_characters(Character *list);

/**
 * Applies healing to a character
 * @param character Target character
 * @param healing Amount of healing to apply
 * @return nothing
 */
void apply_healing(Character *character, int healing);
void fighters_attack_enemy(Character *fighter, Enemy **opponents,
                           Enemy *target);
int fight_character(Character *fighters, Enemy **ennemis, Enemy *target,
                    int nbennemis);

#endif /* ENGINE_H */

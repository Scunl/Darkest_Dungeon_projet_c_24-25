#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constants */
#define NBCLASS 6
#define NBPERSOSMAX 10
#define MAX_NAME_LENGTH 30

/* Type definitions */
typedef struct {
    char name[MAX_NAME_LENGTH];
    int attack;
    int defense;
    int max_hp;
    int restoration;
    int stress_resistance;
} Class;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int attack_bonus;
    int defense_bonus;
    int hp_bonus;
    int restoration_bonus;
    int stress_reduction;
    int accessory_count;
} Accessory;

typedef struct Character {
    char name[MAX_NAME_LENGTH];
    int current_hp;
    int stress;
    int combat_count;
    Class character_class;
    Accessory accessory1;
    Accessory accessory2;
    struct Character *next;
} Character;

typedef struct Enemy {
    char name[MAX_NAME_LENGTH];
    int level;
    int attack;
    int defense;
    int hp;
    int stress_attack;
    struct Enemy *next;
} Enemy;

/* Function prototypes */
/**
 * Allocates and initializes a new character with given class and name
 * @param classes Array of available classes
 * @param name Character name
 * @return Pointer to newly allocated character or NULL if allocation fails
 */
Character *create_character(Class classes[NBCLASS], const char *name);

/**
 * Removes a character from a linked list
 * @param character_list Pointer to the list head pointer
 * @param target Character to remove
 * @return 1 if successful, 0 if character not found
 */
int remove_character(Character **character_list, Character *target);

/**
 * Gets character at specified index in linked list
 * @param list Head of character list
 * @param index Index of character to retrieve (0-based)
 * @return Pointer to character or NULL if index invalid
 */
Character *get_character_at_index(Character *champion, int index);

/**
 * Extracts the first character from the list
 * @param list Pointer to the list head pointer
 * @return Pointer to extracted character or NULL if list empty
 */
Character *extract_head(Character **list);

/**
 * Creates a new accessory with specified stats
 * @param name Accessory name
 * @param attack_bonus Attack bonus value
 * @param defense_bonus Defense bonus value
 * @param hp_bonus HP bonus value
 * @param restoration_bonus Restoration bonus value
 * @param stress_reduction Stress reduction value
 * @return Initialized Accessory structure
 */
Accessory create_accessory(const char *name, int attack_bonus,
                           int defense_bonus, int hp_bonus,
                           int restoration_bonus, int stress_reduction);

#endif /* DATA_H */
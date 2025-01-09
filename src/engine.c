#include "engine.h"
#include "data.h"
#include "inout.h"
#include <time.h>

Enemy* createEnemy(const char name[MAX_NAME_LENGTH], int level, int attack, int defense, int hp, int stress) {
    Enemy *champion = (Enemy *)malloc(sizeof(Enemy));
    if (!champion)
        return champion;
    strncpy(champion->name, name, MAX_NAME_LENGTH - 1);
    champion->name[MAX_NAME_LENGTH - 1] = '\0';

    champion->level = level;
    champion->attack = attack;
    champion->defense = defense;
    champion->hp = hp;
    champion->stress_attack = stress;
    champion->next = NULL;

    return champion;
}

int select_character(Character **source, int size, Character **destination) {
    int choice;
    printf("Please select a character by ID (1-%d): ", size);

    // Input validation
    do {
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n')
                ; // Clear input buffer
            printf("Invalid input. Please enter a number between 1 and %d: ",
                   size);
            continue;
        }
        if (choice <= 0 || choice > size) {
            printf("Invalid choice. Please enter a number between 1 and %d: ",
                   size);
        }
    } while (choice <= 0 || choice > size);

    Character *selected = get_character_at_index(*source, choice - 1);
    if (!selected) {
        return 0;
    }

    // Create new character node
    Character *new_char = (Character *)malloc(sizeof(Character));
    if (!new_char) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 0;
    }
    *new_char = *selected;
    new_char->next = NULL;

    // Add to destination list
    if (!*destination) {
        *destination = new_char;
    } else {
        Character *current = *destination;
        while (current->next) {
            current = current->next;
        }
        current->next = new_char;
    }

    // Remove from source list
    return remove_character(source, selected);
}

int count_characters(Character *list) {
    int count = 0;
    for (Character *current = list; current; current = current->next) {
        count++;
    }
    return count;
}

void apply_healing(Character *character, int healing) {
    if (!character || healing < 0) {
        return;
    }

    if ((character->current_hp + healing) > (character->character_class.max_hp))
        character->current_hp = character->character_class.max_hp;
    else
        character->current_hp += healing;
}

int fight_character(Character *fighters, Enemy ennemis[], int nbennemis) {
    if (!fighters || nbennemis == 0)
        return 0;
    int choice;

    Character champ_selected;

    display_characters(fighters);
    scanf("%d", &choice);
    champ_selected = *get_character_at_index(fighters, choice);
    display_fight_menu(champ_selected);
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        break;

    default:
        break;
    };
    return 1;
}

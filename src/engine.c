#include "engine.h"
#include "data.h"
#include "inout.h"
#include <time.h>

Enemy *createEnemy(const char name[MAX_NAME_LENGTH], int level, int attack,
                   int defense, int hp, int stress) {
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

    Character *selected = get_character_at_index(*source, choice);
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

int delete_enemy(Enemy **opponents, Enemy *target) {
    if (!opponents || !target)
        return 0;

    Enemy *current = *opponents;
    Enemy *prev = NULL;

    for (; current; current = current->next) {
        if (current == target) {
            if (prev) {
                prev->next = current->next;
            } else {
                *opponents = current->next;
            }
            free(current);
            return 1;
        }
        prev = current;
    }
    return 0;
}

void fighters_attack_enemy(Character *fighter, Enemy **opponents,
                           Enemy *target) {
    int result = target->hp - fighter->character_class.attack;

    if (result > 0) {
        target->hp = result;
        printf("You have applied %d HP damage.\n  HP of %s = %d\n",
               fighter->character_class.attack, target->name, target->hp);
    } else {
        delete_enemy(opponents, target);
        printf("You have killed the enemy !\n");
    }
}

int fight_character(Character *fighters, Enemy **ennemis, Enemy *target,
                    int nbennemis) {
    if (!fighters || nbennemis == 0)
        return 0;

    int choice;

    display_characters(fighters);
    for (int i = 1; i < count_characters(fighters) + 1; i++) {
        Character *current = get_character_at_index(fighters, i);
        printf("It's %s turn, which attack do you want to use ?\n",
               current->name);
        display_fight_menu(*fighters);
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            fighters_attack_enemy(current, ennemis, target);
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
        };
    }

    return 1;
}

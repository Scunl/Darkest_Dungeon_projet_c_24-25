#include "data.h"

Accessory create_accessory(const char *name, int attack_bonus,
                           int defense_bonus, int hp_bonus,
                           int restoration_bonus, int stress_reduction) {
    Accessory accessory;
    strncpy(accessory.name, name, MAX_NAME_LENGTH - 1);
    accessory.name[MAX_NAME_LENGTH - 1] = '\0';
    accessory.attack_bonus = attack_bonus;
    accessory.defense_bonus = defense_bonus;
    accessory.hp_bonus = hp_bonus;
    accessory.restoration_bonus = restoration_bonus;
    accessory.stress_reduction = stress_reduction;
    accessory.price = 0;
    return accessory;
}

Character *create_character(Class classes[NBCLASS], const char *name) {
    Character *character = (Character *)malloc(sizeof(Character));
    if (!character) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }

    int class_index = rand() % NBCLASS;
    Class chosen_class = classes[class_index];

    strncpy(character->name, name, MAX_NAME_LENGTH - 1);
    character->name[MAX_NAME_LENGTH - 1] = '\0';
    character->current_hp = chosen_class.max_hp;
    character->stress = 0;
    character->combat_count = 0;
    character->character_class = chosen_class;
    character->next = NULL;
    character->defending = 0;

    // Initialize with empty accessories

    character->accessory1 = create_accessory("", 0, 0, 0, 0, 0);
    character->accessory2 = create_accessory("", 0, 0, 0, 0, 0);

    return character;
}

int remove_character(Character **character_list, Character *target) {
    if (!character_list || !*character_list || !target) {
        return 0;
    }

    Character *current = *character_list;
    Character *prev = NULL;

    while (current) {
        if (current == target) {
            if (prev) {
                prev->next = current->next;
            } else {
                *character_list = current->next;
            }
            free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }

    return 0;
}

Character *get_character_at_index(Character *champion, int index) {
    if (index < 0) {
        return NULL;
    }

    Character *current = champion;
    for (int i = 0; i < (index - 1) && current; i++) {
        current = current->next;
    }
    return current;
}

Character *extract_head(Character **list) {
    if (!list || !*list) {
        return NULL;
    }

    Character *head = *list;
    *list = (*list)->next;
    head->next = NULL;
    return head;
}

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
            current = NULL;
            free(current);
            return 1;
        }
        prev = current;
    }
    return 0;
}
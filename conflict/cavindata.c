#include "data.h"

Accessory create_accessory(const char* name, int attack_bonus, int defense_bonus,
                          int hp_bonus, int restoration_bonus, int stress_reduction) {
    Accessory accessory;
    strncpy(accessory.name, name, MAX_NAME_LENGTH - 1);
    accessory.name[MAX_NAME_LENGTH - 1] = '\0';
    accessory.attack_bonus = attack_bonus;
    accessory.defense_bonus = defense_bonus;
    accessory.hp_bonus = hp_bonus;
    accessory.restoration_bonus = restoration_bonus;
    accessory.stress_reduction = stress_reduction;
    accessory.accessory_count = 0;
    return accessory;
}

Character* create_character(Class classes[NBCLASS], const char* name) {
    Character* new_character = malloc(sizeof(Character));
    if (!new_character) {
        return NULL;
    }
    strcpy(new_character->name, name);
    new_character->current_hp = 15; // Exemple d'initialisation par défaut
    new_character->stress = 0;
    new_character->combat_count = 0;
    new_character->character_class = classes[0]; // Assignez une classe par défaut ou appropriée
    new_character->accessory1 = (Accessory){"", 0, 0, 0, 0, 0};
    new_character->accessory2 = (Accessory){"", 0, 0, 0, 0, 0};
    new_character->defending = 0; // Initialisation du mode défense
    new_character->next = NULL;
    return new_character;
}

Character* create_character1(Class classes[NBCLASS], const char* name) {
    Character* character = (Character*)malloc(sizeof(Character));
    if (!character) {
        fprintf(stderr, "Memory allocation failed for character.\n");
        return NULL;
    }

    int class_index = rand() % NBCLASS;
    Class chosen_class = classes[class_index];

    strncpy(character->name, name, MAX_NAME_LENGTH - 1);
    character->name[MAX_NAME_LENGTH - 1] = '\0';
    character->current_hp = chosen_class.max_hp;
    character->stress = 0;
    character->defending = 0; // NEW
    character->combat_count = 0;
    character->character_class = chosen_class;
    character->next = NULL;

    // Initialize with empty accessories
    
    character->accessory1 = create_accessory("", 0, 0, 0, 0, 0);
    character->accessory2 = create_accessory("", 0, 0, 0, 0, 0);

    return character;
}

int remove_character(Character** character_list, Character* target) {
    if (!character_list || !*character_list || !target) {
        return 0;
    }

    Character* current = *character_list;
    Character* prev = NULL;

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

Character* get_character_at_index(Character* list, int index) {
    if (index < 0) {
        return NULL;
    }

    Character* current = list;
    for (int i = 0; i < index && current; i++) {
        current = current->next;
    }
    return current;
}

Character* extract_head(Character** list) {
    if (!list || !*list) {
        return NULL;
    }
    
    Character* head = *list;
    *list = (*list)->next;
    head->next = NULL;
    return head;
}
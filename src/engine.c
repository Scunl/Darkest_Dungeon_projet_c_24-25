#include "engine.h"
#include "data.h"

int select_character(Character** source, int size, Character** destination) {
    int choice;
    printf("Please select a character by ID (1-%d): ", size);
    
    // Input validation
    do {
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear input buffer
            printf("Invalid input. Please enter a number between 1 and %d: ", size);
            continue;
        }
        if (choice <= 0 || choice > size) {
            printf("Invalid choice. Please enter a number between 1 and %d: ", size);
        }
    } while (choice <= 0 || choice > size);

    Character* selected = get_character_at_index(*source, choice - 1);
    if (!selected) {
        return 0;
    }

    // Create new character node
    Character* new_char = (Character*)malloc(sizeof(Character));
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
        Character* current = *destination;
        while (current->next) {
            current = current->next;
        }
        current->next = new_char;
    }

    // Remove from source list
    return remove_character(source, selected);
}

int count_characters(Character* list) {
    int count = 0;
    for (Character* current = list; current; current = current->next) {
        count++;
    }
    return count;
}

int apply_healing(Character* character, int healing) {
    if (!character || healing < 0) {
        return 0;
    }

    int max_hp = character->character_class.max_hp;
    int hp_before = character->current_hp;
    
    character->current_hp += healing;
    if (character->current_hp > max_hp) {
        character->current_hp = max_hp;
    }

    return character->current_hp - hp_before; // Return actual amount healed
}
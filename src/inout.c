#include "inout.h"

void display_characters(const Character *characters) {
    printf("\n%-4s %-25s %-20s %-10s %-10s %-10s %-10s %-10s %-15s %-10s\n", "ID",
           "Character Name", "Class", "Attack", "Defense", "Max HP",
           "Current HP", "Stress", "Restoration", "Defending");
    printf("-------------------------------------------------------------------"
           "--------------------------"
           "----------------------------------------\n");

    int id = 1;
    for (const Character *current = characters; current;
         current = current->next, id++) {
        printf("%-4d %-25s %-20s %-10d %-10d %-10d %-10d %-10d %-15d %-10s\n", id,
               current->name, current->character_class.name,
               current->character_class.attack,
               current->character_class.defense,
               current->character_class.max_hp, current->current_hp,
               current->stress, current->character_class.restoration, (current->defending ? "Yes" : "No"));
    }
    printf("\n");
}

void display_enemies(Enemy *enemies) {
    printf("Enemy List:\n");
    printf("------------------------------------------------------------\n");
    printf("| %-20s | Level | Attack | Defense | HP   | Stress Attack |\n",
           "Name");
    printf("------------------------------------------------------------\n");

    // Traverse the linked list of enemies
    while (enemies != NULL) {
        printf("| %-20s | %5d | %6d | %7d | %4d | %14d |\n", enemies->name,
               enemies->level, enemies->attack, enemies->defense, enemies->hp,
               enemies->stress_attack);
        enemies = enemies->next; // Move to the next enemy in the list
    }

    printf("------------------------------------------------------------\n");
}

void display_classes(const Class classes[NBCLASS], int size) {
    printf("\n%-4s %-25s %-10s %-10s %-10s %-15s %-10s\n", "ID", "Class Name",
           "Attack", "Defense", "Max HP", "Restoration", "Stress Res");
    printf("-------------------------------------------------------------------"
           "-------------"
           "--------------------\n");

    for (int i = 0; i < size; i++) {
        printf("%-4d %-25s %-10d %-10d %-10d %-15d %-10d\n", i + 1,
               classes[i].name, classes[i].attack, classes[i].defense,
               classes[i].max_hp, classes[i].restoration,
               classes[i].stress_resistance);
    }
    printf("\n");
}

void display_accessories(const Accessory *inventory) {
    if (!inventory) {
        printf("No accessories available.\n");
        return;
    }

    printf("\n%-25s %-10s %-10s %-10s %-15s %-10s\n", "Name", "Attack+",
           "Defense+", "HP+", "Restore+", "Stress-");
    printf("-------------------------------------------------------------------"
           "-------------"
           "--------------------\n");

    for (int i = 0; i < inventory->price; i++) {
        printf("%-25s %-10d %-10d %-10d %-15d %-10d\n", inventory[i].name,
               inventory[i].attack_bonus, inventory[i].defense_bonus,
               inventory[i].hp_bonus, inventory[i].restoration_bonus,
               inventory[i].stress_reduction);
    }
    printf("\n");
}

void display_menu(int round_number) {
    printf("\n======================= ROUND %d =======================\n",
           round_number);
    printf("1. Select a character\n");
    printf("2. View deck\n");
    printf("3. Check accessories\n");
    printf("4. Send characters to sanitarium\n");
    printf("5. Send characters from sanitarium to deck\n");
    printf("6. Send characters to the arena (Preparing fight...) !\n");
    printf("7. Ready to fight\n");
    printf("8. Remove characters from arena\n");
    printf("9. Next round\n");
    printf("10. Show every enemies\n");
    printf("11. Send characters to the Taverne\n");
    printf("12. Move from Taverne to your deck\n");
    printf("====================================================\n");
    printf("Enter your choice (1-12): ");
}


void display_character_status(const Character *character) {
    if (!character) {
        printf("Error: No character to display.\n");
        return;
    }

    printf("\n=== %s's Status ===\n", character->name);
    printf("Class: %s\n", character->character_class.name);
    printf("HP: %d/%d\n", character->current_hp,
           character->character_class.max_hp);
    printf("Stress: %d/100\n", character->stress);
    printf("Combat Count: %d\n", character->combat_count);

    if (strlen(character->accessory1.name) > 0) {
        printf("Accessory 1: %s\n", character->accessory1.name);
    }
    if (strlen(character->accessory2.name) > 0) {
        printf("Accessory 2: %s\n", character->accessory2.name);
    }
    printf("=====================\n\n");
}

void display_fight_menu(Character champion) {
    printf("1. Attack the ennemi with %d dammage point\n",
           champion.character_class.attack);
    printf("2. Defend your champion and reduce %d dammage from ennemies "
           "attack\n",
           champion.character_class.defense);
    printf("3. Restore your champion health with %dHP\n",
           champion.character_class.restoration);
}

// void display_accessories(const Accessory accessories[], int size) {
//     printf("+------------------------+----------+----------+----------+----------+----------+\n");
//     printf("| Nom                   | attbonus | defbonus | HPbonus  | restbonus| strred   |\n");
//     printf("+------------------------+----------+----------+----------+----------+----------+\n");

//     for (int i = 0; i < size; i++) {
//         printf("| %-22s | %+8d | %+8d | %+8d | %+8d | %8d |\n",
//                accessories[i].name,
//                accessories[i].attack_bonus,
//                accessories[i].defense_bonus,
//                accessories[i].hp_bonus,
//                accessories[i].restoration_bonus,
//                accessories[i].stress_reduction);
//     }

//     printf("+------------------------+----------+----------+----------+----------+----------+\n");
// }

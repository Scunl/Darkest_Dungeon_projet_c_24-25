#include "inout.h"

// ===============   MOIII


#include "data.h"
#include "engine.h"


// Fonction pour afficher l'état d'un personnage
void display_character_status(const Character *character) {
    printf("%s (Classe : %s) | HP : %d/%d | Stress : %d | Accessoires : [%s, %s]\n",
           character->name, 
           character->character_class.name, 
           character->current_hp, 
           character->character_class.max_hp, 
           character->stress,
           character->accessory1.name, 
           character->accessory2.name);
}



// Fonction pour afficher l'état de l'ennemi
void display_enemy_status(Enemy *enemy) {
    printf("Ennemi : %s (Niveau : %d) | HP : %d | Attaque : %d | Défense : %d | Stress Attack : %d\n",
           enemy->name, 
           enemy->level, 
           enemy->hp, 
           enemy->attack, 
           enemy->defense, 
           enemy->stress_attack);
}

// Fonction pour demander l'action du joueur
char get_player_action(Character *character) {
    char action;
    printf("Action pour %s : (A)ttaquer, (D)éfendre, (R)estaurer ? ", character->name);
    scanf(" %c", &action); // Le " " avant %c pour ignorer les caractères précédents
    return action;
}

// Fonction pour gérer un tour de combat
void handle_player_turn(Character *character, Enemy *enemy) {
    char action = get_player_action(character);

    switch (action) {
        case 'A': // Attaquer
        case 'a':
            player_attack(character, enemy);
            break;
        case 'D': // Défendre
        case 'd':
            character->defending = 1; // Met le personnage en mode défense
            printf("%s se met en position de défense.\n", character->name);
            break;
        case 'R': // Restaurer
        case 'r': {
            int hp_restored = character->character_class.restoration + 
                              character->accessory1.restoration_bonus + 
                              character->accessory2.restoration_bonus;
            character->current_hp += hp_restored;
            if (character->current_hp > character->character_class.max_hp) {
                character->current_hp = character->character_class.max_hp;
            }
            printf("%s se soigne pour %d HP. HP actuel : %d/%d\n",
                   character->name, hp_restored, character->current_hp, character->character_class.max_hp);
            break;
        }
        default:
            printf("Action invalide. %s passe son tour.\n", character->name);
    }
}

void handle_enemy_turn(Enemy *enemy, Character **characters, int num_characters) {
    if (enemy == NULL) {
        printf("Erreur : L'ennemi n'est pas initialisé.\n");
        return;
    }
    if (characters == NULL || num_characters <= 0) {
        printf("Erreur : Aucune cible disponible pour l'ennemi.\n");
        return;
    }

    // Sélectionner une cible aléatoire parmi les personnages
    int target_index = rand() % num_characters;
    Character *target = characters[target_index];

    if (target == NULL) {
        printf("Erreur : La cible sélectionnée est invalide.\n");
        return;
    }

    // Attaque de l'ennemi
    printf("L'ennemi attaque %s (HP : %d, Stress : %d)\n", target->name, target->current_hp, target->stress);
    enemy_attack(enemy, target);
}

// ===============   MOIII FIN


void display_characters(const Character* characters) {
    printf("\n%-4s %-25s %-20s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "ID", "Character Name", "Class", "Attack", "Defense", "Max HP", "Current HP",
           "Stress", "Restoration");
    printf("--------------------------------------------------------------------------------"
           "----------------------------------------\n");

    int id = 1;
    for (const Character* current = characters; current; current = current->next, id++) {
        printf("%-4d %-25s %-20s %-10d %-10d %-10d %-10d %-10d %-10d\n",
               id,
               current->name,
               current->character_class.name,
               current->character_class.attack,
               current->character_class.defense,
               current->character_class.max_hp,
               current->current_hp,
               current->stress,
               current->character_class.restoration);
    }
    printf("\n");
}

void display_classes(const Class classes[NBCLASS], int size) {
    printf("\n%-4s %-25s %-10s %-10s %-10s %-15s %-10s\n",
           "ID", "Class Name", "Attack", "Defense", "Max HP", "Restoration", "Stress Res");
    printf("--------------------------------------------------------------------------------"
           "--------------------\n");

    for (int i = 0; i < size; i++) {
        printf("%-4d %-25s %-10d %-10d %-10d %-15d %-10d\n",
               i + 1,
               classes[i].name,
               classes[i].attack,
               classes[i].defense,
               classes[i].max_hp,
               classes[i].restoration,
               classes[i].stress_resistance);
    }
    printf("\n");
}

void display_accessories(const Accessory* inventory) {
    if (!inventory) {
        printf("No accessories available.\n");
        return;
    }

    printf("\n%-25s %-10s %-10s %-10s %-15s %-10s\n",
           "Name", "Attack+", "Defense+", "HP+", "Restore+", "Stress-");
    printf("--------------------------------------------------------------------------------"
           "--------------------\n");

    for (int i = 0; i < inventory->accessory_count; i++) {
        printf("%-25s %-10d %-10d %-10d %-15d %-10d\n",
               inventory[i].name,
               inventory[i].attack_bonus,
               inventory[i].defense_bonus,
               inventory[i].hp_bonus,
               inventory[i].restoration_bonus,
               inventory[i].stress_reduction);
    }
    printf("\n");
}

void display_menu(int round_number) {
    printf("\n==============================\n");
    printf("Round %d\n", round_number);
    printf("1. Sélectionner un personnage pour le combat\n");
    printf("2. Voir votre deck et le sanitarium\n");
    printf("3. Voir les accessoires disponibles\n");
    printf("4. Envoyer un personnage au sanitarium\n");
    printf("5. Passer au round suivant\n");
    printf("6. Commencer un combat\n");
    printf("==============================\n");
    printf("Choisissez une option : ");
}

/*

void display_menu(int round_number) {
    printf("\n======================= ROUND %d =======================\n", round_number);
    printf("1. Select a character\n");
    printf("2. View deck\n");
    printf("3. Check accessories\n");
    printf("4. Send characters to sanitarium\n");
    printf("5. Next round\n");
    printf("====================================================\n");
    printf("Enter your choice (1-5): ");
}

void display_character_status(const Character* character) {
    if (!character) {
        printf("Error: No character to display.\n");
        return;
    }

    printf("\n=== %s's Status ===\n", character->name);
    printf("Class: %s\n", character->character_class.name);
    printf("HP: %d/%d\n", character->current_hp, character->character_class.max_hp);
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

*/


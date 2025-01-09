#include "engine.h"
#include "data.h"


// ===============   MOIII

#include "inout.h" // Inclure les fonctions pour afficher et gérer les données

// Fonction pour calculer les dommages infligés par un personnage
int calculate_damage(int att_total, int defense) {
    float roll = ((rand() % 41) + 80) / 100.0; // Nombre aléatoire entre 0.8 et 1.2
    int damage = (att_total - defense) * roll;
    if (damage <= 0) {
        damage = 1; // Minimum 1 point de dommage
    }
    return damage;
}


void player_attack(Character *attacker, Enemy *enemy) {
    if (attacker == NULL || enemy == NULL) {
        printf("Erreur : Attaquant ou ennemi non initialisé.\n");
        return;
    }

    int att_total = attacker->character_class.attack;
    int damage = calculate_damage(att_total, enemy->defense);
    if (enemy->hp > 0) {
        enemy->hp -= damage;
        if (enemy->hp < 0) enemy->hp = 0; // Éviter les HP négatifs
    }
    printf("%s attaque l'ennemi pour %d points de dégâts. HP restant de l'ennemi : %d\n",
           attacker->name, damage, enemy->hp);
}

// Fonction pour une attaque de l'ennemi
void enemy_attack(Enemy *enemy, Character *target) {
    if (enemy == NULL || target == NULL) {
        printf("Erreur : Ennemi ou cible invalide.\n");
        return;
    }

    // Attaque physique ou de stress
    int attack_type = rand() % 2; // 0 = attaque physique, 1 = stress
    if (attack_type == 0) { // Attaque physique
        int damage = calculate_damage(enemy->attack, target->character_class.defense);
        target->current_hp -= damage;
        if (target->current_hp < 0) target->current_hp = 0; // Éviter les HP négatifs
        printf("L'ennemi attaque %s pour %d points de dégâts. HP restant de %s : %d\n", 
               target->name, damage, target->name, target->current_hp);
    } else { // Attaque de stress
        int stress_increase = enemy->stress_attack;
        target->stress += stress_increase;
        printf("L'ennemi cause %d points de stress à %s. Stress actuel de %s : %d\n", 
               stress_increase, target->name, target->name, target->stress);
    }
}


// Fonction pour ajuster les statistiques des ennemis en fonction du niveau
void adjust_enemy_stats(Enemy *enemy, int level) {
    enemy->attack += level * 2;
    enemy->defense += level * 1;
    enemy->hp += level * 5;
    enemy->stress_attack += level; // Augmentation progressive des attaques de stress
    printf("Stats de l'ennemi ajustées pour le niveau %d : Attaque : %d, Défense : %d, HP : %d, Stress Attack : %d\n", 
           level, enemy->attack, enemy->defense, enemy->hp, enemy->stress_attack);
}


void remove_dead_characters(Character **list) {
    Character *current = *list;
    Character *prev = NULL;

    while (current) {
        if (current->current_hp <= 0) { // Si le personnage est mort
            printf("%s est mort(e) et sera retiré(e) du combat.\n", current->name);
            if (prev) {
                prev->next = current->next;
            } else {
                *list = current->next;
            }
            free(current);
            current = (prev) ? prev->next : *list;
        } else {
            prev = current;
            current = current->next;
        }
    }
}



// Fonction pour gérer les récompenses après un combat gagné
void give_rewards(int round, Character **characters, Accessory **accessories) {
    // Ajouter un nouvel accessoire
    Accessory new_accessory = create_accessory("Accessoire Mystique", 5, 2, 10, 3, 5); // Exemple d'accessoire
    Accessory *new_accessory_ptr = (Accessory *)malloc(sizeof(Accessory));
    if (new_accessory_ptr == NULL) {
        printf("Erreur d'allocation mémoire pour le nouvel accessoire.\n");
        return;
    }
    *new_accessory_ptr = new_accessory;
    new_accessory_ptr->accessory_count = 0; // Réinitialiser le compteur

    add_accessory(accessories, *new_accessory_ptr);
    printf("Vous avez obtenu un nouvel accessoire : %s\n", new_accessory.name);

    // Ajouter un nouveau personnage tous les 2 rounds (2, 4, 6, 8)
    if (round % 2 == 0 && round <= 8) {
        Class classes[NBCLASS]; // Vous devez définir ou charger vos classes
        // Exemple : Créer un personnage aléatoire (vous devez ajuster create_character)
        Character *new_character = create_character(classes, "Nouveau Héros");
        if (new_character != NULL) {
            add_character(characters, *new_character);
            printf("Un nouveau personnage rejoint votre équipe : %s (Classe : %s)\n", 
                   new_character->name, new_character->character_class.name);
        } else {
            printf("Erreur lors de la création du nouveau personnage.\n");
        }
    }

    printf("Récompenses distribuées avec succès !\n");
}


// ===============   MOIII FIN


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
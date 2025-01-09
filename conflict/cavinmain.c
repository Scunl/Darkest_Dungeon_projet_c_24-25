#include "data.h"
#include "engine.h"
#include "inout.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int round_number = 0;
    int game_running = 1;
    int selected_characters = 0;
    int total_characters = 0;
    int has_selection = 0;
    int choice = 0;
    srand(time(NULL));

    // Initialize classes
    Class classes[NBCLASS] = {
        {"Fury", 13, 0, 20, 5, 7},          {"Vestal", 3, 0, 20, 15, 3},
        {"Bounty Hunter", 7, 3, 25, 10, 8}, {"Houndmaster", 10, 6, 17, 8, 6},
        {"Faceless", 20, 0, 15, 4, 10},     {"White Walker", 8, 0, 30, 12, 7}};

    // Initialize character names
    const char *character_names[NBPERSOSMAX] = {
        "Arthur", "Merlin",   "Luna",   "Gwen",   "Jon Snow",
        "Arya",   "Daenerys", "Tyrion", "Cersei", "Jaime"};

    // Initialize pointers for character lists
    Character *available_characters = NULL;
    Character *selected_deck = NULL;
    Character *sanitarium = NULL;
    Accessory *inventory = NULL;

    // Add initial 2 characters
    available_characters =
        create_character(classes, character_names[total_characters]);
    total_characters++;
    selected_characters++;
    available_characters->next =
        create_character(classes + 1, character_names[total_characters]);
    total_characters++;
    selected_characters++;

    while (game_running) {
        // Add one new character every 2 rounds after the initial round
        if (round_number > 0 && round_number % 2 == 0 &&
            total_characters < NBPERSOSMAX) {
            Character *current = available_characters;

            // Add one new character
            if (!current) {
                available_characters = create_character(
                    classes, character_names[total_characters]);
            } else {
                while (current->next) {
                    current = current->next;
                }
                current->next =
                    create_character(classes + (total_characters % NBCLASS),
                                     character_names[total_characters]);
            }
            total_characters++;
            selected_characters++;
        }

        display_menu(round_number);
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n')
                ; // Clear input buffer
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
        case 1:
            if (!available_characters) {
                printf("\nNo characters available for selection! Wait for new "
                       "characters to appear.\n");
                break;
            }
            printf("\nSelect your character:\n");
            display_characters(available_characters);
            if (select_character(&available_characters, selected_characters,
                                 &selected_deck)) {
                round_number++;
                selected_characters--;
            }
            break;

        case 2:
            printf("\n     YOUR DECK    ");
            display_characters(selected_deck);
            printf("    SANITARIUM   ");
            display_characters(sanitarium);
            break;

        case 3:
            display_accessories(inventory);
            break;

        case 4: {
            int deck_size = count_characters(selected_deck);
            if (deck_size <= 1) {
                printf("\nCannot send your last character to sanitarium!\n");
            } else if (count_characters(sanitarium) < 2) {
                printf("\n==============================\n");
                printf("Select characters to send to sanitarium (Max 2 "
                       "characters)\n");
                display_characters(selected_deck);
                if (select_character(&selected_deck,
                                     total_characters - selected_characters,
                                     &sanitarium)) {
                    selected_characters--;
                    printf("Characters in sanitarium: %d/2\n",
                           count_characters(sanitarium));
                    display_characters(sanitarium);
                }
            } else {
                printf("Sanitarium is full (2/2 characters).\n");
            }
        } break;

        case 5:
            round_number++;
            printf("\nMoving to round %d...\n", round_number);
            break;

        case 6: { // Commencer un combat
            if (!selected_deck) {
                printf("Vous devez sélectionner au moins un personnage pour "
                       "commencer un combat !\n");
                break;
            }

            // Initialiser un ennemi pour ce round
            Enemy enemy = {
                "Ennemi",         round_number + 1,      3 + 2 * round_number,
                1 + round_number, 20 + 5 * round_number, 5 + round_number};
            printf("\nCombat contre :\n");
            display_enemy_status(&enemy);

            // Boucle de combat
            while (enemy.hp > 0 && count_characters(selected_deck) > 0) {
                printf("\n--- Tour du joueur ---\n");
                Character *current = selected_deck;
                while (current) {
                    display_character_status(current);
                    handle_player_turn(current, &enemy);

                    if (enemy.hp <= 0) {
                        printf("Vous avez vaincu l'ennemi !\n");
                        break;
                    }
                    current = current->next;
                }

                if (enemy.hp > 0) {
                    printf("\n--- Tour de l'ennemi ---\n");
                    handle_enemy_turn(&enemy, &selected_deck,
                                      count_characters(selected_deck));
                    remove_dead_characters(
                        &selected_deck); // Supprimez les personnages morts
                }
            }

            if (enemy.hp <= 0) {
                printf("Félicitations ! Vous avez remporté le combat du round "
                       "%d !\n",
                       round_number);
            } else {
                printf("Vous avez perdu le combat...\n");
            }

            break;
        }

        default:
            printf("Invalid choice. Please select 1-6.\n");
            break;
        }

        if (selected_deck) {
            has_selection = 1;
        }

        // Check game ending conditions
        if (has_selection && !selected_deck) {
            game_running = 0;
            printf("Game Over: No characters remaining.\n");
        }
        if (round_number >= 10) {
            game_running = 0;
            printf("Game Over: Maximum rounds (%d) reached.\n", round_number);
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "engine.h"
#include "inout.h"

int main(void) {
    int nbround = 0;
    int jeu = 1;
    int nbpersoselect = 0;
    int totalperso = 0;

    Classe classes[NBCLASS] = {
        {"Furie", 13, 0, 20, 5, 7},       {"Vestale", 3, 0, 20, 15, 3},
        {"Chasseur de primes", 7, 3, 3, 10, 8}, {"Maître chien", 10, 6, 17, 8, 6},
        {"Nécromancien", 4, 0, 12, 20, 4}, {"Paladin", 15, 5, 25, 6, 12},
        {"Faceless", 20, 0, 15, 4, 10},    {"White Walker", 8, 0, 30, 12, 7},
        {"Dragonier", 10, 5, 20, 9, 15},   {"Winterfell", 15, 10, 18, 7, 10}};

    Personnage personnages[NBPERSOSMAX] = {
        {"Arthur", 0, 0, 0, {"", 0, 0, 0, 0, 0}, "", ""},
        {"Merlin", 0, 0, 0, {"", 0, 0, 0, 0, 0}, "", ""},
        {"Luna", 0, 0, 0, {"", 0, 0, 0, 0, 0}, "", ""},
        {"Gwen", 0, 0, 0, {"", 0, 0, 0, 0, 0}, "", ""},
        {"Jon Snow", 0, 0, 0, {"", 0, 0, 0, 0, 0}, "", ""},
        {"Arya", 0, 0, 0, {"", 0, 0, 0, 0, 0}, "", ""},
        {"Daenerys", 0, 0, 0, {"", 0, 0, 0, 0, 0}, "", ""},
        {"Tyrion", 0, 0, 0, {"", 0, 0, 0, 0, 0}, "", ""},
        {"Cersei", 0, 0, 0, {"", 0, 0, 0, 0, 0}, "", ""},
        {"Jaime", 0, 0, 0, {"", 0, 0, 0, 0, 0}, "", ""}};

    Personnage *joueur = NULL;
    Personnage *dispo = NULL;

    while (jeu) {
        if (nbround % 2 == 0) {
            Personnage *current = joueur;

            for (int i = 0; i < 2 && totalperso < NBPERSOSMAX; i++, totalperso++, nbpersoselect++) {
                if (!current) {
                    joueur = allouepersonnage(classes, personnages[totalperso].name);
                    current = joueur;
                } else {
                    while (current->suivant) {
                        current = current->suivant;
                    }
                    current->suivant = allouepersonnage(classes, personnages[totalperso].name);
                }
            }
        }

        printf("Sélectionnez votre personnage\n");
        affiche_personnages(joueur);
        selection_personnage(&joueur, nbpersoselect, &dispo);
        nbpersoselect--;

        printf("\n===== DISPO =====\n");
        affiche_personnages(dispo);
        printf("===== DISPO =====\n\n");

        nbround++;
        if (nbround >= 10) {
            jeu = 0;
            printf("Fin du jeu après %d tours.\n", nbround);
        }
    }

    return 0;
}

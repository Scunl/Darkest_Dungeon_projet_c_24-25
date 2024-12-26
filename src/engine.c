#include "engine.h"

void selection_personnage(Personnage **joueur, int size, Personnage **dispo) {
    int choix;
    printf("Veuillez sélectionner votre personnage grâce à leurs ID : ");
    do {
        scanf("%d", &choix);
    } while (choix <= 0 || choix > size);

    Personnage *choisi = get_personnage(*joueur, choix - 1);
    printf("Vous avez choisi %s comme personnage à ajouter dans votre deck\n",
           choisi->name);

    Personnage *nouveau = (Personnage *)malloc(sizeof(Personnage));
    if (!nouveau) {
        printf("Erreur d'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }
    *nouveau = *choisi; // Copie complète
    nouveau->suivant = NULL;

    if (!*dispo) {
        *dispo = nouveau;
    } else {
        Personnage *current = *dispo;
        while (current->suivant) {
            current = current->suivant;
        }
        current->suivant = nouveau;
    }

    supprimercellule(joueur, choisi);
}

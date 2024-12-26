#include "data.h"

Personnage *allouepersonnage(Classe classes[NBCLASS], char nom[30]) {
    Personnage *perso = (Personnage *)malloc(sizeof(Personnage));
    if (!perso) {
        printf("Erreur d'allocation mémoire pour le personnage.\n");
        exit(EXIT_FAILURE);
    }
    int classeIndex = rand() % NBCLASS;
    Classe classeChoisie = classes[classeIndex];
    strncpy(perso->name, nom, sizeof(perso->name) - 1);
    perso->name[sizeof(perso->name) - 1] = '\0';

    perso->HP = classeChoisie.HPMax;
    perso->Stress = 0;
    perso->nbcomb = 0;
    perso->classperso = classeChoisie;
    perso->suivant = NULL;
    perso->accessoire1[0] = '\0';
    perso->accessoire2[0] = '\0';

    return perso;
}

int supprimercellule(Personnage **perso, Personnage *extraire) {
    if (!perso || !*perso || !extraire) {
        return 0;
    }

    for (Personnage *tmp = *perso, *prev = NULL; tmp; tmp = tmp->suivant) {
        if (tmp == extraire) {
            if (prev == NULL) {
                *perso = tmp->suivant;
            } else {
                prev->suivant = tmp->suivant;
            }
            free(tmp);
            return 1;
        }
        prev = tmp;
    }

    return 0;
}

Personnage *get_personnage(Personnage *src, int id) {
    for (int i = 0; i < id && src; i++) {
        src = src->suivant;
    }
    return src;
}

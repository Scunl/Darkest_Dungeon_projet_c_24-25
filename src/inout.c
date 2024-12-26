#include "inout.h"

void affiche_personnages(Personnage *personnage) {
    printf("%-25s %-20s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "Nom du Champion", "Classe", "Attaque", "Défense", "HP Max", "HP",
           "Str", "Restoration");
    printf("-------------------------------------------------------------------"
           "-----------------------------------------\n");
    for (int i = 0; personnage; personnage = personnage->suivant, i++) {
        printf("%d | %-25s %-20s %-10d %-10d %-10d %-10d %-10d %-10d\n", i + 1,
               personnage->name, personnage->classperso.name,
               personnage->classperso.att, personnage->classperso.def,
               personnage->classperso.HPMax, personnage->HP, personnage->Stress,
               personnage->classperso.rest);
    }
}

void affiche_classe(Classe class[NBCLASS], int size) {
    printf("%-4s %-25s %-10s %-10s %-10s %-15s %-10s\n", "ID", "Nom de classe",
           "Attaque", "Defense", "HPMax", "Restoration", "Stress");

    printf("-------------------------------------------------------------------"
           "----------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%-2d | %-20s %-20d %-10d %-10d %-10d %-10d\n", i + 1,
               class[i].name, class[i].att, class[i].def, class[i].HPMax,
               class[i].rest, class[i].str);
    }
}

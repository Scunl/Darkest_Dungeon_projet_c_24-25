#include "character.h"
#include <stdio.h>

void showClass(Class type) {
    printf("==========\n");
    printf("Name: %s\n"
           "Attack: %d\n"
           "Defense: %d\n"
           "HPMax: %d\n"
           "Restauration: %d\n",
           type.name, type.att, type.def, type.HPMax, type.rest);
}

void showAllClasses(Class classes[], int size) {
    int i;
    printf("Classes disponibles :\n");
    printf("%-20s %-10s %-10s %-10s %-10s\n", "Nom", "Attaque", "Défense",
           "HPMax", "Ressources");
    printf("-------------------------------------------------------------\n");
    for (i = 0; i < size - 1; i++) {
        printf("%-20s %-10d %-10d %-10d %-10d\n", classes[i].name,
               classes[i].att, classes[i].def, classes[i].HPMax,
               classes[i].rest);
    }
    printf("%-21s %-10d %-10d %-10d %-10d\n", classes[i].name, classes[i].att,
           classes[i].def, classes[i].HPMax, classes[i].rest);
}

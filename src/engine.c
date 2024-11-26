#include "create.h"
#include <stdio.h>

void showClass(Class class) {
    printf("==========\n");
    printf("Name: %s\n"
           "Attack: %d\n"
           "Defense: %d\n"
           "HPMax: %d\n"
           "Restauration: %d\n",
           class.name, class.att, class.def, class.HPMax, class.rest);
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

void showAllCharacters(Character champions[], int size) {
    printf("Liste des Champions :\n");
    printf("%-20s %-20s %-10s %-10s %-10s %-10s\n", "Nom du Champion", "Classe",
           "Attaque", "Défense", "HP Max", "Ressources");
    printf("-------------------------------------------------------------------"
           "------------\n");
    for (int i = 0; i < size; i++) {
        printf("%-20s %-20s %-10d %-10d %-10d %-10d\n", champions[i].name,
               champions[i].class.name, champions[i].class.att,
               champions[i].class.def, champions[i].class.HPMax,
               champions[i].class.rest);
    }
    printf("\n");
}

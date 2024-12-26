#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NBCLASS 10
#define NBPERSOSMAX 10

typedef struct {
    char name[30];
    int att;
    int def;
    int HPMax;
    int rest;
    int str;
} Classe;

typedef struct Personnage {
    char name[30];
    int HP;
    int Stress;
    int nbcomb;
    Classe classperso;
    char accessoire1[25];
    char accessoire2[25];
    struct Personnage *suivant;
} Personnage;

typedef struct {
    char nom[30];
    int attbonus;
    int defbonus;
    int HPbonus;
    int restbonus;
    int strred;
} Accessoire;

typedef struct {
    char nom[30];
    int niveau;
    int attenn;
    int defenn;
    int HPenn;
    int attstrenn;
} Ennemi;

typedef struct NoeudSanitarium {
    Personnage personnage;
    struct NoeudSanitarium *suivant;
} NoeudSanitarium;

typedef struct NoeudTaverne {
    Personnage personnage;
    struct NoeudTaverne *suivant;
} NoeudTaverne;

typedef struct NoeudRoulotte {
    Accessoire accessoire;
    int prix;
    struct NoeudRoulotte *suivant;
} NoeudRoulotte;

Personnage *allouepersonnage(Classe classes[NBCLASS], char nom[30]);
int supprimercellule(Personnage **perso, Personnage *extraire);
Personnage *get_personnage(Personnage *src, int id);

#endif
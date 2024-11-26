#ifndef CREATE_H
#define CREATE_H

#define NBCLASS 4


typedef struct {
    char *name;
    int att;
    int def;
    int HPMax;
    int rest;
    int StressPoint;
} Class;

typedef struct {
    char name[15];
    int HP;
    Class class;
} Character;

typedef struct {
    int player;
    int nbchamp;
    Character champion[10];
} Players;

void createClass(char *name, Class *type);

#endif
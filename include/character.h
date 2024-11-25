#ifndef CHARACTER_H
#define CHARACTER_H

#define NBCLASS 4


typedef struct {
    char *name;
    int att;
    int def;
    int HPMax;
    int rest;
    int HP;
    int StressPoint;
} Class;

typedef struct {
    char *name;
    Class type;
} Character;

typedef struct {
    int nbplayer;
    Character champion[10];
} Players;

void createClass(char *name, Class *type);

#endif
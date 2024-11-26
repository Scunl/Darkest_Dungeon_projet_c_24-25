#include "create.h"
#include "character.h"
#include <stdio.h>
#include <string.h>

void createCharacter(char *name, Character *champion) {
    strncpy(champion->name, name, sizeof(champion->name) - 1);
    champion->name[sizeof(champion->name) - 1] = '\0';

    if (!(strcmp(name, "Boudicca"))) {
        createClass("Furie", &champion->class);
        champion->HP = champion->class.HPMax;
    }
    if (!(strcmp(name, "Junia"))) {
        createClass("Vestale", &champion->class);
        champion->HP = champion->class.HPMax;
    }
}

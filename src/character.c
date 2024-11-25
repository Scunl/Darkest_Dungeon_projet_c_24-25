#include "character.h"
#include <stdio.h>
#include <string.h>

void createClass(char *name, Class *type) {
    if (!(strcmp(name, "Furie"))) {
        type->name = "Furie";
        type->att = 13;
        type->def = 0;
        type->HPMax = 20;
        type->rest = 0;
    } else if (!(strcmp(name, "Vestale"))) {
        type->name = "Vestale";
        type->att = 3;
        type->def = 0;
        type->HPMax = 20;
        type->rest = 10;
    } else if (!(strcmp(name, "Chasseur de primes"))) {
        type->name = "Chasseur de primes";
        type->att = 7;
        type->def = 3;
        type->HPMax = 25;
        type->rest = 3;
    } else if (!(strcmp(name, "Maître chien"))) {
        type->name = "Maître chien";
        type->att = 10;
        type->def = 6;
        type->HPMax = 17;
        type->rest = 5;
    }

}

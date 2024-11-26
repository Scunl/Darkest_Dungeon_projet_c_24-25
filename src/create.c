#include "create.h"
#include <stdio.h>
#include <string.h>

void createClass(char *name, Class *class) {
    if (!(strcmp(name, "Furie"))) {
        class->name = "Furie";
        class->att = 13;
        class->def = 0;
        class->HPMax = 20;
        class->rest = 0;
    } else if (!(strcmp(name, "Vestale"))) {
        class->name = "Vestale";
        class->att = 3;
        class->def = 0;
        class->HPMax = 20;
        class->rest = 10;
    } else if (!(strcmp(name, "Chasseur de primes"))) {
        class->name = "Chasseur de primes";
        class->att = 7;
        class->def = 3;
        class->HPMax = 25;
        class->rest = 3;
    } else if (!(strcmp(name, "Maître chien"))) {
        class->name = "Maître chien";
        class->att = 10;
        class->def = 6;
        class->HPMax = 17;
        class->rest = 5;
    }

}

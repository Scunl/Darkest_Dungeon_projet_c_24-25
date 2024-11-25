#include "character.h"
#include "engine.h"
#include "game.h"


void startgame() {

    Class classes[MAX_CLASSES];

    createClass("Furie", &classes[0]);
    createClass("Vestale", &classes[1]);
    createClass("Chasseur de primes", &classes[2]);
    createClass("Maître chien", &classes[3]);

    showAllClasses(classes, NBCLASS);
}

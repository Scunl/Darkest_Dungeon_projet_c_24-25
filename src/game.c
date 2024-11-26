#include "create.h"
#include "engine.h"
#include "game.h"
#include "character.h"


void startgame() {

    Class classes[MAX_CLASSES];
    Character champion[10];
    createClass("Furie", &classes[0]);
    createClass("Vestale", &classes[1]);
    createClass("Chasseur de primes", &classes[2]);
    createClass("Maître chien", &classes[3]);

    showAllClasses(classes, NBCLASS);

    createCharacter("Boudicca", &champion[0]);
    createCharacter("Junia", &champion[1]);

    showAllCharacters(champion, 2);
}



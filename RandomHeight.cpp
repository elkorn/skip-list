#include <stdlib.h>
#include "RandomHeight.h"

RandomHeight::RandomHeight(int theMaxLevel, float theProbability) {
    // randomize();
    maxLevel = theMaxLevel;
    probability = theProbability;
}

int RandomHeight::newLevel() {
    int temporaryLevel = 1;

    while (rand() < probability && 
            temporaryLevel < maxLevel) {
            ++temporaryLevel;
    }

    return temporaryLevel;
}


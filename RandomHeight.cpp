#include <stdlib.h>
#include "RandomHeight.h"
#include "exceptions/WrongProbabilityException.cpp"

RandomHeight::RandomHeight(int theMaxLevel, float theProbability) {
    if(theProbability > 100 || theProbability < 0) throw WrongProbabilityException(theProbability);
    maxLevel = theMaxLevel;
    probability = theProbability * RAND_MAX;
}

int RandomHeight::newLevel() {
    int temporaryLevel = 1;

    while (rand() < probability &&
           temporaryLevel < maxLevel) {
        temporaryLevel = rand() % maxLevel + 1;
    }

    return temporaryLevel;
}


#include <cstdlib>
#include "ExponentialRandomHeight.h"
#include <random>
#include <cmath>

ExponentialRandomHeight::ExponentialRandomHeight(
        int theMaxLevel,
        double theLambda):
    lambda(theLambda),
    maxLevel(theMaxLevel) {
        distribution = new std::exponential_distribution<double>(theLambda);
}

double ExponentialRandomHeight::generate() {
    double result;
    while((result = (*distribution)(generator)) >= 1.0) {
        // We are interested only in values [0-1), so another generation is
        // required in case such an unfitting number is produced.
    }

    return result;
}

int ExponentialRandomHeight::newLevel() {
    double number = generate();
    return int(number*maxLevel) + 1;
}

ExponentialRandomHeight::~ExponentialRandomHeight() {
    delete distribution;
}



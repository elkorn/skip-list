#include <cstdlib>
#include "ExponentialRandomHeight.h"
#include <random>
#include <cmath>

ExponentialRandomHeight::ExponentialRandomHeight(int theMaxLevel, double theLambda):
    maxLevel(theMaxLevel),
    lambda(theLambda),
    distribution(std::exponential_distribution<double>(theLambda))
{ }

ExponentialRandomHeight::ExponentialRandomHeight(const ExponentialRandomHeight &other):
    maxLevel(other.maxLevel),
    lambda(other.lambda),
    generator(other.generator),
    distribution(other.distribution) { }

double ExponentialRandomHeight::generate()
{
    double result;
    while ((result = distribution(generator)) >= 1.0)
    {
        // We are interested only in values [0-1), so another generation is
        // required in case such an unfitting number is produced.
    }

    return result;
}

const int ExponentialRandomHeight::newLevel()
{
    double number = generate();
    return int(number * maxLevel) + 1;
}



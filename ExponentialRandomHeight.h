#include <random>

class ExponentialRandomHeight {
    public:
        ExponentialRandomHeight(int theMaxLevel, double lambda);
        ~ExponentialRandomHeight();
        int newLevel();

    private:
        double generate();

        int maxLevel;
        double lambda;
        std::default_random_engine generator;
        std::exponential_distribution<double> *distribution;
};

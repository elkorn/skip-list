class RandomHeight {
    public:
        RandomHeight(int theMaxLevel, float theProbability);
        ~RandomHeight() {}
        int newLevel();

    private:
        int maxLevel;
        float probability;
};

#include <iostream>
#include <ctime>
#include <fstream>
#include <stdexcept>
#include "../SkipList.cpp"


using namespace std;

int main()
{
    srand(time(0));
    const int nrolls = 20; // number of experiments
    // const double lambda = 3.5;
    SkipList<int> *sl = new SkipList<int>();
    ofstream of;
    of.open("results.csv");

    int *v = new int[nrolls];

    for (int i = 0; i < nrolls; ++i)
    {
        v[i] = i;
        sl->insert(v[i]);
    }

    sl->display();
    SkipList<int>::iterator begin = sl->begin(),
                            end = sl->end();


    delete sl;
    delete []v;
    return 0;
}

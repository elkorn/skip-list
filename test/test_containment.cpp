#include <iostream>
#include <ctime>
#include <fstream>
#include <stdexcept>
#include "../SkipList.cpp"
#include "../SkipListDisplayer.cpp"

using namespace std;

int main()
{
    srand(time(0));
    const int nrolls = 20; // number of experiments
    // const double lambda = 3.5;
    SkipList<int> sl = SkipList<int>();
    ofstream of;
    of.open("results.csv");

    int *v = new int[nrolls];

    for (int i = 0; i < nrolls; ++i)
    {
        v[i] = i;
        sl.insert(v[i]);
    }

    SkipListDisplayer::display(sl);
    SkipList<int>::iterator begin = sl.begin(),
                            end = sl.end();


    delete []v;
    return 0;
}

#include <iostream>
#include <ctime>
#include <fstream>
#include <stdexcept>
#include "../SkipList.cpp"


using namespace std;

int main()
{
    srand(time(0));
    const int nrolls = 1000; // number of experiments
    const int nstars = 100;  // maximum number of stars to distribute
    const int nintervals = 32; // number of intervals
    // const double lambda = 3.5;
    SkipList<int> *sl = new SkipList<int>();
    ofstream of;
    of.open("results.csv");

    int *v = new int[nrolls];

    for (int i = 0; i < nrolls; ++i)
    {
        v[i] = rand();
        sl->insert(v[i]);
    }

    cout << "Done inserting." << endl;

    SkipList<int>::iterator begin = sl->begin();

    int p[nintervals] = {};
    SkipListNode<int> *node = 0, *endNode = (sl->end()->prev.at(0)->next.at(0));
    for (int i = 0; i < nintervals; ++i)
    {
        // try
        // {
            cout << begin->next[i] << ", size: " << begin->next.size() << endl;
            node = begin->next.at(i);
            cout << "At level " << i << " (with height " << node->getHeight() << ")" << endl;
            while (node != 0 && node != endNode)
            {
                ++p[i];
                node = node->next.at(i);
            }
        // }
        // catch (const std::out_of_range &oor)
        // {
        //     // Don't really know why this happens.
        //     p[i] = -1;
        //     continue;
        // }
    }

    cout << "containment (" << nrolls << " elements, * ~ around 10 elements):" << endl;
    cout << fixed; cout.precision(1);

    for (int i = 0; i < nintervals; ++i)
    {
        cout << i << ": ";
        if (p[i] == -1)
        {
            cout << "error" << endl;
        }
        else
        {
            cout << string(p[i]*nstars / nrolls, '*') << endl;
        }
    }

    delete sl;
    delete []v;
    return 0;
}

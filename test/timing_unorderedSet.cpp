#include <string.h>
#include <unordered_set>
#include <iostream>
#include <utility>
#include <time.h>
#include <fstream>
#include <sstream>
#include <algorithm>

float sec(clock_t time)
{
    return (float)time / CLOCKS_PER_SEC;
}

using namespace std;
int main(int argc, char **argv)
{
    srand(time(0));
    std::stringstream dir;
    dir << "results/";
    if (argc > 1)
    {
        dir << std::string(argv[1]) << "/";
    }

    ofstream inserting, erasing, finding, elements;
    elements.open(dir.str() + "elements_uset.csv");
    inserting.open(dir.str() + "inserting_uset.csv");
    finding.open(dir.str() + "finding_uset.csv");
    erasing.open(dir.str() + "erasing_uset.csv");

    clock_t start, t, total;
    const int MAX = 1000000;
    const int INCREMENT = 10000;
    std::vector<int> values(MAX);

    for (int i = 0; i < MAX; ++i) values.push_back(i);
    std::random_shuffle(values.begin(), values.end());

    total = clock();
    for (int LIMIT = INCREMENT; LIMIT <= MAX; LIMIT += INCREMENT)
    {
        cout << "Procesing " << LIMIT << " elements..." << endl;
        std::unordered_set<int> theList = std::unordered_set<int> ();
        elements << LIMIT << endl;

        cout << "\tInsert" << endl;
        t = 0;
        for (int i = 0; i < LIMIT; ++i)
        {
            start = clock();
            theList.insert(values[i]);
            t += clock() - start;
        }

        inserting << sec(t) << endl;

        cout << "\tFind" << endl;
        t = 0;
        for (int i = 0; i < LIMIT; ++i)
        {
            start = clock();
            theList.find(values[i]);
            t += clock() - start;
        }

        finding << sec(t) << endl;

        cout << "\tErase" << endl;
        t = 0;
        for (int i = 0; i < LIMIT; ++i)
        {
            start = clock();
            theList.erase(values[i]);
            t += clock() - start;
        }

        erasing << sec(t) << endl;
    }

    total = clock() - total;
    cout << "Total: " << sec(total) << " seconds." << endl;

    inserting.close();
    elements.close();
    finding.close();
    erasing.close();
    return 0;
}

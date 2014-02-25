#include <string.h>
#include <set>
#include <iostream>
#include <utility>
#include <time.h>
#include <fstream>
#include "../SkipList.cpp"
#include <sstream>

// Testy:
// wydajność - timing dla milionów: inty (random shuffled)
//                                  słowa (random shuffled) - wykorzystać
//                                                            słownik z lab
// Porównanie jak w ZBP1 (unordered_set, set i skiplist)
// Pomiar pamięci (program zawierający tylko strukturę z milionem słów)

float sec(clock_t time)
{
    return (float)time / CLOCKS_PER_SEC;
}

using namespace std;
int main(int argc, char **argv)
{
    std::stringstream dir;
    dir << "results/";
    if(argc > 1) {
        dir << std::string(argv[1]) << "/";
    }

    srand(time(0));
    const int MAX = 1000000;
    const int INCREMENT = 10000;
    int *values = new int[MAX];
    clock_t start, t, total;
    ofstream inserting, erasing, finding, elements;
    elements.open(dir.str() + "elements.csv");
    inserting.open(dir.str() + "inserting.csv");
    finding.open(dir.str() + "finding.csv");
    erasing.open(dir.str() + "erasing.csv");

    for (int i = 0; i < MAX; ++i) values[i] = rand();
    total = clock();
    for (int LIMIT = INCREMENT; LIMIT <= MAX; LIMIT += INCREMENT)
    {
        cout << "Procesing " << LIMIT << " elements..." << endl;
        SkipList<int> theList = SkipList<int> ();
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
            SkipList<int>::iterator it = theList.begin();
            start = clock();
            theList.erase(it);
            t += clock() - start;
        }

        erasing << sec(t) << endl;

        // set<int> *theSet = new set<int>();
        // string val = "a";
        // /* RUN */
        // // inserting
        // cout << "inserting (" << LIMIT << ")" << endl;
        // start = clock();
        // for(int i = 0; i < LIMIT; ++i) theList->insert(i, values[i]);
        // time = clock() - start;
        // cout << "[skip-list]: " << time << endl;
        // // cout << "[skip-list] Inserted " << LIMIT << " elements in " << time / 1000 << " ms" << endl;
        // start = clock();
        // for(int i = 0; i < LIMIT; ++i) theSet->insert(values[i]);
        // time = clock() - start;
        // cout << "[set]: " << time << endl;

        // // searching
        // cout << "SEARCHING (" << LIMIT << ")" << endl;
        // start = clock();
        // for(int i = 0; i < LIMIT; ++i) theList->find(i);
        // time = clock() - start;
        // cout << "[skip-list]: " << time << endl;
        // start = clock();
        // for(int i = 0; i < LIMIT; ++i) theSet->find(i);
        // time = clock() - start;
        // cout << "[set]: " << time << endl;

        // // erasing
        // cout << "ERASING (" << LIMIT << ")" << endl;
        // start = clock();
        // for(int i = 0; i < LIMIT; ++i) theList->erase(i);
        // time = clock() - start;
        // cout << "[skip-list]: " << time << endl;
        // start = clock();
        // for(int i = 0; i < LIMIT; ++i) theSet->erase(i);
        // time = clock() - start;
        // cout << "[set]: " << time << endl;
        // delete theSet;
    }

    total = clock() - total;
    cout << "Total: " << sec(total) << " seconds." << endl;

    inserting.close();
    elements.close();
    finding.close();
    erasing.close();
    return 0;
}

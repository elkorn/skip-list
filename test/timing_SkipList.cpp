#include <string.h>
#include <set>
#include <iostream>
#include <utility>
#include <time.h>
#include <fstream>
#include "../SkipList.cpp"

// Testy:
// wydajność - timing dla milionów: inty (random shuffled)
//                                  słowa (random shuffled) - wykorzystać
//                                                            słownik z lab
// Porównanie jak w ZBP1 (unordered_set, set i skiplist)
// Pomiar pamięci (program zawierający tylko strukturę z milionem słów)

using namespace std;
int main(int argc, char** argv) {
    srand(time(0));
    const int MAX = 1000000;
    const int INCREMENT = 10000;
    int* values = new int[MAX];
    clock_t start, time;
    ofstream inserting, erasing, finding, elements;
    elements.open("elements.csv");
    inserting.open("inserting.csv");
    finding.open("finding.csv");
    erasing.open("erasing.csv");

    /* SETUP */
    for(int i = 0; i < MAX; ++i) values[i] = rand();
    for(int LIMIT = INCREMENT; LIMIT <= MAX; LIMIT += INCREMENT) {
        cout << "Procesing " << LIMIT << " elements..." << endl;
        cout << "\tInsert" << endl;
        SkipList<int> theList = SkipList<int> ();
        elements << LIMIT << endl;
        start = clock();
        for(int i = 0; i < LIMIT; ++i) theList.insert(values[i]);
        time = clock() - start;
        inserting << time << endl;

        cout << "\tFind" << endl;
        start = clock();
        for(int i = 0; i < LIMIT; ++i) theList.find(values[i]);
        time = clock() - start;
        finding << time << endl;

        cout << "\tErase" << endl;
        start = clock();
        for(int i = 0; i < LIMIT; ++i) theList.erase(values[i]);
        time = clock() - start;
        erasing << time << endl;

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

    inserting.close();
    elements.close();
    finding.close();
    erasing.close();
    return 0;
}

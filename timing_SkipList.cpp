#include <string.h>
#include <set>
#include <iostream>
#include "SkipList.cpp"
#include <utility>
#include <time.h>
#include <fstream>

// Testy:
// wydajność - timing dla milionów: inty (random shuffled)
//                                  słowa (random shuffled) - wykorzystać
//                                                            słownik z lab
// Porównanie jak w ZBP1 (unordered_set, set i skiplist)
// Pomiar pamięci (program zawierający tylko strukturę z milionem słów)

using namespace std;
int main(int argc, char** argv) {
    srand(time(0));
    int MAX = 1000000;
    int* values = new int[MAX];
    clock_t start, time;
    ofstream of;
    of.open("results.csv");

    /* SETUP */
    for(int i = 0; i < MAX; ++i) values[i] = rand();
    for(int LIMIT = 10000; LIMIT <= MAX; LIMIT += 10000) {
        cout << "Procesing " << LIMIT << " elements..." << endl;
        SkipList<int> *theList = new SkipList<int> ();
        start = clock();
        for(int i = 0; i < LIMIT; ++i) theList->insert(values[i]);
        time = clock() - start;
        of << time << endl;
        // set<int> *theSet = new set<int>();
        // string val = "a";
        // /* RUN */
        // // insertion
        // cout << "INSERTION (" << LIMIT << ")" << endl;
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
        delete theList;
        // delete theSet;
    }

    of.close();
    return 0;
}

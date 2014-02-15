#include <string.h>
#include <set>
#include <iostream>
#include "SkipList.cpp"
#include <utility>
#include <time.h>

using namespace std;
int main(int argc, char** argv) {
    srand(time(0));
    SkipList<int, int> *theList = new SkipList<int, int> (5);
    set<int> *theSet = new set<int>();
    string val = "a";
    int MAX = 1000000;
    int* values = new int[MAX];
    clock_t start, time;
    /* SETUP */
    for(int i = 0; i < MAX; ++i) values[i] = rand();
    for(int LIMIT = 10; LIMIT <= MAX; LIMIT *= 10) {
        /* RUN */
        // insertion
        cout << "INSERTION (" << LIMIT << ")" << endl;
        start = clock();
        for(int i = 0; i < LIMIT; ++i) theList->insert(i, values[i]);
        time = clock() - start;
        cout << "[skip-list]: " << time << endl;
        // cout << "[skip-list] Inserted " << LIMIT << " elements in " << time / 1000 << " ms" << endl;
        start = clock();
        for(int i = 0; i < LIMIT; ++i) theSet->insert(values[i]);
        time = clock() - start;
        cout << "[set]: " << time << endl;

        // searching
        cout << "SEARCHING (" << LIMIT << ")" << endl;
        start = clock();
        for(int i = 1; i < LIMIT; ++i) theList->find(i);
        time = clock() - start;
        cout << "[skip-list]: " << time << endl;
        start = clock();
        for(int i = 1; i < LIMIT; ++i) theSet->find(i);
        time = clock() - start;
        cout << "[set]: " << time << endl;

        // erasing
        cout << "ERASING (" << LIMIT << ")" << endl;
        start = clock();
        for(int i = 1; i < LIMIT; ++i) theList->erase(i);
        time = clock() - start;
        cout << "[skip-list]: " << time << endl;
        start = clock();
        for(int i = 1; i < LIMIT; ++i) theSet->erase(i);
        time = clock() - start;
        cout << "[set]: " << time << endl;
    }

    return 0;
}

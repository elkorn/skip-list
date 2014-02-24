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
    const int HEIGHT = 32;
    clock_t start, time;
    ofstream of;
    of.open("creation.csv");
    SkipListNode<int>* p[MAX]{};

    for(int LIMIT = 10000; LIMIT <= MAX; LIMIT += 10000) {
        cout << "Procesing " << LIMIT << " elements..." << endl;
        start = clock();
        for(int i = 0; i < LIMIT; ++i) p[i]=new SkipListNode<int>(i,HEIGHT);
        time = clock() - start;
        of << time << endl;
        for(int i = 0; i < LIMIT; ++i) {
            delete p[i];
        }
    }

    of.close();
    return 0;
}

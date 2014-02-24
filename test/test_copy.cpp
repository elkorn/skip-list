#include <assert.h>
#include <string.h>
#include <iostream>
#include <utility>
#include <time.h>
#include <stdlib.h>
#include "../SkipList.cpp"

using namespace std;

int main(int argc, char** argv) {
    srand(time(0));
    int testVal1 = 12, testVal2 = 23, testVal3 = 34, testVal4 = 56;
    SkipList<int> *theList = new SkipList<int>();

    /* BASIC API TESTS */
    cout << "*** COPYING TEST ***" << endl << "    ";

    theList->insert(testVal1);
    theList->insert(testVal2);
    theList->insert(testVal3);
    theList->insert(testVal4);


    //SkipList<string> *emptyList = new SkipList<string>(*theList);

    //delete emptyList;
    cout << "All tests passed!" << endl;

    delete theList;
    return 0;
}

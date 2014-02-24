#include <assert.h>
#include <string.h>
#include <iostream>
#include <utility>
#include <time.h>
#include <stdlib.h>
#include "../SkipList.cpp"

using namespace std;

int main(int argc, char **argv)
{
    srand(time(0));
    int testVal1 = 12, testVal2 = 23, testVal3 = 34, testVal4 = 56;
    SkipList<int> theList = SkipList<int>();

    /* BASIC API TESTS */
    cout << "*** COPYING TEST ***" << endl << "    ";

    theList.insert(testVal1);
    theList.insert(testVal2);
    theList.insert(testVal3);
    theList.insert(testVal4);

    SkipList<int> copiedList = SkipList<int>(theList);
    SkipList<int> toAssignTo = SkipList<int>();
    SkipList<int> toBeAssigned = SkipList<int>();

    toAssignTo.insert(testVal1);
    toAssignTo.insert(testVal2);
    toBeAssigned.insert(testVal3);
    toBeAssigned.insert(testVal4);

    for (SkipList<int>::iterator it1 = theList.begin(),
            it2 = copiedList.begin(),
            end1 = theList.end(),
            end2 = copiedList.end();
            it1 != end2 && it2 != end2;
            ++it1, ++it2)
    {
        assert(it1->getVal() == it2->getVal());
    }

    toAssignTo = toBeAssigned;

    for (SkipList<int>::iterator it1 = toAssignTo.begin(),
            it2 = toBeAssigned.begin(),
            end1 = toAssignTo.end(),
            end2 = toBeAssigned.end();
            it1 != end2 && it2 != end2;
            ++it1, ++it2)
    {
        assert(it1->getVal() == it2->getVal());
    }

    cout << "All tests passed!" << endl;
    return 0;
}

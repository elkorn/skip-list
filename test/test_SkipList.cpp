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
    string maxKey = "Z";
    int testVal1 = 12, testVal2 = 23, testVal3 = 34, testVal4 = 56, defaultVal = 0;
    SkipList<int> *theList = new SkipList<int>();
    SkipList<int> *toClear = new SkipList<int>();
    SkipList<string> *emptyList = new SkipList<string>();

    /* BASIC API TESTS */
    cout << "*** BASIC API TESTS ***" << endl << "    ";
    theList->insert(testVal1);
    theList->insert(testVal2);
    assert(theList->find(testVal2)->getVal() == testVal2);
    assert(theList->find(9865) == theList->end() && "It should throw an exception when searching for a non-existent key.");
    theList->insert(testVal3);
    assert(emptyList->empty() == 1);
    assert(theList->empty() == 0);
    assert(theList->size() == 3);
    assert(emptyList->size() == 0);
    assert(theList->count(testVal2) == 1);
    assert(theList->count(123) == 0);
    assert(emptyList->count("etreu") == 0);
    assert(theList->erase(testVal3) == theList->end());
    assert(theList->size() == 2 && "It should erase the 'b' element.");
    theList->insert(testVal3);
    std::pair<bool, SkipList<int>::iterator> insertionResult = theList->insert(testVal3);
    assert(insertionResult.first == false && "Cannot insert duplicate elements into the set.");
    assert(insertionResult.second->getVal() == testVal3 && "Cannot insert duplicate elements into the set.");

    toClear->insert(testVal1);
    toClear->insert(testVal2);
    toClear->insert(testVal3);
    toClear->insert(testVal4);
    toClear->clear();
    assert(toClear->size() == 0 && "A cleared list should not have any elements.");
    assert(toClear->begin() == toClear->end() && "A cleared list should not have any elements.");
    toClear->insert(testVal1);
    toClear->insert(testVal2);
    assert(toClear->size() == 2 && "A cleared list should work normally after the clearing.");
    assert(toClear->find(testVal1)->getVal() == testVal1 && "A cleared list should work normally after the clearing.");
    cout << endl;

    /* ITERATOR TESTS */
    cout << "*** ITERATOR TESTS ***" << endl << "    ";
    SkipList<int>::iterator it = theList->begin();
    assert(*it == testVal1 && "An iterator acquired through the `begin` method should point at the first value of the skiplist.");
    ++it;
    assert(*it == testVal2 && "After incrementing, the iterator should point to the second value.");
    assert(*it == it->getVal() && "The `->` operator should return the element pointed at by the iterator.");

    assert(it->prev[0]->getVal() == testVal1 && "The previous element for the iterator at key 'b' should be that under the key 'a'.");
    SkipList<int>::reverse_iterator rit = theList->rbegin();
    assert(*rit == testVal3 && "A reverse iterator acquired through the `rbegin` method should point at the last value of the skiplist.");
    ++rit;
    assert(*rit == testVal2 && "After incrementing, the reverse iterator should point to the value at key 'b'.");
    assert(*rit == rit->getVal() && "The `->` operator should return the element pointed at by the reverse iterator.");
    ++rit;
    assert(*rit == testVal1 && "After incrementing twice, the reverse iterator should point to the value at key 'a'.");
    cout << endl;

    /* BOUND-RELATED METHOD TESTS */
    cout << "*** BOUND-RELATED METHOD TESTS ***" << endl;
    cout << "    Lower bound" << endl << "    ";

    assert(theList->lower_bound(testVal1)->getVal() == testVal1 && "The lower bound for an existing element should be the element itself.");
    theList->erase(testVal2);
    assert(theList->lower_bound(testVal2)->getVal() == testVal3 && "The lower bound for a non-existing element should be the first element with a key that is not less than the given key.");
    assert(theList->lower_bound(8888) == theList->end() &&  "[FAIL] The lower bound for a non-existing element with a key greater than any key conatined within the set should not exist.");

    theList->insert(testVal2);
    cout << endl << "    Upper bound" << endl << "    ";
    assert(theList->upper_bound(testVal1)->getVal() == testVal2 && "The upper bound for an existing element should be the first element with a key greater than the given one.");
    theList->erase(testVal2);
    assert(theList->upper_bound(testVal2)->getVal() == testVal3 && "The upper bound for a non-existing element should be the first element with a key that is greater than the given key.");
    theList->insert(testVal2);
    assert(theList->upper_bound(testVal4) == theList->end() &&  "The upper bound for an existing element with a key greater than any key conatined within the set should not exist.");

    theList->insert(testVal4);
    cout << endl << "    Equal range" << endl << "    ";
    std::pair<SkipList<int>::iterator, SkipList< int>::iterator> equalRange = theList->equal_range(testVal2);

    assert(*(equalRange.first) == testVal2 && "The first element of the equal range should equal the lower bound for that key.");
    assert(*(equalRange.second) == testVal3 && "The second element of the equal range should equal the upper bound for that key.");
    cout << endl;
    /* DEGENERATE CASE TESTS */
    cout << "*** DEGENERATE CASE TESTS ***" << endl;
    cout << "    Item with the same key as head/tail" << endl << "    ";

    SkipList<int> *degenerate = new SkipList<int>();
    assert(degenerate->insert(defaultVal).first == true && "It should be possible to insert an element with a key equal to the default value of given type.");
    assert(degenerate->size() == 1 && "The inserted element should be counted into the overall size of the structure.");
    assert(degenerate->find(defaultVal)->getVal() == defaultVal && "It should be possible to find an element placed under the key equal to the default value of given type.");
    assert(degenerate->erase(defaultVal) == degenerate->end() && "It should be possible to erase an element placed under the key equal to the default value of given type.");
    assert(degenerate->size() == 0);
    assert(degenerate->find(defaultVal) == degenerate->end() && "The erased element should not exist in the structure.");

    cout << endl;

    cout << "*** CONSTRUCTOR TESTS ***" << endl;
    cout << "    Range constructor" << endl << "    ";
    SkipList<int> *rangeList = new SkipList<int>(equalRange.first, equalRange.second);
    assert(rangeList->begin()->getVal() == equalRange.first->getVal() &&
           "The list created from a range should begin with the first element of the range.");
    assert(rangeList->size() == 1 &&
           "The list created from an equal range should contain only one element.");
    delete rangeList;
    rangeList = 0;
    rangeList = new SkipList<int>(equalRange.first, theList->end());
    SkipList<int>::iterator pos = rangeList->begin();
    assert(pos->getVal() == equalRange.first->getVal() &&
           "The list created from a range should begin with the first element of the range.");
    ++pos;
    assert(pos->getVal() == equalRange.second->getVal() &&
           "The list created from a range should end with the last element of the range.");
    assert(rangeList->size() == 3 &&
           "The list created a range should contain all the provided elements except the last one.");
    cout << "*** DELETING THE STRUCTURE ***" << endl;

    delete theList;
    delete emptyList;
    delete degenerate;
    delete rangeList;
    delete toClear;
    cout << "All tests passed!" << endl;

    return 0;
}

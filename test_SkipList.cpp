#include <assert.h>
#include <string.h>
#include <iostream>
#include "SkipList.cpp"
#include <utility>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv) {
    srand(time(0));
    string maxKey = "Z";
    string testKey1 = "a", testKey2 = "c", testKey3 = "dddd";
    int testVal1 = 12, testVal2 = 1238, testVal3 = 124546, testVal4 = 5;
    SkipList<string, int> *theList = new SkipList<string, int>(5);
    SkipList<string, string> *emptyList = new SkipList<string, string>();

    /* BASIC API TESTS */
    cout << "*** BASIC API TESTS ***" << endl << "    ";
    theList->insert("a", testVal1);
    theList->insert("c", testVal2);
    theList->find("c"); // removing this causes a segfault. No more?
    try {
        theList->find("xxyzzyxx");
        assert(false && "It should throw an exception when searching for a non-existent key.");
    } catch(ElementNotFoundException<string> &ex) { }

    theList->insert("b", testVal3);
    assert(emptyList->empty() == 1);
    assert(theList->empty() == 0);
    assert(theList->size() == 3);
    assert(emptyList->size() == 0);
    assert(theList->count("c") == 1);
    assert(theList->count("z") == 0);
    assert(emptyList->count("c") == 0);
    theList->erase("b");
    assert(theList->size() == 2 && "It should erase the 'b' element.");
    theList->insert("b", testVal3);
    cout << endl;

    /* ITERATOR TESTS */
    cout << "*** ITERATOR TESTS ***" << endl << "    ";
    SkipList<string, int>::iterator it = theList->begin();
    assert(*it == testVal1 && "An iterator acquired through the `begin` method should point at the first value of the skiplist.");
    ++it;
    assert(*it == testVal3 && "After incrementing, the iterator should point to the value at key 'b'.");
    assert(*it == it->getVal() && "The `->` operator should return the element pointed at by the iterator.");

    assert(it->prev[0]->getVal() == testVal1 && "The previous element for the iterator at key 'b' should be that under the key 'a'.");
    SkipList<string, int>::reverse_iterator rit = theList->rbegin();
    assert(*rit == testVal2 && "A reverse iterator acquired through the `rbegin` method should point at the last value of the skiplist.");
    ++rit;
    assert(*rit == testVal3 && "After incrementing, the reverse iterator should point to the value at key 'b'.");
    assert(*rit == rit->getVal() && "The `->` operator should return the element pointed at by the reverse iterator.");
    ++rit;
    assert(*rit == testVal1 && "After incrementing twice, the reverse iterator should point to the value at key 'a'.");
    cout << endl;

    /* BOUND-RELATED METHOD TESTS */
    cout << "*** BOUND-RELATED METHOD TESTS ***" << endl;
    cout << "    Lower bound" << endl << "    ";

    assert(theList->lower_bound("a")->getKey() == "a" && "The lower bound for an existing element should be the element itself.");
    theList->erase("b");
    assert(theList->lower_bound("b")->getKey() == "c" && "The lower bound for a non-existing element should be the first element with a key that is not less than the given key.");
    try {
        theList->lower_bound("d");
        assert(false &&  "[FAIL] The lower bound for a non-existing element with a key greater than any key conatined within the set should not exist.");
    } catch(LowerBoundNotFoundException<string>& ex) {
        // This is a better idea for test output...
        // cout << "[ OK ] The lower bound for a non-existing element with a key greater than any key conatined within the set should not exist." << endl;
    }

    cout << endl << "    Upper bound" << endl << "    ";
    assert(theList->upper_bound("a")->getKey() == "c" && "The upper bound for an existing element should be the first element with a key greater than the given one.");
    assert(theList->upper_bound("b")->getKey() == "c" && "The upper bound for a non-existing element should be the first element with a key that is greater than the given key.");
    try {
        theList->upper_bound("c");
        assert(false &&  "[FAIL] The upper bound for an existing element with a key greater than any key conatined within the set should not exist.");
    } catch(UpperBoundNotFoundException<string>& ex) { }

    theList->insert("d", testVal4);
    cout << endl << "    Equal range" << endl << "    ";
    std::pair<SkipList<string, int>::iterator, SkipList<string, int>::iterator> equalRange = theList->equal_range("c");

    assert(*(equalRange.first) == testVal2 && "The first element of the equal range should equal the lower bound for that key.");
    assert(*(equalRange.second) == testVal4 && "The second element of the equal range should equal the upper bound for that key.");
    cout << endl;
    /* DEGENERATE CASE TESTS */
    cout << "*** DEGENERATE CASE TESTS ***" << endl;
    cout << "    Item with the same key as head/tail" << endl << "    ";

    SkipList<int, int> *degenerate = new SkipList<int, int>();
    assert(degenerate->insert(0,testVal1) == true && "It should be possible to insert an element with a key equal to the default value of given type.");
    assert(degenerate->size() == 1 && "The inserted element should be counted into the overall size of the structure.");
    assert(degenerate->find(0) == testVal1 && "It should be possible to find an element placed under the key equal to the default value of given type.");
    assert(degenerate->erase(0) == true && "It should be possible to erase an element placed under the key equal to the default value of given type.");
    assert(degenerate->size() == 0);
    try {
        degenerate->find(0);
        assert(false && "The erased element should not exist in the structure.");
    } catch (ElementNotFoundException<int> &ex) { }

    cout << endl;

    cout << "*** DELETING THE STRUCTURE ***" << endl;
    delete theList;
    delete emptyList;
    delete degenerate;
    cout << "All tests passed!" << endl;

    return 0;
}

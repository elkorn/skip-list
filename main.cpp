#include <assert.h>
#include <string.h>
#include <iostream>
#include "SkipList.cpp"

using namespace std;

int main(int argc, char** argv) {
    string maxKey = "Z";
    string testKey1 = "a", testKey2 = "c", testKey3 = "dddd";
    int testVal1 = 12, testVal2 = 1238, testVal3 = 124546;
    SkipList<string, int> *theList = new SkipList<string, int>((float).6, 5, maxKey);
    SkipList<string, string> *emptyList = new SkipList<string, string>();
    theList->insert("a", &testVal1);
    theList->insert("c", &testVal2);
    theList->find("c"); // removing this causes a segfault.
    try {
        theList->find("xxyzzyxx");
        assert(false && "It should throw an exception when searching for a non-existent key.");
    } catch(ElementNotFoundException<string> &ex) { }

    theList->insert("b", &testVal3);
    assert(emptyList->empty() == 1);
    assert(theList->empty() == 0);
    assert(theList->size() == 3);
    assert(emptyList->size() == 0);
    assert(theList->count("c") == 1);
    assert(theList->count("z") == 0);
    assert(emptyList->count("c") == 0);
    theList->erase("b");
    assert(theList->size() == 2 && "It should erase the 'b' element.");
    theList->insert("b", &testVal3);
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

    return 0;
}

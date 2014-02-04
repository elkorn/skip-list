#include <string.h>
#include <iostream>
#include "SkipList.cpp"

using namespace std;

int main(int argc, char** argv) {
    string maxKey = "Z";
    string testKey1 = "a", testKey2 = "c", testKey3 = "dddd";
    int testVal1 = 12, testVal2 = 1238, testVal3 = 124546;
    SkipList<string, int> *theList = new SkipList<string, int>((float).6, 5, maxKey);
    theList->insert("a", &testVal1);
    theList->insert("c", &testVal2);
    theList->print(cout);

    cout << theList->find("c") << endl;
    try {
        cout << theList->find("xxyzzyxx");
    } catch(ElementNotFoundException<string> &ex) {
        cout << ex.what();
    }

    theList->insert("b", &testVal3);
    cout << endl;
    theList->print(cout);

    SkipList<string, string> *emptyList = new SkipList<string, string>();

    cout << "For an empty set: " << emptyList->empty() << ", for a non-empty set: " << theList->empty();

    return 0;
}

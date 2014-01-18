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
    theList->insert("c", &testVal1);
    theList->print(cout);

    cout << theList->find("c");
    try {
        cout << theList->find("xxyzzyxx");
    } catch(ElementNotFoundException<string> &ex) {
        cout << ex.what();
    }
    return 0;
}

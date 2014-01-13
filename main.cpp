#include <string.h>
#include <iostream>
#include "SkipList.cpp"

using namespace std;

int main(int argc, char** argv) {
    string maxKey = "Z";
    string testKey = "a";
    int testVal = 12;
    SkipList<string, int> *theList = new SkipList<string, int>((float).6, 5, &maxKey);
    theList->insert(&testKey, &testVal);
    theList->print(cout);

    return 0;
}

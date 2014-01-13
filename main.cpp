#include <string.h>
#include <iostream>
#include "SkipList.cpp"

using namespace std;

int main(int argc, char** argv) {
    string maxKey = "Z";
    SkipList<string, int> *theList = new SkipList<string, int>((float).6, 5, &maxKey);

    theList->print(cout);

    return 0;
}

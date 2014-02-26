#include "../SkipList.cpp"
int main()
{
    const long MAX = 100000000;
    const long INC = 10000000;
    for (int LIMIT = INC; LIMIT <= MAX; LIMIT += INC)
    {
        SkipList<int> *theList = new SkipList<int> ();
        for (int i = 0; i < LIMIT; ++i) theList->insert(i);
        delete theList;
    }

    return 0;
}
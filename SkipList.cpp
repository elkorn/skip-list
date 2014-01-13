#include <iostream>
#include <fstream>
#include "SkipListNode.h"
#include "RandomHeight.h"

template <class Key, class Val>
class SkipList {
    public:
        SkipList(float, int, Key*);
        ~SkipList();

        bool insert(Key*, Val*);
        bool remove(Key*);
        Val* retrieve(Key*);
        void print(std::ofstream &);

    private:
        SkipListNode<Key, Val>* head;
        SkipListNode<Key, Val>* tail;
        float probability;
        int maxHeight;
        int currentHeight;
        RandomHeight* randomizer;
};

template <class Key, class Val>
SkipList<Key, Val>::SkipList(float theProbability, int theMaxHeight, Key* theKey) {
    currentHeight = 1;
    maxHeight = theMaxHeight;
    probability = theProbability;
    randomizer = new RandomHeight(theMaxHeight, theProbability);

    head = new SkipListNode<Key, Val>(theMaxHeight);
    tail = new SkipListNode<Key, Val>(theKey, (Val*)nullptr, theMaxHeight);
    for (int i = 1; i <= theMaxHeight; ++i) head->next[i] = tail;
}

template <class Key, class Val>
bool SkipList<Key, Val>::insert(Key* theKey, Val* theValue) {
    int lvl = 0, h = currentHeight;
    SkipListNode<Key, Val>** toUpdate = new SkipListNode<Key, Val>*[maxHeight+1];
    SkipListNode<Key, Val>* tempNode = head;
    Key* compareKey;
    for(; h > 0; --h) {
        
    }
}

template <class Key, class Val>
SkipList<Key, Val>::~SkipList() {
    SkipListNode<Key, Val> *tempNode = head, *nextNode;
    while(tempNode) {
        nextNode = tempNode->next[1];
        delete tempNode;
        tempNode = nextNode;
    }
}

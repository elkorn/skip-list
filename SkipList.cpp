#include <iostream>
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
        void print(std::ostream &);

    private:
        SkipListNode<Key, Val>* head;
        SkipListNode<Key, Val>* tail;
        float probability;
        int maxHeight;
        int currentHeight;
        RandomHeight* randomizer;
};

template <class Key, class Val>
SkipList<Key, Val>::SkipList(float theProbability, int theMaxHeight, Key* maxKey) {
    currentHeight = 1;
    maxHeight = theMaxHeight;
    probability = theProbability;
    randomizer = new RandomHeight(theMaxHeight, theProbability);

    head = new SkipListNode<Key, Val>(theMaxHeight);
    tail = new SkipListNode<Key, Val>(maxKey, (Val*)nullptr, theMaxHeight);
    for (int i = 1; i <= theMaxHeight; ++i) head->next[i] = tail;
}

template <class Key, class Val>
bool SkipList<Key, Val>::insert(Key* theKey, Val* theValue) {
    int level = 0, h = currentHeight;
    SkipListNode<Key, Val>** toUpdate = new SkipListNode<Key, Val>*[maxHeight+1];
    SkipListNode<Key, Val>* tempNode = head;
    Key* compareKey;
    // Check all the height levels for where to insert the new node.
    for(; h > 0; --h) {
        compareKey = tempNode->next[h]->getKey();
        while(*compareKey < * *theKey) {
            // We have to go further.
            tempNode = tempNode->next[h];
            compareKey = tempNode->next[h]->getKey();
        }

        // This node at level h will have to be updated after inserting the new one.
        toUpdate[h] = tempNode;
    }

    tempNode = tempNode->next[1];
    compareKey = tempNode->getKey();

    if(*compareKey == *theKey) {
        // We already have this key in the set - cannot insert.
        return false;
    }

    // Get a random level for the node to be inserted into.
    level = randomizer->newLevel();
    if(level > currentHeight) {
        // Create all the levels between the previous and new currentHeight
        // and add them to the update matrix.
        for(int i = currentHeight + 1; i <= level; ++i) toUpdate[i] = head; // The default lookup node.
        currentHeight = level;
    }

    tempNode = new SkipListNode<Key, Val>(theKey, theValue, level);

    // Actually insert the node where it belongs.
    for (int i = 1; i <= level; ++i) {
        tempNode->next[i] = toUpdate[i]->next[i];
        toUpdate[i]->next[i] = tempNode;
    }

    // Success!
    return true;
}

template <class Key, class Val>
bool SkipList<Key, Val>::remove(Key* theKey) {
    SkipListNode<Key, Val>** toUpdate = new SkipListNode<Key, Val>*[maxHeight+1];
    SkipListNode<Key,Val>* tempNode = head;
    Key* compareKey;

    // TODO: extract this to a common private function.
    for (int h = currentHeight; h > 0; --h) {
        compareKey = tempNode->next[h]->getKey();
        while(*compareKey < *theKey) {
            tempNode = tempNode->next[h];
            compareKey = tempNode->next[h]->getKey();
        }

        toUpdate[h] = tempNode;
    }

    // Get the found node at the base level.
    tempNode = tempNode->next[1];
    compareKey = tempNode->getKey();

    if (*compareKey == *theKey) {
        for (int i = 1; i <= currentHeight; ++i) {
            if (toUpdate[i]->next[i] != tempNode) break; // The removed node does not exist at this level.
            toUpdate[i]->next[i] = tempNode->next[i]; // Wire up the pointers.
        }

        delete tempNode;

        // Adjust currentHeight.
        while ((currentHeight > 1) &&
            (head->next[currentHeight]->getKey() == tail->getKey())) {
            // If there are no nodes at currentHeight, decrement the value - no need to poke around there.
            --currentHeight;
        }

        // Success!
        return true;
    }

    // Node not found - nothing to remove.
    return false;
}

template <class Key, class Val>
Val* SkipList<Key, Val>::retrieve(Key* theKey) {
    int h = currentHeight;
    SkipListNode<Key, Val> **toUpdate = new SkipListNode<Key, Val>*[maxHeight+1];
    SkipListNode<Key, Val>* tempNode = head;
    Key* compareKey;

    for (; h > 0; --h) {
        compareKey = tempNode->next[h]->getKey();
        while(*compareKey < *theKey) {
            tempNode = tempNode->next[h];
            compareKey = tempNode->getKey();
        }

        toUpdate[h] = tempNode;
    }

    tempNode = tempNode->next[1];
    compareKey = tempNode->getKey();

    if (*compareKey == *theKey) {
        // Success!
        return tempNode->getVal();
    }

    return (SkipListNode<Key, Val>*)nullptr;
}

template <class Key, class Val>
void SkipList<Key, Val>::print(std::ostream &out) {
    SkipListNode<Key, Val> *tempNode = head;

    while(tempNode != tail) {
        if(tempNode == head) {
            out << "HEAD";
        } else {
            out << tempNode->getKey();
        }

        out << std::endl << std::flush;
    }

    out << "TAIL" << std::endl << std::flush;
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

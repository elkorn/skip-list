#include <iostream>
#include "SkipListNode.cpp"
#include "RandomHeight.cpp"
#include "ElementNotFoundException.cpp"

template <class Key, class Val>
class SkipList {
    public:
        SkipList(float, int, const Key&);
        SkipList();
        ~SkipList();

        bool insert(const Key&, Val*);
        bool erase(const Key);
        const Val& find(const Key&);
        void print(std::ostream &);
        const bool empty();
        const unsigned int count(const Key&);
        const unsigned int size();

        struct iterator {
            typedef iterator self_type;
            typedef SkipListNode<Key, Val> value_type;
 
            iterator(value_type *start) {
                current = start;
            }

            bool hasNext() {
                return current->next[0] != 0 && current->next[0]->next[0] != 0;
            }

            self_type operator ++() {
                self_type res = *this;
                current = current->next[0];
                return res;
            }

            const Val& operator *() {
                return current->getVal();
            }

            value_type *operator ->() {
                return current;
            }

            bool operator==(const self_type &other) {
                return current == other.current;
            }

            bool operator!=(const self_type &other) {
                return current != other.current;
            }

            private:
                SkipListNode<Key, Val> *current;
        };

        iterator begin();
        iterator end();


    private:
        SkipListNode<Key, Val>* head;
        SkipListNode<Key, Val>* tail;
        float probability;
        int maxHeight;
        int currentHeight;
        unsigned int _size;
        RandomHeight* randomizer;
};

template <class Key, class Val>
SkipList<Key, Val>::SkipList():  currentHeight(1) {
    maxHeight = 15;
    head = new SkipListNode<Key, Val>(maxHeight);
    tail = 0;
    for(int i = 0; i < maxHeight; ++i) {
        head->next[i] = tail;
    }
}

template <class Key, class Val>
SkipList<Key, Val>::SkipList(float theProbability, int theMaxHeight, const Key &maxKey) {
    currentHeight = 1;
    maxHeight = theMaxHeight;
    probability = theProbability;
    randomizer = new RandomHeight(theMaxHeight, theProbability);

    head = new SkipListNode<Key, Val>(theMaxHeight);
    tail = new SkipListNode<Key, Val>(maxKey, (Val*)0, theMaxHeight);
    for (int i = 0; i < theMaxHeight; ++i) head->next[i] = tail;
}

template <class Key, class Val>
bool SkipList<Key, Val>::insert(const Key &theKey, Val* theValue) {
    int level = 0, h = currentHeight - 1;
    SkipListNode<Key, Val>** toUpdate = new SkipListNode<Key, Val>*[maxHeight];
    SkipListNode<Key, Val>* tempNode = head;

    // Check all the height levels for where to insert the new node.
    for (; h >= 0; --h) {
        while (tempNode->next[h] != tail && tempNode->next[h]->getKey() < theKey) {
            tempNode = tempNode->next[h];
        }

        // This node will have to be updated at level h after inserting the new one.
        toUpdate[h] = tempNode;
    }

    if(tempNode->getKey() == theKey) {
        // We already have this key in the set - cannot insert.
        return false;
    }

    // Get a random level for the node to be inserted into.
    level = randomizer->newLevel();
    if(level > currentHeight) {
        // Create all the levels between the previous and new currentHeight
        // and add them to the update matrix.
        for(int i = currentHeight; i < level; ++i) toUpdate[i] = head; // The default lookup node.
        currentHeight = level;
    }

    tempNode = new SkipListNode<Key, Val>(theKey, theValue, level);

    // Actually insert the node where it belongs.
    for (int i = 0; i < level; ++i) {
        tempNode->next[i] = toUpdate[i]->next[i];
        toUpdate[i]->next[i] = tempNode;
    }

    ++_size;

    // Success!
    return true;
}

template <class Key, class Val>
bool SkipList<Key, Val>::erase(const Key theKey) {
    SkipListNode<Key, Val>** toUpdate = new SkipListNode<Key, Val>*[maxHeight+1];
    SkipListNode<Key,Val>* tempNode = head;
    Key compareKey;

    // TODO: extract this to a common private function.
    for (int h = currentHeight - 1; h >= 0; --h) {
        if(tempNode->next[h] != tail) {
            compareKey = tempNode->next[h]->getKey();
            while(compareKey < theKey) {
                tempNode = tempNode->next[h];
                compareKey = tempNode->next[h]->getKey();
            }
        }

        toUpdate[h] = tempNode;
    }

    // Get the found node at the base level.
    tempNode = tempNode->next[0];
    compareKey = tempNode->getKey();

    if (compareKey == theKey) {
        for (int i = 0; i < currentHeight; ++i) {
            if (toUpdate[i]->next[i] != tempNode) break; // The erased node does not exist at this level.
            toUpdate[i]->next[i] = tempNode->next[i]; // Wire up the pointers.
        }

        delete tempNode;

        // Adjust currentHeight.
        while ((currentHeight > 1) &&
            (head->next[currentHeight]->getKey() == tail->getKey())) {
            // If there are no nodes at currentHeight, decrement the value - no need to poke around there.
            --currentHeight;
        }

        --_size;

        // Success!
        return true;
    }

    // Node not found - nothing to erase.
    return false;
}

template <class Key, class Val>
const Val& SkipList<Key, Val>::find(const Key &theKey) {
    int h = currentHeight - 1;
    SkipListNode<Key, Val>* tempNode = head;

    if (empty()) {
        throw ElementNotFoundException<Key>(theKey);
    }

    for (; h >= 0; --h) {
        while (tempNode->next[h] != tail && tempNode->next[h]->getKey() < theKey) {
            tempNode = tempNode->next[h];
        }
    }



    tempNode = tempNode->next[0];

    if (tempNode->getKey() == theKey) {
        // Success!
        return tempNode->getVal();
    }

    throw ElementNotFoundException<Key>(theKey);
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
        tempNode = tempNode->next[0];
    }

    out << "TAIL" << std::endl << std::flush;
}

template <class Key, class Val>
const bool SkipList<Key, Val>::empty() {
    return head->next[0] == tail;
}

template <class Key, class Val>
const unsigned int SkipList<Key, Val>::size() {
    // To keep the size operation at O(1), the size is being maintained 
    // throughout the lifetime of the list.
    return _size;
}

template <class Key, class Val>
const unsigned int SkipList<Key, Val>::count(const Key& theKey) {
    try {
        find(theKey);
        return 1;
    } catch(ElementNotFoundException<Key>& e) {
        return 0;
    }
}

template <class Key, class Val>
SkipList<Key, Val>::~SkipList() {
    SkipListNode<Key, Val> *tempNode = head, *nextNode;
    while(tempNode) {
        nextNode = tempNode->next[0];
        delete tempNode;
        tempNode = nextNode;
    }
}

template <class Key, class Val>
typename SkipList<Key, Val>::iterator SkipList<Key, Val>::begin() {
    return SkipList<Key, Val>::iterator(head->next[0]);
}

template <class Key, class Val>
typename SkipList<Key, Val>::iterator SkipList<Key, Val>::end() {
    return SkipList<Key, Val>::iterator(tail);
}


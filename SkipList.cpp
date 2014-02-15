#include <iostream>
#include "SkipListNode.cpp"
#include "RandomHeight.cpp"
#include "SkipList.h"
#include <utility>

#include "exceptions/ElementNotFoundException.cpp"
#include "exceptions/LowerBoundNotFoundException.cpp"
#include "exceptions/UpperBoundNotFoundException.cpp"

template <class Key, class Val>
struct SkipList<Key, Val>::iterator {
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

template<class Key, class Val>
struct SkipList<Key,Val>::reverse_iterator {
    typedef reverse_iterator self_type;
    typedef SkipListNode<Key, Val> value_type;

    reverse_iterator(value_type *start) {
        current = start;
    }

    bool hasNext() {
        return current->prev[0] != 0 && current->prev[0]->prev[0] != 0;
    }

    self_type operator ++() {
        self_type res = *this;
        current = current->prev[0];
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

template <class Key, class Val>
SkipList<Key, Val>::SkipList():
    currentHeight(1),
    maxHeight(15)
{
    head = new SkipListNode<Key, Val>(maxHeight);
    tail = new SkipListNode<Key, Val>(maxHeight);
    for(int i = 0; i < maxHeight; ++i) {
        head->next[i] = tail;
    }
}

template <class Key, class Val>
SkipList<Key, Val>::SkipList(int theMaxHeight):
    currentHeight(1),
    maxHeight(theMaxHeight)
{
    head = new SkipListNode<Key, Val>(theMaxHeight);
    tail = new SkipListNode<Key, Val>(theMaxHeight);
    for (int i = 0; i < theMaxHeight; ++i) {
        head->next[i] = tail;
    }
}

template <class Key, class Val>
bool SkipList<Key, Val>::insert(const Key &theKey, Val &theValue) {
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
        delete []toUpdate;
        return false;
    }

    // Get a random level for the node to be inserted into.
    level = rand() % maxHeight + 1;
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
        tempNode->prev[i] = toUpdate[i];
        toUpdate[i]->next[i]->prev[i] = tempNode;
        toUpdate[i]->next[i] = tempNode;
    }

    ++_size;

    // Success!
    delete[] toUpdate;
    return true;
}

template <class Key, class Val>
bool SkipList<Key, Val>::erase(const Key theKey) {
    SkipListNode<Key, Val>** toUpdate = new SkipListNode<Key, Val>*[maxHeight+1];
    SkipListNode<Key,Val>* tempNode = head;
    Key compareKey;

    for (int h = currentHeight - 1; h >= 0; --h) {
        if(tempNode->next[h] != tail) {
            compareKey = tempNode->next[h]->getKey();
            while(compareKey < theKey &&
                    tempNode->next[h] != tail) {
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
            // Wire up the pointers.
            toUpdate[i]->next[i] = tempNode->next[i];
            tempNode->next[i]->prev[i] = toUpdate[i];
        }

        delete tempNode;

        // Adjust currentHeight.
        while ((currentHeight > 1) &&
            (head->next[currentHeight-1] == tail)) {
            // If there are no nodes at currentHeight, decrement the value - no need to poke around there.
            --currentHeight;
        }

        --_size;

        // Success!
        delete []toUpdate;
        return true;
    }

    // Node not found - nothing to erase.
    delete []toUpdate;
    return false;
}

template <class Key, class Val>
const Val& SkipList<Key, Val>::find(const Key &theKey) {
    if (empty()) {
        throw ElementNotFoundException<Key>(theKey);
    }

    int h = currentHeight - 1;
    SkipListNode<Key, Val>* tempNode = head;

    for (; h >= 0; --h) {
        while (tempNode->next[h] != tail && tempNode->next[h]->getKey() < theKey) {
            tempNode = tempNode->next[h];
        }

        if (tempNode->getKey() == theKey) {
            // Success!
            return tempNode->getVal();
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

template <class Key, class Val>
typename SkipList<Key, Val>::reverse_iterator SkipList<Key, Val>::rbegin() {
    return SkipList<Key, Val>::reverse_iterator(tail->prev[0]);
}

template <class Key, class Val>
typename SkipList<Key, Val>::reverse_iterator SkipList<Key, Val>::rend() {
    return SkipList<Key, Val>::reverse_iterator(head);
}

template <class Key, class Val>
typename SkipList<Key, Val>::iterator SkipList<Key, Val>::lower_bound(const Key& theKey) {
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

    if(tempNode == tail) {
        throw LowerBoundNotFoundException<Key>(theKey);
    }

    return iterator(tempNode);
}

template <class Key, class Val>
typename SkipList<Key, Val>::iterator SkipList<Key, Val>::upper_bound(const Key& theKey) {
    int h = currentHeight - 1;
    SkipListNode<Key, Val>* tempNode = head;

    if (empty()) {
        throw ElementNotFoundException<Key>(theKey);
    }

    for (; h >= 0; --h) {
        while (tempNode->next[h] != tail && tempNode->next[h]->getKey() <= theKey) {
            tempNode = tempNode->next[h];
        }
    }

    tempNode = tempNode->next[0];

    if(tempNode == tail) {
        throw UpperBoundNotFoundException<Key>(theKey);
    }

    return iterator(tempNode);
}

template <class Key, class Val>
std::pair<typename SkipList<Key, Val>::iterator, typename SkipList<Key, Val>::iterator> SkipList<Key, Val>::equal_range(const Key& theKey) {
    return std::pair<SkipList<Key, Val>::iterator, SkipList<Key, Val>::iterator>(lower_bound(theKey), upper_bound(theKey));
}

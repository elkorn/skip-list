#include "SkipListNode.h"

template <class Key, class Val>
SkipListNode<Key, Val>::SkipListNode(Key* theKey, Val* theVal, int theHeight) {
    nodeHeight = theHeight;
    key = theKey;
    value = theVal;
    next = new SkipListNode<Key, Val>* [nodeHeight+1];
    for(int x = 1; x <= nodeHeight; ++x) next[x] = (SkipListNode<Key, Val>*)0;
}

template <class Key, class Val>
SkipListNode<Key, Val>::SkipListNode(int theHeight):
    nodeHeight(theHeight),
    key((Key*)0),
    value((Val*)0) {
    next = new SkipListNode<Key, Val>*[theHeight+1];
    for(int x = 1; x <= nodeHeight; ++x) next[x] = (SkipListNode<Key, Val>*)0;
}

template <class Key, class Val>
Key* SkipListNode<Key, Val>::getKey() {
    return key;
}

template <class Key, class Val>
Val* SkipListNode<Key, Val>::getVal() {
    return value;
}


template <class Key, class Val>
int SkipListNode<Key, Val>::getHeight() {
    return nodeHeight;
}

template <class Key, class Val>
SkipListNode<Key, Val>::~SkipListNode() {
    delete key;
    delete value;
    delete []next;
}




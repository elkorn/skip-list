template <class Key, class Val>
class SkipList;

template <class Key, class Val>
class SkipListNode {
    public:
        SkipListNode(const Key&, Val&, int);
        // Creates an empty node.
        SkipListNode(int);
        ~SkipListNode();

        const Key& getKey();
        const Val& getVal();
        int getHeight();
        SkipListNode** next;
        SkipListNode** prev;

    private:
        int nodeHeight;
        Key key;
        Val* value;
};

template <class Key, class Val>
SkipListNode<Key, Val>::SkipListNode(const Key &theKey, Val& theVal, int theHeight) {
    nodeHeight = theHeight;
    key = theKey;
    value = &theVal;
    next = new SkipListNode<Key, Val>* [nodeHeight];
    prev = new SkipListNode<Key, Val>* [nodeHeight];
    for(int x = 0; x < nodeHeight; ++x) {
        next[x] = (SkipListNode<Key, Val>*)0;
        prev[x] = (SkipListNode<Key, Val>*)0;
    }
}

template <class Key, class Val>
SkipListNode<Key, Val>::SkipListNode(int theHeight):
    nodeHeight(theHeight),
    key(Key()),
    value((Val*)0) {
    next = new SkipListNode<Key, Val>* [nodeHeight];
    prev = new SkipListNode<Key, Val>* [nodeHeight];
    for(int x = 0; x < nodeHeight; ++x) {
        next[x] = (SkipListNode<Key, Val>*)0;
        prev[x] = (SkipListNode<Key, Val>*)0;
    }
}

template <class Key, class Val>
const Key& SkipListNode<Key, Val>::getKey() {
    return key;
}

template <class Key, class Val>
const Val& SkipListNode<Key, Val>::getVal() {
    return *value;
}


template <class Key, class Val>
int SkipListNode<Key, Val>::getHeight() {
    return nodeHeight;
}

template <class Key, class Val>
SkipListNode<Key, Val>::~SkipListNode() {
    delete []next;
    delete []prev;
}




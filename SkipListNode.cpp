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
        SkipListNode** next;
        SkipListNode** prev;

    private:
        const Key key;
        const int height;
        Val* value;
};

template <class Key, class Val>
SkipListNode<Key, Val>::SkipListNode(const Key &theKey, Val& theVal, const int theHeight):
    key(theKey),
    value(&theVal),
    height(theHeight),
    next(new SkipListNode<Key, Val>* [theHeight]),
    prev(new SkipListNode<Key, Val>* [theHeight]){
}

template <class Key, class Val>
SkipListNode<Key, Val>::SkipListNode(const int theHeight):
    key(Key()),
    value((Val*)0),
    height(theHeight),
    next(new SkipListNode<Key, Val>* [theHeight]),
    prev(new SkipListNode<Key, Val>* [theHeight]){
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
SkipListNode<Key, Val>::~SkipListNode() {
    delete []next;
    delete []prev;
}




template <class Key, class Val>
class SkipList;

template <class Key, class Val>
class SkipListNode {
    public:
        SkipListNode(Key*, Val*, int);
        // Creates an empty node.
        SkipListNode(int);
        ~SkipListNode();

        Key* getKey();
        Val* getVal();
        int getHeight();
        SkipListNode** next;

    private:
        int nodeHeight;
        Key* key;
        Val* value;
};

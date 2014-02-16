template <class Key, class Val>
class SkipList {
    public:
        SkipList(int maxHeight);
        SkipList();
        ~SkipList();

        struct iterator;
        struct reverse_iterator;

        bool insert(const Key&, Val&);
        bool erase(const Key);
        const Val& find(const Key&);
        void print(std::ostream &);
        const bool empty();
        const unsigned int count(const Key&);
        const unsigned int size();

        iterator begin();
        iterator end();
        reverse_iterator rbegin();
        reverse_iterator rend();
        iterator lower_bound(const Key& theKey);
        iterator upper_bound(const Key& theKey);
        std::pair<iterator, iterator> equal_range(const Key& theKey);

    private:
        SkipListNode<Key, Val>* head;
        SkipListNode<Key, Val>* tail;
        int maxHeight;
        int currentHeight;
        unsigned int _size;
        RandomHeight *randomizer;
};

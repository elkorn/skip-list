#include "SkipListNode.cpp"
#include <vector>
#include <utility>

template <class Val>
class SkipList {
    public:
        struct iterator;
        struct reverse_iterator;

        SkipList(int maxHeight);
        SkipList();
        SkipList(iterator first, const iterator last);
        SkipList(const SkipList& other);
        ~SkipList();

        std::pair<bool, iterator> insert(const Val&);
        iterator erase(iterator);
        iterator find(const Val&);
        const bool empty();
        const unsigned int count(const Val&);
        const unsigned int size() const;
        void clear();
        void swap(SkipList &other);
        SkipList& operator=(const SkipList& other);

        iterator begin();
        iterator end();
        reverse_iterator rbegin();
        reverse_iterator rend();
        iterator lower_bound(const Val& theVal);
        iterator upper_bound(const Val& theVal);
        std::pair<iterator, iterator> equal_range(const Val& theVal);

    private:
        SkipListNode<Val>* head;
        SkipListNode<Val>* tail;
        int maxHeight;
        unsigned int currentHeight;
        unsigned int _size;
        std::vector<SkipListNode<Val>*> toUpdate;

        bool isNodeMeaningful(SkipListNode<Val> *node);
        void removeMeaningfulNodes();
        void resetBorderNodes();
        void insertRange(iterator first, iterator last);
};



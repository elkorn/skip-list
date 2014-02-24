#include "ExponentialRandomHeight.cpp"
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
        ~SkipList();

        std::pair<bool, iterator> insert(const Val&);
        iterator erase(const Val&);
        iterator find(const Val&);
        const bool empty();
        const unsigned int count(const Val&);
        const unsigned int size();
        void clear();

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
        int currentHeight;
        unsigned int _size;
        std::vector<SkipListNode<Val>*> toUpdate;
        ExponentialRandomHeight *randomizer;

        bool isNodeMeaningful(SkipListNode<Val> *node);
        void removeMeaningfulNodes();
        void resetBorderNodes();
};

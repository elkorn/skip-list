#include "ExponentialRandomHeight.cpp"
#include "SkipListNode.cpp"
#include <vector>
#include <utility>
#include <list>

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
        iterator erase(const Val&);
        iterator find(const Val&);
        const bool empty();
        const unsigned int count(const Val&);
        const unsigned int size();
        const unsigned int& getCurrentHeight() const;
        void clear();

        SkipList& operator=(const SkipList& other);

        iterator begin();
        iterator end();
        reverse_iterator rbegin();
        reverse_iterator rend();
        iterator lower_bound(const Val& theVal);
        iterator upper_bound(const Val& theVal);
        std::pair<iterator, iterator> equal_range(const Val& theVal);
        std::vector<int> bla;
        std::list<SkipListNode<Val>> list;

        void display();
        void displvl(int l);

    private:
        SkipListNode<Val>* head;
        SkipListNode<Val>* tail;
        int maxHeight;
        unsigned int currentHeight;
        unsigned int _size;
        std::vector<SkipListNode<Val>*> toUpdate;
        ExponentialRandomHeight *randomizer;

        bool isNodeMeaningful(SkipListNode<Val> *node);
        void removeMeaningfulNodes();
        void resetBorderNodes();
        void insertRange(iterator first, iterator last);
};



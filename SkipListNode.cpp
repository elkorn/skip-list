#include "SkipListNode.h"
#include <vector>
template <class Val>
SkipListNode<Val>::SkipListNode(const Val &theVal, const int theHeight):
    value(theVal),
    height(theHeight),
    next(std::vector<SkipListNode *>(theHeight)),
    prev(std::vector<SkipListNode *>(theHeight)) { }

template <class Val>
SkipListNode<Val>::SkipListNode(const int theHeight):
    value(Val()),
    height(theHeight),
    next(std::vector<SkipListNode *>(theHeight)),
    prev(std::vector<SkipListNode *>(theHeight)) { }

template <class Val>
SkipListNode<Val>::SkipListNode(const SkipListNode<Val> &other):
    value(Val(other.value)),
    height(other.height),
    next(std::vector<SkipListNode *>(other.next)),
    prev(std::vector<SkipListNode *>(other.prev)) { }

template <class Val>
const Val &SkipListNode<Val>::getVal()
{
    return value;
}

template <class Val>
const int SkipListNode<Val>::getHeight()
{
    return height;
}

template <class Val>
bool SkipListNode<Val>::valueEquals(const Val &otherVal)
{
    return !(getVal() < otherVal || otherVal < getVal());
}


template <class Val>
SkipListNode<Val>::~SkipListNode()
{
    next.clear();
    prev.clear();
}




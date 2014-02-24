#include "SkipListNode.h"
#include <vector>
template <class Val>
SkipListNode<Val>::SkipListNode(const Val &theVal, const int theHeight):
    value(theVal),
    height(theHeight),
    next(std::vector<SkipListNode *>(theHeight)),
    prev(std::vector<SkipListNode *>(theHeight))
{
    for (int i = 0; i < theHeight; ++i)
    {
        next[i] = 0;
        prev[i] = 0;
    }
}

template <class Val>
SkipListNode<Val>::SkipListNode(const int theHeight):
    value(Val()),
    height(theHeight),
    next(std::vector<SkipListNode *>(theHeight)),
    prev(std::vector<SkipListNode *>(theHeight))
{
    for (int i = 0; i < theHeight; ++i)
    {
        next[i] = 0;
        prev[i] = 0;
    }
}

template <class Val>
SkipListNode<Val>::SkipListNode(const SkipListNode<Val> &other):
    value(Val(other.value)),
    height(other.height)
{
    next.resize(height);
    prev.resize(height);
    for (int i = 0; i < height; ++i)
    {
        if (other.next.at(i) != 0)
        {
            next.at(i) = new SkipListNode(*other.next.at(i));
        }

        if (other.prev.at(i) != 0)
        {
            prev.at(i) = new SkipListNode(*other.prev.at(i));
        }
    }
}

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




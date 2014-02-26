#include <iostream>
#include <list>
#include "SkipList.h"
#include <cmath>

#define DEFAULT_HEIGHT 32

template <class Val>
struct SkipList<Val>::iterator
{
    typedef iterator self_type;
    typedef SkipListNode<Val> value_type;

    iterator(value_type *start)
    {
        current = start;
    }

    self_type operator ++()
    {
        self_type res = *this;
        current = current->next.at(0);
        return res;
    }

    const Val &operator *()
    {
        return current->getVal();
    }

    SkipListNode<Val> *get()
    {
        return current;
    }

    value_type *operator ->()
    {
        return current;
    }

    bool operator==(const self_type &other)
    {
        return current == other.current;
    }

    bool operator!=(const self_type &other)
    {
        return current != other.current;
    }

private:
    SkipListNode<Val> *current;
};

template<class Val>
struct SkipList<Val>::reverse_iterator
{
    typedef reverse_iterator self_type;
    typedef SkipListNode<Val> value_type;

    reverse_iterator(value_type *start)
    {
        current = start;
    }

    self_type operator ++()
    {
        self_type res = *this;
        current = current->prev.at(0);
        return res;
    }

    const Val &operator *()
    {
        return current->getVal();
    }

    value_type *operator ->()
    {
        return current;
    }

    bool operator==(const self_type &other)
    {
        return current == other.current;
    }

    bool operator!=(const self_type &other)
    {
        return current != other.current;
    }

private:
    SkipListNode<Val> *current;
};

template <class Val>
SkipList<Val>::SkipList():
    currentHeight(1),
    maxHeight(DEFAULT_HEIGHT),
    _size(0),
    head(new SkipListNode<Val>(DEFAULT_HEIGHT)),
    tail(new SkipListNode<Val>(DEFAULT_HEIGHT)),
    toUpdate(std::vector<SkipListNode<Val>*>(DEFAULT_HEIGHT))
{
    resetBorderNodes();
}

template <class Val>
SkipList<Val>::SkipList(int theMaxHeight):
    currentHeight(1),
    maxHeight(theMaxHeight),
    _size(0),
    head(new SkipListNode<Val>(theMaxHeight)),
    tail(new SkipListNode<Val>(theMaxHeight)),
    toUpdate(std::vector<SkipListNode<Val>*>(theMaxHeight))
{
    resetBorderNodes();
}

template <class Val>
SkipList<Val>::SkipList(SkipList<Val>::iterator first, const SkipList<Val>::iterator last):
    currentHeight(1),
    maxHeight(DEFAULT_HEIGHT),
    _size(0),
    head(new SkipListNode<Val>(DEFAULT_HEIGHT)),
    tail(new SkipListNode<Val>(DEFAULT_HEIGHT)),
    toUpdate(std::vector<SkipListNode<Val>*>(DEFAULT_HEIGHT))
{
    resetBorderNodes();
    insertRange(first, last);
}

template <class Val>
SkipList<Val>::SkipList(const SkipList<Val> &other):
    currentHeight(1),
    maxHeight(other.maxHeight),
    _size(other._size),
    head(new SkipListNode<Val>(other.maxHeight)),
    tail(new SkipListNode<Val>(other.maxHeight)),
    toUpdate(std::vector<SkipListNode<Val>*>(maxHeight))
{
    resetBorderNodes();
    insertRange(SkipList<Val>::iterator(other.head->next.at(0)), SkipList<Val>::iterator(other.tail));
}

template <class Val>
std::pair<bool, typename SkipList<Val>::iterator> SkipList<Val>::insert(const Val &theVal)
{
    SkipListNode<Val> *tempNode = head;
    SkipListNode<Val> *newNode = 0;

    // Check all the height levels for where to insert the new node.
    for (int h = currentHeight - 1; h >= 0; --h)
    {
        while (tempNode->next.at(h) != tail && tempNode->next.at(h)->getVal() < theVal)
        {
            tempNode = tempNode->next.at(h);
        }

        // This node will have to be updated at level h
        // after inserting the new one.
        toUpdate[h] = tempNode;
    }

    tempNode = tempNode->next.at(0);

    if (isNodeMeaningful(tempNode) && tempNode->valueEquals(theVal))
    {
        // We already have this key in the set - cannot insert.
        return std::pair<bool, typename SkipList<Val>::iterator>(false, SkipList<Val>::iterator(tempNode));
    }

    // Get a random level for the node to be inserted into.
    int level = 1;
    while (rand() % 100 < 50 && level < maxHeight)
    {
        level++;
    }

    if (level > currentHeight)
    {
        // Create all the levels between the previous and new currentHeight
        // and add them to the update matrix.
        for (int i = currentHeight; i < level; ++i)
        {
            toUpdate[i] = head;
        }

        currentHeight = level;
    }

    newNode = new SkipListNode<Val>(theVal, level);

    // Actually insert the node where it belongs.
    for (int i = 0; i < level; ++i)
    {
        newNode->next.at(i) = toUpdate.at(i)->next.at(i);
        newNode->prev.at(i) = toUpdate.at(i);

        toUpdate.at(i)->next.at(i)->prev.at(i) = newNode;
        toUpdate.at(i)->next.at(i) = newNode;
    }

    ++_size;
    return std::pair<bool, typename SkipList<Val>::iterator>(true, SkipList<Val>::iterator(newNode));
}

template <class Val>
typename SkipList<Val>::iterator SkipList<Val>::erase(SkipList<Val>::iterator pos)
{
    SkipListNode<Val> *tempNode = head;
    // Check all the height levels for where to insert the new node.
    for (int h = currentHeight - 1; h >= 0; --h)
    {
        while (tempNode->next.at(h) != tail &&
                tempNode->next.at(h)->getVal() < pos->getVal())
        {
            tempNode = tempNode->next.at(h);
        }

        // This node will have to be updated at level h
        // after inserting the new one.
        // Prealokować toUpdate i tym podobne struktury w konstruktorze całej
        // listy, usuwać w destruktorze.
        toUpdate.at(h) = tempNode;
    }

    // Get the found node at the base level.
    tempNode = tempNode->next.at(0);

    if (isNodeMeaningful(tempNode) &&
            tempNode->valueEquals(pos->getVal()))
    {
        for (int i = 0; i < currentHeight; ++i)
        {
            // The erased node might not exist at this level.
            if (toUpdate.at(i)->next.at(i) != tempNode) break;
            // Wire up the pointers.
            toUpdate.at(i)->next.at(i) = tempNode->next.at(i);
            tempNode->next.at(i)->prev.at(i) = toUpdate.at(i);
        }

        SkipList<Val>::iterator ret = iterator(tempNode->next.at(0));
        delete tempNode;
        tempNode = 0;
        // Adjust currentHeight.
        while ((currentHeight > 1) &&
                (head->next.at(currentHeight - 1) == tail))
        {
            // If there are no nodes at currentHeight, decrement the value -
            // no need to poke around there.
            --currentHeight;
        }

        --_size;

        // Success!
        return ret;
    }

    // Node not found - nothing to erase.
    return end();
}

template <class Val>
typename SkipList<Val>::iterator SkipList<Val>::find(const Val &theVal)
{
    if (empty())
    {
        return end();
    }

    SkipListNode<Val> *tempNode = head;

    for (int h = currentHeight - 1; h >= 0; --h)
    {
        while (tempNode->next.at(h) != tail &&
                tempNode->next.at(h)->getVal() < theVal)
        {
            tempNode = tempNode->next.at(h);
        }
    }

    tempNode = tempNode->next.at(0);

    if (isNodeMeaningful(tempNode))
    {
        if (tempNode->valueEquals(theVal))
        {
            // Success!
            return SkipList<Val>::iterator(tempNode);
        }
    }

    return end();
}

template <class Val>
const bool SkipList<Val>::empty()
{
    return head->next.at(0) == tail;
}

template <class Val>
const unsigned int SkipList<Val>::size() const
{
    // To keep the size operation at O(1), the size is being maintained
    // throughout the lifetime of the list.
    return _size;
}

template <class Val>
void SkipList<Val>::resetBorderNodes()
{
    for (int i = 0; i < maxHeight; ++i)
    {
        head->next.at(i) = tail;
        tail->prev.at(i) = head;
    }
}

template <class Val>
void SkipList<Val>::removeMeaningfulNodes()
{
    SkipListNode<Val> *tempNode = head->next.at(0), *nextNode;
    while (tempNode != 0 && tempNode != tail)
    {
        nextNode = tempNode->next.at(0);
        // if(tempNode != head &&
        //    tempNode->prev.at(0) != NULL) delete tempNode->prev.at(0);
        if (nextNode != 0)          nextNode->prev.at(0) = 0;
        delete tempNode;
        tempNode = 0;
        tempNode = nextNode;
    }
}

template <class Val>
void SkipList<Val>::insertRange(SkipList<Val>::iterator first, SkipList<Val>::iterator last)
{
    for (; first != last; ++first)
    {
        insert(first->getVal());
    }
}

template <class Val>
void SkipList<Val>::clear()
{
    removeMeaningfulNodes();
    resetBorderNodes();
    _size = 0;
    currentHeight = 1;
}

template <class Val>
void SkipList<Val>::swap(SkipList &other)
{
    SkipListNode<Val> *temp = other.head;
    std::vector<SkipListNode<Val> *> tempToUpdate = other.toUpdate;
    int tempMaxHeight = other.maxHeight;
    int tempSize = other._size;
    int tempCurrentHeight = other.currentHeight;

    other.head = head;
    head = temp;
    temp = other.tail;
    other.tail = tail;
    tail = temp;
    other.toUpdate = toUpdate;
    toUpdate = tempToUpdate;

    other.maxHeight = maxHeight;
    maxHeight = tempMaxHeight;
    other._size = _size;
    _size = tempSize;
    other.currentHeight = currentHeight;
    currentHeight = tempCurrentHeight;
}

template <class Val>
SkipList<Val> &SkipList<Val>::operator=(const SkipList &other)
{
    clear();
    insertRange(SkipList<Val>::iterator(other.head->next.at(0)), SkipList<Val>::iterator(other.tail));
}

template <class Val>
const unsigned int SkipList<Val>::count(const Val &theVal)
{
    if (find(theVal) == end()) return 0;
    else return 1;
}

template <class Val>
bool SkipList<Val>::isNodeMeaningful(SkipListNode<Val> *node)
{
    return node != head && node != tail;
}

template <class Val>
SkipList<Val>::~SkipList()
{
    removeMeaningfulNodes();
    delete head;
    head = 0;
    delete tail;
    tail = 0;
}

template <class Val>
typename SkipList<Val>::iterator SkipList<Val>::begin()
{
    return SkipList<Val>::iterator(head->next.at(0));
}

template <class Val>
typename SkipList<Val>::iterator SkipList<Val>::end()
{
    return SkipList<Val>::iterator(tail);
}

template <class Val>
typename SkipList<Val>::reverse_iterator SkipList<Val>::rbegin()
{
    return SkipList<Val>::reverse_iterator(tail->prev.at(0));
}

template <class Val>
typename SkipList<Val>::reverse_iterator SkipList<Val>::rend()
{
    return SkipList<Val>::reverse_iterator(head);
}

template <class Val>
typename SkipList<Val>::iterator SkipList<Val>::lower_bound(const Val &theVal)
{
    int h = currentHeight - 1;
    SkipListNode<Val> *tempNode = head;

    if (empty())
    {
        return end();
    }

    for (; h >= 0; --h)
    {
        while (tempNode->next.at(h) != tail && tempNode->next.at(h)->getVal() < theVal)
        {
            tempNode = tempNode->next.at(h);
        }
    }

    tempNode = tempNode->next.at(0);

    if (tempNode == tail)
    {
        return end();
    }

    return iterator(tempNode);
}

template <class Val>
typename SkipList<Val>::iterator SkipList<Val>::upper_bound(const Val &theVal)
{
    int h = currentHeight - 1;
    SkipListNode<Val> *tempNode = head;

    if (empty())
    {
        return end();
    }

    for (; h >= 0; --h)
    {
        while (tempNode->next.at(h) != tail && tempNode->next.at(h)->getVal() <= theVal)
        {
            tempNode = tempNode->next.at(h);
        }
    }

    tempNode = tempNode->next.at(0);

    if (tempNode == tail)
    {
        return end();
    }

    return iterator(tempNode);
}

template <class Val>
std::pair<typename SkipList<Val>::iterator, typename SkipList<Val>::iterator> SkipList<Val>::equal_range(const Val &theVal)
{
    return std::pair<SkipList<Val>::iterator, SkipList<Val>::iterator>(lower_bound(theVal), upper_bound(theVal));
}

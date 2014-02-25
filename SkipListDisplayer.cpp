#include <iostream>

template <class Val>
class SkipList;

template <class Val>
struct SkipListNode;

class SkipListDisplayer
{
public:
    template<class Val>
    static void display(SkipList<Val> &);
private:
    template<class Val>
    static void displvl(SkipList<Val> &, int l);
};


template<class Val>
void SkipListDisplayer::displvl(SkipList<Val> &skipList, const int l)
{

    SkipListNode<Val> *x = skipList.begin()->prev.at(0)->next.at(l),
                      *tail = skipList.end()->prev.at(0)->next.at(0);

    while (x != tail)    {
        std::cout << x->getVal() << " ";
        x = x->next.at(l);
    }

    std::cout << std::endl;
}

template <class Val>
void SkipListDisplayer::display(SkipList<Val> &skipList)
{
    
    for (int i = 0, h = skipList.end()->getHeight(); i < h; ++i)
    {
        SkipListDisplayer::displvl(skipList, i);
    }
}
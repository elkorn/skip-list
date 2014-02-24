#include <vector>

template <class Val>
class SkipList;

template <class Val>
struct SkipListNode {
    public:
        SkipListNode(const Val&, int);
        // Creates an empty node.
        SkipListNode(int);
        SkipListNode(const SkipListNode&);
        ~SkipListNode();
 
        bool valueEquals(const Val& otherVal);

        const Val& getVal();
        const int getHeight();
        std::vector<SkipListNode*> next;
        std::vector<SkipListNode*> prev;

    private:
        const int height;
        const Val* value;
};
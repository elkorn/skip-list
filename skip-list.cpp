template<typename T>
class SkipList {
    struct SkipListNode {
        const T& _data;
        SkipListNode _next[];

        SkipListNode(const T& data, const int level):
            _data(data),
            _next(new SkipListNode[level+1])
        { }
    };

    private:
        const int _maxLevel;
    SkipListNode _head;

    public:
    SkipList(const int maxLevel):
        _maxLevel(maxLevel)
    {
        _head = new SkipListNode(nullptr, _maxLevel);
        SkipListNode sentinel = new SkipListNode(nullptr, maxLevel);
        for (int i = 0; i <= maxLevel; ++i) {
            _head.next[i] = sentinel;
        }
    }

    T find(T key) {
        SkipListNode current = _head;

        for(int i = _maxLevel; i >= 0; --i) {
            SkipListNode next = current.next[i];
            while (next._data < key) {
                current = next;
                next = current._next[i];
            }

            current = current._next[0];
            if(current.data == key) return current.data;
            else return nullptr;
        }
    }

};

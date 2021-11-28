#include <stdexcept>

//this is the linked list used in the dict, each node of the dicts array is a linked list of this type;


template<typename Key, typename Value>
struct DictListNode{
    Key key;
    Value value;
    DictListNode *next;
};

template<typename KEY, typename VALUE>
class DictList{
    public:
        DictList();
        bool in(KEY key);
        void add(KEY key, VALUE value);
        VALUE get(KEY key);
    private:
        DictListNode<KEY, VALUE> *root;
        DictListNode<KEY, VALUE> *lastBuffer;
        int n;//the length this node;
template <typename Key, typename Value> friend class dict;
};

template<typename KEY, typename VALUE>
DictList<KEY, VALUE>::DictList(){
    n = 0;
}

template<typename KEY, typename VALUE>
bool DictList<KEY, VALUE>::in(KEY key){
    DictListNode<KEY, VALUE> *tmp = root;
    while(tmp != NULL){
        if(tmp->key == key){
            lastBuffer = tmp;
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

template<typename KEY, typename VALUE>
VALUE DictList<KEY, VALUE>::get(KEY key){
    if(in(key))
        return lastBuffer->value;
    return VALUE();
}

template<typename KEY, typename VALUE>
void DictList<KEY, VALUE>::add(KEY key, VALUE value){
    DictListNode<KEY, VALUE> *newnode = new DictListNode<KEY, VALUE>();
    newnode->key = key;
    newnode->value = value;
    newnode->next = root;
    root = newnode;
    n++;
}
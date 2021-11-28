#include "dictlist.hpp"
#include <iostream>
#include <iomanip>
#include <functional>

using namespace std;

#define DEFAULTCAPACITY 100

template<class Key,class Value>
class dict{
    public:
        dict(int cap);
        dict();
        Value get(Key key);
        void set(Key key, Value value);
        void add(Key key, Value value);
        bool find(Key key);
    private:
        int getHash(Key key);
        DictList<Key, Value> **data;
        int len; //the size of the array
        int nkeys; //the number of keys in the array;
        int capacity; //the total capacity of the array;
};

template<class Key, class Value>
dict<Key, Value>::dict(int cap){
    capacity = cap + cap / 2;
    data = new DictList<Key, Value>*[cap];
    len = cap;
    nkeys = 0;
}

template<class Key, class Value>
int dict<Key, Value>::getHash(Key key){
    std::hash<Key> hasher;
    return hasher(key) % len;
}

template<class Key, class Value>
Value dict<Key, Value>::get(Key key){
    int _hash = getHash(key);
    if(data[_hash] != NULL)
        return data[getHash(key)]->get(key);
    return Value();
}

template<class Key, class Value>
void dict<Key, Value>::add(Key key, Value value){
    int _hash = getHash(key);
    if(data[_hash] == NULL)
        data[_hash] = new DictList<Key, Value>();
    data[_hash]->add(key, value);
};

template<class Key, class Value>
void dict<Key, Value>::set(Key key, Value value){
    int _hash = getHash(key);
    if(data[_hash] != nullptr)
        if(data[_hash]->in(key))
            data[_hash]->lastBuffer->value = value;
}

template<class Key, class Value>
bool dict<Key, Value>::find(Key key){
    int _hash = getHash(key);
    if(data[_hash] != NULL)
        return data[_hash]->in(key);
    return false;
}
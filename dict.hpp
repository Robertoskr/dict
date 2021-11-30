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
		Value next();
        DictListNode<Key, Value>* nextNode();
        DictListNode<Key, Value>* getIter();
    private:
        DictListNode<Key, Value>* _next();
        int getHash(Key key);
        DictList<Key, Value> **data;
        int len; //the size of the array
        int nkeys; //the number of keys in the array;
        int capacity; //the total capacity of the array;
		int _next_position; //used for iterating over the dictionary;
};

template<class Key, class Value>
dict<Key, Value>::dict(int cap){
    capacity = cap + cap / 2;
    data = new DictList<Key, Value>*[cap];
    len = cap;
    nkeys = 0;
	_next_position = 0;
}

template<class Key, class Value>
int dict<Key, Value>::getHash(Key key){
    std::hash<Key> hasher;
    return hasher(key) % len;
}

/*
    Basic operations of the dictionary
*/

template<class Key, typename Value>
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
/*
    Functions related to iterating over the dictionary
*/

template<class Key, class Value>
Value dict<Key, Value>::next(){
    /*Return the next value*/
    DictListNode<Key, Value> *__next = _next();
    if(__next)
        return __next->value;
    return Value();
}

template<class Key, class Value>
DictListNode<Key, Value>* dict<Key, Value>::nextNode(){
    /*Return the next DictListNode*/
    return _next();
}


template<class Key, class Value>
DictListNode<Key, Value>* dict<Key, Value>::_next(){
    //search the next node and return it ;
    while(_next_position <= len){
        if(_next_position == len){
            _next_position = 0;
            return nullptr;
        }
        if(data[_next_position] != NULL){
            if(data[_next_position]->hasNextNode()){
                return  data[_next_position]->nextNode();
            }
        }
        _next_position++;
    }
    return nullptr;
}


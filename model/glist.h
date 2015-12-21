#ifndef GLIST_H
#define GLIST_H
#include<iostream>
using namespace std;
template<class T>
class GList{
    friend class iterator;
    friend class const_iterator;

public:
    typedef unsigned int size_type;
    typedef T value_type;

private:
    class Item;
    class SmartP {
    public:
        Item* pointerItem;

        SmartP(Item* =0);
        SmartP(const SmartP&);
        ~SmartP();

        bool operator==(const SmartP&) const;
        bool operator!=(const SmartP&) const;
        SmartP& operator=(const SmartP&);
        Item& operator*() const;
        Item* operator->() const;

        //conversione esplicita da SmartP a bool
        operator bool();
    };
    class Item {
    public:
        value_type info;
        SmartP next;
        Item* previous;
        int references;

        Item();
        Item(const value_type&,SmartP =0);
    };

    SmartP first;
    Item* last;
    size_type dimension;
    //bool ord;

public:
    class iterator {
        friend class GList;
        friend class const_iterator;
    private:
        Item* pointer;

    public:
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);

        value_type& operator*();
        value_type& operator[](int);

        //conversione esplicita da iterator a bool
        operator bool();
    };
    class const_iterator {
        friend class GList;
    private:
        const Item* pointer;

    public:
        const_iterator(iterator =0);

        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;

        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);

        const value_type& operator[](int) const;
        const value_type& operator*() const;

        //conversione esplicita da const_iterator a bool
        operator bool();
    };

    GList();
    GList(size_type);
    GList(size_type, const value_type&);
    //GList(const GList&);
    //~GList();

    size_type size() const;
    bool empty() const;

    iterator begin() const;
    iterator end() const;
    iterator back() const;

    iterator insert(iterator,const value_type&);
    void insert(iterator,size_type,const value_type&);
    iterator erase(iterator);
    iterator erase(iterator,iterator);

    void push_back(const value_type&);
    void pop_back();
    void push_front(const value_type&);
    void pop_front();

    void clear();
    void merge(GList&);
    void reverse();
    void sort();
};

/**
 * SmartP methods
 */
template<class T> GList<T>::SmartP::SmartP(Item* item) : pointerItem(item) {
    if(pointerItem)
        pointerItem->references++;
}

template<class T> GList<T>::SmartP::SmartP(const SmartP& sp) : pointerItem(sp.pointerItem) {
    if(pointerItem)
        pointerItem->references++;
}

template<class T> GList<T>::SmartP::~SmartP() {
    if(pointerItem) {
        pointerItem->references--;
        if(pointerItem->references == 0)
            delete pointerItem;
    }
}

template<class T> bool GList<T>::SmartP::operator==(const SmartP& sp) const {
    return pointerItem == sp.pointerItem;
}

template<class T> bool GList<T>::SmartP::operator!=(const SmartP& sp) const {
    return pointerItem != sp.pointerItem;
}

template<class T> typename GList<T>::SmartP& GList<T>::SmartP::operator=(const SmartP& sp) {
    if(this != &sp) {
        Item* aux = pointerItem;
        pointerItem = sp.pointerItem;
        if(pointerItem)
            pointerItem->references++;
        if(aux) {
            aux->references--;
            if(aux->references == 0)
                delete aux;
        }
    }
    return *this;
}

template<class T> typename GList<T>::Item& GList<T>::SmartP::operator*() const {
    return *pointerItem;
}

template<class T> typename GList<T>::Item* GList<T>::SmartP::operator->() const {
    return pointerItem;
}

template<class T> GList<T>::SmartP::operator bool() {
    return pointerItem != 0;
}

/**
 * Item methods
 */
template<class T> GList<T>::Item::Item() : next(0),previous(0) {}

template<class T> GList<T>::Item::Item(const value_type& value, SmartP sp) : info(value), next(sp), previous(0) {}

/**
 * iterator methods
 */
template<class T> bool GList<T>::iterator::operator==(const iterator& it) const {
    return pointer == it.pointer;
}

template<class T> bool GList<T>::iterator::operator!=(const iterator& it) const {
    return pointer != it.pointer;
}

template<class T> typename GList<T>::iterator& GList<T>::iterator::operator++() {
    if(pointer)
        pointer = (pointer->next).pointerItem;
    return *this;
}

template<class T> typename GList<T>::iterator GList<T>::iterator::operator++(int n) {
    iterator aux = *this;
    if(pointer)
        pointer = (pointer->next).pointerItem;
    return aux;
}

template<class T> typename GList<T>::iterator& GList<T>::iterator::operator--() {
    if(pointer)
        pointer = pointer->previous;
    return *this;
}

template<class T> typename GList<T>::iterator GList<T>::iterator::operator--(int n) {
    iterator aux = *this;
    --(*this);
    return aux;
}

template<class T> T& GList<T>::iterator::operator*() {
    return pointer->info;
}

template<class T> T& GList<T>::iterator::operator[](int n) {
    for(int i = 0; i < n; i++)
        (*this)++;
    return (*this)->info;
}

template<class T> GList<T>::iterator::operator bool() {
    return pointer != 0;
}

/**
 * const_iterator methods
 */
template<class T> GList<T>::const_iterator::const_iterator(iterator it) {
    if(it)
        pointer = it.pointer;
    else
        pointer = 0;
}

template<class T> bool GList<T>::const_iterator::operator==(const const_iterator& it) const {
    return pointer == it.pointer;
}

template<class T> bool GList<T>::const_iterator::operator!=(const const_iterator& it) const {
    return pointer != it.pointer;
}

template<class T> typename GList<T>::const_iterator& GList<T>::const_iterator::operator++() {
    if(pointer)
        pointer = (pointer->next).pointerItem;
    return *this;
}

template<class T> typename GList<T>::const_iterator GList<T>::const_iterator::operator++(int n) {
    const_iterator aux = *this;
    if(pointer)
        pointer = (pointer->next).pointerItem;
    return aux;
}

template<class T> typename GList<T>::const_iterator& GList<T>::const_iterator::operator--() {
    if(pointer)
        pointer = pointer->previous;
    return *this;
}

template<class T> typename GList<T>::const_iterator GList<T>::const_iterator::operator--(int n) {
    const_iterator aux = *this;
    if(pointer)
        pointer = pointer->previous;
    return aux;
}

template<class T> const T& GList<T>::const_iterator::operator*() const {
    return pointer->info;
}

template<class T> const T& GList<T>::const_iterator::operator[](int n) const {
    for(int i = 0; i < n; i++)
        (*this)++;
    return (*this)->info;
}

template<class T> GList<T>::const_iterator::operator bool() {
    return pointer != 0;
}

/**
 * GList methods
 */
template<class T> GList<T>::GList() : last(0), dimension(0) {}

template<class T> GList<T>::GList(size_type n) : dimension(n) {
    if(n>0) {
        first = new Item();
        SmartP sp = first;
        for(size_type i = 1; i < n; i++) {
            SmartP& nextItem = sp.pointerItem->next;
            nextItem = new Item();
            sp = nextItem;
        }
        last = sp.pointerItem;
    }
}

template<class T> GList<T>::GList(size_type n, const value_type& t) : last(0), dimension(0) {}

template<class T> typename GList<T>::size_type GList<T>::size() const {
    return dimension;
}

template<class T> bool GList<T>::empty() const {
    return first == 0;
}

template<class T> typename GList<T>::iterator GList<T>::begin() const {
    iterator aux;
    aux.pointer = first.pointerItem;
    return aux;
}

template<class T> typename GList<T>::iterator GList<T>::end() const {
    iterator aux;
    aux.pointer = 0;
    return aux;
}

template<class T> typename GList<T>::iterator GList<T>::back() const {
    iterator aux;
    aux.pointer = last;
    return aux;
}

template<class T> typename GList<T>::iterator GList<T>::insert(iterator it, const value_type& t) {
    Item* newItem = new Item(t,it.pointer);
    Item* prevItem = last;

    if(it) {
        prevItem = it.pointer->previous;
        it.pointer->previous = newItem;
    }
    else
        last = newItem;
    newItem->previous = prevItem;
    if(prevItem)
        prevItem->next = newItem;
    else
        first = newItem;
    dimension++;

    iterator aux;
    aux.pointer = newItem;
    return aux;
}

template<class T> void GList<T>::insert(iterator it, size_type n, const value_type& t) {
    if(n <= 0)
        return;
    iterator itAux = insert(it,t);
    if(n != 1) {
        iterator itNextNewItem;
        for(size_type i = 1; i < n; i++) {
            itNextNewItem = insert(it,t);
            itAux.pointer->next = itNextNewItem.pointer;
            itAux.pointer = itNextNewItem.pointer;
        }
    }
}

template<class T> typename GList<T>::iterator GList<T>::erase(iterator it) {
    iterator aux;
    if(!it) {
        aux.pointer = 0;
        return aux;
    }
    Item* currentItem = it.pointer;
    Item* previousItem = currentItem->previous;
    Item* nextItem = currentItem->next.pointerItem;
    if(previousItem)
        previousItem->next = nextItem;
    else
        first = nextItem;

    if(nextItem)
        nextItem->previous = previousItem;
    else
        last = previousItem;

    dimension--;
    aux.pointer = nextItem;
    return aux;
}

template<class T> typename GList<T>::iterator GList<T>::erase(iterator itStart, iterator itEnd) {
    iterator i;
    for(i = itStart; i != itEnd;) {
        i = erase(i);
    }
    return i;
}

template<class T> void GList<T>::push_back(const value_type& t) {

}

template<class T> void GList<T>::pop_back() {

}

template<class T> void GList<T>::push_front(const value_type& t) {

}

template<class T> void GList<T>::pop_front() {

}

template<class T> void GList<T>::clear() {
    erase(begin(),end());
}

template<class T> void GList<T>::merge(GList<T>& list) {

}

template<class T> void GList<T>::reverse() {
    if(empty()){
        return;
    }
    SmartP previousItem = 0;
    SmartP currentItem = first;
    SmartP nextItem;
    while(currentItem) {
        nextItem = currentItem->next;
        currentItem->next = previousItem;
        currentItem->previous = nextItem.pointerItem;
        previousItem = currentItem;
        currentItem = nextItem;
    }
    cout<<"fine ciclo"<<endl;
    first = previousItem;
}

template<class T> void GList<T>::sort() {

}

#endif // GLIST_H


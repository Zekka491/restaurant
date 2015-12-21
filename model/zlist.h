#ifndef GLIST_H
#define GLIST_H

template<class T>
class GList{
    friend class iterator;
    friend class const_iterator;
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
        Item* operator*() const;
        Item* operator->() const;

        //conversione esplicita da SmartP a bool
        operator bool();
    };
    class Item {
        T info;
        SmartP next;
        Item* previous;
        int references;

        Item();
        Item(const T&,SmartP =0);
    };

    SmartP first;
    Item* last;
    unsigned int dimension;
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

        T& operator*();
        T& operator[](int);

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

        const T& operator[](int) const;
        const T& operator*() const;

        //conversione esplicita da const_iterator a bool
        operator bool();
    };

    GList();

    unsigned int size();
    bool empty() const;

    iterator begin() const;
    iterator end() const;

    iterator insert(iterator,const T&);
    void insert(iterator,n,const T&);
    iterator erase(iterator);
    iterator erase(iterator,iterator);

    void push_back(const T&);
    void pop_back();
    void push_front(const T&);
    void pop_front();

    void clear();
    void merge(GList<T>&);
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

template<class T> GList<T>::SmartP::SmartP(const SmartP* sp) : pointerItem(sp->pointerItem) {
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
    return pointerItem == p.pointerItem;
}

template<class T> bool GList<T>::SmartP::operator!=(const SmartP& sp) const {
    return pointerItem != p.pointerItem;
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

template<class T> GList<T>::Item::Item(const T& value, SmartP sp) : info(value), next(sp), previous(0) {}

/**
 * iterator methods
 */
template<class T> bool GList<T>::iterator::operator==(const iterator& it) const {
    return pointer == it.pointer;
}

template<class T> bool GList<T>::iterator::operator!=(const iterator& it) const {
    return pointer != it.pointer;
}

template<class T> GList<T>::iterator& GList::iterator::operator++() {
    if(pointer)
        pointer = (pointer->next).pointerItem;
    return *this;
}

template<class T> GList<T>::iterator GList::iterator::operator++(int n) {
    iterator aux = *this;
    if(pointer)
        pointer = (pointer->next).pointerItem;
    return aux;
}

template<class T> GList<T>::iterator& GList::iterator::operator--() {
    if(pointer)
        pointer = pointer->previous;
    return *this;
}

template<class T> GList<T>::iterator GList::iterator::operator--(int n) {
    iterator aux = *this;
    if(pointer)
        pointer = pointer->previous;
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
template<class T> GList<T>::const_iterator(iterator it) {
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

template<class T> GList<T>::const_iterator& GList::const_iterator::operator++() {
    if(pointer)
        pointer = (pointer->next).pointerItem;
    return *this;
}

template<class T> GList<T>::const_iterator GList::const_iterator::operator++(int n) {
    const_iterator aux = *this;
    if(pointer)
        pointer = (pointer->next).pointerItem;
    return aux;
}

template<class T> GList<T>::const_iterator& GList::const_iterator::operator--() {
    if(pointer)
        pointer = pointer->previous;
    return *this;
}

template<class T> GList<T>::const_iterator GList::const_iterator::operator--(int n) {
    const_iterator aux = *this;
    if(pointer)
        pointer = pointer->previous;
    return aux;
}

template<class T> T& GList<T>::const_iterator::operator*() {
    return pointer->info;
}

template<class T> T& GList<T>::const_iterator::operator[](int n) {
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

template<class T> unsigned int GList<T>::size() const {
    return dimension;
}

template<class T> bool GList<T>::empty() const {
    return first == 0;
}

template<class T> GList<T>::iterator GList<T>::begin() const {
    iterator aux;
    aux.pointer = first.pointerItem;
    return aux;
}

template<class T> GList<T>::iterator GList<T>::end() const {
    iterator aux;
    aux.pointer = 0;
    return aux;
}

template<class T> GList<T>::iterator GList<T>::insert(iterator it, const T& t) {
    Item* newItem = new Item(t,it.pointer);
    Item* prevItem = last;

    if(it)
        prevItem = it.pointer->previous;
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

#endif // GLIST_H


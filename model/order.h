#ifndef ORDER_H
#define ORDER_H

#include"glist.h"
#include"orderitem.h"


class Order {
private:
    GList<OrderItem*> items;

public:
    Order();

    void addItem(const OrderItem&);
    void removeItem(const OrderItem&);
    GList<OrderItem*>::iterator findItem(int id);
};

#endif // ORDER_H

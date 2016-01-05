#ifndef ORDER_H
#define ORDER_H

#include"glist.h"
#include"orderitem.h"


class Order {
private:
    GList<OrderItem*> items;

public:

    Order();

    GList<OrderItem*> getItems();
    void addItem(OrderItem*);
    void removeItem(int id);
    GList<OrderItem*>::iterator findItem(int id);
    double getTotal() const;
};

#endif // ORDER_H

#include "order.h"

Order::Order() {}

GList<OrderItem*> Order::getItems() {
    return items;
}

void Order::addItem(OrderItem* item) {
    items.push_back(item);
}

void Order::removeItem(int id) {
    items.erase(findItem(id));
}

GList<OrderItem*>::iterator Order::findItem(int id) {
    GList<OrderItem*>::iterator it;
    for(it = items.begin(); it != items.end(); it++) {
        if((*it)->getId() == id) {
            return it;
        }
    }
    return it;
}

double Order::getTotal() const {
    double total = 0;
    GList<OrderItem*>::iterator it;
    for(it = items.begin(); it != items.end(); it++) {
        total = total + ((*it)->getQuantity()*((*it)->getVarPrice()+(*it)->getFood()->getPrice()));
    }
    return total;
}

void Order::clear() {
    items.clear();
}

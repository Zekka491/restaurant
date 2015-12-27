#include "orderitem.h"

OrderItem::OrderItem(Food* _food) : id(nextId), food(_food), quantity(1) {
    nextId++;
}

OrderItem::OrderItem(Food* _food, int _quantity) : id(nextId), food(_food), quantity(_quantity) {
    nextId++;
}

void OrderItem::setFood(Food* _food) {
    food = _food;
}

Food* OrderItem::getFood() const {
    return food;
}

void OrderItem::setQunatity(int _qunatity) {
    quantity = _qunatity;
}

int OrderItem::getQunatity() const {
    return food;
}

void OrderItem::addChanges(QString change) {
    changes.push_back(change);
}

void OrderItem::removeChanges(QString change) {
    changes.erase(findChanges(change));
}

GList<QString>::iterator OrderItem::findChanges(QString change) const {
    GList<QString>::iterator it;
    for(it = changes.begin(); it != changes.end(); it++) {
        if(*it == change) {
            return it;
        }
    }
    return it;
}

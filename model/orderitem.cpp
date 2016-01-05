#include "orderitem.h"

//static field
int OrderItem::nextId = 1;

OrderItem::OrderItem() : id(nextId), quantity(1) {
    nextId++;
}

OrderItem::OrderItem(Food* _food) : id(nextId), food(_food), quantity(1) {
    varPrice = food->getPrice();
    nextId++;
}

OrderItem::OrderItem(Food* _food, int _quantity) : id(nextId), food(_food), quantity(_quantity) {
    varPrice = food->getPrice();
    nextId++;
}

int OrderItem::getId() const {
    return id;
}

void OrderItem::setFood(Food* _food) {
    food = _food;
}

Food* OrderItem::getFood() const {
    return food;
}

void OrderItem::setQuantity(int _qunatity) {
    quantity = _qunatity;
}

int OrderItem::getQuantity() const {
    return quantity;
}

void OrderItem::setVarPrice(double _varPrice) {
    varPrice = _varPrice;
}

double OrderItem::getVarPrice() const {
    return varPrice;
}

void OrderItem::addChange(QString change) {
    changes.push_back(change);
    if(change[0] == QChar('+')) {
        varPrice = varPrice + 0.20;
    } else {
        varPrice = varPrice - 0.20;
    }
}

void OrderItem::removeChanges(QString change) {
    changes.erase(findChanges(change));
    if(change[0] == QChar('+')) {
        varPrice = varPrice - 0.20;
    } else {
        varPrice = varPrice + 0.20;
    }
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

GList<QString> OrderItem::getChanges() const {
    return changes;
}

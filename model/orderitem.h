#ifndef ORDERITEM_H
#define ORDERITEM_H

#include<QString>
#include"glist.h"
#include"food.h"

class OrderItem {
private:
    int id;
    Food* food;
    int quantity;
    GList<QString> changes;
    double varPrice;

    static int nextId;

public:
    OrderItem();
    OrderItem(Food*);
    OrderItem(Food*,int);

    int getId() const;
    void setFood(Food*);
    Food* getFood() const;
    void setQuantity(int);
    int getQuantity() const;
    void setVarPrice(double);
    double getVarPrice() const;
    void addChange(QString);
    void removeChanges(QString);
    GList<QString>::iterator findChanges(QString) const;
    GList<QString> getChanges() const;
};

#endif // ORDERITEM_H

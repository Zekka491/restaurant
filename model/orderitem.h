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

    static int nextId = 1;

public:
    OrderItem(Food*);
    OrderItem(Food*,int);

    void setFood(Food*);
    Food* getFood() const;
    void setQuantity(int);
    int getQuantity() const;
    void addChanges(QString);
    void removeChanges(QString);
    GList<QString>::iterator findChanges(QString) const;
    GList<QString> getChanges() const;
};

#endif // ORDERITEM_H

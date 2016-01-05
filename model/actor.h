#ifndef ACTOR_H
#define ACTOR_H

#include<QFile>
#include<QJsonDocument>
#include<QJsonArray>
#include"glist.h"
#include"food.h"
#include"dish.h"
#include"beverage.h"
#include"order.h"

class Actor {
private:
    GList<Food*> menu;
    Order order;

public:
    Actor();

    GList<Food*> getMenu() const;
    Order* getOrder();

    GList<Food*>::iterator findFood();

    //void newMenu();
    bool loadMenu();
    bool saveMenu() const;

    void read(const QJsonObject&);
    void write(QJsonObject&) const;

};

#endif // ACTOR_H

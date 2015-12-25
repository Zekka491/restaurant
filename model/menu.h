#ifndef MENU_H
#define MENU_H

#include<QFile>
#include<QJsonDocument>
#include<QJsonArray>
#include"glist.h"
#include"food.h"
#include"dish.h"
#include"beverage.h"

class Menu {
private:
    GList<Food*> menu;

public:
    Menu();

    void newMenu();
    bool loadMenu();
    //bool saveMenu() const;

    void read(const QJsonObject&);
    //void write(QJsonObject&) const;

};

#endif // MENU_H

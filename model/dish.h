#ifndef DISH_H
#define DISH_H

#include<QString>
#include<QJsonObject>
#include"glist.h"
#include"food.h"

#include<iostream>
using namespace std;

class Dish : public Food {
private:
    GList<QString> ingredients;

    //private methods
    GList<QString>::iterator findIngredient(const QString&) const;

public:
    Dish();
    Dish(const QString&, double, const QString&);
    virtual ~Dish();

    //get method
    GList<QString> getIngredients() const;

    //set method
    void setIngredients(const GList<QString>&);

    //edit ingredients method
    void addIngredient(const QString&);
    void removeIngredient(const QString&);
    void editIngredient(const QString&,const QString&);

    void read(const QJsonObject&);
    void write(QJsonObject&) const;

    friend ostream& operator<<(ostream&,const Dish&);
};

#endif // DISH_H

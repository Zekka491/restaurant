#ifndef DISH_H
#define DISH_H

#include<QList>
#include<QString>
#include"glist.h"
#include"food.h"

class Dish : public Food {
private:
    QList<QString> ingredients;

    //private methods
    int findIngredient(const QString&) const;

public:
    Dish(const QString&, float, const QString&);
    virtual ~Dish();

    //get method
    QList<QString> getIngredients() const;

    //set method
    void setIngredients(const QList<QString>&);

    //edit ingredients method
    void addIngredient(const QString&);
    void removeIngredient(const QString&);
    void editIngredient(const QString&,const QString&);

};

#endif // DISH_H

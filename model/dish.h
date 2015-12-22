#ifndef DISH_H
#define DISH_H

#include<QString>
#include"glist.h"
#include"food.h"

class Dish : public Food {
private:
    GList<QString> ingredients;

    //private methods
    GList<QString>::iterator findIngredient(const QString&) const;

public:
    Dish(const QString&, float, const QString&);
    virtual ~Dish();

    //get method
    GList<QString> getIngredients() const;

    //set method
    void setIngredients(const GList<QString>&);

    //edit ingredients method
    void addIngredient(const QString&);
    void removeIngredient(const QString&);
    void editIngredient(const QString&,const QString&);

};

#endif // DISH_H

#ifndef DISH_H
#define DISH_H

#include<QList>
#include<QString>
#include"food.h"

class Dish : public Food {
private:
    QList<QString> ingredients;

    //private methods
    QString* findIngredient(QString) const;

public:
    Dish();
    virtual ~Dish();

    //get method
    QList<QString> getIngredients() const;

    //set method
    void setIngredients(QList<QString>);

    //edit ingredients method
    void addIngredient(QString);
    void removeIngredient(QString);
    void editIngredient(QString,QString);

};

#endif // DISH_H

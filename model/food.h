#ifndef FOOD_H
#define FOOD_H

#include<QString>

/**
 * @brief The Food class
 */
class Food {
private:
    QString name;
    float price;
    QString category;

public:
    Food(QString,float,QString);
    virtual ~Food() = 0;

    //metodi get
    QString getName() const;
    float getPrice() const;
    QString getCategory() const;

    //metodi set
    void setName(QString);
    void setPrice(float);
    void setCategory(QString);

    //overloading operatori
    bool operator==(const Food&) const;
    bool operator!=(const Food&) const;

};

#endif // FOOD_H

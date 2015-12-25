#ifndef FOOD_H
#define FOOD_H

#include<QString>
#include<iostream>
using namespace std;

/**
 * @brief The Food class
 */
class Food {
private:
    QString name;
    double price;
    QString category;

public:
    Food();
    Food(const QString&,double,const QString&);
    virtual ~Food() = 0;

    //metodi get
    QString getName() const;
    double getPrice() const;
    QString getCategory() const;

    //metodi set
    void setName(const QString&);
    void setPrice(double);
    void setCategory(const QString&);

    //overloading operatori
    virtual bool operator==(const Food&) const;
    virtual bool operator!=(const Food&) const;
    virtual bool operator<(const Food&) const;
    virtual bool operator<=(const Food&) const;
    virtual bool operator>(const Food&) const;
    virtual bool operator>=(const Food&) const;

    friend ostream& operator<<(ostream&,const Food&);
};

#endif // FOOD_H

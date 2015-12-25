#ifndef BEVERAGE_H
#define BEVERAGE_H

#include<QJsonObject>
#include"food.h"

class Beverage : public Food {
private:
    double capacity;

public:
    Beverage();
    Beverage(const QString&, double, const QString&, double);
    virtual ~Beverage();

    //get method
    double getCapacity() const;

    //set method
    void setCapacity(double);

    void read(const QJsonObject&);
    void write(QJsonObject&) const;

    friend ostream& operator<<(ostream&,const Beverage&);
};

#endif // BEVERAGE_H

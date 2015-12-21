#ifndef BEVERAGE_H
#define BEVERAGE_H

#include"food.h"

class Beverage : public Food {
private:
    float capacity;

public:
    Beverage(const QString&, float, const QString&, float);
    virtual ~Beverage();

    //get method
    float getCapacity() const;

    //set method
    void setCapacity(float);
};

#endif // BEVERAGE_H

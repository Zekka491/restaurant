#ifndef BEVERAGE_H
#define BEVERAGE_H

#include"food.h"

class Beverage : public Food {
private:
    float capacity;

public:
    Beverage();
    virtual ~Beverage();

    //get method
    float getCapacity() const;

    //set method
    void setCapacity(float);
};

#endif // BEVERAGE_H

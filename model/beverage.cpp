#include "beverage.h"

Beverage::Beverage(const QString& name, float price, const QString& category, float _capacity) : Food(name,price,category), capacity(_capacity) {}

Beverage::~Beverage() {}

float Beverage::getCapacity() const {
    return capacity;
}

void Beverage::setCapacity(float _capacity) {
    capacity = _capacity;
}


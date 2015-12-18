#include "beverage.h"

Beverage::Beverage() : Food("Coca Cola",3,"bibita"), capacity(1) {}

float Beverage::getCapacity() const {
    return capacity;
}

void Beverage::setCapacity(float _capacity) {
    capacity = _capacity;
}

Beverage::~Beverage() {

}

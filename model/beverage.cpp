#include "beverage.h"

Beverage::Beverage() : Food(), capacity(0) {}

Beverage::Beverage(const QString& name, double price, const QString& category, double _capacity) : Food(name,price,category), capacity(_capacity) {}

Beverage::~Beverage() {}

double Beverage::getCapacity() const {
    return capacity;
}

void Beverage::setCapacity(double _capacity) {
    capacity = _capacity;
}

void Beverage::read(const QJsonObject& json) {
    setName(json["name"].toString());
    setPrice(json["price"].toDouble());
    setCategory(json["category"].toString());
    setCapacity(json["capacity"].toDouble());
}

void Beverage::write(QJsonObject& json) const {
    json["name"] = getName();
    json["price"] = getPrice();
    json["category"] = getCategory();
    json["capacity"] = getCapacity();
}

ostream& operator<<(ostream& os, const Beverage& beverage) {
    os << "printBeverage" <<endl;
    os <<beverage.getName().toStdString()<<endl;
    os <<"  Prezzo: "<<beverage.getPrice()<<"€"<<endl;
    os <<"  Categoria: "<<beverage.getCategory().toStdString()<<endl;
    os <<"  Capacità: "<<beverage.getCapacity()<<"lt"<<endl;
    return os;
}

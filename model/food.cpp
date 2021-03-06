#include "food.h"

Food::Food() : name(""), price(0), category("") {}

Food::Food(const QString& _name,double _price,const QString& _category) : name(_name), price(_price), category(_category) {}

Food::~Food() {}

QString Food::getName() const {
    return name;
}

double Food::getPrice() const {
    return price;
}

QString Food::getCategory() const {
    return category;
}

void Food::setName(const QString& _name) {
    name = _name;
}

void Food::setPrice(double _price) {
    price = _price;
}

void Food::setCategory(const QString& _category) {
    category = _category;
}

bool Food::operator==(const Food& food) const {
    return name == food.getName() && price == food.getPrice() && category == food.getCategory();
}

bool Food::operator!=(const Food& food) const {
    return !(name == food.getName() && price == food.getPrice() && category == food.getCategory());
}

bool Food::operator<(const Food& food) const {
    if(category.toLower() < food.getCategory().toLower()) {
        return true;
    } else {
        if(category.toLower() == food.getCategory().toLower()) {
            if(name.toLower() < food.getName().toLower()) {
                return true;
            } else {
                if(name.toLower() == food.getName().toLower()) {
                    if(price < food.getPrice()) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        } else {
            return false;
        }
    }
}

bool Food::operator<=(const Food& food) const {
    return !(*this > food);
}

bool Food::operator>(const Food& food) const {
    if(category.toLower() > food.getCategory().toLower()) {
        return true;
    } else {
        if(category.toLower() == food.getCategory().toLower()) {
            if(name.toLower() > food.getName().toLower()) {
                return true;
            } else {
                if(name.toLower() == food.getName().toLower()) {
                    if(price > food.getPrice()) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        } else {
            return false;
        }
    }
}

bool Food::operator>=(const Food& food) const {
    return !(*this < food);
}

ostream& operator<<(ostream& os, const Food& food) {
    os << "printFood" <<endl;
    os <<food.getName().toStdString()<<endl;
    os <<"  Prezzo: "<<food.getPrice()<<" euro"<<endl;
    os <<"  Categoria: "<<food.getCategory().toStdString()<<endl;
    return os;
}

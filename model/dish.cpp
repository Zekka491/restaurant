#include "dish.h"
#include<QJsonArray>

Dish::Dish() : Food() {}

Dish::Dish(const QString& name, double price, const QString& category) : Food(name,price,category) {}

Dish::~Dish() {
    cout<<endl<<endl<<"~Dish()"<<endl<<endl;
}

//getter & setter
GList<QString> Dish::getIngredients() const {
    return ingredients;
}

void Dish::setIngredients(const GList<QString>& _ingredients) {
    ingredients = _ingredients;
}

void Dish::addIngredient(const QString& ingredientToAdd) {
    if(!findIngredient(ingredientToAdd))
        ingredients.push_back(ingredientToAdd);
}

void Dish::removeIngredient(const QString& ingredientToRemove) {
    GList<QString>::iterator itIngredient = findIngredient(ingredientToRemove);
    if(itIngredient)
        ingredients.erase(itIngredient);
}

void Dish::editIngredient(const QString& oldIngredient, const QString& newIngredient) {
    GList<QString>::iterator itIngredient = findIngredient(oldIngredient);
    if(itIngredient)
        *itIngredient = newIngredient;
}

GList<QString>::iterator Dish::findIngredient(const QString& ingredientToFind) const{
    GList<QString>::iterator it = ingredients.begin();
    while(it != ingredients.end()) {
        if(*it == ingredientToFind)
            return it;
        it++;
    }
    return it;
}

void Dish::read(const QJsonObject& json) {
    setName(json["name"].toString());
    setPrice(json["price"].toDouble());
    setCategory(json["category"].toString());
    QJsonArray jIngredients = json["ingredients"].toArray();
    for(int i = 0; i < jIngredients.size(); i++) {
        addIngredient(jIngredients[i].toString());
    }
}

void Dish::write(QJsonObject& json) const {
    json["name"] = getName();
    json["price"] = getPrice();
    json["category"] = getCategory();
    QJsonArray jIngredients;
    for(GList<QString>::iterator it = ingredients.begin(); it != ingredients.end(); it++) {
        jIngredients.append(*it);
    }
    json["ingredients"] = jIngredients;
}

ostream& operator<<(ostream& os, const Dish& dish) {
    os << "printDish" <<endl;
    os <<dish.getName().toStdString()<<endl;
    os <<"  Prezzo: "<<dish.getPrice()<<"€"<<endl;
    os <<"  Categoria: "<<dish.getCategory().toStdString()<<endl;
    GList<QString>::iterator it;
    os <<"  Ingredienti:"<<endl;
    for(it = dish.ingredients.begin(); it != dish.getIngredients().end(); it++)
        os <<"    - "<<(*it).toStdString()<<endl;
    return os;
}


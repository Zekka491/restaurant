#include "dish.h"

Dish::Dish(const QString& name, float price, const QString& category) : Food(name,price,category) {}

Dish::~Dish() {}

//getter & setter
GList<QString> Dish::getIngredients() const {
    return ingredients;
}

void Dish::setIngredients(const GList<QString>& _ingredients) {
    ingredients = _ingredients;
}

/**
 * this method attempts if the value is already in the list of ingredients
 * if not present adds the value at the end of the list
 *
 * @brief Dish::addIngredient
 * @param ingredientToAdd   name of the ingredient to add
 */
void Dish::addIngredient(const QString& ingredientToAdd) {
    if(findIngredient(ingredientToAdd) == -1)
        ingredients.push_back(ingredientToAdd);
}

/**
 * this method attempts if the value is in the list of ingredients
 * if present removes the value from the list
 *
 * @brief Dish::removeIngredient
 * @param ingredientToRemove    name of the ingredient to remove
 */
void Dish::removeIngredient(const QString& ingredientToRemove) {
    GList<QString>::iterator itIngredient = findIngredient(ingredientToRemove);
    if(itIngredient)
        ingredients.erase(itIngredient);
}

/**
 * this method attempts if the value is in the list of ingredients
 * if present changes the value with a new value
 *
 * @brief Dish::editIngredient
 * @param oldIngredient     name of the ingredient to change
 * @param newIngredient     new name of the ingredients
 */
void Dish::editIngredient(const QString& oldIngredient, const QString& newIngredient) {
    GList<QString>::iterator itIngredient = findIngredient(oldIngredient);
    if(itIngredient)
        *itIngredient = newIngredient;
}

/**
 * this method attempts if a value is in the list
 * if present returns the index value
 * if not present returns -1
 *
 * @brief Dish::findIngredient
 * @param ingredientToFind
 * @return      ex of QString with specified value,
 *              0 otherwise
 */
GList<QString>::iterator Dish::findIngredient(const QString& ingredientToFind) const{
    GList<QString>::iterator it = ingredients.begin();
    while(it != ingredients.end()) {
        if(*it == ingredientToFind)
            return it;
        it++;
    }
    return it;
}


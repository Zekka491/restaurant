#include "actor.h"
#include <QMessageBox>

Actor::Actor() {
    if(!loadMenu()) {
        QMessageBox error;
        error.critical(0,"File non trovato","File menu non trovato");
    }
}

GList<Food*> Actor::getMenu() const {
    return menu;
}

Order* Actor::getOrder() {
    return &order;
}

GList<Food*>::iterator Actor::findFood(Food* food) {
    GList<Food*>::iterator it;
    for(it = menu.begin(); it != menu.end(); it++) {
        if((*it) == food) {
            return it;
        }
    }

    return it;
}

void Actor::addFood(Food* food) {
    GList<Food*>::iterator it;
    for(it = menu.begin(); it != menu.end(); it++) {
        if(*food < **it) {
            menu.insert(it,food);
            break;
        }
    }
    if(it == menu.end())
        menu.push_back(food);
    saveMenu();
}

void Actor::removeFood(Food* food) {
    menu.erase(findFood(food));
    saveMenu();
}

bool Actor::loadMenu() {
    QFile loadFile(QStringLiteral("json/menu.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());
    loadFile.close();
    return true;
}

bool Actor::saveMenu() const {
    QFile saveFile(QStringLiteral("json/menu.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    saveFile.resize(0);
    QJsonObject menuObject;
    write(menuObject);
    QJsonDocument saveDoc(menuObject);
    saveFile.write(saveDoc.toJson());
    saveFile.close();
    return true;
}

void Actor::read(const QJsonObject& json) {
    menu.clear();
    QJsonArray newMenu = json["menu"].toArray();
    for (int i = 0; i < newMenu.size(); i++) {
        QJsonObject foodObject = newMenu[i].toObject();
        Food* food;
        if(!foodObject.contains("capacity")) {
            Dish* dish = new Dish();
            dish->read(foodObject);
            food = dish;
        } else {
            Beverage* beverage = new Beverage();
            beverage->read(foodObject);
            food = beverage;
        }
        menu.push_back(food);
    }
}

void Actor::write(QJsonObject& json) const {
    QJsonArray menuArray;
    GList<Food*>::iterator it;
    for(it = menu.begin(); it != menu.end(); it++) {
        QJsonObject foodObject;
        if(dynamic_cast<Dish*>(*it)) {
            Dish* dish = static_cast<Dish*>(*it);
            dish->write(foodObject);
        } else {
            Beverage* beverage = static_cast<Beverage*>(*it);
            beverage->write(foodObject);
        }
        menuArray.append(foodObject);
    }
    json["menu"] = menuArray;
}

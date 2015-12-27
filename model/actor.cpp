#include "actor.h"

Actor::Actor() {}

GList<Food*> Actor::getMenu() const {
    return menu;
}

bool Actor::loadMenu() {
    QFile loadFile(QStringLiteral("C:/Users/Mattia/Documents/Università/p2/progetto15-16/ristorante/json/menu.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());

    return true;
}

bool Actor::saveMenu() const {
    QFile saveFile(QStringLiteral("C:/Users/Mattia/Documents/Università/p2/progetto15-16/ristorante/json/menu.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject menuObject;
    write(menuObject);
    QJsonDocument saveDoc(menuObject);
    saveFile.write(saveDoc.toJson());

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

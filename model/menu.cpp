#include "menu.h"

Menu::Menu() {

}

bool Menu::loadMenu() {
    QFile loadFile(QStringLiteral("json/menu.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());

    return true;
}

/*bool Menu::saveMenu() const
{
    QFile saveFile(QStringLiteral("save.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());

    return true;
}*/

void Menu::read(const QJsonObject& json)
{
    menu.clear();
    QJsonArray newMenu = json["menu"].toArray();
    for (int i = 0; i < newMenu.size(); i++) {
        QJsonObject foodObject = newMenu[i].toObject();
        Food* food;
        if(foodObject["capacity"].toDouble()) {
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

/*void Menu::write(QJsonObject& json) const
{
    QJsonObject playerObject;
    mPlayer.write(playerObject);
    json["player"] = playerObject;

    QJsonArray levelArray;
    foreach (const Level level, mLevels) {
        QJsonObject levelObject;
        level.write(levelObject);
        levelArray.append(levelObject);
    }
    json["levels"] = levelArray;
}*/

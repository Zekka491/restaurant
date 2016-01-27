#ifndef NEWFOODWIDGET_H
#define NEWFOODWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QCloseEvent>
#include "actor.h"
#include "glist.h"
#include "changeitem.h"

class NewFoodWidget : public QWidget {
    Q_OBJECT
public:
    explicit NewFoodWidget(Actor*,QWidget *parent = 0);
    explicit NewFoodWidget(Actor*,Food*,QWidget *parent = 0);

signals:
    void sendNewFood(Food*);
    void closeNewFood(bool);

public slots:
    void newDish();
    void newBeverage();
    void showAddWidget();
    void addIngredient(QString*);
    void removeIngredient(const QString&);
    void saveDish();
    void saveBeverage();

private:
    Actor* actor;

    Food* food;
    Dish* dish;
    Beverage* beverage;

    QHBoxLayout* mainButtonsLayout;
    QPushButton* dishBtn;
    QPushButton* beverageBtn;

    QVBoxLayout* mainLayout;

    QGroupBox* nameGB;
    QHBoxLayout* nameLayout;
    QLabel* nameLbl;
    QLineEdit* nameTxt;
    QGroupBox* priceGB;
    QHBoxLayout* priceLayout;
    QLabel* priceLbl;
    QLineEdit* priceTxt;
    QGroupBox* categoryGB;
    QHBoxLayout* categoryLayout;
    QLabel* categoryLbl;
    QLineEdit* categoryTxt;

    QGroupBox* buttonsGB;
    QPushButton* submitBtn;
    QPushButton* cancelBtn;

    //dish
    QGroupBox* ingredientsGB;
    QVBoxLayout* ingredientsLayout;
    QGroupBox* newIngredientsGB;
    QHBoxLayout* newIngredientsLayout;
    QPushButton* newIngredientBtn;
    QGroupBox* showIngredientsGB;
    QVBoxLayout* showIngredientsLayout;
    QScrollArea* scroll;
    GList<ChangeItem*> ingredientsList;


    //beverage
    QGroupBox* capacityGB;
    QHBoxLayout* capacityLayout;
    QLabel* capacityLbl;
    QLineEdit* capacityTxt;


    void saveFood(Food*);
    void dishLayout(Dish*);
    void beverageLayout(Beverage*);
    void standardLayout(Food*);
    void clearLayout();
    void showIngredientsList();
    void showIngredient(QString*);

    void closeEvent(QCloseEvent*);

};

#endif // NEWFOODWIDGET_H

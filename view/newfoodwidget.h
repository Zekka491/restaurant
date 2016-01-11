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
#include "actor.h"
#include "glist.h"
#include "changeitem.h"

class NewFoodWidget : public QWidget {
    Q_OBJECT
public:
    explicit NewFoodWidget(Actor*,QWidget *parent = 0);

signals:
    void sendNewFood(Food*);

public slots:
    void dishLayout();
    void beverageLayout();
    void showAddWidget();
    void addIngredient(QString*);
    void removeIngredient(const QString&);
    void saveDish();

private:
    Actor* actor;
    //Food* food;
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
    /*QGroupBox* categoryGB;
    QHBoxLayout* categoryLayout;
    QLabel* categoryLbl;
    QLineEdit* categoryTxt;*/


    void saveFood(Food*);
    void standardLayout();
    void clearLayout();
    void showIngredientsList();

};

#endif // NEWFOODWIDGET_H

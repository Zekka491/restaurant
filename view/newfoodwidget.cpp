#include "newfoodwidget.h"

NewFoodWidget::NewFoodWidget(Actor* _actor, QWidget *parent) : actor(_actor), QWidget(parent) {
    mainButtonsLayout = new QHBoxLayout;

    dishBtn = new QPushButton("|||\n|||\n--\n |\n |\n\nDish");
    beverageBtn = new QPushButton("\\/\n | \n--\nBeverage");
    dishBtn->setMaximumWidth(170);
    beverageBtn->setMaximumWidth(170);
    connect(dishBtn,SIGNAL(clicked()),this,SLOT(dishLayout()));
    connect(beverageBtn,SIGNAL(clicked()),this,SLOT(beverageLayout()));
    mainButtonsLayout->addWidget(dishBtn);
    mainButtonsLayout->addWidget(beverageBtn);
    setMinimumSize(300,500);
    setMaximumSize(300,500);
    resize(300,500);
    move(100,100);
    setLayout(mainButtonsLayout);
}

void NewFoodWidget::dishLayout() {
    clearLayout();
    dish = new Dish();
    mainLayout = new QVBoxLayout;
    standardLayout();

    ingredientsGB = new QGroupBox;
    ingredientsLayout = new QVBoxLayout;

    newIngredientsGB = new QGroupBox;
    newIngredientsLayout = new QHBoxLayout;
    newIngredientBtn = new QPushButton("Add");
    connect(newIngredientBtn,SIGNAL(clicked(bool)),this,SLOT(showAddWidget()));
    newIngredientBtn->setMaximumWidth(100);
    newIngredientsLayout->addWidget(new QLabel("Ingredients:"),10,Qt::AlignLeft);
    newIngredientsLayout->addWidget(newIngredientBtn,10,Qt::AlignRight);
    newIngredientsGB->setLayout(newIngredientsLayout);

    showIngredientsGB = new QGroupBox;
    showIngredientsLayout = new QVBoxLayout;
    showIngredientsLayout->addWidget(new QLabel("Ingredients list empty"),10);
    showIngredientsLayout->addWidget(new QLabel,90);
    showIngredientsGB->setLayout(showIngredientsLayout);
    scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setWidget(showIngredientsGB);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    ingredientsLayout->addWidget(newIngredientsGB,10);
    ingredientsLayout->addWidget(scroll,90);
    ingredientsGB->setLayout(ingredientsLayout);
    mainLayout->addWidget(ingredientsGB,90);


    mainLayout->addWidget(buttonsGB,10);
    setLayout(mainLayout);
}


void NewFoodWidget::beverageLayout() {
    clearLayout();
    mainLayout = new QVBoxLayout;
    standardLayout();


    mainLayout->addWidget(buttonsGB,10);
    setLayout(mainLayout);
}

void NewFoodWidget::standardLayout() {
    nameGB = new QGroupBox;
    nameLayout = new QHBoxLayout;
    nameLbl = new QLabel("Name");
    nameTxt = new QLineEdit;
    nameLbl->setMinimumWidth(50);
    nameTxt->setMinimumWidth(80);
    nameLayout->addWidget(nameLbl,10,Qt::AlignLeft);
    nameLayout->addWidget(nameTxt,90,Qt::AlignLeft);
    nameGB->setLayout(nameLayout);

    priceGB = new QGroupBox;
    priceLayout = new QHBoxLayout;
    priceLbl = new QLabel("Price");
    priceTxt = new QLineEdit;
    priceTxt->setValidator(new QRegExpValidator(QRegExp("^(0|[1-9]{1,1}[0-4]{0,9})[.]{1,1}(0|[0-9]{1,2})$"),this));
    priceLbl->setMinimumWidth(50);
    priceTxt->setMinimumWidth(80);
    priceLayout->addWidget(priceLbl,10,Qt::AlignLeft);
    priceLayout->addWidget(priceTxt,90,Qt::AlignLeft);
    priceGB->setLayout(priceLayout);

    categoryGB = new QGroupBox;
    categoryLayout = new QHBoxLayout;
    categoryLbl = new QLabel("Category");
    categoryTxt = new QLineEdit;
    categoryLbl->setMinimumWidth(50);
    categoryTxt->setMinimumWidth(80);
    categoryLayout->addWidget(categoryLbl,10,Qt::AlignLeft);
    categoryLayout->addWidget(categoryTxt,90,Qt::AlignLeft);
    categoryGB->setLayout(categoryLayout);

    mainLayout->addWidget(nameGB,10);
    mainLayout->addWidget(priceGB,10);
    mainLayout->addWidget(categoryGB,10);

    buttonsGB = new QGroupBox;
    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    cancelBtn = new QPushButton("Cancel");
    submitBtn = new QPushButton("Save");
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(submitBtn,SIGNAL(clicked()),this,SLOT(saveDish()));
    buttonsLayout->addWidget(cancelBtn);
    buttonsLayout->addWidget(submitBtn);
    buttonsGB->setLayout(buttonsLayout);
}

void NewFoodWidget::showAddWidget() {
    AddChange* newItem = new AddChange(1);
    newItem->show();

    connect(newItem,SIGNAL(sendNewChange(QString*)),this,SLOT(addIngredient(QString*)));
}

void NewFoodWidget::addIngredient(QString* myString) {
    QWidget* child;
    if(ingredientsList.empty()) {
        child = showIngredientsLayout->takeAt(0)->widget();
        showIngredientsLayout->removeWidget(child);
        delete(child);
    }
    child = showIngredientsLayout->takeAt(showIngredientsLayout->count()-1)->widget();
    showIngredientsLayout->removeWidget(child);
    delete(child);
    dish->addIngredient(*myString);
    ingredientsList.push_back(new ChangeItem(myString));
    connect(*ingredientsList.back(),SIGNAL(sendDeleteChange(QString)),this,SLOT(removeIngredient(const QString&)));
    showIngredientsLayout->addWidget(*ingredientsList.back(),10);
    showIngredientsLayout->addWidget(new QLabel,90);
}

void NewFoodWidget::removeIngredient(const QString& string) {
    int itCI = 0;
    GList<ChangeItem*>::iterator itLbl = ingredientsList.begin();
    GList<QString>::iterator itOI;
    for(itOI = dish->getIngredients().begin(); itOI != dish->getIngredients().end(); itOI++) {
        if(*itOI == string) {

            QWidget* child = showIngredientsLayout->takeAt(itCI)->widget();
            showIngredientsLayout->removeWidget(child);
            delete(child);
            ingredientsList.erase(itLbl);
            dish->removeIngredient(string);
            if(dish->getIngredients().size() == 0) {
                child = showIngredientsLayout->takeAt(0)->widget();
                showIngredientsLayout->removeWidget(child);
                delete(child);
            }

            if(ingredientsList.empty()) {
                showIngredientsLayout->addWidget(new QLabel("No changes"),10);
                showIngredientsLayout->addWidget(new QLabel,90);
            }
            return;
        }
        itCI++;
        itLbl++;
    }
}

void NewFoodWidget::saveDish() {
    if(nameTxt->text().isEmpty() || priceTxt->text().isEmpty() || categoryTxt->text().isEmpty()) {
        QMessageBox error;
        error.critical(0,"Complete fields","Name, price and category fields are required");
    } else {
        dish->setName(nameTxt->text());
        dish->setPrice((priceTxt->text().remove(QChar('.')).toDouble())/100);
        dish->setCategory(categoryTxt->text());
        saveFood(dish);
    }
}

void NewFoodWidget::saveFood(Food* food) {
    emit sendNewFood(food);
    close();
}

void NewFoodWidget::clearLayout() {
    QWidget* child;
    for(int i = 0; i < mainButtonsLayout->count();) {
        child = mainButtonsLayout->takeAt(i)->widget();
        mainButtonsLayout->removeWidget(child);
        delete(child);
    }
    delete mainButtonsLayout;
}

#include "newfoodwidget.h"

NewFoodWidget::NewFoodWidget(Actor* _actor, QWidget *parent) : actor(_actor), QWidget(parent) {
    mainButtonsLayout = new QHBoxLayout;

    QPixmap pDish;
    QPixmap pBeverage;
    dishBtn = new QPushButton("\nDish\n");
    beverageBtn = new QPushButton("\nBeverage\n");
    if(pDish.load("resources/dish.png") && pBeverage.load("resources/beverage.png")) {
        dishBtn->setIcon(QIcon(pDish));
        dishBtn->setIconSize(QSize(65,65));
        beverageBtn->setIcon(QIcon(pBeverage));
        beverageBtn->setIconSize(QSize(65,65));
    }
    dishBtn->setMaximumWidth(170);
    beverageBtn->setMaximumWidth(170);
    connect(dishBtn,SIGNAL(clicked()),this,SLOT(newDish()));
    connect(beverageBtn,SIGNAL(clicked()),this,SLOT(newBeverage()));
    mainButtonsLayout->addWidget(dishBtn);
    mainButtonsLayout->addWidget(beverageBtn);
    setMinimumSize(300,500);
    setMaximumSize(300,500);
    resize(300,500);
    move(100,100);
    setLayout(mainButtonsLayout);
}

NewFoodWidget::NewFoodWidget(Actor* _actor, Food* _food, QWidget *parent) : actor(_actor), food(_food), QWidget(parent) {
    mainButtonsLayout = new QHBoxLayout;
    setLayout(mainButtonsLayout);
    setMinimumSize(300,500);
    setMaximumSize(300,500);
    resize(300,500);
    move(100,100);
    if(dynamic_cast<Dish*>(food)) {
        dishLayout(static_cast<Dish*>(food));
    } else {
        beverageLayout(static_cast<Beverage*>(food));
    }
}

void NewFoodWidget::dishLayout(Dish* _dish) {
    clearLayout();
    dish = _dish;
    mainLayout = new QVBoxLayout;
    standardLayout(dish);

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
    showIngredientsLayout->addWidget(new QLabel("List ingredients empty"),10);
    showIngredientsLayout->addWidget(new QLabel,90);
    showIngredientsList();
    showIngredientsGB->setLayout(showIngredientsLayout);
    scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setWidget(showIngredientsGB);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    ingredientsLayout->addWidget(newIngredientsGB,10);
    ingredientsLayout->addWidget(scroll,90);
    ingredientsGB->setLayout(ingredientsLayout);

    buttonsGB = new QGroupBox;
    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    cancelBtn = new QPushButton("Cancel");
    submitBtn = new QPushButton("Save");
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(submitBtn,SIGNAL(clicked()),this,SLOT(saveDish()));
    buttonsLayout->addWidget(cancelBtn);
    buttonsLayout->addWidget(submitBtn);
    buttonsGB->setLayout(buttonsLayout);

    mainLayout->addWidget(ingredientsGB,90);
    mainLayout->addWidget(buttonsGB,10);
    setLayout(mainLayout);
}


void NewFoodWidget::beverageLayout(Beverage* _beverage) {
    clearLayout();
    beverage = _beverage;
    mainLayout = new QVBoxLayout;
    standardLayout(beverage);

    capacityGB = new QGroupBox;
    capacityLayout = new QHBoxLayout;
    capacityLbl = new QLabel("Capacity");
    capacityTxt = new QLineEdit(QString::number(beverage->getCapacity(),'f',2));
    capacityLbl->setMinimumWidth(50);
    capacityTxt->setMinimumWidth(80);
    capacityTxt->setValidator(new QRegExpValidator(QRegExp("^(0|[1-9]{1,1}[0-9]{0,2})[.]{0,1}(0|[0-9]{0,2})$"),this));
    capacityLayout->addWidget(capacityLbl,10,Qt::AlignLeft);
    capacityLayout->addWidget(capacityTxt,90,Qt::AlignLeft);
    capacityLayout->addWidget(new QLabel("L"),40,Qt::AlignLeft);
    capacityGB->setLayout(capacityLayout);

    buttonsGB = new QGroupBox;
    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    cancelBtn = new QPushButton("Cancel");
    submitBtn = new QPushButton("Save");
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(submitBtn,SIGNAL(clicked()),this,SLOT(saveBeverage()));
    buttonsLayout->addWidget(cancelBtn);
    buttonsLayout->addWidget(submitBtn);
    buttonsGB->setLayout(buttonsLayout);

    mainLayout->addWidget(capacityGB,10);
    mainLayout->addWidget(new QLabel,90);
    mainLayout->addWidget(buttonsGB,10);
    setLayout(mainLayout);
}

void NewFoodWidget::standardLayout(Food* _food) {
    nameGB = new QGroupBox;
    nameLayout = new QHBoxLayout;
    nameLbl = new QLabel("Name");
    nameTxt = new QLineEdit(_food->getName());
    nameLbl->setMinimumWidth(50);
    nameTxt->setMinimumWidth(80);
    nameLayout->addWidget(nameLbl,10,Qt::AlignLeft);
    nameLayout->addWidget(nameTxt,90,Qt::AlignLeft);
    nameGB->setLayout(nameLayout);

    priceGB = new QGroupBox;
    priceLayout = new QHBoxLayout;
    priceLbl = new QLabel("Price");
    priceTxt = new QLineEdit(QString::number(_food->getPrice(),'f',2));
    priceTxt->setValidator(new QRegExpValidator(QRegExp("^(0|[1-9]{1,1}[0-9]{0,9})[.]{0,1}(0|[0-9]{0,2})$"),this));
    priceLbl->setMinimumWidth(50);
    priceTxt->setMinimumWidth(80);
    priceLayout->addWidget(priceLbl,10,Qt::AlignLeft);
    priceLayout->addWidget(priceTxt,90,Qt::AlignLeft);
    priceLayout->addWidget(new QLabel("€"),40,Qt::AlignLeft);
    priceGB->setLayout(priceLayout);

    categoryGB = new QGroupBox;
    categoryLayout = new QHBoxLayout;
    categoryLbl = new QLabel("Category");
    categoryTxt = new QLineEdit(_food->getCategory());
    categoryLbl->setMinimumWidth(50);
    categoryTxt->setMinimumWidth(80);
    categoryLayout->addWidget(categoryLbl,10,Qt::AlignLeft);
    categoryLayout->addWidget(categoryTxt,90,Qt::AlignLeft);
    categoryGB->setLayout(categoryLayout);

    mainLayout->addWidget(nameGB,10);
    mainLayout->addWidget(priceGB,10);
    mainLayout->addWidget(categoryGB,10);
}

void NewFoodWidget::showAddWidget() {
    AddChange* newItem = new AddChange(1);
    newItem->show();

    connect(newItem,SIGNAL(sendNewChange(QString*)),this,SLOT(addIngredient(QString*)));
}

void NewFoodWidget::addIngredient(QString* myString) {
    showIngredient(myString);

    dish->addIngredient(*myString);
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
        if(!priceTxt->text().contains(QChar('.'))) {
            dish->setPrice(priceTxt->text().toDouble());
        } else {
            if(priceTxt->text().indexOf(QChar('.')) == priceTxt->text().size()-2) {
                dish->setPrice((priceTxt->text().remove(QChar('.')).toDouble())/10);
            } else {
                dish->setPrice((priceTxt->text().remove(QChar('.')).toDouble())/100);
            }
        }
        dish->setCategory(categoryTxt->text().toLower());
        saveFood(dish);
    }
}

void NewFoodWidget::saveBeverage() {
    if(nameTxt->text().isEmpty() || priceTxt->text().isEmpty() || categoryTxt->text().isEmpty() || capacityTxt->text().isEmpty()) {
        QMessageBox error;
        error.critical(0,"Complete fields","Name, price, category and capacity fields are required");
    } else {
        beverage->setName(nameTxt->text());

        if(!priceTxt->text().contains(QChar('.'))) {
            beverage->setPrice(priceTxt->text().toDouble());
        } else {
            if(priceTxt->text().indexOf(QChar('.')) == priceTxt->text().size()-2) {
                beverage->setPrice((priceTxt->text().remove(QChar('.')).toDouble())/10);
            } else {
                beverage->setPrice((priceTxt->text().remove(QChar('.')).toDouble())/100);
            }
        }
        beverage->setCategory(categoryTxt->text().toLower());
        if(!capacityTxt->text().contains(QChar('.'))) {
            beverage->setCapacity(capacityTxt->text().toDouble());
        } else {
            if(capacityTxt->text().indexOf(QChar('.')) == capacityTxt->text().size()-2) {
                beverage->setCapacity((capacityTxt->text().remove(QChar('.')).toDouble())/10);
            } else {
                beverage->setCapacity((capacityTxt->text().remove(QChar('.')).toDouble())/100);
            }
        }
        saveFood(beverage);
    }
}

void NewFoodWidget::newDish() {
    dishLayout(new Dish());
}

void NewFoodWidget:: newBeverage() {
    beverageLayout(new Beverage());
}

void NewFoodWidget::saveFood(Food* _food) {
    emit sendNewFood(_food);
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

void NewFoodWidget::showIngredient(QString* myString) {
    QWidget* child;
    if(ingredientsList.empty()) {
        child = showIngredientsLayout->takeAt(0)->widget();
        showIngredientsLayout->removeWidget(child);
        delete(child);
    }
    child = showIngredientsLayout->takeAt(showIngredientsLayout->count()-1)->widget();
    showIngredientsLayout->removeWidget(child);
    delete(child);

    ingredientsList.push_back(new ChangeItem(myString));
    connect(*ingredientsList.back(),SIGNAL(sendDeleteChange(QString)),this,SLOT(removeIngredient(const QString&)));
    showIngredientsLayout->addWidget(*ingredientsList.back(),10);
    showIngredientsLayout->addWidget(new QLabel,90);
}

void NewFoodWidget::showIngredientsList() {
    GList<QString>::iterator it;
    for(it = dish->getIngredients().begin(); it != dish->getIngredients().end(); it++) {
        showIngredient(&(*it));
    }
}

void NewFoodWidget::closeEvent(QCloseEvent* event) {
    emit closeNewFood(true);
    event->accept();
}

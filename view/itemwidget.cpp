#include "itemwidget.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QIntValidator>
#include <QMessageBox>

ItemWidget::ItemWidget(Actor* _actor, QWidget *parent) : actor(_actor), orderItem(new OrderItem()), QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QMenuBar* menuBar = new QMenuBar;

    //menu 'File'
    QMenu* fileMenu = menuBar->addMenu(tr("File"));
    QAction* closeAction = fileMenu->addAction(tr("Close"));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(close()));

    createMainGroupBox();

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(vGroupBox);
    setMinimumSize(600,500);
    setMaximumSize(600,500);
    resize(600,500);
    move(100,100);
    setLayout(mainLayout);
}

void ItemWidget::createMainGroupBox() {
    vGroupBox = new QGroupBox;
    QVBoxLayout* layout = new QVBoxLayout;

    foodGB = new QGroupBox;
    QHBoxLayout* foodLayout = new QHBoxLayout(foodGB);
    foodLbl = new QLabel(tr("Food:"));
    selectFoodLbl = new QLabel(tr(""));
    foodBtn = new QPushButton("select food");
    foodLayout->addWidget(foodLbl);
    foodLayout->addWidget(selectFoodLbl);
    foodLayout->addWidget(foodBtn);
    connect(foodBtn,SIGNAL(clicked()),this,SLOT(selectFood()));
    foodGB->setLayout(foodLayout);

    quantityGB = new QGroupBox;
    QHBoxLayout* quantityLayout = new QHBoxLayout(quantityGB);
    quantityLbl = new QLabel("Quantity:");
    quantityLbl->setMaximumWidth(50);
    quantityTxt = new QLineEdit;
    quantityTxt->setValidator(new QIntValidator(0,100,this));
    quantityTxt->setMaximumWidth(50);
    quantityLayout->addWidget(quantityLbl,10,Qt::AlignLeft);
    quantityLayout->addWidget(quantityTxt,90,Qt::AlignLeft);
    quantityGB->setLayout(quantityLayout);

    changesGB = new QGroupBox;
    QVBoxLayout* changesLayout = new QVBoxLayout(changesGB);
    labelListGB = new QGroupBox;
    QHBoxLayout* labelListLayout = new QHBoxLayout(labelListGB);
    changesLbl = new QLabel("Changes:");
    addChangeBtn = new QPushButton("Add change");
    connect(addChangeBtn,SIGNAL(clicked()),this,SLOT(writeChange()));
    labelListLayout->addWidget(changesLbl);
    labelListLayout->addWidget(addChangeBtn);
    listGB = new QGroupBox;
    listLayout = new QVBoxLayout(listGB);
    printChanges();
    listGB->setLayout(listLayout);
    scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setWidget(listGB);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    changesLayout->addWidget(labelListGB,10);
    changesLayout->addWidget(scroll,90);
    changesGB->setLayout(changesLayout);


    buttonsGB = new QGroupBox;
    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    cancelBtn = new QPushButton("Cancel");
    submitBtn = new QPushButton("Save");
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(submitBtn,SIGNAL(clicked()),this,SLOT(saveItem()));
    buttonsLayout->addWidget(cancelBtn);
    buttonsLayout->addWidget(submitBtn);
    buttonsGB->setLayout(buttonsLayout);


    layout->addWidget(foodGB,10);
    layout->addWidget(quantityGB,10);
    layout->addWidget(changesGB,80);
    layout->addWidget(buttonsGB,10);
    vGroupBox->setLayout(layout);
}

void ItemWidget::selectFood() {
    MenuWidget* newItem = new MenuWidget(actor,0);
    newItem->show();
    this->setEnabled(false);
    //foodBtn->setEnabled(false);
    connect(newItem,SIGNAL(food(Food*)),this,SLOT(newFood(Food*)));
    connect(newItem,SIGNAL(closeMenu(bool)),this,SLOT(setEnabled(bool)));
}

void ItemWidget::writeChange() {
    AddChange* newItem = new AddChange();
    newItem->show();
    this->setEnabled(false);
    connect(newItem,SIGNAL(sendNewChange(QString*)),this,SLOT(addChange(QString*)));
    connect(newItem,SIGNAL(closeAddChange(bool)),this,SLOT(setEnabled(bool)));
}

void ItemWidget::newFood(Food *food) {
    this->setEnabled(true);
    selectFoodLbl->setText(food->getName());
    orderItem->setFood(food);
}

void ItemWidget::addChange(QString *myString) {
    QWidget* child;
    if(listLbl.empty()) {
        child = listLayout->takeAt(0)->widget();
        listLayout->removeWidget(child);
        delete(child);
    }
    child = listLayout->takeAt(listLayout->count()-1)->widget();
    listLayout->removeWidget(child);
    delete(child);
    orderItem->addChange(*myString);
    listLbl.push_back(new ChangeItem(myString));
    connect(*listLbl.back(),SIGNAL(sendDeleteChange(QString)),this,SLOT(removeChange(QString)));
    listLayout->addWidget(*listLbl.back(),10);
    listLayout->addWidget(new QLabel,90);
}

void ItemWidget::removeChange(QString string) {
    int itCI = 0;
    GList<ChangeItem*>::iterator itLbl = listLbl.begin();
    GList<QString>::iterator itOI;
    for(itOI = orderItem->getChanges().begin(); itOI != orderItem->getChanges().end(); itOI++) {
        if(*itOI == string) {

            QWidget* child = listLayout->takeAt(itCI)->widget();
            listLayout->removeWidget(child);
            delete(child);
            listLbl.erase(itLbl);
            orderItem->removeChanges(string);
            if(orderItem->getChanges().size() == 0) {
                child = listLayout->takeAt(0)->widget();
                listLayout->removeWidget(child);
                delete(child);
            }

            printChanges();
            return;
        }
        itCI++;
        itLbl++;
    }
}

void ItemWidget::saveItem() {
    if(foodLbl->text().isEmpty() || quantityTxt->text().isEmpty()) {
        QMessageBox error;
        error.critical(0,"Complete fields","Food and quantity fields are required");
    } else {
        orderItem->setQuantity(quantityTxt->text().toInt());
        actor->getOrder()->addItem(orderItem);
        emit updateOrder();
        close();
    }
}

void ItemWidget::printChanges() {
    if(listLbl.empty()) {
        listLayout->addWidget(new QLabel("No changes"),10);
        listLayout->addWidget(new QLabel,90);
    }
}

void ItemWidget::closeEvent(QCloseEvent* event) {
    emit closeItem();
    event->accept();
}

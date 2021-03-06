#include "mainwidget.h"

#include <QBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QMessageBox>

MainWidget::MainWidget(Actor* _actor, QWidget *parent) : actor(_actor), QWidget(parent) {
    mainLayout = new QVBoxLayout;
    QMenuBar* menuBar = new QMenuBar;


    //menu 'File'
    QMenu* fileMenu = menuBar->addMenu("File");
    QAction* newOrder = fileMenu->addAction("New order");
    connect(newOrder,SIGNAL(triggered()),this,SLOT(restartView()));
    fileMenu->addSeparator();
    QAction* closeAction = fileMenu->addAction("Close");
    connect(closeAction,SIGNAL(triggered()),this,SLOT(close()));

    //menu 'Menu'
    QMenu* menuMenu = menuBar->addMenu("Menu");
    addFoodAct = menuMenu->addAction("Add a food");
    removeFoodAct = menuMenu->addAction("Remove a food");
    editFoodAct = menuMenu->addAction("Edit a food");
    connect(addFoodAct,SIGNAL(triggered()),this,SLOT(addFood()));
    connect(removeFoodAct,SIGNAL(triggered()),this,SLOT(removeFood()));
    connect(editFoodAct,SIGNAL(triggered()),this,SLOT(editFood()));

    createMainGroupBox();

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(hGroupBox);
    setMinimumSize(600,500);
    setMaximumSize(600,500);
    resize(600,500);
    move(100,100);
    setLayout(mainLayout);
}

MainWidget::~MainWidget() {}

void MainWidget::createMainGroupBox() {
    hGroupBox = new QGroupBox;
    QHBoxLayout* layout = new QHBoxLayout;

    editOrderGB = new QGroupBox;
    editOrderLayout = new QVBoxLayout(editOrderGB);
    addItemButton = new QPushButton("Add");
    payBillButton = new QPushButton("Pay Bill");
    editOrderLayout->addWidget(addItemButton,0,Qt::AlignTop);
    editOrderLayout->addWidget(payBillButton,0,Qt::AlignBottom);
    connect(addItemButton,SIGNAL(clicked()),this,SLOT(addItem()));
    connect(payBillButton,SIGNAL(clicked()),this,SLOT(payBill()));
    editOrderGB->setLayout(editOrderLayout);

    showOrderGB = new QGroupBox;
    showOrderLayout = new QVBoxLayout(showOrderGB);
    createShowOrderGroupBox();
    showOrderGB->setLayout(showOrderLayout);
    scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setWidget(showOrderGB);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    if(actor->getMenu().size() == 0) {
        removeFoodAct->setEnabled(false);
        editFoodAct->setEnabled(false);
        addItemButton->setEnabled(false);
    }
    layout->addWidget(scroll,30);
    layout->addWidget(editOrderGB,10);
    hGroupBox->setLayout(layout);
}

void MainWidget::createShowOrderGroupBox() {
    GList<OrderItem*>::iterator it;
    if(actor->getOrder()->getItems().begin() == 0) {
        QLabel* emptyOrder = new QLabel("Empty order");
        showOrderLayout->addWidget(emptyOrder);
        payBillButton->setEnabled(false);
    } else {
        for(it = actor->getOrder()->getItems().begin(); it != actor->getOrder()->getItems().end(); it++) {
            listItems.push_back(new OrderItemWidget(*it));
            showOrderLayout->addWidget(*listItems.back(),10);
            connect(*listItems.back(),SIGNAL(itemToRemove(int)),this,SLOT(removeItem(int)));
        }
    }
    showOrderLayout->addWidget(new QLabel,90);
}

//Slots
void MainWidget::addItem() {
    ItemWidget* newItem = new ItemWidget(actor);
    newItem->resize(500,300);
    this->hide();
    newItem->show();
    connect(newItem,SIGNAL(updateOrder()),this,SLOT(showNewItem()));
    connect(newItem,SIGNAL(closeItem()),this,SLOT(show()));
}

void MainWidget::showNewItem() {
    if(actor->getOrder()->getItems().size() == 1) {
        //remove QLabel 'empty order'
        QWidget* child = showOrderLayout->takeAt(0)->widget();
        showOrderLayout->removeWidget(child);
        delete(child);
    }
    QWidget* child = showOrderLayout->takeAt((showOrderLayout->count())-1)->widget();
    showOrderLayout->removeWidget(child);
    delete(child);
    OrderItem* last = *actor->getOrder()->getItems().back();
    listItems.push_back(new OrderItemWidget(last));
    connect(*listItems.back(),SIGNAL(itemToRemove(int)),this,SLOT(removeItem(int)));
    showOrderLayout->addWidget(*listItems.back(),10);
    showOrderLayout->addWidget(new QLabel,90);
    payBillButton->setEnabled(true);
}

void MainWidget::removeItem(int id) {
    actor->getOrder()->removeItem(id);
    GList<OrderItemWidget*>::iterator it;
    int counter = 0;
    for(it = listItems.begin(); it != listItems.end(); it++) {
        if((*it)->returnId() == id) {
            QWidget* child = showOrderLayout->takeAt(counter)->widget();
            showOrderLayout->removeWidget(child);
            delete(child);
            listItems.erase(it);
            if(listItems.size() == 0) {
                child = showOrderLayout->takeAt(0)->widget();
                showOrderLayout->removeWidget(child);
                delete(child);
                showOrderLayout->addWidget(new QLabel("Empty order"),10);
                showOrderLayout->addWidget(new QLabel,90);
                payBillButton->setEnabled(false);
            }
            return;
        }
        counter++;
    }
}

void MainWidget::payBill() {
    BillWidget* bill = new BillWidget(actor->getOrder());
    bill->show();
    connect(bill,SIGNAL(closeBill()),this,SLOT(restartView()));
}

void MainWidget::restartView() {
    actor->getOrder()->clear();
    listItems.clear();
    QWidget* child;
    for(int i = 0; i < showOrderLayout->count();) {
        child = showOrderLayout->takeAt(i)->widget();
        showOrderLayout->removeWidget(child);
        delete(child);
    }
    createShowOrderGroupBox();
}

void MainWidget::addFood() {
    NewFoodWidget* addWidget = new NewFoodWidget(actor);
    setEnabled(false);
    connect(addWidget,SIGNAL(sendNewFood(Food*)),this,SLOT(addFoodToMenu(Food*)));
    connect(addWidget,SIGNAL(closeNewFood(bool)),this,SLOT(setEnabled(bool)));
    addWidget->show();

}

void MainWidget::addFoodToMenu(Food* food) {
    actor->addFood(food);
    if(actor->getMenu().size() != 0) {
        removeFoodAct->setEnabled(true);
        editFoodAct->setEnabled(true);
        addItemButton->setEnabled(true);
    }
}

void MainWidget::removeFood() {
    MenuWidget* removeWidget = new MenuWidget(actor,1);
    setEnabled(false);
    connect(removeWidget,SIGNAL(closeMenu(bool)),this,SLOT(controlMenu()));
    removeWidget->show();
}

void MainWidget::editFood() {
    MenuWidget* editWidget = new MenuWidget(actor,2);
    setEnabled(false);
    connect(editWidget,SIGNAL(closeMenu(bool)),this,SLOT(controlMenu()));
    editWidget->show();
}

void MainWidget::controlMenu() {
    setEnabled(true);
    if(actor->getMenu().size() == 0) {
        removeFoodAct->setEnabled(false);
        editFoodAct->setEnabled(false);
        addItemButton->setEnabled(false);
    }
}

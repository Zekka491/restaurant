#include "menuwidget.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>

MenuWidget::MenuWidget(Actor* _actor, int _function, QWidget *parent) : actor(_actor), function(_function), QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QMenuBar* menuBar = new QMenuBar;

    //menu 'File'
    QMenu* fileMenu = menuBar->addMenu("File");
    QAction* closeAction = fileMenu->addAction("Close");
    connect(closeAction,SIGNAL(triggered()),this,SLOT(close()));
    vGroupBox = new QGroupBox;
    layout = new QVBoxLayout;
    createMainGroupBox();
    vGroupBox->setLayout(layout);
    scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setWidget(vGroupBox);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(scroll);
    setMinimumSize(500,500);
    setMaximumSize(500,500);
    resize(500,500);
    move(750,100);
    setLayout(mainLayout);
}

void MenuWidget::createMainGroupBox() {
    GList<Food*>::iterator it;
    GList<Food*>::iterator it2 = actor->getMenu().begin();
    int counter = 0;
    for(it = actor->getMenu().begin(); it != actor->getMenu().end(); it++) {
        if(it == actor->getMenu().begin() || (*it)->getCategory().toUpper() != (*it2)->getCategory().toUpper()) {
            if(!categoryGB.empty())
                (*categoryGB.back())->setLayout(*categoryLayout.back());
            categoryGB.push_back(new QGroupBox);
            categoryLayout.push_back(new QVBoxLayout);
            (*categoryLayout.back())->addWidget(new QLabel((*it)->getCategory().toUpper()),10);

        }
        itemList.push_back(new MenuItemWidget(*it));
        (*categoryLayout.back())->addWidget(*(itemList.back()),10);
        switch(function){
        case 0: connect((*itemList.back()),SIGNAL(valueButton(Food*)),this,SLOT(selectFood(Food*)));
            break;
        case 1: connect((*itemList.back()),SIGNAL(valueButton(Food*)),this,SLOT(removeFood(Food*)));
            break;
        case 2: connect((*itemList.back()),SIGNAL(valueButton(Food*)),this,SLOT(editFood(Food*)));
            break;
        }
        if(it != actor->getMenu().begin()) {
            it2++;
        }
        counter++;
    }
    (*categoryGB.back())->setLayout(*categoryLayout.back());
    GList<QGroupBox*>::iterator itC;
    for(itC = categoryGB.begin(); itC != categoryGB.end(); itC++) {
        layout->addWidget(*itC,10);
    }
    layout->addWidget(new QLabel,90);
}

void MenuWidget::selectFood(Food* _food) {
    emit food(_food);
    close();
}

void MenuWidget::removeFood(Food* _food) {
    actor->removeFood(_food);
    GList<QVBoxLayout*>::iterator it;
    GList<QGroupBox*>::iterator itGB = categoryGB.begin();
    GList<MenuItemWidget*>::iterator itMIW = itemList.begin();
    int countLayout = 0;
    for(it = categoryLayout.begin(); it != categoryLayout.end(); it++){
        for(int i = 0; i < (*it)->count(); i++) {
            QString string;
            QWidget* component = (*it)->itemAt(i)->widget();
            if(dynamic_cast<QLabel*>(component)) {
                QLabel* label = static_cast<QLabel*>(component);
                string = label->text();
            } else {
                MenuItemWidget* item = static_cast<MenuItemWidget*>(component);
                string = item->text();
            }
            if(string == _food->getName()) {
                itemList.erase(itMIW);
                QVBoxLayout* parent = static_cast<QVBoxLayout*>(component->parentWidget()->layout());
                QWidget* child = parent->takeAt(i)->widget();
                parent->removeWidget(child);
                delete(child);
                if((*it)->count() == 1) {
                    categoryGB.erase(itGB);
                    categoryLayout.erase(it);
                    QWidget* category = layout->takeAt(countLayout)->widget();
                    layout->removeWidget(category);
                    delete(category);
                }
                return;
            }
            if(i != 0) {
                itMIW++;
            }
        }
        countLayout++;
        itGB++;
    }

}

void MenuWidget::editFood(Food* _food) {
    NewFoodWidget* editFood = new NewFoodWidget(actor,_food);
    setEnabled(false);
    connect(editFood,SIGNAL(sendNewFood(Food*)),this,SLOT(updateMenu()));
    connect(editFood,SIGNAL(closeNewFood(bool)),this,SLOT(setEnabled(bool)));
    editFood->show();

}

void MenuWidget::updateMenu() {
    setEnabled(true);
    actor->saveMenu();
    QWidget* child;
    for(int i = 0; i < layout->count();) {
        child = layout->takeAt(i)->widget();
        layout->removeWidget(child);
        delete(child);
    }
    categoryGB.clear();
    categoryLayout.clear();
    itemList.clear();
    createMainGroupBox();
}

void MenuWidget::closeEvent(QCloseEvent* event) {
    emit closeMenu(true);
    event->accept();
}

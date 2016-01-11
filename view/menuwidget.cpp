#include "menuwidget.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>

MenuWidget::MenuWidget(Actor* _actor, int _function, QWidget *parent) : actor(_actor), function(_function), QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QMenuBar* menuBar = new QMenuBar;

    //menu 'File'
    QMenu* fileMenu = menuBar->addMenu(tr("File"));
    QAction* newOrder = fileMenu->addAction(tr("New order"));
    fileMenu->addSeparator();
    QAction* closeAction = fileMenu->addAction(tr("Close"));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(close()));

    createMainGroupBox();

    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(scroll);
    setMinimumSize(500,500);
    setMaximumSize(500,500);
    resize(500,500);
    move(750,100);
    setLayout(mainLayout);
}

void MenuWidget::createMainGroupBox() {
    //cout<<"createMainGrouBox"<<endl;
    vGroupBox = new QGroupBox;
    layout = new QVBoxLayout;
    GList<Food*>::iterator it;
    GList<Food*>::iterator it2 = actor->getMenu().begin();
    //cout<<"for item"<<endl;
    int counter = 0;
    for(it = actor->getMenu().begin(); it != actor->getMenu().end(); it++) {
        //cout<<"count "<<counter<<endl;
        //cout<<(*it)->getCategory().toStdString()<<" == "<<(*it2)->getCategory().toStdString()<<endl;
        if(it == actor->getMenu().begin() || (*it)->getCategory().toUpper() != (*it2)->getCategory().toUpper()) {
            //cout<<"cambio categoria"<<endl;
            if(!categoryGB.empty())
                (*categoryGB.back())->setLayout(*categoryLayout.back());
            categoryGB.push_back(new QGroupBox);
            categoryLayout.push_back(new QVBoxLayout);
            (*categoryLayout.back())->addWidget(new QLabel((*it)->getCategory().toUpper()),10);

        }
        //cout<<"aggiungo widget"<<endl;
        itemList.push_back(new MenuItemWidget(*it));
        //(*itemList.back())->setIndent(30);
        (*categoryLayout.back())->addWidget(*(itemList.back()),10);
        //(*(itemList.back()))->setParent(*categoryLayout.back());
        //cout<<"imposto signal - slot"<<endl;
        switch(function){
        case 0: connect((*itemList.back()),SIGNAL(valueButton(Food*)),this,SLOT(selectFood(Food*)));
            break;
        case 1: connect((*itemList.back()),SIGNAL(valueButton(Food*)),this,SLOT(removeFood(Food*)));
            break;
        case 2: //connect((*itemList.back()),SIGNAL(valueButton(Food*)),this,SLOT(editFood(Food*)));
            //cout<<endl<<endl<<"ECCOMI QUI"<<endl<<endl<<endl;
            break;
        }
        if(it != actor->getMenu().begin()) {
            //cout<<"incremento it2"<<endl;
            it2++;
        }
        counter++;
    }
    (*categoryGB.back())->setLayout(*categoryLayout.back());
    GList<QGroupBox*>::iterator itC;
    //cout<<"for GB"<<endl;
    for(itC = categoryGB.begin(); itC != categoryGB.end(); itC++) {
        layout->addWidget(*itC,10);
    }
    layout->addWidget(new QLabel,90);
    vGroupBox->setLayout(layout);
    scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setWidget(vGroupBox);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void MenuWidget::selectFood(Food* _food) {
    emit food(_food);
    close();
}

void MenuWidget::removeFood(Food* _food) {
    //cout<<"Remove"<<endl;
    actor->removeFood(_food);
    GList<QVBoxLayout*>::iterator it;
    GList<QGroupBox*>::iterator itGB = categoryGB.begin();
    //cout<<"category: "<<categoryLayout.size()<<endl;
    GList<MenuItemWidget*>::iterator itMIW = itemList.begin();
    //cout<<"itemList: "<<itemList.size()<<endl;
    int countLayout = 0;
    for(it = categoryLayout.begin(); it != categoryLayout.end(); it++){
        //cout<<"elementi per categoria: "<<(*it)->count()<<endl;
        for(int i = 0; i < (*it)->count(); i++) {
            //cout<<"i: "<<i<<endl;
            QString string;
            QWidget* component = (*it)->itemAt(i)->widget();
            if(dynamic_cast<QLabel*>(component)) {
                QLabel* label = static_cast<QLabel*>(component);
                string = label->text();
            } else {
                MenuItemWidget* item = static_cast<MenuItemWidget*>(component);
                string = item->text();
            }
            //cout<<"confronto: "<<string.toStdString()<<" == "<<_food->getName().toStdString()<<endl;
            if(string == _food->getName()) {
                //cout<<"trovato"<<endl;
                //cout<<"itemList: "<<itemList.size()<<endl;
                itemList.erase(itMIW);
                //cout<<"itemList: "<<itemList.size()<<endl;
                QVBoxLayout* parent = static_cast<QVBoxLayout*>(component->parentWidget()->layout());
                QWidget* child = parent->takeAt(i)->widget();
                parent->removeWidget(child);
                delete(child);
                if((*it)->count() == 1) {
                    //cout<<"remove category"<<endl;
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

void MenuWidget::closeEvent(QCloseEvent* event) {
    emit closeMenu(true);
    event->accept();
}

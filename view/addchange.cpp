#include "addchange.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>

AddChange::AddChange(QWidget *parent) : QWidget(parent) {
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
    mainLayout->addWidget(vGroupBox);
    //setMinimumSize(500,500);
    //setMaximumSize(500,500);
    //resize(250,50);
    move(600,100);
    setLayout(mainLayout);
}

void AddChange::createMainGroupBox() {
    vGroupBox = new QGroupBox;
    QVBoxLayout* layout = new QVBoxLayout;
    QGroupBox* checkBoxGB = new QGroupBox;
    QHBoxLayout* checkBoxLayout = new QHBoxLayout(checkBoxGB);
    add = new QRadioButton("Add",this);
    add->setChecked(true);
    remove = new QRadioButton("Remove",this);
    checkBoxLayout->addWidget(add);
    checkBoxLayout->addWidget(remove);
    checkBoxGB->setLayout(checkBoxLayout);

    QGroupBox* textGB = new QGroupBox;
    QHBoxLayout* textLayout = new QHBoxLayout(textGB);
    label = new QLabel("change:");
    change = new QLineEdit;
    textLayout->addWidget(label);
    textLayout->addWidget(change);
    textGB->setLayout(textLayout);

    submit = new QPushButton("Submit");
    connect(submit,SIGNAL(clicked()),this,SLOT(readChange()));

    layout->addWidget(checkBoxGB);
    layout->addWidget(textGB);
    layout->addWidget(submit);
    vGroupBox->setLayout(layout);
}

void AddChange::readChange() {
    if(!change->text().isEmpty()) {
        if(add->isChecked()) {
            emit sendNewChange(&(QString("+ ").append(change->text())));
        } else {
            emit sendNewChange(&(QString("- ").append(change->text())));
        }
        close();
    } else {

    }
}

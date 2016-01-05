#ifndef ADDCHANGE_H
#define ADDCHANGE_H

#include <QWidget>
#include <QGroupBox>
#include <QBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>

class AddChange : public QWidget {
    Q_OBJECT
public:
    explicit AddChange(QWidget *parent = 0);

signals:
    void sendNewChange(QString*);

public slots:
    void readChange();

private:

    QGroupBox* vGroupBox;
    QLabel* label;
    QLineEdit* change;
    QRadioButton* add;
    QRadioButton* remove;
    QPushButton* submit;


    void createMainGroupBox();


};

#endif // ADDCHANGE_H

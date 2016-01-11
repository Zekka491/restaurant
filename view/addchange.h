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
#include <QCloseEvent>

class AddChange : public QWidget {
    Q_OBJECT
public:
    explicit AddChange(int = 0, QWidget *parent = 0);

signals:
    void sendNewChange(QString*);
    void closeAddChange(bool);

public slots:
    void readChange();

private:
    int function;

    QGroupBox* vGroupBox;
    QLabel* label;
    QLineEdit* change;
    QRadioButton* add;
    QRadioButton* remove;
    QPushButton* submit;


    void createMainGroupBox();

    void closeEvent(QCloseEvent*);

};

#endif // ADDCHANGE_H

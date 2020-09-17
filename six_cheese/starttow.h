#ifndef STARTTOW_H
#define STARTTOW_H

#include <QMainWindow>
//
#include "gamewindow.h"


namespace Ui {
class Starttow;
}

class Starttow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Starttow(QWidget *parent = 0);
    ~Starttow();
public slots:
    void Sendslot();
    //
    void showMainwindow3();
    void dealmainwindow3();


private:
    Ui::Starttow *ui;
    QPushButton *returnButton;
//
    QPushButton *btnClose2;
    QPoint last2;
    QPushButton  *btnopen2;
    GameWindow w3;


signals:
    void Mysignal();




};

#endif // STARTTOW_H

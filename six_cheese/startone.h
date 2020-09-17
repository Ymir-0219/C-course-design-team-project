#ifndef STARTONE_H
#define STARTONE_H

#include <QMainWindow>
#include "starttow.h"

namespace Ui {
class Startone;
}

class Startone : public QMainWindow
{
    Q_OBJECT

public:
    explicit Startone(QWidget *parent = 0);
    ~Startone();


private:
    Ui::Startone *ui;
    QPushButton *btnClose;

    QPoint last;

    QPushButton  *btnopen;
    Starttow w2;




public slots:
    void showMainwindow2();
    void dealmainwindow2();
};

#endif // STARTONE_H

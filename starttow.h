#ifndef STARTTOW_H
#define STARTTOW_H

#include <QMainWindow>
#include <QPushButton>

#include <QPoint>

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



private:
    Ui::Starttow *ui;
    QPushButton *returnButton;
signals:
    void Mysignal();




};

#endif // STARTTOW_H

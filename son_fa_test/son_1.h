#ifndef SON_1_H
#define SON_1_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class son_1;
}

class son_1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit son_1(QWidget *parent = 0);
    ~son_1();

private:
    Ui::son_1 *ui;

    QPushButton *P2Pbtn;
    QPushButton *P2Cbtn;

signals:
    void MysignalP2P();
    void MysignalP2C();

public slots:
    void SendslotP2P();
    void SendslotP2C();


};

#endif // SON_1_H

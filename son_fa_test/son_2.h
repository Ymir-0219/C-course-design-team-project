#ifndef SON_2_H
#define SON_2_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class son_2;
}

class son_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit son_2(QWidget *parent = 0);
    ~son_2();

private:
    Ui::son_2 *ui;
    QPushButton *Black;
    QPushButton *White;
signals:
    void MysignalB();
    void MysignalW();
public slots:
    void SendslotB();
    void SendslotW();


};

#endif // SON_2_H

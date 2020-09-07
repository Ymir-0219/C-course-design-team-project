#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <QPoint>
#include <QString>



#define N 15



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);//绘制棋盘
    void mousePressEvent(QMouseEvent *event);        //单击
    int ok1(int,int);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

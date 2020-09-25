#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <QPoint>
#include <QString>
#include <QPushButton>


#define N 15
#define same_u_i same(row + dx[u] * i, col + dy[u] * i, Board[row][col])
#define OutOrNotEmpty (Board[row + dx[u] * i][col + dy[u] * i] != 0)


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
    //void mousePressEvent(QMouseEvent *event);        //单击


    int ok1(int,int);
    int same(int row, int col, int key);
    int num(int row, int col, int u);
    int live5(int row, int col);
    int cheng6(int row, int col);
    int chong5(int row, int col);
    int live4(int row, int col);
    bool overline(int row, int col);
    bool ban(int row, int col);
    bool end_if(int row, int col);
    int point(int row, int col);
    int AI3(int p2);
    int AI2();
    void AI();
    void Game();
    void AIdown(int,int);


private:
    Ui::MainWindow *ui;

    int inface=1;
    int s = 0, ais = 1, s0, S;//控制下棋方
    QString scoreone={"0"},scoretow={"0"};
    bool is_end = false;
    int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

    QPushButton *Close;
    QPushButton *Next1;
    QPushButton *Next2;
    QPushButton *Next3;
    QPushButton *Next4;
    QPushButton *Back;
    QPoint last;
    QString nameone;
    QString nametow;

public slots:

    void winNextAI();
    void winNextPlayer();
    void winNextW();
    void winNextB();
    void winBack();




};

#endif // MAINWINDOW_H

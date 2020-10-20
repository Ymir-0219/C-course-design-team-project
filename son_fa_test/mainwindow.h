#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <son_1.h>
#include <son_2.h>
#include <QPainter>
#include <qevent.h>
#include <QString>
#include <QMessageBox>

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

    int s = 0, ais = 1, s0, S;//控制下棋方
    int scoreone,scoretow;
    QString playerone,playertow;
    bool is_end = false;
    int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
    int Board[N+2][N+2];


    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void initialization();
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
    void AIdown(int,int);
    void gameOver();


private:
    Ui::MainWindow *ui;

    QPushButton *start;

    QPoint last;
    son_1 w2;
    son_2 w3;


public slots:
    void showSon_1();
    void dealSon_1P2P();
    void dealSon_1P2C();
    void dealSon_2B();
    void dealSon_2W();
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setGeometry(250,100,1500,1000);
    w.setWindowTitle("六子棋游戏");


    return a.exec();
}

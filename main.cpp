#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setFixedSize(1500,900);
    w.setWindowTitle("六子棋游戏");

    return a.exec();
}

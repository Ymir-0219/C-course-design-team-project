#include "startone.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Startone w;
    w.show();

    return a.exec();
}

#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("窗口2");
    this->resize(300,300);

    returnButton2 = new QPushButton(this);
    returnButton2->setText("返回主菜单");
    returnButton2->move(100,150);

    connect(returnButton2,&QPushButton::clicked,this,&GameWindow::Sendslot2);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::Sendslot2()
{
        emit Mysignal2();
}

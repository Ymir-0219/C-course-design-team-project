#include "starttow.h"
#include "ui_starttow.h"

Starttow::Starttow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Starttow)
{
    ui->setupUi(this);

    this->setWindowTitle("窗口2");
    this->resize(1500,900);

    returnButton = new QPushButton(this);
    returnButton->setText("返回主菜单");
    returnButton->setGeometry(QRect(580,620,300,60));
    returnButton->setFont(QFont("微软雅黑",12,60,false));

    connect(returnButton,&QPushButton::clicked,this,&Starttow::Sendslot);
    //
    this->setWindowTitle("主菜单");
    this->setStyleSheet("background:gray");            //设置背景色
    this->setWindowFlags(Qt::WindowCloseButtonHint);    //去掉最大化和最小化按钮，保留关闭按钮

    //定义打开的第二个窗口的按钮
    btnopen2 = new QPushButton(this);
    btnopen2->setGeometry(QRect(580,280,300,60));
    btnopen2->setFont(QFont("微软雅黑",12,60,false));
    btnopen2->setText("玩家一执黑先行");
    connect(btnopen2,SIGNAL(clicked()),this,SLOT(showMainwindow3()));
    btnopen2 = new QPushButton(this);
    btnopen2->setGeometry(QRect(580,450,300,60));
    btnopen2->setFont(QFont("微软雅黑",12,60,false));
    btnopen2->setText("玩家二执黑先行");
    connect(btnopen2,SIGNAL(clicked()),this,SLOT(showMainwindow3()));

    //处理子窗口的信号
    connect(&w3,&GameWindow::Mysignal2,this,&Starttow::dealmainwindow3);
}

Starttow::~Starttow()
{
    delete ui;
}

void Starttow::Sendslot()
{
    emit Mysignal();

}

void Starttow::showMainwindow3()
{
        w3.show();
        this->hide();

}

void Starttow::dealmainwindow3()
{
    w3.hide();
    this->show();
}

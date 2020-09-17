#include "startone.h"
#include "ui_startone.h"

Startone::Startone(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Startone)
{
    ui->setupUi(this);


    this->setWindowTitle("主菜单");
    this->setMaximumSize(1500,900);                      //最大尺寸
    this->setMinimumSize(1500,900);                      //最小尺寸
    this->setStyleSheet("background:gray");            //设置背景色
    this->setWindowIcon(QIcon(":/image/pig.ico"));      //设置窗体图片
    this->setWindowFlags(Qt::WindowCloseButtonHint);    //去掉最大化和最小化按钮，保留关闭按钮


    //新增关闭按钮
    btnClose = new QPushButton(this);
    btnClose->setText("关闭按钮");
    btnClose->setFont(QFont("微软雅黑",12,60,false));
    btnClose->setGeometry(QRect(580,620,300,60));
    //链接信号与槽函数
    connect(btnClose,SIGNAL(clicked()),this,SLOT(close()));


    //定义打开的第二个窗口的按钮
    btnopen = new QPushButton(this);
    btnopen->setGeometry(QRect(580,280,300,60));
    btnopen->setFont(QFont("微软雅黑",12,60,false));
    btnopen->setText("人人对战");
    connect(btnopen,SIGNAL(clicked()),this,SLOT(showMainwindow2()));

    btnopen = new QPushButton(this);
    btnopen->setGeometry(QRect(580,450,300,60));
    btnopen->setFont(QFont("微软雅黑",12,60,false));
    btnopen->setText("人机对战");
    connect(btnopen,SIGNAL(clicked()),this,SLOT(showMainwindow2()));

    //处理子窗口的信号
    connect(&w2,&Starttow::Mysignal,this,&Startone::dealmainwindow2);
}

Startone::~Startone()
{
    delete ui;
}

void Startone::showMainwindow2()
{
    w2.show();
    this->hide();
}

void Startone::dealmainwindow2()
{
    w2.hide();
    this->show();
}








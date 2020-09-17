#include "startone.h"
#include "ui_startone.h"

Startone::Startone(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Startone)
{
    ui->setupUi(this);


    this->setWindowTitle("窗体变化");
    this->setMaximumSize(300,300);                      //最大尺寸
    this->setMinimumSize(300,300);                      //最小尺寸
    this->setStyleSheet("background:white");            //设置背景色
    this->setWindowIcon(QIcon(":/image/pig.ico"));      //设置窗体图片
    this->setWindowFlags(Qt::WindowCloseButtonHint);    //去掉最大化和最小化按钮，保留关闭按钮


    //新增关闭按钮
    btnClose = new QPushButton(this);
    btnClose->setText("关闭按钮");
    btnClose->move(100,100);
    //链接信号与槽函数
    connect(btnClose,SIGNAL(clicked()),this,SLOT(close()));


    //定义打开的第二个窗口的按钮
    btnopen = new QPushButton(this);
    btnopen->setGeometry(QRect(100,200,100,25));
    btnopen->setText("打开窗口");
    connect(btnopen,SIGNAL(clicked()),this,SLOT(showMainwindow2()));
    //connect(w2,SIGNAL(sensignal()),this,SLOT(reshowMainwindow()));

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
}

void Startone::dealmainwindow2()
{
    w2.hide();
    this->show();
}








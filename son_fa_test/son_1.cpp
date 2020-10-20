#include "son_1.h"
#include "ui_son_1.h"

son_1::son_1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::son_1)
{
    ui->setupUi(this);

    this->setWindowTitle("模式选择");
    this->resize(1500,1000);

    P2Pbtn = new QPushButton(this);
    P2Pbtn->setGeometry(QRect(600,360,300,80));
    P2Pbtn->setFont(QFont("微软雅黑",20,4,false));
    P2Pbtn->setText("人人对战");

    connect(P2Pbtn,&QPushButton::clicked,this,&son_1::SendslotP2P);

    P2Cbtn = new QPushButton(this);
    P2Cbtn->setGeometry(QRect(600,540,300,80));
    P2Cbtn->setFont(QFont("微软雅黑",20,4,false));
    P2Cbtn->setText("人机对战");

    connect(P2Cbtn,&QPushButton::clicked,this,&son_1::SendslotP2C);


}

son_1::~son_1()
{
    delete ui;
}

void son_1::SendslotP2P()
{
    emit MysignalP2P();
}

void son_1::SendslotP2C()
{
    emit MysignalP2C();
}

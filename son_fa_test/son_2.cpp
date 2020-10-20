#include "son_2.h"
#include "ui_son_2.h"

son_2::son_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::son_2)
{
    ui->setupUi(this);

    this->setWindowTitle("棋子选择");
    this->resize(1500,1000);

    Black = new QPushButton(this);
    Black->setGeometry(QRect(600,360,300,80));
    Black->setFont(QFont("微软雅黑",20,4,false));
    Black->setText("执黑先行");
    connect(Black,&QPushButton::clicked,this,&son_2::SendslotB);

    White = new QPushButton(this);
    White->setGeometry(QRect(600,540,300,80));
    White->setFont(QFont("微软雅黑",20,4,false));
    White->setText("执白后行");

    connect(White,&QPushButton::clicked,this,&son_2::SendslotW);
}

son_2::~son_2()
{
    delete ui;
}

void son_2::SendslotB()
{
    emit MysignalB();

}

void son_2::SendslotW()
{
    emit MysignalW();
}

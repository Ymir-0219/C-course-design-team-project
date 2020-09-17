#include "starttow.h"
#include "ui_starttow.h"

Starttow::Starttow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Starttow)
{
    ui->setupUi(this);

    this->setWindowTitle("窗口2");
    this->resize(300,300);

    returnButton = new QPushButton(this);
    returnButton->setText("返回主窗口");
    returnButton->move(100,150);

    connect(returnButton,&QPushButton::clicked,this,&Starttow::Sendslot);
}

Starttow::~Starttow()
{
    delete ui;
}

void Starttow::Sendslot()
{
    emit Mysignal();

}

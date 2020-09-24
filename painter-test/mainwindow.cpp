#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p (this);
    if (S==1)
    {
        for(int i=0;i<=16;i++){
            for(int j =0;j<=16;j++){
                p.setPen(Qt::transparent);
                p.setBrush(Qt::gray);
                p.drawRect(i*50+40,j*50+100,45,45);
            }
        }
    }
    else if (S==2)
    {
                for(int i=0;i<=16;i++){
                    for(int j =0;j<=16;j++){
                p.setPen(QPen(Qt::black));
                p.setBrush(Qt::black);
                p.drawEllipse(i*50+25,j*50+85,25,25);
                }
          }
     }



}

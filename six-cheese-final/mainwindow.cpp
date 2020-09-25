#include "mainwindow.h"
#include "ui_mainwindow.h"

int Board[N+2][N+2];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowCloseButtonHint);



    Next3 = new QPushButton(this);
    Next3->setGeometry(QRect(580,280,300,60));
    Next3->setFont(QFont("微软雅黑",12,60,false));
    Next3->setText("执黑先行");
    connect(Next3,SIGNAL(clicked()),this,SLOT(winNextB()));

    Next4 = new QPushButton (this);
    Next4 = new QPushButton (this);
    Next4->setGeometry(QRect(580,450,300,60));
    Next4->setFont(QFont("微软雅黑",12,60,false));
    Next4->setText("执白后行");
    connect(Next4,SIGNAL(clicked()),this,SLOT(winNextW()));

    Back = new QPushButton (this );
    Back->setText("返回主菜单");
    Back->setFont(QFont("微软雅黑",12,60,false));
    Back->setGeometry(QRect(580,620,300,60));
    connect(Back,SIGNAL(clicked()),this,SLOT(winBack()));
    //人机对战选择按钮
        Next1 = new QPushButton (this);
        Next1->setGeometry(QRect(580,280,300,60));
        Next1->setFont(QFont("微软雅黑",12,60,false));
        Next1->setText("人机对战");
        connect(Next1,SIGNAL(clicked()),this,SLOT(winNextAI()));
        //人人对战选择按钮
        Next2 = new QPushButton (this);
        Next2->setGeometry(QRect(580,450,300,60));
        Next2->setFont(QFont("微软雅黑",12,60,false));
        Next2->setText("人人对战");
        connect(Next2,SIGNAL(clicked()),this,SLOT(winNextPlayer()));

        //关闭按钮
        Close = new QPushButton(this);
        Close->setText("关闭按钮");
        Close->setFont(QFont("微软雅黑",12,60,false));
        Close->setGeometry(QRect(580,620,300,60));
        connect(Close,SIGNAL(clicked()),this,SLOT(close()));



}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (inface==3)
    {
        QPainter p (this);
        for(int i=0;i<=14;i++){
            for(int j =0;j<=14;j++){
        for(int i=0;i<=N;i++){
            for(int j =0;j<=N;j++){
                p.setPen(Qt::transparent);
                p.setBrush(Qt::gray);
                p.drawRect(i*50+40,j*50+100,45,45);

                if (Board[i][j] == 1)
                    {
                        p.setPen(QPen(Qt::blue,4));
                        p.drawEllipse(i*50+40,j*50+100,15,15);
                        p.setPen(QPen(Qt::black));
                        p.setBrush(Qt::black);
                        p.drawEllipse(i*50+25,j*50+85,25,25);
                    }
                   if (Board[i][j] == 2)
                   {
                       p.setPen(QPen(Qt::blue,4));
                       p.drawEllipse(i*50+40,j*50+100,15,15);
                       p.setPen(QPen(Qt::white));
                       p.setBrush(Qt::white);
                       p.drawEllipse(i*50+25,j*50+85,25,25);
                   }
                }
            }


        p.setBrush(Qt::gray);
        p.drawRect(900,100,450,400);
        p.setPen(Qt::black);
        p.setFont(QFont("微软雅黑",25,700,false));
        p.drawText(QRectF(900,100,450,500),"游戏规则",QTextOption(Qt::AlignHCenter));

        p.setFont(QFont("微软雅黑",12,700,false));
        p.drawText(QRectF(900,150,450,500),"（1）对局双方各执一色棋子。\n"
                   "（2）空棋盘开局。\n"
                   "（3）黑先、白后，交替下子，每次只能下一子。\n"
                   "（4）棋子下在棋盘的空白点上，棋子下定后，不得向其它点移动，不得从棋盘上拿掉或拿起另落别处。\n"
                   "（5）黑方的第一枚棋子可下在棋盘任意交叉点上。\n"
                   "五子棋对局，执行黑方指定开局、三手可交换、五手两打的规定。整个对局过程中黑方有禁手，白方无禁手。黑方禁手有三三禁手、四四禁手和长连禁手三种。\n",QTextOption(Qt::AlignLeft));

        p.setBrush(Qt::gray);
        p.drawRect(900,525,200,50);
        p.setPen(Qt::black);
        p.setFont(QFont("微软雅黑",20,700,false));
        p.drawText(QRectF(900,525,200,50),"玩家一得分",QTextOption(Qt::AlignHCenter));

        p.setBrush(Qt::gray);
        p.drawRect(1150,525,200,50);
        p.setPen(Qt::black);
        p.setFont(QFont("微软雅黑",20,700,false));
        p.drawText(QRectF(1150,525,200,50),"玩家二得分",QTextOption(Qt::AlignHCenter));


        p.setBrush(Qt::gray);
        p.drawRect(900,600,200,100);
        p.setPen(Qt::black);
        p.setFont(QFont("微软雅黑",35,700,false));
        p.drawText(QRectF(900,600,200,100),scoreone,QTextOption(Qt::AlignHCenter));

        p.setBrush(Qt::gray);
        p.drawRect(1150,600,200,100);
        p.setPen(Qt::black);
        p.setFont(QFont("微软雅黑",35,700,false));
        p.drawText(QRectF(1150,600,200,100),scoretow,QTextOption(Qt::AlignHCenter));
    }


        }
    }
}

void MainWindow::winNextPlayer()
{
    inface+=1;
    S=2;
    delete Next1;
    delete Next2;
    delete Close;
        update();
}

void MainWindow::winNextW()
{
    inface+=1;
    s=1;
    s0=1;
    delete Next3;
    delete Next4;
    delete Back;
        update();
}

void MainWindow::winNextB()
{
    inface=inface+1;
    s=2;
    s0=2;
    delete Next3;
    delete Next4;
    delete Back;
    update();
}

void MainWindow::winNextAI()
{
    inface=inface+1;
    S=1;
    delete Close;
    delete Next1;
    delete Next2;
    update();


}

void MainWindow::winBack()
{
    inface=inface-1;
    delete Next1;
    delete Next2;
    delete Back;
        update();
}

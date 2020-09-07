#include "mainwindow.h"
#include "ui_mainwindow.h"

int Board[N + 2][N + 2];



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


    for(int i=0;i<=14;i++){
        for(int j =0;j<=14;j++){
            p.setPen(Qt::transparent);
            p.setBrush(Qt::gray);
            p.drawRect(i*50+40,j*50+100,45,45);

            if (Board[i][j] == 1)
                {
                    p.setPen(QPen(Qt::blue,4));
                    p.drawEllipse(i*50+40,j*50+100,15,15);
                }
               if (Board[i][j] == 2)
               {
                   p.setPen(QPen(Qt::blue,4));
                   p.drawEllipse(i*50+40,j*50+100,15,15);
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

}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 如果是鼠标左键按下
        if (event->button() == Qt::LeftButton){
            //qDebug() << "left click";
            QPoint p_re = event->pos();
            QString strx,stry;
            strx = QString("%1").arg(p_re.x());
            stry = QString("%1").arg(p_re.y());
            bool ok;
            int x=strx.toInt(&ok,10);
            int y=stry.toInt(&ok,10);

            Board[(x-35)/50][(y-45)/50] ={ ok1(x,y)};

        }
}

int MainWindow::ok1(int x,int y){
    for(int i=0;i<=14;i++){
        for(int j =0;j<=14;j++){
            if(x>i*50+25&&x<i*50+55&&y>j*50+25&&y<j*50+55){
                return 1;
            }
        }
    }
    return 0;
}





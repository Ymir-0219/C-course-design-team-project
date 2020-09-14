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

    for(int i=0;i<=N;i++){
        for(int j =0;j<=N;j++){
            p.setPen(Qt::transparent);
            p.setBrush(Qt::gray);
            p.drawRect(i*50+40,j*50+100,45,45);

            if (Board[i][j] == 1)
                {
                    p.setPen(QPen(Qt::black));
                    p.setBrush(Qt::black);
                    p.drawEllipse(i*50+25,j*50+85,25,25);
                }
               if (Board[i][j] == 2)
               {
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
               "六子棋对局，整个对局过程中黑方有禁手，白方无禁手。黑方禁手有三三禁手、四四禁手和长连禁手三种。\n",QTextOption(Qt::AlignLeft));

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


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint p_re = event->pos();
        QString strx,stry;
        strx = QString("%1").arg(p_re.x());
        stry = QString("%1").arg(p_re.y());
        bool ok;
        int x=strx.toInt(&ok,10);
        int y=stry.toInt(&ok,10);
        int x1=qRound((x-40)/50.0),y1=qRound((y-100)/50.0);
        Board[x1][y1] ={ ok1(x1,y1)};
        end_if(x1,y1);

        s=3-s;
        update();
        AI();
        if(is_end)
        {
            QApplication* app;
            app->exit(0);
        }
    }
}

int MainWindow::ok1(int x,int y){
    if(Board[x][y]==0){
        if(s==1)
            return 1;
        return 2;
    }
    return Board[x][y];
}

int MainWindow::same(int row, int col, int key)
{
        return (Board[row][col] == key || Board[row][col] + key == 0);
}

int MainWindow::num(int row, int col, int u)
{
    int i = row + dx[u], j = col + dy[u], sum = 0, ref = Board[row][col];
       if (ref == 0)return 0;
       while (same(i, j, ref))sum++, i += dx[u], j += dy[u];
       return sum;
}

int MainWindow::live5(int row, int col)
{
    int sum = 0, i, u;
    for (u = 0; u < 4; u++)
    {
        int sumk = 1;
        for (i = 1; same_u_i; i++)sumk++;
        if (OutOrNotEmpty)continue;
        for (i = -1; same_u_i; i--)sumk++;
        if (OutOrNotEmpty)continue;
        if (sumk == 5)sum++;
    }
    return sum;
}

int MainWindow::cheng6(int row, int col)
{
    int sum = 0, i, u;
        for (u = 0; u < 8; u++)
        {
            int  sumk = 0;
            bool flag = true;
            for (i = 1; same_u_i || flag; i++)
            {
                if (!same_u_i)
                {
                    if (Board[row + dx[u] * i][col + dy[u] * i])sumk -= 10;
                    flag = false;
                }
                sumk++;
            }
            for (i = -1; same_u_i; i--)sumk++;
            if (sumk == 5)sum++;
        }
        return sum;
}

int MainWindow::chong5(int row, int col)
{
    return cheng6(row, col) - live5(row, col) * 2;
}

int MainWindow::live4(int row, int col)
{
    int sum = 0, i, u, flag = 2;
        for (u = 0; u < 4; u++)
        {
            int sumk = 1;
            for (i = 1; same_u_i; i++)sumk++;
            if (OutOrNotEmpty)continue;
            i++;
            if (OutOrNotEmpty)flag--;
            for (i = -1; same_u_i; i--)sumk++;
            if (OutOrNotEmpty)continue;
            i--;
            if (OutOrNotEmpty)flag--;
            if (sumk == 4 && flag > 0)sum++;
        }
        for (u = 0; u < 8; u++)
        {
            int  sumk = 0;
            bool flag = true;
            for (i = 1; same_u_i || flag; i++)
            {
                if (!same_u_i)
                {
                    if (flag && Board[row + dx[u] * i][col + dy[u] * i])sumk -= 10;
                    flag = false;
                }
                sumk++;
            }
            if (OutOrNotEmpty)continue;;

            if (Board[row + dx[u] * (i)][col + dy[u] * i] == 0)
            {
                i=i-1;
                continue;
            }
            for (i = 1; same_u_i; i++)sumk++;
            if (OutOrNotEmpty)continue;;
            if (sumk == 4)sum++;
        }
        return sum;
}

bool MainWindow::overline(int row, int col)
{
    for (int u = 0; u < 4; u++)if (num(row, col, u) + num(row, col, u + 4) > 5)return true;
    return false;
}

bool MainWindow::ban(int row, int col)
{
    if (same(row, col, 2))return false;//白方无禁手
    return live4(row, col) > 1 || overline(row, col) || live5(row, col) + chong5(row, col) > 1;
}

bool MainWindow::end_if(int row, int col)
{
    for (int u = 0; u < 4; u++)if (num(row, col, u) + num(row, col, u + 4) >= 5)is_end = true;
    if (is_end)return true;
    is_end = ban(row, col);
    return is_end;
}

int MainWindow::point(int row, int col)
{
    if (ban(row, col))return 0;//禁手判输
    if (end_if(row, col))
    {
        is_end = false;
        return 10000;
    }
    int ret = live5(row, col) * 1000 + (chong5(row, col) + live4(row, col)) * 100, u;
    for (u = 0; u < 8; u++)if (Board[row + dx[u]][col + dy[u]])ret++;
    return ret;
}

int MainWindow::AI3(int p2)
{
    int keyp = -100000, tempp;
    for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++)
    {
        if(Board[i][j]!=0)continue;
        Board[i][j] = s0;
        tempp = point(i, j);
        if (tempp == 0)
        {
            Board[i][j] = 0;
            continue;
        }
        if (tempp == 10000)
        {
            Board[i][j] = 0;
            return 10000;
        }
        Board[i][j]=0;
        if (tempp - p2 * 2 > keyp)keyp = tempp - p2 * 2;
    }
    return keyp;
}

int MainWindow::AI2()
{
    int keyp = 100000, tempp;
    for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++)
    {
        if(Board[i][j]!=0)continue;
        Board[i][j] = 3 - s0;
        tempp = point(i, j);
        if (tempp == 0)
        {
            Board[i][j] = 0;
            continue;
        }
        if (tempp == 10000)
        {
            Board[i][j] = 0;
            return -10000;
        }
        tempp = AI3(tempp);
        Board[i][j]=0;
        if (tempp < keyp)keyp = tempp;
    }
    return keyp;
}

void MainWindow::AI()
{
    if (Board[8][8] == 0)
    {
        return AIdown(8,8);

    }
    int i, j;
    int keyp = -100000, keyi, keyj, tempp;
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            if(Board[i][j]!=0)continue;
            Board[i][j] = s0;
            tempp = point(i, j);
            if (tempp == 0)
            {
                Board[i][j] = 0;
                continue;
            }
            if (tempp == 10000)
            {
                Board[keyi][keyj]=s;
                continue;
            }
            tempp = AI2();
            Board[i][j]=0;
            if (tempp > keyp)
            {
                keyp = tempp;
                keyi = i;
                keyj = j;
            }
        }
    }
    AIdown(keyi,keyj);
    end_if(keyi,keyj);
}

void MainWindow::AIdown(int i,int j)
{
    Board[i][j]=s;
    s=3-s;
}









#include <stdio.h>
#include<windows.h>
#include <memory.h> 

//本游戏可以完成玩家与玩家、玩家与电脑的对局。并且电脑的算法采用三层嵌套的极大极小搜索法和α-β剪枝法，尽可能地使AI更加聪明。
//在对输赢条件地判定上，采用坐标法使判定输赢更方便。但因为测试次数有限，可能仍存在bug。

#define N 15//标准棋盘大小15*15
#define same_u_i same(row + dx[u] * i, col + dy[u] * i, p[row][col])//坐标法判断颜色
#define OutOrNotEmpty (!inboard(row + dx[u] * i, col + dy[u] * i) || p[row + dx[u] * i][col + dy[u] * i] != 0) //筛选空格

int p[N + 2][N + 2]; //0空棋，1黑，2白，1●，2○，-1▲，-2△，圆圈下过，三角刚下
int s = 0, ais = 1, s0, S;//s是轮到谁下,s=s0是黑方下,S判断玩家或AI
bool is_end = false;//胜利判断值
int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };//坐标（dx,dy）是8个方向向量，以当前点为坐标原点
int manu[2][300], manukey = 0;//下棋记录
int result1, result2, sum;//玩家一获胜数，玩家二获胜数，总游戏数 

int out(int i, int j)//棋盘设定
{
    if (p[i][j] == 1)return printf("●");
    if (p[i][j] == 2)return printf("○");
    if (p[i][j] == -1)return printf("▲");
    if (p[i][j] == -2)return printf("△");//判断棋子类型
    if (i == N)
    {
        if (j == 1)return printf("┏");
        if (j == N)return printf("┓");
        return printf("┯");
    }
    if (i == 1)
    {
        if (j == 1)return printf("┗");
        if (j == N)return printf("┛");
        return printf("┷");
    }
    if (j == 1)return printf("┠");
    if (j == N)return printf("┨");
    return printf("┼");
}

void DrawBoard()//打印整个游戏界面
{
    system("cls");//清屏
    int row = 0, col = 0, keyr = 0, keyc = 0;
    char alpha = 'A';
    printf("\n————————对局开始————————\n\n     ");
    for (col = 1; col <= N; col++)printf("%c ", alpha++);//横坐标
    for (row = N; row >= 1; row--)
    {
        printf("\n   %2d", row);//纵坐标
        for (col = 1; col <= N; col++)
        {
            out(row, col);
            if (p[row][col] < 0)keyr = row, keyc = col;
        }
        printf("%d", row);
    }
    alpha = 'A';
    printf("\n     ");
    for (col = 1; col <= N; col++)printf("%c ", alpha++);//横坐标
    printf("\n\n");
    if (s0 == ais && S == 2)printf("  AI执黑，玩家执白\n");
    else if (s0 == ais && S != 2)printf("  玩家一执白，玩家二执黑\n");
    else if (s0 != ais && S == 2)printf("AI执白，玩家执黑\n");
    else printf("  玩家一执黑，玩家二执白\n");
    alpha = 'A';
    if (keyr)printf("  最后落子位置：%c%d\n", alpha + keyc - 1, keyr);
}

void init()//游戏第二主体
{
    system("cls");
    system("color f0");//改变DOS窗口颜色
    if (S == 2)
        printf("输入1或者2进行选择\n1、AI执黑先行\n2、玩家执黑先行\n");
    else printf("输入1或者2进行选择\n1、玩家二执黑先行\n2、玩家一执黑先行\n");
    scanf_s("%d", &s);
    if (s != 1 && s != 2)return init();
    s0 = s;
    int i, j;
    for (i = 0; i <= N + 1; i++)for (j = 0; j <= N + 1; j++)p[i][j] = 0;//用空格包围棋盘	
    DrawBoard();
    for (j = 0; j < 300; j++)manu[0][j] = manu[1][j] = 0;
}

void result(int result1, int result2, int sum)//输出局势
{
    if (S == 2)printf("AI胜利局数%d\n玩家胜利局数%d\n总局数%d\n", result2, result1, sum);
    else printf("玩家一胜利局数%d\n玩家二胜利局数%d\n总局数%d\n", result1, result2, sum);
}

bool inboard(int row, int col)//判断落子是否在棋盘内
{
    if (row <1 || row > N)return false;
    return col >= 1 && col <= N;
}

int same(int row, int col, int key)//判断2个棋子是否同色，颜色取决于key的值
{
    if (!inboard(row, col))return false;
    return (p[row][col] == key || p[row][col] + key == 0);
}

int num(int row, int col, int u)//判断某个方向有多少连续同色棋子，输赢，积分依赖于此
{
    int i = row + dx[u], j = col + dy[u], sum = 0, ref = p[row][col];
    if (ref == 0)return 0;
    while (same(i, j, ref))sum++, i += dx[u], j += dy[u];
    return sum;
}

int live4(int row, int col)//落子成活4的数量
{
    int sum = 0, i, u;
    for (u = 0; u < 4; u++)
    {
        int sumk = 1;
        for (i = 1; same_u_i; i++)sumk++;
        if (OutOrNotEmpty)continue;
        for (i = -1; same_u_i; i--)sumk++;
        if (OutOrNotEmpty)continue;
        if (sumk == 4)sum++;
    }
    return sum;
}

int cheng5(int row, int col)//成5点的数量
{
    int sum = 0, i, u;
    for (u = 0; u < 8; u++)//8个成五点的方向
    {
        int  sumk = 0;
        bool flag = true;
        for (i = 1; same_u_i || flag; i++)
        {
            if (!same_u_i)//该方向的第一个不是相同的点
            {
                if (p[row + dx[u] * i][col + dy[u] * i])sumk -= 10;//该方向的第一个不同色的点是对方棋子
                flag = false;
            }
            sumk++;
        }
        if (!inboard(row + dx[u] * --i, col + dy[u] * i))continue;//该方向的第一个不同色的点是超出边界
        for (i = -1; same_u_i; i--)sumk++;
        if (sumk == 4)sum++;
    }
    return sum;
}

int chong4(int row, int col)//冲4的数量
{
    return cheng5(row, col) - live4(row, col) * 2;
}

int live3(int row, int col)//活3的数量
{
    int key = p[row][col], sum = 0, i, u, flag = 2;
    for (u = 0; u < 4; u++)//三连的活三
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
        if (sumk == 3 && flag > 0)sum++;
    }
    for (u = 0; u < 8; u++)//非三连的活三
    {
        int  sumk = 0;
        bool flag = true;
        for (i = 1; same_u_i || flag; i++)
        {
            if (!same_u_i)
            {
                if (flag && p[row + dx[u] * i][col + dy[u] * i])sumk -= 10;
                flag = false;
            }
            sumk++;
        }
        if (OutOrNotEmpty)continue;;
        if (p[row + dx[u] * --i][col + dy[u] * i] == 0)continue;
        for (i = 1; same_u_i; i++)sumk++;
        if (OutOrNotEmpty)continue;;
        if (sumk == 3)sum++;
    }
    return sum;
}

bool overline(int row, int col)//长连禁手
{
    for (int u = 0; u < 4; u++)if (num(row, col, u) + num(row, col, u + 4) > 4)return true;
    return false;
}

bool ban(int row, int col)//判断落子后是否成禁手
{
    if (same(row, col, 2))return false;//白方无禁手
    return live3(row, col) > 1 || overline(row, col) || live4(row, col) + chong4(row, col) > 1;//三三禁手，四四禁手，长连禁手
}

bool full()//判断棋盘已满
{
    int i = 0, j = 0;
    for (i = 0; i < N; i++)for (j = 0; j < N; j++)
    {
        if (p[i][j] == ' ');
        return false;
    }
    return true;
}

bool end_if(int row, int col)//判断游戏结束
{
    for (int u = 0; u < 4; u++)if (num(row, col, u) + num(row, col, u + 4) >= 4)is_end = true;
    if (is_end)return true;
    is_end = ban(row, col) || full();
    return is_end;
}

void falldown(int row, int col)//落下一子
{
    if (s == s0)p[row][col] = -1; //标出最新下的棋
    else p[row][col] = -2;
    for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //取消上一个最新棋的标识
    {
        if (i == row && j == col)continue;
        if (p[i][j] < 0)p[i][j] *= -1;
    }
    DrawBoard();
    if (ban(row, col))
    {
        printf("禁手\n");
        if (s0 == 1 && S == 2) { printf("玩家胜\n"); result1++; }
        else if (s0 == 1 && S != 2) { printf("玩家一胜\n"); result1++; }
        else if (s0 != 1 && S == 2) { printf("AI胜\n"); result2++; }
        else { printf("玩家二胜\n"); result2++; }
        sum++;
    }
    if (end_if(row, col))
    {
        if (!full() && !ban(row, col))
        {
            if (s == ais && S == 2) { printf("AI胜\n"); result2++; }
            else if (s == ais && S != 2) { printf("玩家二胜\n"); result2++; }
            else if (s != ais && S == 2) { printf("玩家胜\n"); result1++; }
            else { printf("玩家一胜\n"); result1++; }
            sum++;
            return;
        }
        else if (full())
        {
            printf("平局\n");
            sum++;
        }
        else
        {
            return;
        }
    }
    manu[0][manukey] = row, manu[1][manukey++] = col;
}

bool ok(int row, int col)//能否落子
{
    return inboard(row, col) && (p[row][col] == 0);
}

int point(int row, int col)//点位积分
{
    if (ban(row, col))return 0;//禁手判输
    if (end_if(row, col))
    {
        is_end = false;
        return 10000;
    }
    int ret = live4(row, col) * 1000 + (chong4(row, col) + live3(row, col)) * 100, u;
    for (u = 0; u < 8; u++)if (p[row + dx[u]][col + dy[u]])ret++;
    return ret;
}

int AI3(int p2)
{
    int keyp = -100000, tempp;
    for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++)
    {
        if (!ok(i, j))continue;
        p[i][j] = s0;
        tempp = point(i, j);
        if (tempp == 0)
        {
            p[i][j] = 0;
            continue;
        }
        if (tempp == 10000)
        {
            p[i][j] = 0;
            return 10000;
        }
        p[i][j] = 0;
        if (tempp - p2 * 2 > keyp)keyp = tempp - p2 * 2;
    }
    return keyp;
}

int AI2()
{
    int keyp = 100000, tempp;
    for (int i = 1; i <= N; i++)for (int j = 1; j <= N; j++)
    {
        if (!ok(i, j))continue;
        p[i][j] = 3 - s0;
        tempp = point(i, j);
        if (tempp == 0)
        {
            p[i][j] = 0;
            continue;
        }
        if (tempp == 10000)
        {
            p[i][j] = 0;
            return -10000;
        }
        tempp = AI3(tempp);
        p[i][j] = 0;
        if (tempp < keyp)keyp = tempp;
    }
    return keyp;
}

void AI()
{
    DrawBoard();
    printf("  轮到AI下，请稍候： ");
    if (p[8][8] == 0)return falldown(8, 8);
    int i, j;
    int keyp = -100000, keyi, keyj, tempp;
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            if (!ok(i, j))continue;
            p[i][j] = s0;
            tempp = point(i, j);
            if (tempp == 0)
            {
                p[i][j] = 0;
                continue;
            }
            if (tempp == 10000)return falldown(i, j);
            tempp = AI2();
            p[i][j] = 0;
            if (tempp > keyp)keyp = tempp, keyi = i, keyj = j;
        }
    }
    return falldown(keyi, keyj);
}

void out_manual()//展示落子
{
    char alpha = 'A';
    int i;
    printf("\n  黑方落子位置: ");
    for (i = 0; i < manukey; i += 2)printf("  %c%d", alpha + manu[1][i] - 1, manu[0][i]);
    printf("\n  白方落子位置: ");
    for (i = 1; i < manukey; i += 2)printf("  %c%d", alpha + manu[1][i] - 1, manu[0][i]);
    Sleep(5000);
}

void player()
{
    DrawBoard();
    if (S != 2 && s == ais)printf("  轮到玩家二下，请输入坐标(输入=0查看棋谱)：");
    else if (S != 2 && s != ais)printf("  轮到玩家一下，请输入坐标(输入=0查看棋谱)：");
    else printf("  轮到玩家下，请输入坐标(输入=0查看棋谱)： ");
    char c = '\n';
    int row = 0, col = 0;
    while (c < '0')scanf_s("%c%d", &c, &row);
    if (c == '=')
    {
        out_manual();
        return player();
    }
    if (c < 'a')col = c - 'A' + 1;
    else col = c - 'a' + 1;
    if (!ok(row, col))
    {
        printf("  此处不能下\n");
        Sleep(1000);
        return player();
    }
    falldown(row, col);
}

void Game()
{
    system("cls");
    system("color f0");
    printf("  欢迎来到五子棋\n  1、双人对局\n  2、电脑对局\n  3、退出游戏");
    printf("\n\n\n游戏规则：\n（1）对局双方各执一色棋子。\n（2）空棋盘开局。\n（3）黑先、白后，交替下子，每次只能下一子。\n（4）棋子下在棋盘的空白点上，棋子下定后，不得向其它点移动，不得从棋盘上拿掉或拿起另落别处。\n（5）黑方的第一枚棋子可下在棋盘任意交叉点上。\n\n  P.S.五子棋对局，执行黑方指定开局、三手可交换、五手两打的规定。整个对局过程中黑方有禁手，白方无禁手。黑方禁手有三三禁手、四四禁手和长连禁手三种。\n ");
    scanf_s("%d", &S);
    result1 = 0;
    if (S == 3)return;
    result2 = 0;
    sum = 0;
    while (1)
    {
        int x = 0;
        init();
        if (S == 2)
        {
            memset(manu, 0, sizeof(manu));
            manukey = 0;
            while (!is_end)
            {
                if (s == ais)AI();
                else player();
                s = 3 - s;//换下棋方
            }
            is_end = false;
            result(result1, result2, sum);
            Sleep(1000);
            printf("  是否继续对局\n  1.再来一局\n  2.回到菜单\n");
            scanf_s("%d", &x);
            if (x - 1)break;

        }
        else
        {
            memset(manu, 0, sizeof(manu));
            manukey = 0;
            while (!is_end)
            {
                player();
                s = 3 - s;
            }
            is_end = false;
            result(result1, result2, sum);
            Sleep(1000);
            printf("  是否继续对局\n  1.再来一局\n  2.回到菜单\n");
            scanf_s("%d", &x);
            if (x - 1)break;
        }
    }
    return Game();
}

int main()
{
    Game();
    return 0;
}
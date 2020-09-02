#include <stdio.h>
#include<windows.h>
#include <memory.h> 

//����Ϸ��������������ҡ��������ԵĶԾ֡����ҵ��Ե��㷨��������Ƕ�׵ļ���С�������ͦ�-�¼�֦���������ܵ�ʹAI���Ӵ�����
//�ڶ���Ӯ�������ж��ϣ��������귨ʹ�ж���Ӯ�����㡣����Ϊ���Դ������ޣ������Դ���bug��

#define N 15//��׼���̴�С15*15
#define same_u_i same(row + dx[u] * i, col + dy[u] * i, p[row][col])//���귨�ж���ɫ
#define OutOrNotEmpty (!inboard(row + dx[u] * i, col + dy[u] * i) || p[row + dx[u] * i][col + dy[u] * i] != 0) //ɸѡ�ո�

int p[N + 2][N + 2]; //0���壬1�ڣ�2�ף�1��2��-1����-2����ԲȦ�¹������Ǹ���
int s = 0, ais = 1, s0, S;//s���ֵ�˭��,s=s0�Ǻڷ���,S�ж���һ�AI
bool is_end = false;//ʤ���ж�ֵ
int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };//���꣨dx,dy����8�������������Ե�ǰ��Ϊ����ԭ��
int manu[2][300], manukey = 0;//�����¼
int result1, result2, sum;//���һ��ʤ������Ҷ���ʤ��������Ϸ�� 

int out(int i, int j)//�����趨
{
    if (p[i][j] == 1)return printf("��");
    if (p[i][j] == 2)return printf("��");
    if (p[i][j] == -1)return printf("��");
    if (p[i][j] == -2)return printf("��");//�ж���������
    if (i == N)
    {
        if (j == 1)return printf("��");
        if (j == N)return printf("��");
        return printf("��");
    }
    if (i == 1)
    {
        if (j == 1)return printf("��");
        if (j == N)return printf("��");
        return printf("��");
    }
    if (j == 1)return printf("��");
    if (j == N)return printf("��");
    return printf("��");
}

void DrawBoard()//��ӡ������Ϸ����
{
    system("cls");//����
    int row = 0, col = 0, keyr = 0, keyc = 0;
    char alpha = 'A';
    printf("\n�����������������Ծֿ�ʼ����������������\n\n     ");
    for (col = 1; col <= N; col++)printf("%c ", alpha++);//������
    for (row = N; row >= 1; row--)
    {
        printf("\n   %2d", row);//������
        for (col = 1; col <= N; col++)
        {
            out(row, col);
            if (p[row][col] < 0)keyr = row, keyc = col;
        }
        printf("%d", row);
    }
    alpha = 'A';
    printf("\n     ");
    for (col = 1; col <= N; col++)printf("%c ", alpha++);//������
    printf("\n\n");
    if (s0 == ais && S == 2)printf("  AIִ�ڣ����ִ��\n");
    else if (s0 == ais && S != 2)printf("  ���һִ�ף���Ҷ�ִ��\n");
    else if (s0 != ais && S == 2)printf("AIִ�ף����ִ��\n");
    else printf("  ���һִ�ڣ���Ҷ�ִ��\n");
    alpha = 'A';
    if (keyr)printf("  �������λ�ã�%c%d\n", alpha + keyc - 1, keyr);
}

void init()//��Ϸ�ڶ�����
{
    system("cls");
    system("color f0");//�ı�DOS������ɫ
    if (S == 2)
        printf("����1����2����ѡ��\n1��AIִ������\n2�����ִ������\n");
    else printf("����1����2����ѡ��\n1����Ҷ�ִ������\n2�����һִ������\n");
    scanf_s("%d", &s);
    if (s != 1 && s != 2)return init();
    s0 = s;
    int i, j;
    for (i = 0; i <= N + 1; i++)for (j = 0; j <= N + 1; j++)p[i][j] = 0;//�ÿո��Χ����	
    DrawBoard();
    for (j = 0; j < 300; j++)manu[0][j] = manu[1][j] = 0;
}

void result(int result1, int result2, int sum)//�������
{
    if (S == 2)printf("AIʤ������%d\n���ʤ������%d\n�ܾ���%d\n", result2, result1, sum);
    else printf("���һʤ������%d\n��Ҷ�ʤ������%d\n�ܾ���%d\n", result1, result2, sum);
}

bool inboard(int row, int col)//�ж������Ƿ���������
{
    if (row <1 || row > N)return false;
    return col >= 1 && col <= N;
}

int same(int row, int col, int key)//�ж�2�������Ƿ�ͬɫ����ɫȡ����key��ֵ
{
    if (!inboard(row, col))return false;
    return (p[row][col] == key || p[row][col] + key == 0);
}

int num(int row, int col, int u)//�ж�ĳ�������ж�������ͬɫ���ӣ���Ӯ�����������ڴ�
{
    int i = row + dx[u], j = col + dy[u], sum = 0, ref = p[row][col];
    if (ref == 0)return 0;
    while (same(i, j, ref))sum++, i += dx[u], j += dy[u];
    return sum;
}

int live4(int row, int col)//���ӳɻ�4������
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

int cheng5(int row, int col)//��5�������
{
    int sum = 0, i, u;
    for (u = 0; u < 8; u++)//8�������ķ���
    {
        int  sumk = 0;
        bool flag = true;
        for (i = 1; same_u_i || flag; i++)
        {
            if (!same_u_i)//�÷���ĵ�һ��������ͬ�ĵ�
            {
                if (p[row + dx[u] * i][col + dy[u] * i])sumk -= 10;//�÷���ĵ�һ����ͬɫ�ĵ��ǶԷ�����
                flag = false;
            }
            sumk++;
        }
        if (!inboard(row + dx[u] * --i, col + dy[u] * i))continue;//�÷���ĵ�һ����ͬɫ�ĵ��ǳ����߽�
        for (i = -1; same_u_i; i--)sumk++;
        if (sumk == 4)sum++;
    }
    return sum;
}

int chong4(int row, int col)//��4������
{
    return cheng5(row, col) - live4(row, col) * 2;
}

int live3(int row, int col)//��3������
{
    int key = p[row][col], sum = 0, i, u, flag = 2;
    for (u = 0; u < 4; u++)//�����Ļ���
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
    for (u = 0; u < 8; u++)//�������Ļ���
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

bool overline(int row, int col)//��������
{
    for (int u = 0; u < 4; u++)if (num(row, col, u) + num(row, col, u + 4) > 4)return true;
    return false;
}

bool ban(int row, int col)//�ж����Ӻ��Ƿ�ɽ���
{
    if (same(row, col, 2))return false;//�׷��޽���
    return live3(row, col) > 1 || overline(row, col) || live4(row, col) + chong4(row, col) > 1;//�������֣����Ľ��֣���������
}

bool full()//�ж���������
{
    int i = 0, j = 0;
    for (i = 0; i < N; i++)for (j = 0; j < N; j++)
    {
        if (p[i][j] == ' ');
        return false;
    }
    return true;
}

bool end_if(int row, int col)//�ж���Ϸ����
{
    for (int u = 0; u < 4; u++)if (num(row, col, u) + num(row, col, u + 4) >= 4)is_end = true;
    if (is_end)return true;
    is_end = ban(row, col) || full();
    return is_end;
}

void falldown(int row, int col)//����һ��
{
    if (s == s0)p[row][col] = -1; //��������µ���
    else p[row][col] = -2;
    for (int i = 0; i <= N; i++)for (int j = 0; j <= N; j++) //ȡ����һ��������ı�ʶ
    {
        if (i == row && j == col)continue;
        if (p[i][j] < 0)p[i][j] *= -1;
    }
    DrawBoard();
    if (ban(row, col))
    {
        printf("����\n");
        if (s0 == 1 && S == 2) { printf("���ʤ\n"); result1++; }
        else if (s0 == 1 && S != 2) { printf("���һʤ\n"); result1++; }
        else if (s0 != 1 && S == 2) { printf("AIʤ\n"); result2++; }
        else { printf("��Ҷ�ʤ\n"); result2++; }
        sum++;
    }
    if (end_if(row, col))
    {
        if (!full() && !ban(row, col))
        {
            if (s == ais && S == 2) { printf("AIʤ\n"); result2++; }
            else if (s == ais && S != 2) { printf("��Ҷ�ʤ\n"); result2++; }
            else if (s != ais && S == 2) { printf("���ʤ\n"); result1++; }
            else { printf("���һʤ\n"); result1++; }
            sum++;
            return;
        }
        else if (full())
        {
            printf("ƽ��\n");
            sum++;
        }
        else
        {
            return;
        }
    }
    manu[0][manukey] = row, manu[1][manukey++] = col;
}

bool ok(int row, int col)//�ܷ�����
{
    return inboard(row, col) && (p[row][col] == 0);
}

int point(int row, int col)//��λ����
{
    if (ban(row, col))return 0;//��������
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
    printf("  �ֵ�AI�£����Ժ� ");
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

void out_manual()//չʾ����
{
    char alpha = 'A';
    int i;
    printf("\n  �ڷ�����λ��: ");
    for (i = 0; i < manukey; i += 2)printf("  %c%d", alpha + manu[1][i] - 1, manu[0][i]);
    printf("\n  �׷�����λ��: ");
    for (i = 1; i < manukey; i += 2)printf("  %c%d", alpha + manu[1][i] - 1, manu[0][i]);
    Sleep(5000);
}

void player()
{
    DrawBoard();
    if (S != 2 && s == ais)printf("  �ֵ���Ҷ��£�����������(����=0�鿴����)��");
    else if (S != 2 && s != ais)printf("  �ֵ����һ�£�����������(����=0�鿴����)��");
    else printf("  �ֵ�����£�����������(����=0�鿴����)�� ");
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
        printf("  �˴�������\n");
        Sleep(1000);
        return player();
    }
    falldown(row, col);
}

void Game()
{
    system("cls");
    system("color f0");
    printf("  ��ӭ����������\n  1��˫�˶Ծ�\n  2�����ԶԾ�\n  3���˳���Ϸ");
    printf("\n\n\n��Ϸ����\n��1���Ծ�˫����ִһɫ���ӡ�\n��2�������̿��֡�\n��3�����ȡ��׺󣬽������ӣ�ÿ��ֻ����һ�ӡ�\n��4�������������̵Ŀհ׵��ϣ������¶��󣬲������������ƶ������ô��������õ�����������𴦡�\n��5���ڷ��ĵ�һö���ӿ������������⽻����ϡ�\n\n  P.S.������Ծ֣�ִ�кڷ�ָ�����֡����ֿɽ�������������Ĺ涨�������Ծֹ����кڷ��н��֣��׷��޽��֡��ڷ��������������֡����Ľ��ֺͳ����������֡�\n ");
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
                s = 3 - s;//�����巽
            }
            is_end = false;
            result(result1, result2, sum);
            Sleep(1000);
            printf("  �Ƿ�����Ծ�\n  1.����һ��\n  2.�ص��˵�\n");
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
            printf("  �Ƿ�����Ծ�\n  1.����һ��\n  2.�ص��˵�\n");
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
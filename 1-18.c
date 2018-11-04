/*
07-图4 哈利·波特的考试 （25 分）
哈利·波特要考试了，他需要你的帮助。这门课学的是用魔咒将一种动物变成另一种动物
的本事。例如将猫变成老鼠的魔咒是haha，将老鼠变成鱼的魔咒是hehe等等。反方向变
化的魔咒就是简单地将原来的魔咒倒过来念，例如ahah可以将老鼠变成猫。另外，如果
想把猫变成鱼，可以通过念一个直接魔咒lalala，也可以将猫变老鼠、老鼠变鱼的魔咒
连起来念：hahahehe。

现在哈利·波特的手里有一本教材，里面列出了所有的变形魔咒和能变的动物。老师允许
他自己带一只动物去考场，要考察他把这只动物变成任意一只指定动物的本事。于是他来
问你：带什么动物去可以让最难变的那种动物（即该动物变为哈利·波特自己带去的动物
所需要的魔咒最长）需要的魔咒最短？例如：如果只有猫、鼠、鱼，则显然哈利·波特应
该带鼠去，因为鼠变成另外两种动物都只需要念4个字符；而如果带猫去，则至少需要念
6个字符才能把猫变成鱼；同理，带鱼去也不是最好的选择。

输入格式:
输入说明：输入第1行给出两个正整数N (≤100)和M，其中N是考试涉及的动物总数，M是
用于直接变形的魔咒条数。为简单起见，我们将动物按1~N编号。随后M行，每行给出了3
个正整数，分别是两种动物的编号、以及它们之间变形需要的魔咒的长度(≤100)，数字
之间用空格分隔。

输出格式:
输出哈利·波特应该带去考场的动物的编号、以及最长的变形魔咒的长度，中间以空格分
隔。如果只带1只动物是不可能完成所有变形要求的，则输出0。如果有若干只动物都可以
备选，则输出编号最小的那只。

输入样例:
6 11
3 4 70
1 2 1
5 4 50
2 6 50
5 6 60
1 3 70
4 6 60
3 6 80
5 1 100
2 4 60
5 2 80
输出样例:
4 70
作者: 陈越
单位: 浙江大学
时间限制: 400 ms
内存限制: 64 MB
代码长度限制: 16 KB

*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_INT 0x7fff
#define SIDE 100

typedef int MAT[SIDE][SIDE];
void read_input(int M, int E, MAT mat);
void Floyd(int N, MAT mat, MAT path);
void Find_Min(int N, MAT mat);
void print_mat(int N, MAT mat);

int main(int argc, char const *argv[])
{   
    int N, E;
    scanf("%d %d", &N, &E);
    MAT mat, path;
    read_input(N, E, mat);
    //print_mat(N, mat);
    Floyd(N, mat, path);
    //print_mat(N, mat);
    Find_Min(N, mat);
    scanf("%d %d", &N, &E);
    return 0;
}

void read_input(int N, int E, MAT mat)
{   // 读取输入
    int x, y, w;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            mat[i][j] = MAX_INT;
        }
        mat[i][i] = 0;
    }
    for(int i=0; i<E; i++)
    {
        scanf("%d %d %d", &x, &y, &w);
        mat[x-1][y-1] = w;
        mat[y-1][x-1] = w;
    }
}

void Floyd(int N, MAT mat, MAT path)
{   // 注意ijk的顺序
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            path[i][j] = -1;
        }
    }
    for(int k=0; k<N; k++)
    {
        for(int i=0; i<N; i++)
        {
           for(int j=0; j<N; j++)
            {   
                if (mat[i][j] > mat[i][k] + mat[j][k])
                {
                    mat[i][j] = mat[i][k] + mat[j][k];
                    path[i][j] = k;
                }
            }
        }
    }
}

void Find_Min(int N, MAT mat)
{   // 寻找最大长度最小的一行
    int sum, min_sum = MAX_INT, min_sum_i = -1, max_w, min_sum_max_w=MAX_INT;
    for(int i=0; i<N; i++)
    {   
        sum = 0;
        max_w = -1;
        for(int j=0; j<N; j++)
        {   
            if (mat[i][j] > max_w)
                max_w = mat[i][j];
            sum += mat[i][j];
        }
        //printf("%d max: %d\n", i+1, max_w);
        if (max_w < min_sum_max_w)
        {
            min_sum = sum;
            min_sum_i = i;
            min_sum_max_w = max_w;
        }
    }
    if (min_sum >= MAX_INT)
        printf("0");
    else
        printf("%d %d", min_sum_i + 1, min_sum_max_w);
}

void print_mat(int N, MAT mat)
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            printf("%05d, ", mat[i][j]);
        }
        printf("\n");
    }
}
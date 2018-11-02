/*
06-图2 Saving James Bond - Easy Version （25 分）
This time let us consider the situation in the movie "Live and Let Die" 
in which James Bond, the world's most famous spy, was captured by a group 
of drug dealers. He was sent to a small piece of land at the center of 
a lake filled with crocodiles. There he performed the most daring action 
to escape -- he jumped onto the head of the nearest crocodile! Before the 
animal realized what was happening, James jumped again onto the next big 
head... Finally he reached the bank before the last crocodile could bite 
him (actually the stunt man was caught by the big mouth and barely escaped 
with his extra thick boot).

Assume that the lake is a 100 by 100 square one. Assume that the center 
of the lake is at (0,0) and the northeast corner at (50,50). The central 
island is a disk centered at (0,0) with the diameter of 15. A number of 
crocodiles are in the lake at various positions. Given the coordinates 
of each crocodile and the distance that James could jump, you must tell 
him whether or not he can escape.

Input Specification:
Each input file contains one test case. Each case starts with a line 
containing two positive integers N (≤100), the number of crocodiles, and 
D, the maximum distance that James could jump. Then N lines follow, each 
containing the (x,y) location of a crocodile. Note that no two crocodiles 
are staying at the same position.

Output Specification:
For each test case, print in a line "Yes" if James can escape, or "No" if not.

Sample Input 1:
14 20
25 -15
-25 28
8 49
29 15
-35 -2
5 28
27 -29
-8 -28
-20 -35
-25 -20
-13 29
-30 15
-35 40
12 12
Sample Output 1:
Yes
Sample Input 2:
4 13
-12 12
12 12
-12 -12
12 -12
Sample Output 2:
No
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define WIDTH 50
#define RAIDUS 7.5000

struct Graph
{
    int node_num;
    int *x;
    int *y;
    int *reach;
    double jump_len;
};

typedef struct Graph *pgraph;

pgraph create_graph(int N, int J);
int jump(pgraph pg, int pos1, int pos2);
int DFS(pgraph pg, int pos);


int main(int argc, char const *argv[])
{   
    int N, J, is_reach;
    pgraph pg;
    scanf("%d %d", &N, &J);
    pg = create_graph(N, J);
    is_reach = DFS(pg, 0);
    if (is_reach)
        printf("Yes");
    else
        printf("No");
    //scanf("%d %d", &N, &J);
    return 0;
}

pgraph create_graph(int N, int J)
{
    int *x, *y, *reach;
    x = (int *)malloc((N+2)*sizeof(int));
    y = (int *)malloc((N+2)*sizeof(int));
    reach = (int *)malloc((N+2)*sizeof(int));
    x[0] = 0;
    y[0] = 0;
    x[N+1] = 50;
    y[N+1] = 50;
    reach[N+1] = 0;
    for(int i=1; i<=N; i++)
    {   
        reach[i] = 0;
        scanf("%d %d", x+i, y+i);
    }
    pgraph pg;
    pg = (pgraph)malloc(sizeof(struct Graph));
    pg->node_num = N;
    pg->jump_len = J * 1.0;
    pg->x = x;
    pg->y = y;
    pg->reach = reach;
    return pg;
}

int DFS(pgraph pg, int pos) 
{   // 深度优先探索
    int is_reach = 0;
    for(int i=1; i<=pg->node_num+1; i++)
    {
        if (pg->reach[i] == 0 && jump(pg, pos, i) == 1) // 剔除已到达点 与不能到达点
        {   
            //printf("reach (%d, %d) node:%d\n", pg->x[i], pg->y[i], i);
            if (i == pg->node_num+1)        // 目的地为终点
                return 1;                   // 程序结束
            pg->reach[i] = 1;
            is_reach = DFS(pg, i);          // 子程序到达目的地 程序结束
            if (is_reach == 1)
                return is_reach;
        }
    }
    return is_reach;
}


int jump(pgraph pg, int pos1, int pos2)
{   
    double distance, jump_len;
    if (pos1 == pos2)                               // 禁止原地跳
        return 0;
    if (pos2 == pg->node_num + 1)                   // 若目的地为终点
    {   
        jump_len = pg->jump_len;
        if (pos1 == 0)                              // 若出发点为起点
            jump_len += RAIDUS;
        if((pg->x[pos1] >= WIDTH - jump_len) || (pg->x[pos1] <= -WIDTH + jump_len) ||
           (pg->y[pos1] >= WIDTH - jump_len) || (pg->y[pos1] <= -WIDTH + jump_len))
            return 1;                               // 能跳到岸
        else
            return 0;                               // 不能跳到岸
    }
    distance = sqrt((pg->x[pos1] - pg->x[pos2]) * (pg->x[pos1] - pg->x[pos2])
                  + (pg->y[pos1] - pg->y[pos2]) * (pg->y[pos1] - pg->y[pos2]));
    if (pos1 == 0)                                  // 若出发点为起点
        jump_len = pg->jump_len + RAIDUS;
    else                                            //
        jump_len = pg->jump_len;
    if (jump_len >= distance)                       // 能跳到岸
        return 1;
    else
        return 0;
}


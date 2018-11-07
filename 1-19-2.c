/*
07-图5 Saving James Bond - Hard Version （30 分）
This time let us consider the situation in the movie "Live and Let Die" in 
which James Bond, the world's most famous spy, was captured by a group of 
drug dealers. He was sent to a small piece of land at the center of a lake 
filled with crocodiles. There he performed the most daring action to escape 
-- he jumped onto the head of the nearest crocodile! Before the animal realized 
what was happening, James jumped again onto the next big head... Finally 
he reached the bank before the last crocodile could bite him (actually the 
stunt man was caught by the big mouth and barely escaped with his extra thick 
boot).

Assume that the lake is a 100 by 100 square one. Assume that the center of 
the lake is at (0,0) and the northeast corner at (50,50). The central island 
is a disk centered at (0,0) with the diameter of 15. A number of crocodiles 
are in the lake at various positions. Given the coordinates of each crocodile 
and the distance that James could jump, you must tell him a shortest path to 
reach one of the banks. The length of a path is the number of jumps that James 
has to make.

Input Specification:
Each input file contains one test case. Each case starts with a line containing 
two positive integers N (≤100), the number of crocodiles, and D, the maximum 
distance that James could jump. Then N lines follow, each containing the (x,y) 
location of a crocodile. Note that no two crocodiles are staying at the same 
position.

Output Specification:
For each test case, if James can escape, output in one line the minimum number 
of jumps he must make. Then starting from the next line, output the position 
(x,y) of each crocodile on the path, each pair in one line, from the island 
to the bank. If it is impossible for James to escape that way, simply give 
him 0 as the number of jumps. If there are many shortest paths, just output 
the one with the minimum first jump, which is guaranteed to be unique.

Sample Input 1:
17 15
10 -21
10 21
-40 10
30 -50
20 40
35 10
0 -10
-25 22
40 -40
-30 30
-10 22
0 11
25 21
25 10
10 10
10 35
-30 10
Sample Output 1:
4
0 11
10 21
10 35
Sample Input 2:
4 13
-12 12
12 12
-12 -12
12 -12
Sample Output 2:
0
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define WIDTH 50
#define RAIDUS 7.5000
#define MAX_DISTANCE 1000000.0
#define MAX_NODE 100
#define false 0
#define true 1

struct Graph
{
    int node_num;
    int Nv;
    int *x;
    int *y;
    int *path;
    double *dist;
    double (*G)[MAX_NODE];
    double jump_len;
};

typedef struct Graph *pgraph;

pgraph create_graph(int N, int J);
double jump(pgraph pg, int pos1, int pos2);
int FindMinDist( pgraph graph, int collected[] );
int Dijkstra( pgraph graph, int S );
void print_path(pgraph pg, int pos, int step);

int main(int argc, char const *argv[])
{   
    int N, J, is_reach;
    pgraph pg;
    scanf("%d %d", &N, &J);
    pg = create_graph(N, J);
    is_reach = Dijkstra(pg, 0);
    // for(int i=0; i<=pg->node_num+1; i++)
    //     printf("%d:%0.2lf, ", i, pg->dist[i]);
    // printf("\n");
    // for(int i=0; i<=pg->node_num+1; i++)
    //     printf("%d:%d, ", i, pg->path[i]);
    // printf("\n");
    if (is_reach)
        print_path(pg, pg->node_num+1, 0);
    else
        printf("0");
    scanf("%d %d", &N, &J);
    return 0;
}

pgraph create_graph(int N, int J)
{
    int *x, *y, *path;
    double *dist, (*G)[MAX_NODE];
    x = (int *)malloc((N+2)*sizeof(int));
    y = (int *)malloc((N+2)*sizeof(int));
    path = (int *)malloc((N+2)*sizeof(int));
    dist = (double*)malloc((N+2)*sizeof(double));
    G = (double(*)[MAX_NODE])malloc((N+2)*MAX_NODE*sizeof(double));
    x[0] = 0;
    y[0] = 0;
    x[N+1] = 50;
    y[N+1] = 50;
    path[0] = 0;
    path[N+1] = -1;
    dist[0] = 0;
    dist[N+1] = MAX_DISTANCE;
    for(int i=1; i<=N; i++)
    {   
        path[i] = -1;
        dist[i] = MAX_DISTANCE;
        scanf("%d %d", x+i, y+i);
    }
    pgraph pg;
    pg = (pgraph)malloc(sizeof(struct Graph));
    pg->node_num = N;
    pg->Nv = N + 2;
    pg->jump_len = J * 1.0;
    pg->x = x;
    pg->y = y;
    pg->path = path;
    pg->dist = dist;
    pg->G = G;
    return pg;
}


int FindMinDist( pgraph graph, int collected[] )
{ /* 返回未被收录顶点中dist最小者 */
    int MinV, V;
    double MinDist = MAX_NODE;
 
    for (V=0; V<graph->Nv; V++) 
    {
        if ( collected[V]==false && graph->dist[V]<MinDist) 
        {
            /* 若V未被收录，且dist[V]更小 */
            MinDist = graph->dist[V]; /* 更新最小距离 */
            MinV = V; /* 更新对应顶点 */
        }
    }
    if (MinDist < MAX_NODE) /* 若找到最小dist */
        return MinV; /* 返回对应的顶点下标 */
    else return -1;  /* 若这样的顶点不存在，返回错误标记 */
}
 
int Dijkstra( pgraph graph, int S )
{
    int collected[MAX_NODE];
    int V, W;
    
    for ( int i=0; i<graph->Nv; i++)
    {
        for (int j=0; j<graph->Nv; j++)
        {
            graph->G[i][j] = jump(graph, i, j);
        }
    }
    /* 初始化：此处默认邻接矩阵中不存在的边用MAX_NODE表示 */
    for ( V=0; V<graph->Nv; V++ ) 
    {
        graph->dist[V] = graph->G[S][V];
        if ( graph->dist[V]<MAX_DISTANCE )
            graph->path[V] = S;
        else
            graph->path[V] = -1;
        collected[V] = false;
    }
    /* 先将起点收入集合 */
    graph->dist[S] = 0;
    collected[S] = true;
 
    while (true) 
    {
        /* V = 未被收录顶点中dist最小者 */
        V = FindMinDist( graph, collected );
        if ( V==-1 ) /* 若这样的V不存在 */
            break;      /* 算法结束 */
        collected[V] = true;  /* 收录V */
        printf("collect %d (%d, %d)\n", V, graph->x[V], graph->y[V]);
        for( W=0; W<graph->Nv; W++ ) /* 对图中的每个顶点W */
        {
            /* 若W是V的邻接点并且未被收录 */
            if ( graph->G[V][W] < MAX_DISTANCE) 
            {
                if ( graph->G[V][W]<0 ) /* 若有负边 */
                    return false; /* 不能正确解决，返回错误标记 */
                /* 若收录V使得dist[W]变小 */
                if ( graph->dist[V]+graph->G[V][W] < graph->dist[W] ||
                    (graph->dist[V]+graph->G[V][W] == graph->dist[W] && V < graph->path[W])) 
                {   
                    printf("%.0lf + %.0lf < %.0lf\n", graph->dist[V], graph->G[V][W], graph->dist[W]);
                    printf("0->(%d, %d)->(%d, %d)\n", graph->x[V], graph->y[V], graph->x[W], graph->y[W]);
                    graph->dist[W] = graph->dist[V]+graph->G[V][W]; /* 更新dist[W] */
                    graph->path[W] = V; /* 更新S到W的路径 */
                }
            }
        }
    } /* while结束*/
    if (graph->dist[graph->Nv-1] < MAX_DISTANCE)
        return true; 
    else
        return false;
}


void print_path(pgraph pg, int pos, int step)
{   
    step++;
    if (pg->path[pos] < 0)
    {   
        printf("0\n");
        return;
    }
    if (pg->path[pos] == 0)
        printf("%d\n", step);
    else
        print_path(pg, pg->path[pos], step);
    if (pos <= pg->node_num)
        printf("%d %d\n", pg->x[pos], pg->y[pos]);
}

double jump(pgraph pg, int pos1, int pos2)
{   
    double distance;
    if (pos2 == pos1)
        return 0;
    if (pos2 == pg->node_num + 1)                   // 若目的地为终点
    {   
        double d_x, d_y;
        if (pg->x[pos1] > 0)
            d_x = WIDTH - pg->x[pos1];
        else
            d_x = WIDTH + pg->x[pos1];
        if (pg->y[pos1] > 0)
            d_y = WIDTH - pg->y[pos1];
        else
            d_y = WIDTH + pg->y[pos1];
        if (d_x < 0)
            d_x = -d_x;
        if (d_y < 0)
            d_y = -d_y;
        if (d_x < d_y)
            distance = d_x;
        else
            distance = d_y;
    }
    else
    {
        distance = sqrt((pg->x[pos1] - pg->x[pos2]) * (pg->x[pos1] - pg->x[pos2]) * 1.0
                      + (pg->y[pos1] - pg->y[pos2]) * (pg->y[pos1] - pg->y[pos2]) * 1.0);
    }
    if (pos1 == 0)                                  // 若出发点为起点
        distance -= RAIDUS;
    //printf("jump %d->%d %.2lf\n", pos1, pos2, distance);
    if (distance > pg->jump_len)
        return MAX_DISTANCE;
    if (distance < 0)
        return 0;
    else
        return 1;
}


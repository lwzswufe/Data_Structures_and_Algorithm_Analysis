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

struct Graph
{
    int node_num;
    int *x;
    int *y;
    int *path;
    double jump_len;
};

struct Queue
{
    int *arr;
    int size;
    int front;
    int rear;
};

typedef struct Graph *pgraph;
typedef struct Queue* pqueue;

pgraph create_graph(int N, int J);
double jump(pgraph pg, int pos1, int pos2);
int BFS(pgraph pg);
void insert(pqueue, int);
int delete(pqueue);
pqueue create_queue(int);
void print_path(pgraph pg, int pos, int step);

int main(int argc, char const *argv[])
{   
    int N, J, is_reach;
    pgraph pg;
    scanf("%d %d", &N, &J);
    pg = create_graph(N, J);
    is_reach = BFS(pg);
    // for(int i=0; i<pg->node_num+2; i++)
    //     printf("%d, ", pg->path[i]);
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
    x = (int *)malloc((N+2)*sizeof(int));
    y = (int *)malloc((N+2)*sizeof(int));
    path = (int *)malloc((N+2)*sizeof(int));
    x[0] = 0;
    y[0] = 0;
    path[0] = 0;
    x[N+1] = WIDTH;
    y[N+1] = WIDTH;
    path[N+1] = -1;
    for(int i=1; i<=N; i++)
    {   
        path[i] = -1;
        scanf("%d %d", x+i, y+i);
    }
    pgraph pg;
    pg = (pgraph)malloc(sizeof(struct Graph));
    pg->node_num = N;
    pg->jump_len = J * 1.0;
    pg->x = x;
    pg->y = y;
    pg->path = path;
    return pg;
}

pqueue create_queue(int N)
{   // 创建队列
    pqueue q;
    int *arr;
    arr = (int*)malloc(N*sizeof(int));
    q = (pqueue)malloc(sizeof(struct Queue));
    q->size = N;
    q->rear = 0;
    q->front = 0;
    q->arr = arr;
    return q;
}

void insert(pqueue q, int x)
{   // 队列插入
    //printf("insert: %d\n", x);
    q->arr[q->front] = x;
    q->front++;
    q->front %= q->size;
}

int delete(pqueue q)
{   // 队列移出数据
    int x;
    x = q->arr[q->rear];
    //printf("delete: %d\n", x);
    q->rear++;
    q->rear %= q->size;
    return x;
}

void sort(pqueue q, pgraph pg)
{
    double dist[pg->node_num+2];
    int posarr[pg->node_num+2], pos, idx[pg->node_num+2], N=0, insert_arr[pg->node_num+2];
    while (q->front != q->rear)
    {   
        pos = delete(q);
        posarr[N] = pos;
        idx[N] = 0;
        dist[N] = jump(pg, 0, pos);
        N++;
    }
    //printf("sort %d\n", N);
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            if (dist[i] > dist[j] || (dist[i] == dist[j] && posarr[i] > posarr[j]))
                idx[i]++ ;
        }
        insert_arr[i] = 0;
    }
    for (int i=0; i<N; i++)
    {   
        //printf("idx:%d pos:%d dist:%.4lf  ", idx[i], posarr[i], dist[i]);
        insert_arr[idx[i]] = posarr[i];
    }
    //printf("\n");
    for (int i=0; i<N; i++)
    {
        insert(q, insert_arr[i]);
    }
}

int BFS(pgraph pg) 
{   // 广度优先探索
    int pos, is_reach = 0;
    pqueue queue = create_queue(pg->node_num + 2);
    insert(queue, 0);
    while (queue->front != queue->rear)
    {
        pos = delete(queue);
        for(int i=1; i<=pg->node_num+1; i++)
        {   
            if (pg->path[i] < 0 && jump(pg, pos, i) > 0) 
            {
                if (pg->path[i] < 0)
                    insert(queue, i);
                pg->path[i] = pos;
                //printf("%d(%d, %d)->%d(%d %d)\n", pos, pg->x[pos], pg->y[pos], i, pg->x[i], pg->y[i]);
                if (i == pg->node_num+1)
                    is_reach = 1;
            }   
        }
        if (pos == 0)
            sort(queue, pg);
    }
    return is_reach;
}

void print_path(pgraph pg, int pos, int step)
{   
    step++;
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
    if (pg->y[pos2] * pg->y[pos2] + pg->x[pos2] * pg->x[pos2] < RAIDUS * RAIDUS)
        return 0;
    if (pos2 != pg->node_num + 1 && 
        (pg->x[pos2] * pg->x[pos2] >= WIDTH * WIDTH ||  pg->y[pos2] * pg->y[pos2] >= WIDTH * WIDTH))
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
            return 0;
        if (d_y < 0)
            return 0;
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
        return 0;
    if (distance < 0)
        return 0;
    else
        return distance;
}


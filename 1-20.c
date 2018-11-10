/*
07-图6 旅游规划 （25 分）
有了一张自驾旅游路线图，你会知道城市间的高速公路长度、以及该公路要收取的
过路费。现在需要你写一个程序，帮助前来咨询的游客找一条出发地和目的地之间
的最短路径。如果有若干条路径都是最短的，那么需要输出最便宜的一条路径。

输入格式:
输入说明：输入数据的第1行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市
的个数，顺便假设城市的编号为0~(N−1)；M是高速公路的条数；S是出发地的城市编
号；D是目的地的城市编号。随后的M行中，每行给出一条高速公路的信息，分别是：
城市1、城市2、高速公路长度、收费额，中间用空格分开，数字均为整数且不超过500。
输入保证解的存在。

输出格式:
在一行里输出路径的长度和收费总额，数字间以空格分隔，输出结尾不能有多余空格。

输入样例:
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
输出样例:
3 40
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_DISTANCE 0x7fffffff
#define MAX_NODE 500
#define false 0
#define true 1

struct Graph
{
    int N;
    int *path;
    int *cost;
    int *dist;
    int (*Dist)[MAX_NODE];
    int (*Cost)[MAX_NODE];
};

typedef struct Graph *pgraph;

pgraph create_graph(int N, int J);
double jump(pgraph pg, int pos1, int pos2);
int FindMinDist( pgraph graph, int collected[] );
int Dijkstra( pgraph graph, int S );
void print_path(pgraph pg, int pos, int step);

int main(int argc, char const *argv[])
{   
    int N, M, S, D;
    pgraph graph;
    scanf("%d %d %d %d", &N, &M, &S, &D);
    graph = create_graph(N, M);
    Dijkstra(graph, S);
    printf("%d %d", graph->dist[D], graph->cost[D]);
    scanf("%d %d %d %d", &N, &M, &S, &D);
    return 0;
}

pgraph create_graph(int N, int M)
{
    int *path, *dist, *cost, (*Dist)[MAX_NODE], (*Cost)[MAX_NODE];
    path = (int *)malloc((N)*sizeof(int));
    dist = (int*)malloc((N)*sizeof(int));
    cost = (int*)malloc((N)*sizeof(int));
    Dist = (int(*)[MAX_NODE])malloc((N)*MAX_NODE*sizeof(int));
    Cost = (int(*)[MAX_NODE])malloc((N)*MAX_NODE*sizeof(int));
    for(int i=0; i<N; i++)
    {   
        for (int j=0; j<N; j++)
        {
            Dist[i][j] = MAX_DISTANCE;
            Cost[i][j] = MAX_DISTANCE;
        }
        dist[i] = MAX_DISTANCE;
        cost[i] = MAX_DISTANCE;
        path[i] = -1;
    }
    int s, d, l, f;
    for(int i=0; i<M; i++)
    {
        scanf("%d %d %d %d", &s, &d, &l, &f);
        Dist[s][d] = l; 
        Cost[s][d] = f;
        Dist[d][s] = l; 
        Cost[d][s] = f;
    }
    pgraph pg;
    pg = (pgraph)malloc(sizeof(struct Graph));
    pg->N = N;
    pg->dist = dist;
    pg->cost = cost;
    pg->path = path;
    pg->Dist = Dist;
    pg->Cost = Cost;
    return pg;
}

int FindMinDist( pgraph graph, int collected[] )
{ /* 返回未被收录顶点中dist最小者 */
    int MinV, V;
    int MinDist = MAX_DISTANCE;
    int MinCost = MAX_DISTANCE;
 
    for (V=0; V<graph->N; V++) 
    {
        if ( collected[V] == false &&           // 若V未被收录，且dist[V]更小 dist相同比较cost
             (graph->dist[V] <  MinDist ||
              (graph->dist[V] == MinDist && graph->cost[V] < MinCost)
             )
           )

        {
            MinDist = graph->dist[V];           // 更新最小距离 
            MinCost = graph->cost[V];
            MinV = V;                           // 更新对应顶点 
        }
    }
    if (MinDist < MAX_DISTANCE)                 // 若找到最小dist 
        return MinV;                            // 返回对应的顶点下标
    else return -1;                             // 若这样的顶点不存在，返回错误标记 
}
 
int Dijkstra( pgraph graph, int S )
{
    int collected[graph->N];
    int V, W, new_dist, new_cost;
    
    /* 初始化：此处默认邻接矩阵中不存在的边用MAX_NODE表示 */
    for ( V=0; V<graph->N; V++ ) 
    {
        graph->dist[V] = graph->Dist[S][V];
        graph->cost[V] = graph->Cost[S][V];
        if ( graph->dist[V]<MAX_DISTANCE )
            graph->path[V] = S;
        else
            graph->path[V] = -1;
        collected[V] = false;
    }
    graph->dist[S] = 0;                         //先将起点收入集合 
    graph->cost[V] = 0;
    collected[S] = true;
 
    while (true) 
    {
        V = FindMinDist( graph, collected );    // V = 未被收录顶点中dist最小者
        if ( V==-1 )                            // 若这样的V不存在 
            break;                              // 算法结束 
        collected[V] = true;                    // 收录V
        //printf("collect %d (%d, %d)\n", V, graph->x[V], graph->y[V]);
        for( W=0; W<graph->N; W++ )             // 对图中的每个顶点W 
        {
            if (collected[W] == false &&        // 若W是V的邻接点并且未被收录
                graph->Dist[V][W] < MAX_DISTANCE)  
            {
                if ( graph->Dist[V][W]<0 )      // 若有负边 
                    return false;               // 不能正确解决，返回错误标记 
                                                // 若收录V使得dist[W]变小
                new_dist = graph->dist[V] + graph->Dist[V][W];
                new_cost = graph->cost[V] + graph->Cost[V][W];
                if ( new_dist <  graph->dist[W] ||
                    (new_dist == graph->dist[W] &&
                     new_cost <  graph->cost[W])) 
                {   
                    //printf("dist:%d cost:%d update dist:%d cost:%d\n",
                    // graph->dist[W], graph->cost[W], new_dist, new_cost);
                    graph->dist[W] = new_dist; // 更新dist[W] 
                    graph->cost[W] = new_cost;
                    graph->path[W] = V;         // 更新S到W的路径 
                }
            }
        }
    } // while结束
    if (graph->dist[graph->N-1] < MAX_DISTANCE)
        return true; 
    else
        return false;
}
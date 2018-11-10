/*
08-图7 公路村村通 （30 分）
现有村落间道路的统计数据表中，列出了有可能建设成标准公路的若干条道路
的成本，求使每个村落都有公路连通所需要的最低成本。

输入格式:
输入数据包括城镇数目正整数N（≤1000）和候选道路数目M（≤3N）；随后的M
行对应M条道路，每行给出3个正整数，分别是该条道路直接连通的两个城镇的
编号以及该道路改建的预算成本。为简单起见，城镇从1到N编号。

输出格式:
输出村村通需要的最低成本。如果输入数据不足以保证畅通，则输出−1，表示
需要建设更多公路。

输入样例:
6 15
1 2 5
1 3 3
1 4 7
1 5 4
1 6 2
2 3 4
2 4 6
2 5 2
2 6 6
3 4 6
3 5 1
3 6 1
4 5 10
4 6 8
5 6 3
输出样例:
12
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_DISTANCE 0x7fffffff
#define MAX_NODE 1000
#define false 0
#define true 1

struct MGraph
{
    int N;
    int *parent;
    int *dist;
    int (*Dist)[MAX_NODE];
};

typedef struct MGraph *pgraph;

pgraph create_graph(int N, int J);
int FindMinDist( pgraph graph);
int Prim( pgraph graph, int S );

int main(int argc, char const *argv[])
{   
    int N, M;
    pgraph graph;
    scanf("%d %d", &N, &M);
    graph = create_graph(N, M);
    Prim(graph, 0);
    scanf("%d %d", &N, &M);
    return 0;
}

pgraph create_graph(int N, int M)
{
    int *parent, *dist, (*Dist)[MAX_NODE];
    parent = (int *)malloc((N)*sizeof(int));
    dist = (int*)malloc((N)*sizeof(int));
    Dist = (int(*)[MAX_NODE])malloc((N)*MAX_NODE*sizeof(int));
    for(int i=0; i<N; i++)
    {   
        for (int j=0; j<N; j++)
        {
            Dist[i][j] = MAX_DISTANCE;
        }
        dist[i] = MAX_DISTANCE;
        parent[i] = -1;
    }
    int s, d, l;
    for(int i=0; i<M; i++)
    {
        scanf("%d %d %d", &s, &d, &l);
        Dist[s-1][d-1] = l; 
        Dist[d-1][s-1] = l; 
    }
    pgraph pg;
    pg = (pgraph)malloc(sizeof(struct MGraph));
    pg->N = N;
    pg->dist = dist;
    pg->parent = parent;
    pg->Dist = Dist;
    return pg;
}

int FindMinDist( pgraph graph)
{ /* 返回未被收录顶点中dist最小者 */
    int MinV, V;
    int MinDist = MAX_DISTANCE;
 
    for (V=0; V<graph->N; V++) 
    {
        if ( graph->dist[V] <  MinDist && graph->dist[V] > 0)

        {
            MinDist = graph->dist[V];                   // 更新最小距离 
            MinV = V;                                   // 更新对应顶点 
        }
    }
    if (MinDist < MAX_DISTANCE)                         // 若找到最小dist 
        return MinV;                                    // 返回对应的顶点下标
    else return -1;                                     // 若这样的顶点不存在，返回错误标记 
}

int Prim( pgraph graph, int S )
{   // Prim算法构建最小生成树  dist[V] == 0表示点已经被收录
    int V, W, total_weight=0, total_node=0;

    for ( V=0; V<graph->N; V++ ) 
    {
        graph->dist[V] = graph->Dist[S][V];
        graph->parent[V] = S; 
    }
    graph->parent[S] = -1;                               // 先将起点收入集合
    total_node++;
    graph->dist[S] = 0;
 
    while (true) 
    {
        V = FindMinDist( graph );                       // V = 未被收录顶点中dist最小者
        // printf("min V is:%d  ", V);
        if ( V < 0 )                                    // 若这样的V不存在 
            break;                                      // 算法结束 
        total_node++;
        W = graph->parent[V];
        if ( W < 0 )                                    
            break; 
        total_weight += graph->Dist[V][W];
        graph->dist[V] = 0;
        // printf("collect %d->%d len:%d\n", W, V, graph->Dist[V][W]);
        for( W=0; W<graph->N; W++ )                     // 对图中的每个顶点W 
        {
                                                        // 若W是V的邻接点并且未被收录 
            if ( graph->dist[W] > 0 && graph->Dist[V][W] < MAX_DISTANCE) 
            {
                                                        // 若收录V使得dist[W]变小 
                if ( graph->Dist[V][W] < graph->dist[W]) 
                {   
                    graph->dist[W] = graph->Dist[V][W]; // 更新dist[W] 
                    graph->parent[W] = V;               // 更新S到W的路径
                    // printf("set %d->%d\n", V, W);
                }
            }
        }
    }                                                   // while结束
    if (total_node == graph->N)
        printf("%d\n", total_weight);
    else
        printf("-1\n");
    return 0;
}
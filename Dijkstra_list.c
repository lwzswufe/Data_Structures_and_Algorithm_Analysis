/* 邻接矩阵存储 - 有权图的单源最短路算法 */
typedef int Vertex;
#define ERROR -1
#define false 0
#define true 1
#define INFINITY 0x7fffff               // 无穷大
#define MaxVertexNum 100                // 最大节点数
#include <stdio.h>
#include <stdlib.h>

typedef int WeightType;                 // 权重数据类型 int或double
struct Graph
{
    int Nv;
    WeightType (*G)[MaxVertexNum];
};
typedef struct Graph *pgraph;
typedef struct Graph* MGraph;


Vertex FindMinDist( MGraph Graph, WeightType dist[], int collected[] )
{ /* 返回未被收录顶点中dist最小者 */
    Vertex MinV, V;
    WeightType MinDist = INFINITY;
 
    for (V=0; V<Graph->Nv; V++) 
    {
        if ( collected[V]==false && dist[V]<MinDist) 
        {
            /* 若V未被收录，且dist[V]更小 */
            MinDist = dist[V]; /* 更新最小距离 */
            MinV = V; /* 更新对应顶点 */
        }
    }
    if (MinDist < INFINITY) /* 若找到最小dist */
        return MinV; /* 返回对应的顶点下标 */
    else return ERROR;  /* 若这样的顶点不存在，返回错误标记 */
}
 
int Dijkstra( MGraph Graph, WeightType dist[], int path[], Vertex S )
{
    int collected[MaxVertexNum];
    Vertex V, W;
 
    /* 初始化：此处默认邻接矩阵中不存在的边用INFINITY表示 */
    for ( V=0; V<Graph->Nv; V++ ) 
    {
        dist[V] = Graph->G[S][V];
        if ( dist[V]<INFINITY )
            path[V] = S;
        else
            path[V] = -1;
        collected[V] = false;
    }
    /* 先将起点收入集合 */
    dist[S] = 0;
    collected[S] = true;
 
    while (true) 
    {
        /* V = 未被收录顶点中dist最小者 */
        V = FindMinDist( Graph, dist, collected );
        if ( V==ERROR ) /* 若这样的V不存在 */
            break;      /* 算法结束 */
        collected[V] = true;  /* 收录V */
        printf("collect %d\n", V);
        for( W=0; W<Graph->Nv; W++ ) /* 对图中的每个顶点W */
        {
            /* 若W是V的邻接点并且未被收录 */
            if ( collected[W]==false && Graph->G[V][W]<INFINITY ) 
            {
                if ( Graph->G[V][W]<0 ) /* 若有负边 */
                    return false; /* 不能正确解决，返回错误标记 */
                /* 若收录V使得dist[W]变小 */
                if ( dist[V]+Graph->G[V][W] < dist[W] ) 
                {   
                    //printf("0->W = 0->V->W\n");
                    dist[W] = dist[V]+Graph->G[V][W]; /* 更新dist[W] */
                    path[W] = V; /* 更新S到W的路径 */
                }
            }
        }
    } /* while结束*/
    return true; /* 算法执行完毕，返回正确标记 */
}

MGraph create_Graph(int N)
{   
    MGraph graph;
    WeightType (*mat)[MaxVertexNum];
    mat = (int(*)[MaxVertexNum])malloc(N * MaxVertexNum * sizeof(int));
    for (int i=0; i<N; i++)
    {   
        for (int j=0; j<N; j++)
        {
            mat[i][j] = INFINITY;
        }
    }
    graph = (MGraph)malloc(sizeof(struct Graph));
    graph->G = mat;
    graph->Nv = N;
    return graph;
}

void print_path(int *path, int S, int V)
{   // 输出S->V路径
    if (S == V)
        printf("%d", S);
    else
    {   
        if (path[V] < 0)
            printf("break");
        else
        {   
            print_path(path, S, path[V]);
            printf("->%d", V);
        }
    }
}


void read_input(int N, MGraph graph, char *strs)
{   
    int x, y, w;
    for(int i=0; i<N; i++, strs+=6)
    {   
        sscanf_s(strs, "%d %d %d", &x, &y, &w);
        graph->G[x-1][y-1] = w;
        printf("%d %d %d\n", x, y, w);
    }
}

int main(int argc, char const *argv[])
{
    MGraph graph;
    int N = 7;
    graph = create_Graph(N);
    char map[] = "1 2 2\t1 4 1\t2 4 3\t2 5 9\t3 1 4\t3 6 5\t4 2 3\t4 3 2\t4 6 8\t4 7 4\t5 7 6\t7 6 1";
    read_input(12, graph, map);
    printf("Graph init over\n");
    WeightType dist[N];
    Vertex S = 0;
    int path[N];
    Dijkstra(graph, dist, path, S );
    print_path(path, S, 5);
    return 0;
}

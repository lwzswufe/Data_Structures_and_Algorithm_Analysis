/*
08-图8 How Long Does It Take （25 分）
Given the relations of all the activities of a project, you 
are supposed to find the earliest completion time of the project.

Input Specification:
Each input file contains one test case. Each case starts with a line 
containing two positive integers N (≤100), the number of activity check 
points (hence it is assumed that the check points are numbered from 0 to
 N−1), and M, the number of activities. Then M lines follow, each gives 
 the description of an activity. For the i-th activity, three non-negative 
 numbers are given: S[i], E[i], and L[i], where S[i] is the index of the 
 starting check point, E[i] of the ending check point, and L[i] the lasting 
 time of the activity. The numbers in a line are separated by a space.

Output Specification:
For each test case, if the scheduling is possible, print in a line its earliest 
completion time; or simply output "Impossible".

Sample Input 1:
9 12
0 1 6
0 2 4
0 3 5
1 4 1
2 4 1
3 5 2
5 4 0
4 6 9
4 7 7
5 7 4
6 8 2
7 8 4
Sample Output 1:
18
Sample Input 2:
4 5
0 1 1
0 2 2
2 1 3
1 3 4
3 2 5
Sample Output 2:
Impossible
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_DISTANCE 0x7fffffff
#define MAX_NODE 1000
#define false 0
#define true 1


struct Queue
{
    int rear;
    int front;
    int size;
    int *arr;
};

typedef struct Queue *pqueue;
struct ENode
{
    int ed;
    int len;
    struct ENode* next;
};

typedef struct ENode *pnode;
struct LGraph
{
    int N;
    pnode* nodearr;
};

typedef struct LGraph *pgraph;

pgraph create_graph(int N, int J);
void graph_insert(pgraph graph, int st, pnode new_node);
void graph_delete(pgraph graph, int st, int ed);
pnode create_node(int ed, int len);
void TopSort(pgraph graph, int *topOrder);

int main(int argc, char const *argv[])
{
    int N, M;
    pgraph graph;
    scanf("%d %d", &N, &M);
    int TopOrder[N];
    graph = create_graph(N, M);
    TopSort(graph, TopOrder);
    scanf("%d %d", &N, &M);
    return 0;
}

void graph_insert(pgraph graph, int st, pnode new_node)
{
    pnode pn = graph->nodearr[st];
    while(pn->next != NULL)
    {
        pn=pn->next;
    }
    pn->next = new_node;
}

void graph_delete(pgraph graph, int st, int ed)
{
    pnode pn = graph->nodearr[st], delete_node;
    while(pn->next != NULL && pn->next->ed != ed)
    {
        pn=pn->next;
    }
    if (pn->next->ed == ed)
    {
        delete_node = pn->next;
        pn->next = pn->next->next;
        free(delete_node);
    }
    else
    {
        printf("we do not find node %d->%d", st, ed);
    }
}

pnode create_node(int ed, int len)
{
    pnode pn;
    pn = (pnode)malloc(sizeof(struct ENode));
    pn->ed = ed;
    pn->len = len;
    pn->next = NULL;
    return pn;
}

pgraph create_graph(int N, int M)
{
    pgraph graph;
    pnode *nodearr, pn;
    graph = (pgraph)malloc(sizeof(struct LGraph));
    nodearr = (pnode*)malloc(N * sizeof(struct ENode));
    graph->N = N;
    graph->nodearr = nodearr;
    for(int i=0; i<N; i++)
    {   
        nodearr[i] = create_node(i, -1);
    }
    int s, d, l;
    for(int i=0; i<M; i++)
    {
        scanf("%d %d %d", &s, &d, &l);
        //printf("%d %d %d\n", s, d, l);
        pn = create_node(d, l);
        graph_insert(graph, s, pn);
    }
    //printf("graph create over\n");
    return graph;
}

pqueue create_queue(int N)
{
    pqueue queue;
    int *arr;
    arr = (int*)malloc(N * sizeof(int));
    queue = (pqueue)malloc(sizeof(struct Queue));
    queue->arr = arr;
    queue->rear = 0;
    queue->front = 0;
    queue->size = N;
    return queue;
}

void insert_queue(pqueue queue, int v)
{   
    //printf("add node %d at %d\n", v, queue->front);
    queue->arr[queue->front] = v;
    queue->front++;
    queue->front %= queue->size;
}

int delete_queue(pqueue queue)
{   
    int v;
    v = queue->arr[queue->rear];
    //printf("pop node %d\n", v);
    queue->rear++;
    queue->rear %= queue->size;
    return v;
}


void TopSort(pgraph graph, int *topOrder)
{
    int InDegree[graph->N], Dist[graph->N], cnt=0, Max_dist=0;
    int V, W;
    pqueue queue = create_queue(graph->N);
    pnode pn;
    for(V=0; V < graph->N; V++)
    {
        InDegree[V] = 0;
        Dist[V] = 0;
    }
    
    for(V=0; V < graph->N; V++)                 // 初始化入度
    {   
        for(pn=graph->nodearr[V]->next; pn != NULL; pn=pn->next)
        {
            InDegree[pn->ed]++;
        }
    }

    for(V=0; V < graph->N; V++)                 // 将入度为0的点加入队列
    {   
        if (InDegree[V] == 0)
        {
            insert_queue(queue, V);
        }
    }

    cnt = 0;
    while(queue->rear != queue->front)
    {
        V = delete_queue(queue);
        topOrder[cnt++] = V;
        for(pn=graph->nodearr[V]->next; pn != NULL; pn=pn->next)    // 删除起点是入度为0的节点的边
        {   
            W = pn->ed;
            //printf("delete %d->%d\n", V, W);
            graph_delete(graph, V, W);
            InDegree[W]--;
            if (InDegree[W] == 0)                                   // 若终点的入度为0 将其加入队列
                insert_queue(queue, W);
            if (Dist[W] < Dist[V] + pn->len)                        // 更新到该点的距离
                Dist[W] = Dist[V] + pn->len;
        }
    }

    for(V=0; V < graph->N; V++)
    {
        if (Dist[V] > Max_dist)
            Max_dist = Dist[V];
    }

    if (cnt != graph->N)
        printf("Impossible\n");
    else
        printf("%d\n", Max_dist);
}
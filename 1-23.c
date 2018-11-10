/*
08-图9 关键活动 （30 分）
假定一个工程项目由一组子任务构成，子任务之间有的可以并行执行，有的必须在完成
了其它一些子任务后才能执行。“任务调度”包括一组子任务、以及每个子任务可以执行
所依赖的子任务集。

比如完成一个专业的所有课程学习和毕业设计可以看成一个本科生要完成的一项工程，
各门课程可以看成是子任务。有些课程可以同时开设，比如英语和C程序设计，它们没
有必须先修哪门的约束；有些课程则不可以同时开设，因为它们有先后的依赖关系，比
如C程序设计和数据结构两门课，必须先学习前者。

但是需要注意的是，对一组子任务，并不是任意的任务调度都是一个可行的方案。比如
方案中存在“子任务A依赖于子任务B，子任务B依赖于子任务C，子任务C又依赖于子任务
A”，那么这三个任务哪个都不能先执行，这就是一个不可行的方案。

任务调度问题中，如果还给出了完成每个子任务需要的时间，则我们可以算出完成整个
工程需要的最短时间。在这些子任务中，有些任务即使推迟几天完成，也不会影响全局
的工期；但是有些任务必须准时完成，否则整个项目的工期就要因此延误，这种任务就
叫“关键活动”。

请编写程序判定一个给定的工程项目的任务调度是否可行；如果该调度方案可行，则计
算完成整个工程项目需要的最短时间，并输出所有的关键活动。

输入格式:
输入第1行给出两个正整数N(≤100)和M，其中N是任务交接点（即衔接相互依赖的两个子
任务的节点，例如：若任务2要在任务1完成后才开始，则两任务之间必有一个交接点）
的数量。交接点按1~N编号，M是子任务的数量，依次编号为1~M。随后M行，每行给出了
3个正整数，分别是该任务开始和完成涉及的交接点编号以及该任务所需的时间，整数间
用空格分隔。

输出格式:
如果任务调度不可行，则输出0；否则第1行输出完成整个工程项目需要的时间，第2行开
始输出所有关键活动，每个关键活动占一行，按格式“V->W”输出，其中V和W为该任务开
始和完成涉及的交接点编号。关键活动输出的顺序规则是：任务开始的交接点编号小者
优先，起点编号相同时，与输入时任务的顺序相反。

输入样例:
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 1
4 6 6
5 7 5
6 7 2
输出样例:
17
1->2
2->4
4->6
6->7
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
{   // 新节点插入到前面
    pnode tmp, pn = graph->nodearr[st];
    tmp = pn->next;
    pn->next = new_node;
    new_node->next = tmp;
}

void graph_delete(pgraph graph, int st, int ed)
{
    pnode pn = graph->nodearr[st];
    while(pn->next != NULL && pn->next->ed != ed)
    {
        pn=pn->next;
    }
    if (pn->next->ed == ed)
    {
        ;
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
        pn = create_node(d-1, l);
        graph_insert(graph, s-1, pn);
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
    int InDegree[graph->N], OutDegree[graph->N], Earlist[graph->N], Latest[graph->N], cnt=0, Max_dist=0;
    int V, W;
    pqueue queue = create_queue(graph->N);
    pnode pn;
    for(V=0; V < graph->N; V++)
    {
        InDegree[V] = 0;
        OutDegree[V] = 0;
        Earlist[V] = 0;
        Latest[V] = MAX_DISTANCE;
    }
    
    for(V=0; V < graph->N; V++)                 // 初始化入度
    {   
        for(pn=graph->nodearr[V]->next; pn != NULL; pn=pn->next)
        {
            InDegree[pn->ed]++;
            OutDegree[V]++;
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
            if (Earlist[W] < Earlist[V] + pn->len)                  // 更新到该点的距离
                Earlist[W] = Earlist[V] + pn->len;
        }
    }

    for(V=0; V < graph->N; V++)
    {
        if (Earlist[V] > Max_dist)
            Max_dist = Earlist[V];
    }

    if (cnt != graph->N)
    {
        printf("0");
        return;
    }
    else
        printf("%d\n", Max_dist);


    for(V=0; V < graph->N; V++)                                         // 将出度为0的点加入队列
    {   
        if (OutDegree[V] == 0)
        {
            insert_queue(queue, V);
            Latest[V] = Max_dist;                                       // 初始化终点的最迟完成时间
        }
    }

    while(queue->rear != queue->front)
    {
        W = delete_queue(queue);
        for(V=0; V < graph->N; V++)                
        {
            for(pn=graph->nodearr[V]->next; pn != NULL; pn=pn->next)    // 删除终点是出度为0的节点的边
            {
                if (pn->ed != W)
                    continue;
                //printf("delete %d->%d\n", V, W);
                OutDegree[V]--;
                if (OutDegree[V] == 0)                                  // 将出度为0的点加入队列
                    insert_queue(queue, V);
                if (Latest[V] > Latest[W] - pn->len)                    // 更新最迟完成时间
                    Latest[V] = Latest[W] - pn->len;
            }
        } 
        
    }

    // for(V=0; V < graph->N; V++)                 
    // {   
    //     printf("%d earlist: %d latest: %d\n", V+1, Earlist[V], Latest[V]);
    // }
    for(V=0; V < graph->N; V++)                 
    {   
        for(pn=graph->nodearr[V]->next; pn != NULL; pn=pn->next)
        {
            W = pn->ed;
            //printf("%d earlist: %d  %d latest: %d len: %d\n", V+1, Earlist[V], W+1, Latest[W], pn->len);
            if (Latest[W] == Earlist[V] + pn->len)
                printf("%d->%d\n", V+1, W+1);
        }
    }
}
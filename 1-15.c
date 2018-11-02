/*
06-图1 列出连通集 （25 分）
给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。
假设顶点从0到N−1编号。进行搜索时，假设我们总是从编号最小的顶点出发，按
编号递增的顺序访问邻接点。

输入格式:
输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。随后E行，每
行给出一条边的两个端点。每行中的数字之间用1空格分隔。

输出格式:
按照"{ v1, v2, ... vk}"的格式，每行输出一个连通集。先输出DFS的结果，
再输出BFS的结果。

输入样例:
8 6
0 7
0 1
2 0
4 1
2 4
3 5
输出样例:
{ 0 1 4 2 7 }
{ 3 5 }
{ 6 }
{ 0 1 2 7 4 }
{ 3 5 }
{ 6 }
*/
#include <stdio.h>
#include <stdlib.h>

struct enode
{
    int id;                 // 编号
    struct enode* next;     // 指向下一条边
};

struct Queue
{
    int *arr;
    int size;
    int front;
    int rear;
};

typedef struct enode* pnode;
typedef pnode* graph;
typedef struct Queue* pqueue;
graph read_input();

void print_graph(graph, int);
void DFS_graph(graph, int);
void DFS(graph, int*, int);
void BFS_graph(graph, int);
void BFS(graph, pqueue, int*);
void insert(pqueue, int);
int delete(pqueue);
pqueue create_queue(int);

int main(int argc, char const *argv[])
{
    graph g;
    int N, E;
    scanf("%d %d", &N, &E);
    g = read_input(N, E);
    //print_graph(g, N);
    DFS_graph(g, N);
    BFS_graph(g, N);
    scanf("%d %d", &N, &E);
    return 0;
}

void DFS(graph g, int *visit, int pos) 
{   // 深度优先探索
    if (visit[pos] == 0)
        printf("%d ", pos);
    visit[pos] = 1;
    pnode pn = g[pos];
    while(pn!=NULL)
    {   
        if (visit[pn->id] == 0)
            DFS(g, visit, pn->id);
        pn = pn->next;
    }
}

void DFS_graph(graph g, int N)
{   // 深度优先主程序 从不同的点出发
    int visit[N], pos=0;
    for(int i=0; i<N; i++)
        visit[i] = 0;
    while(pos < N && visit[pos] == 0)
    {   
        printf("{ ");
        DFS(g, visit, pos);
        printf("}\n");
        pos = 0;
        for(int i=0; i<N && visit[i]>0; i++)
            pos++;
    }
}

void BFS(graph g, pqueue q, int *visit) 
{   // 广度优先探索
    int pos;
    while(q->rear!=q->front)
    {
        pos = delete(q);
        printf("%d ", pos);
        pnode pn = g[pos];
        while(pn!=NULL)
        {   
            if (visit[pn->id] == 0)
            {
                visit[pn->id] = 1;  // 表明该邻接点被加入过队列
                insert(q, pn->id);  // 依次将该点未加入进队列的邻接点 加入队列
            }
            pn = pn->next;
        }
    }
}

void BFS_graph(graph g, int N)
{   // 广度优先探索主程序  
    int visit[N], pos=0;
    pqueue q;
    
    for(int i=0; i<N; i++)
        visit[i] = 0;
    q = create_queue(N + 2);
    insert(q, pos);
    visit[pos] = 1;
    while(q->rear != q->front)
    {   
        printf("{ ");
        BFS(g, q, visit);
        printf("}\n");
        pos = 0;
        for(int i=0; i<N && visit[i]>0; i++)
            pos++;
        if (visit[pos] == 0 && pos<N)
        {
            insert(q, pos);
            visit[pos] = 1;
        }
    }
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

void add_edge(graph g, int v1, int v2)
{   // 增加边
    pnode new_node, pn, tmp;
    new_node = (pnode)malloc(sizeof(struct enode));
    new_node->next = NULL;
    new_node->id = v2;

    if (g[v1] == NULL || g[v1]->id > v2)
    {   
        tmp = g[v1];
        g[v1] = new_node;
        new_node->next = tmp;
    }
    else
    {
        pn = g[v1];
        while(pn->next != NULL && pn->next->id < v2)
        {
            pn = pn->next;
        }
        if (pn->next != NULL)
        {
            tmp = pn->next;
            pn->next = new_node;
            new_node->next = tmp;
        }
        else
        {
            pn->next = new_node;
        }
    }
}

graph read_input(int N, int E)
{   // 读取图
    int v1, v2;
    graph g;
    g = (graph)malloc(N * sizeof(pnode));
    for(int i=0; i<N; i++)
    {   
        g[i] = NULL;
    }
    for(int i=0; i<E; i++)
    {
        scanf("%d %d", &v1, &v2);
        add_edge(g, v1, v2);
        add_edge(g, v2, v1);
    }
    return g;
}

void print_graph(graph g, int N)
{   // 输出图
    pnode pn;
    for(int i=0; i<N; i++)
    {
        pn = g[i];
        printf("%d->", i);
        while(pn != NULL)
        {
            printf("%d,", pn->id);
            pn = pn->next;
        }
        printf("\n");
    }
}

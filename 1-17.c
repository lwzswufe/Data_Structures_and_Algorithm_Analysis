/*
06-图3 六度空间 （30 分）
"六度空间"理论又称作"六度分隔（Six Degrees of Separation）"理论。这个理论
可以通俗地阐述为："你和任何一个陌生人之间所间隔的人不会超过六个，也就是说，最
多通过五个人你就能够认识任何一个陌生人。"如图1所示。


图1 六度空间示意图
"六度空间"理论虽然得到广泛的认同，并且正在得到越来越多的应用。但是数十年来，
试图验证这个理论始终是许多社会学家努力追求的目标。然而由于历史的原因，这样的
研究具有太大的局限性和困难。随着当代人的联络主要依赖于电话、短信、微信以及因
特网上即时通信等工具，能够体现社交网络关系的一手数据已经逐渐使得"六度空间"理
论的验证成为可能。

假如给你一个社交网络图，请你对每个节点计算符合"六度空间"理论的结点占结点总数的
百分比。

输入格式:
输入第1行给出两个正整数，分别表示社交网络图的结点数N（1<N≤10^​4，表示人数）、
边数M（≤33×N，表示社交关系数）。随后的M行对应M条边，每行给出一对正整数，分别是
该条边直接连通的两个结点的编号（节点从1到N编号）。

输出格式:
对每个结点输出与该结点距离不超过6的结点数占结点总数的百分比，精确到小数点后2位。
每个结节点输出一行，格式为"结点编号:（空格）百分比%"。

输入样例:
10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
输出样例:
1: 70.00%
2: 80.00%
3: 90.00%
4: 100.00%
5: 100.00%
6: 100.00%
7: 100.00%
8: 90.00%
9: 80.00%
10: 70.00%
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_INT 0x7fffffff
struct enode
{
    int id;                 // 编号
    int step;               // 几步到达
    struct enode* next;     // 指向下一条边
};
typedef struct enode* pnode;
struct Graph
{
    pnode* node;
    int node_num;
};
typedef struct Graph *pgraph;
void add_edge(pgraph g, int v1, int v2, int step);

pgraph read_tree(int, int);
pgraph build_tree(int N);
void Relation(pgraph, int);
double stat(int *visit, int N);

int main(int argc, char const *argv[])
{   
    int N, M;
    scanf("%d %d", &N, &M);
    pgraph pg0;
    pg0 = read_tree(N, M); 
    //pg = build_tree(N);
    //stat(pg);
    for (int i=0; i<N; i++)
    {   
        //printf(">>>>>>>iter: %d<<<<<<\n", i+1);
        Relation(pg0, i);
        //stat(pg);
    }
    scanf("%d %d", &N, &M);
    return 0;
}


pgraph build_tree(int N)
{
    pgraph g;
    pnode* node_arr, new_node;
    node_arr = (pnode*)malloc(N * sizeof(pnode));
    g = (pgraph)malloc(sizeof(struct Graph));
    g->node = node_arr;
    g->node_num = N;
    for(int i=0; i<N; i++)
    {   
        new_node = (pnode)malloc(sizeof(struct enode));
        new_node->next = NULL;
        new_node->id = i;
        new_node->step = 0;
        g->node[i] = new_node;
    }
    return g;
}

pgraph read_tree(int N, int M)
{   
    int v1, v2;
    pgraph g;
    g = build_tree(N);
    for(int i=0; i<M; i++)
    {
        scanf("%d %d", &v1, &v2);
        add_edge(g, v1-1, v2-1, 1);
        add_edge(g, v2-1, v1-1, 1);
    }
    return g;
}

void add_edge(pgraph g, int v1, int v2, int step)
{   // 增加边
    if(v1 == v2)
        return;
    pnode new_node, pn, tmp;
    new_node = (pnode)malloc(sizeof(struct enode));
    new_node->next = NULL;
    new_node->id = v2;
    new_node->step = step;

    if (g->node[v1] == NULL || g->node[v1]->id > v2)
    {   
        tmp = g->node[v1];
        g->node[v1] = new_node;
        new_node->next = tmp;
    }
    else
    {
        pn = g->node[v1];
        while(pn->next != NULL && pn->next->id <= v2)
        {
            pn = pn->next;
        }
        if (pn->id == v2)
            return;
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

void Relation(pgraph pg0, int pos)
{   // 依次计算每一个节点的6度连接
    pnode pn;
    int pos1, pos2, N, step;
    N = pg0->node_num;
    int visit[N];
    for (int i=0; i<N; i++)
        visit[i] = MAX_INT;
    visit[pos] = 0;

    for (step=0; step<6; step++)
    {
        for (pos1=0; pos1<N; pos1++)
        {   
            if (visit[pos1] > step)
                continue;
            pn = pg0->node[pos1];
            do
            {   
                pos2 = pn->id;
                //printf("add edge %d %d->%d\n", i, pos1, pos2);
                if (visit[pos2] > step)
                    visit[pos2] = step +1;
                pn = pn->next;
            }
            while(pn != NULL);
        }
    }
    double ratio = stat(visit, N);
    printf("%d: %.2f%%\n", pos+1, ratio);
}

double stat(int *visit, int N)
{   
    int count = 0;
    for (int i=0; i<N; i++)
    {   
        count += visit[i] <= 6; 
    }
    return count * 100.0 / N;
}

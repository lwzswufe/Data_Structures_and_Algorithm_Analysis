/*
05-树7 堆中的路径 （25 分）
将一系列给定数字插入一个初始为空的小顶堆H[]。随后对任意给定的下标i，
打印从H[i]到根结点的路径。

输入格式:
每组测试第1行包含2个正整数N和M(≤1000)，分别是插入元素的个数、以及需要
打印的路径条数。下一行给出区间[-10000, 10000]内的N个要被插入一个初始
为空的小顶堆的整数。最后一行给出M个下标。

输出格式:
对输入中给出的每个下标i，在一行中输出从H[i]到根结点的路径上的数据。数字
间以1个空格分隔，行末不得有多余空格。

输入样例:
5 3
46 23 26 24 10
5 4 3
输出样例:
24 23 10
46 23 10
26 10
*/

#include <stdio.h>
#include <stdlib.h>
#define  MIN_INT 0x80000000
struct Heap
{
    int *data;
    int size;
    int capacity;
};
typedef struct Heap *pheap;

pheap read_input(int);
pheap read_input2(int);
void insert(pheap, int);
void adjust_all(pheap);
void adjust(pheap, int);
void print(pheap, int);
int main()
{   
    pheap ph;
    int N, M;
    scanf("%d %d", &N, &M);
    ph = read_input2(N);
    // adjust_all(ph);
    print(ph, M);
    //scanf("%d %d", &N, &M);
    return 0;
}

void adjust_all(pheap ph)
{   // 自尾到头调整所有的节点及其子节点的顺序
    for (int i=ph->size/2; i>0; i--)
    {
        adjust(ph, i);
    }
}

void adjust(pheap ph, int pos)
{   // 自上到下调整节点顺序
    int tmp, child_pos, N;
    N = ph->size;
    while(pos*2 <= N)
    {   
        if (pos*2 + 1<= N && ph->data[2 * pos] > ph->data[2*pos + 1])
            child_pos = 2*pos + 1;
        else
            child_pos = 2*pos;
        if (ph->data[child_pos] < ph->data[pos])
        {   
            //printf("exchange %d: %d\n", ph->data[child_pos] , ph->data[pos]);
            tmp = ph->data[pos];
            ph->data[pos] = ph->data[child_pos];
            ph->data[child_pos] = tmp;
        }
        pos = child_pos;
    }
}

void insert(pheap ph, int X)
{   // 插入元素到最小堆
    int pos, tmp;
    ph->size++;
    pos = ph->size;
    ph->data[pos] = X;
    while(ph->data[pos]< ph->data[pos/2])
    {
        tmp = ph->data[pos/2];
        ph->data[pos/2] = ph->data[pos];
        ph->data[pos] = tmp;
        pos/=2;
    }
}

pheap read_input2(int N)
{   // 读入数据 初始化 最小堆 边插入边排序
    int *arr, X;
    pheap ph;
    arr = (int *)malloc((N + 1) * sizeof(int));
    arr[0] = MIN_INT;
    ph = (pheap)malloc(sizeof(struct Heap));
    ph->size = 0;
    ph->capacity = N;
    ph->data = arr;
    for(int i=1; i<=N; i++)
    {
        scanf("%d", &X);
        insert(ph, X);
    }
    return ph;
}

pheap read_input(int N)
{   // 读入数据 初始化 最小堆 先储存再排序
    int *arr;
    pheap ph;
    arr = (int *)malloc((N + 1) * sizeof(int));
    arr[0] = MIN_INT;
    for(int i=1; i<=N; i++)
        scanf("%d", arr+i);

    ph = (pheap)malloc(sizeof(struct Heap));
    ph->size = ph->capacity = N;
    ph->data = arr;
    return ph;
}

void print(pheap ph, int M)
{   
    int pos;
    for(int i=0; i<M; i++)
    {
        scanf("%d", &pos);
        if (pos < 1 || pos > ph->size)
            continue;
        while(pos != 1)
        {
            printf("%d ", ph->data[pos]);
            pos /= 2;
        }
        printf("%d\n", ph->data[1]);
    }
}

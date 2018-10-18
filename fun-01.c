/*
01-复杂度3 二分查找 （20 分）
本题要求实现二分查找算法。

函数接口定义：
Position BinarySearch( List L, ElementType X );
其中List结构定义如下：

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; // 保存线性表中最后一个元素的位置 //
};
L是用户传入的一个线性表，其中ElementType元素可以通过>、==、<进行比较，并且
题目保证传入的数据是递增有序的。函数BinarySearch要查找X在Data中的位置，即数
组下标（注意：元素从下标1开始存储）。找到则返回下标，否则返回一个特殊的失败
标记NotFound。


输入样例1：
5
12 31 55 89 101
31
输出样例1：
2
输入样例2：
3
26 78 233
31
输出样例2：
0
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
struct LNode 
{
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};
typedef struct LNode *List;
List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    struct LNode node; 
    L = &node;
    ElementType X;
    Position P;

    int N;
    scanf("%d", &N);
    for (int i=0; i<N; i++)
    {
        scanf("%d", L->Data + i +1);
    }
    L->Last = N;
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}

Position sub_BinarySearch( List L, ElementType X, int st, int ed)
{   
    // printf("%d-%d\n", st, ed);
    if (ed - st == 1)                               // 退出条件
    {
        if (L->Data[ed] == X)
            return ed;
        if (L->Data[st] == X)
            return st;
        return NotFound;
    }
    int mid = (ed + st) / 2;                        // 中点
    if (L->Data[mid] > X)                           // 左分支
        return sub_BinarySearch(L, X, st, mid);
    if (L->Data[mid] < X)                           // 右分支
        return sub_BinarySearch(L, X, mid, ed);
    if (L->Data[mid] == X)
        return mid;
    return -1;
}

Position BinarySearch( List L, ElementType X )
{   
    int N = L->Last, pos;
    if(X > L->Data[N] || X < L->Data[1])            // 范围判断
        return NotFound;
    pos = sub_BinarySearch(L, X, 1, N);
    return pos;
}

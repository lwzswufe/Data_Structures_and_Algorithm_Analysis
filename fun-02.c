/*
02-线性结构1 两个有序链表序列的合并 （15 分）
本题要求实现一个函数，将两个链表表示的递增整数序列合并为一个非递减的整数序列。

函数接口定义：
List Merge( List L1, List L2 );
其中List结构定义如下：

typedef struct Node *PtrToNode;
struct Node {
    ElementType Data; // 存储结点数据 //
    PtrToNode   Next; // 指向下一个结点的指针 //
};
typedef PtrToNode List; // 定义单链表类型 //
L1和L2是给定的带头结点的单链表，其结点存储的数据是递增有序的；函数Merge要将
L1和L2合并为一个非递减的整数序列。应直接使用原序列中的结点，返回归并后的带头结点的链表头指针。

裁判测试程序样例：
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); // 细节在此不表 //
void Print( List L ); // 细节在此不表；空链表将输出NULL //

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

// 你的代码将被嵌在这里 //
输入样例：
3
1 3 5
5
2 4 6 8 10
输出样例：
1 2 3 4 5 6 8 10 
NULL
NULL
*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
struct Node {
    ElementType Data;
    struct Node  *Next;
};
typedef struct Node *PtrToNode;
typedef PtrToNode List;

List Read() // 细节在此不表 //
{   
    List first_L, past_L, L;
    int N, x;
    scanf("%d", &N);
    L = (List)malloc(sizeof(struct Node));
    L->Data = N;
    L->Next = NULL;
    past_L = first_L = L;
    for(int i=0; i<N; i++)
    {
        scanf("%d", &x);
        L = (List)malloc(sizeof(struct Node));
        L->Data = x;
        L->Next = NULL;
        past_L->Next = L;
        past_L = L;
    }
    return first_L;
}

void Print( List L )  // 细节在此不表；空链表将输出NULL //
{
    if (L == NULL || L->Next == NULL)
    {
        printf("NULL\n");
        return;
    }
    L = L->Next;
    while(L->Next != NULL)
    {
        printf("%d ", L->Data);
        L = L->Next;
    }
    printf("%d\n", L->Data);
}

List Merge( List L1, List L2 )
{   
    List first_L, tmp_L, L;
    L = (List)malloc(sizeof(struct Node));
    L->Data = 0;
    L->Next = NULL;
    first_L = L;
    while(L1->Next!=NULL || L2->Next!=NULL)
    {   
        if (L2->Next==NULL || (L1->Next!=NULL &&  L1->Next->Data < L2->Next->Data))
        {   
            L->Next = L1->Next;
            L1->Next = L1->Next->Next;
            //Print(L1);
        }
        else
        {   
            L->Next = L2->Next;
            L2->Next = L2->Next->Next;
            //Print(L2);
        }
        L = L->Next;
        L->Next = NULL;
        //Print(first_L);
        //printf("%d %p\n", L->Data, L->Next);
    }
    return first_L;
}


int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

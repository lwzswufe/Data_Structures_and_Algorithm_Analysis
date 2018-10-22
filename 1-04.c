/*
02-线性结构3 Reversing Linked List （25 分）
Given a constant K and a singly linked list L, you are supposed to reverse the
 links of every K elements on L. For example, given L being 1→2→3→4→5→6, if K=3,
  then you must output 3→2→1→6→5→4; if K=4, you must output 4→3→2→1→5→6.

Input Specification:
Each input file contains one test case. For each case, the first line contains 
the address of the first node, a positive N (≤10^5) which is the total number 
of nodes, and a positive K (≤N) which is the length of the sublist to be reversed
. The address of a node is a 5-digit nonnegative integer
, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Data Next
where Address is the position of the node, Data is an integer, and Next is 
the position of the next node.

Output Specification:
For each case, output the resulting ordered linked list. Each node occupies a 
line, and is printed in the same format as in the input.

Sample Input:
00100 6 4
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218
Sample Output:
00000 4 33218
33218 3 12309
12309 2 00100
00100 1 99999
99999 5 68237
68237 6 -1
*/

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100001
struct LNode
{   
    int No;
    int addr;
    struct LNode * next;
    struct LNode * previous;
};
typedef struct LNode * PtrLNode;
PtrLNode ReadInput(int, int, int*);
PtrLNode Move(int, int, PtrLNode);
void Print(PtrLNode, int);
void PrintPrevious(PtrLNode, int, int);


int main()
{      
    PtrLNode firstNode;
    int addr, N, K, N2;
    scanf("%d %d %d", &addr, &N, &K);
    //printf("%d %d %d\n", addr, N, K);
    firstNode = ReadInput(N, addr, &N2);
    //firstNode = Move(N, K, firstNode);
    //printf("over\n");
    if(K==0 || K==1)
        Print(firstNode, N2);
    else
        PrintPrevious(firstNode, N2, K);
    scanf("%d %d %d", &addr, &N, &K);
    return 0;
}

PtrLNode ReadInput(int N, int firstAddr, int* ptr_N)
{   
    PtrLNode L, firstNode=NULL, pastNode;
    int addrArr[MAXSIZE], NoArr[N], nextAddrArr[N], addr, No, nextAddr, idx, N2; 
    for(int i=0; i<MAXSIZE; i++)
        addrArr[i] = -1;
    for(int i=0; i<N; i++)
    {   
        scanf("%d %d %d", &addr, &No, &nextAddr);
        //addr = addr % 1000;
        //nextAddr = nextAddr % 1000;
        //printf("%d %d %d\n", addr, No, nextAddr);
        addrArr[addr] = i;
        NoArr[i] = No;
        nextAddrArr[i] = nextAddr;
    }
    idx = addrArr[firstAddr];
    nextAddr = nextAddrArr[idx];
    L = (PtrLNode)malloc(sizeof(struct LNode));
    L->No = NoArr[idx];
    L->addr = firstAddr;
    L->next = NULL;
    L->previous = NULL;
    //printf("%p\n", L);
    //printf("%d %d %d\n", L->No, L->addr, nextAddr);
    N2 = 1;
    pastNode = firstNode = L;
    while (nextAddr >= 0)
    {   
        addr = nextAddr;
        idx = addrArr[addr];
        L = (PtrLNode)malloc(sizeof(struct LNode));
        L->No = NoArr[idx];
        L->addr = addr;
        L->next = NULL;
        L->previous = pastNode;
        pastNode->next = L;
        pastNode = L;
        nextAddr = nextAddrArr[idx];
        N2++;
        //printf("%d %d %d\n", L->No, L->addr, nextAddr);
    }
    *ptr_N = N2;
    //printf("N2: %d\n", N2);
    //L->next = firstNode;
    //firstNode->previous = L;
    //printf("over\n");
    //printf("%p\n", firstNode);
    return firstNode;
}


void Print(PtrLNode pNode, int N)
{   
    for(int i=1; i<N; i++)
    {   
        printf("%05d %d %05d\n", pNode->addr, pNode->No, pNode->next->addr);
        pNode = pNode->next;
    }
    printf("%05d %d -1\n", pNode->addr, pNode->No);
}

void PrintPrevious(PtrLNode pNode, int N, int K)
{   
    PtrLNode firstNode=pNode, tmpNode=NULL, tmpPastNode=NULL;
    for(int i=1; i<=N; i++)
    {
        if (i % K == 1)                         // 记录本次反转的结束位置作为下次反转的开始
        {   
            tmpPastNode = tmpNode;
            tmpNode = pNode;
        }
        if (i % K == 0)                         // 每K个元素反转
        {   
            if(i == K)
                firstNode = pNode;
            else
                tmpPastNode->previous = pNode;
        }
        pNode = pNode->next;
    }
    if (N % K != 0)
    {
        tmpPastNode->previous = tmpNode;
        tmpNode->previous = NULL;
    }
    pNode = firstNode;
    for(int i=1, flag=0; i<N; i++)
    {   
        if (pNode->previous != NULL && flag==0) // 逆序输出
        {   
            printf("%05d %d %05d\n", pNode->addr, pNode->No, pNode->previous->addr);
            pNode = pNode->previous;
        }
        else                                    // 开始正向输出
        {   
            flag = 1;
            printf("%05d %d %05d\n", pNode->addr, pNode->No, pNode->next->addr);
            pNode = pNode->next;
        }
    }
    printf("%05d %d -1\n", pNode->addr, pNode->No);
}

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
#define MAXSIZE 1000
struct LNode
{   
    int No;
    int addr;
    struct LNode * next;
};
typedef struct LNode * PtrLNode;
PtrLNode ReadInput(int, int);
void Print(PtrLNode);
int readnum();

int main()
{      
    PtrLNode firstNode;
    int addr, N, K;
    scanf("%d %d %d", &addr, &N, &K);
    printf("\n%d %d %d\n", addr, N, K);
    firstNode = ReadInput(N, addr);
    //Print(firstNode);
    return 0;
}

PtrLNode ReadInput(int N, int firstAddr)
{   
    PtrLNode L, firstNode=NULL, pastNode;
    int addrArr[MAXSIZE], NoArr[N], nextAddrArr[N], addr, No, nextAddr, idx; 
    for(int i=0; i<MAXSIZE; i++)
        addrArr[i] = -1;
    for(int i=0; i<N; i++)
    {   
        scanf("%d %d %d", &addr, &No, &nextAddr);
        printf("%d %d %d\n", addr, No, nextAddr);
        addr = addr % 1000;
        addrArr[addr] = i;
        NoArr[i] = No;
        nextAddrArr[i] = nextAddr;
    }
    printf("over");
    idx = addrArr[firstAddr];
    nextAddr = nextAddrArr[idx];
    L = (PtrLNode)malloc(sizeof(struct LNode));
    L->No = NoArr[idx];
    L->addr = 0;
    L->next = NULL;
    pastNode = firstNode = L;
    while (nextAddr >= 0)
    {   
        printf("%d: ", idx);
        addr = nextAddr;
        idx = addrArr[addr];
        L = (PtrLNode)malloc(sizeof(struct LNode));
        L->No = NoArr[idx];
        L->addr = addr;
        L->next = NULL;
        pastNode->next = L;
        pastNode = L;
        nextAddr = nextAddrArr[idx];
    }
    return firstNode;
}

int readnum()
{   
    int n=0, i=0;
    while(n == 0 && i<1)
    {
        scanf("%d", &n);
        i++;
    }
    return n;
}

void Print(PtrLNode pNode)
{   
    while(pNode == NULL)
    {   
        if (pNode->next != NULL)
            printf("%05d %d %05d\n", pNode->addr, pNode->No, pNode->next->addr);
        else
            printf("%05d %d -1\n", pNode->addr, pNode->No);
    }
}

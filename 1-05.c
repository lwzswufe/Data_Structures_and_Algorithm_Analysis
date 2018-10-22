/*
02-线性结构4 Pop Sequence （25 分）
Given a stack which can keep M numbers at most. Push N numbers in the order 
of 1, 2, 3, ..., N and pop randomly. You are supposed to tell if a given 
sequence of numbers is a possible pop sequence of the stack. For example, 
if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, 
but not 3, 2, 1, 7, 5, 6, 4.

Input Specification:
Each input file contains one test case. For each case, the first line contains 
3 numbers (all no more than 1000): M (the maximum capacity of the stack), N 
(the length of push sequence), and K (the number of pop sequences to be checked). 
Then K lines follow, each contains a pop sequence of N numbers. All the numbers 
in a line are separated by a space.

Output Specification:
For each pop sequence, print in one line "YES" if it is indeed a possible pop 
sequence of the stack, or "NO" if not.

Sample Input:
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2
Sample Output:
YES
NO
NO
YES
NO
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000

struct LNode
{   
    int *Data;
    int maxsize;
    int top;
};
typedef struct LNode * PtrLNode;
PtrLNode CreateNode(int);
void ReadInput(int, int*);
void Print(PtrLNode);
void DelNode(PtrLNode);
void Move(int, int, PtrLNode, int*);
int Pop(PtrLNode);
int Push(PtrLNode, int);

int main()
{      
    PtrLNode pnode = NULL;
    int M, N, K, status;
    scanf("%d %d %d", &M, &N, &K);
    int Arr[N];
    for(int i=0; i<K; i++)
    {   
        DelNode(pnode);
        pnode = CreateNode(M);
        ReadInput(N, Arr);
        Move(M, N, pnode, Arr);
    }
    //Print(firstNode);
    return 0;
}
  
void ReadInput(int N, int* Arr)
{   
    for(int i=0; i<N; i++)
    {   
        scanf("%d", Arr + i);
    }
}

PtrLNode CreateNode(int M)
{   
    PtrLNode pnode;
    pnode = (PtrLNode)malloc(sizeof(struct LNode));
    pnode->Data = (int*)malloc(M * sizeof(int));
    pnode->maxsize = M;
    pnode->top = 0;
    return pnode;
}

void DelNode(PtrLNode pnode)
{
    if (pnode == NULL)
        return;
    free(pnode->Data);
    free(pnode);
}

int Pop(PtrLNode pnode)
{
    if (pnode->top == 0)
        return -1;
    pnode->top--;
    return pnode->Data[pnode->top];
}

int Push(PtrLNode pnode, int num)
{
    if (pnode->top == pnode->maxsize)
        return -1;
    pnode->Data[pnode->top] = num;
    pnode->top++;
    return 0;
}

void Move(int M, int N, PtrLNode pnode, int* Arr)
{   // 按序入栈出栈
    int push_num = 1, out_idx = 0, result=0, popnum, push_res;
    while (out_idx < N)                                             // 出栈数量小于N
    {   
        if (pnode->top == M ||                                      // 栈满 
            (pnode->top > 0 && pnode->Data[pnode->top - 1] >= Arr[out_idx]) ||  // 栈顶数大于等于下一个出栈的数字
            (pnode->top > 0 && push_num > N)                        // 入栈数为空 且栈非空
           )
        {
            popnum = Pop(pnode);
            if (popnum == Arr[out_idx])
                out_idx++;
            else
            {
                result = -1;
                break;
            }
        }
        else if (pnode->top == 0 || push_num <= Arr[out_idx])       //  栈位空或栈顶数小于下一个需要出栈的数字
        {
            push_res = Push(pnode, push_num);
            push_num++;
        }
        else
        {
            result = -1;
            break;
        }
    }
    if (result < 0)
        printf("NO\n");
    else
        printf("YES\n");
}

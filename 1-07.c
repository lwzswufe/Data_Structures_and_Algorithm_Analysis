/*
03-树2 List Leaves （25 分）
Given a tree, you are supposed to list all the leaves i
n the order of top down, and left to right.

Input Specification:
Each input file contains one test case. For each case, 
the first line gives a positive integer N (≤10) which 
is the total number of nodes in the tree -- and hence 
the nodes are numbered from 0 to N−1. Then N lines follow, 
each corresponds to a node, and gives the indices of 
the left and right children of the node. If the child 
does not exist, a "-" will be put at the position. Any 
pair of children are separated by a space.

Output Specification:
For each test case, print in one line all the leaves' 
indices in the order of top down, and left to right. 
There must be exactly one space between any adjacent 
numbers, and no extra space at the end of the line.

Sample Input:
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
Sample Output:
4 1 5
作者: 陈越
单位: 浙江大学
时间限制: 400 ms
内存限制: 64 MB
代码长度限制: 16 KB

*/
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int left;
    int right;
};
struct Queue
{
    int arr[16];
    int front;
    int rear;
};
typedef struct Node  *PNode;
typedef PNode *PNodeArr; 
typedef struct Queue Queue;
PNode * ReadInput();
int get_root(PNodeArr);
int get_pos(char);
int compare(int, int, PNodeArr, PNodeArr);
int push(Queue*, int);
int pop(Queue*);
void traverse(PNodeArr, int);

int main()
{
    PNodeArr tree;
    int pos;
    tree = ReadInput();
    pos = get_root(tree);
    if(pos > 0)
        traverse(tree, pos);
    // char c;
    // scanf("%c", &c);
    // scanf("%c", &c);
    // scanf("%c", &c);
    return 0;
}

int get_pos(char c)
{
    if (c == '-')
        return 0;
    else
        return c - 47;                  // 0-9映射到 1-10
}

PNode* ReadInput()
{
    int N;
    char left, right;
    scanf("%d", &N);
    PNode pnode;
    PNodeArr pnodeArr;
    pnodeArr = (PNode*)malloc((N+1)*sizeof(PNode));
    pnode = (PNode)malloc(sizeof(struct Node));
    pnode->left = pnode->right = N;
    pnodeArr[0] = pnode;
    //printf("%d %d\n", pnode->left, pnode->right);
    for(int i=1; i<=N; i++)
    {
        scanf("\n%c %c", &left, &right);
        //printf("left:%c right:%c\n", left, right);
        pnode = (PNode)malloc(sizeof(struct Node));
        pnode->left = get_pos(left);
        pnode->right = get_pos(right);
        pnodeArr[i] = pnode;
        // printf("%c %d %d\n", pnode->name, pnode->left, pnode->right);
    }
    return pnodeArr;
}


int get_root(PNodeArr pnodeArr)
{                                       // 寻找根节点的位置
    int N;
    N = pnodeArr[0]->left;
    if (N == 0)
        return 0;                       // 空树
    int flag[N+1];
    for(int i=0; i<=N; i++)
    {
        flag[i] = 0;
    }
    for(int i=1; i<=N; i++)             // 标记子节点
    {   
        //printf("%d %d\n", pnodeArr[i]->left, pnodeArr[i]->right);
        flag[pnodeArr[i]->left] = 1;
        flag[pnodeArr[i]->right] = 1;
    }
    for(int i=1; i<=N; i++)
    {
        if (flag[i] == 0)
            return i;
    }
    return -1;
}

void traverse(PNodeArr tree, int pos)
{   
    Queue queue, write_queue;
    queue.rear = queue.front = 0;
    write_queue.rear = write_queue.front = 0;
    push(&queue, pos);
    while(queue.front > queue.rear)
    {   
        pos = pop(&queue);                       // 从队列取出节点
        //printf("visit %d\n", pos-1);
        if (pos == 0)
            break;
        if(tree[pos]->left + tree[pos]->right == 0)
        { 
            push(&write_queue, pos-1);           // 添加到输出队列
            //printf("add leaf: %d\n", pos);
        }
        if (tree[pos]->left > 0)                // 增加左节点
            push(&queue, tree[pos]->left);
        if (tree[pos]->right > 0)               // 增加右节点
            push(&queue, tree[pos]->right);
    }
    //printf("visit over");
    while(write_queue.front > write_queue.rear + 1)
    {   
        pos = pop(&write_queue);
        printf("%d ", pos);
    }
    pos = pop(&write_queue);
    printf("%d", pos);
}

int push(Queue* queue, int pos)
{
    queue->arr[queue->front] = pos;
    queue->front++;
    return 0;
}


int pop(Queue* queue)
{   
    int pos;
    pos = queue->arr[queue->rear];
    queue->rear++;
    return pos;
}

/*
03-树3 Tree Traversals Again （25 分）
An inorder binary tree traversal can be implemented in a non-recursive 
way with a stack. For example, suppose that when a 6-node binary tree 
(with the keys numbered from 1 to 6) is traversed, the stack operations 
are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); 
push(5); push(6); pop(); pop(). Then a unique binary tree can be generated 
from this sequence of operations. Your task is to give the postorder 
traversal sequence of this tree.

                1
    2                       5    
3       4               6

Input Specification:
Each input file contains one test case. For each case, the first line 
contains a positive integer N (≤30) which is the total number of nodes 
in a tree (and hence the nodes are numbered from 1 to N). Then 2N lines 
follow, each describes a stack operation in the format: "Push X" where X 
is the index of the node being pushed onto the stack; or "Pop" meaning to 
pop one node from the stack.

Output Specification:
For each test case, print the postorder traversal sequence of the corresponding 
tree in one line. A solution is guaranteed to exist. All the numbers must 
be separated by exactly one space, and there must be no extra space at 
the end of the line.

Sample Input:
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop
Sample Output:
3 4 2 6 5 1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    struct Node* left;
    struct Node* right;
    int id;
    int status;                         // 标记节点状态 -1指向左子节点 0指向自己 1指向右子节点
};
typedef struct Node  *PNode;
struct Stack
{
    PNode arr[64];
    int top;
};
typedef struct Stack *PStack;
PNode ReadInput();
PNode pop(PStack);
void push(PStack, PNode);
void traverse(PNode, PNode);

int main()
{
    PNode pnode;
    pnode = ReadInput();
    traverse(pnode, pnode);
    // char c;
    // scanf("%c", &c);
    // scanf("%c", &c);
    // scanf("%c", &c);
    return 0;
}

void push(PStack pstack, PNode pnode)
{
    pstack->arr[pstack->top] = pnode;
    pstack->top++;
}


PNode pop(PStack pstack)
{   
    PNode pnode;
    if (pstack->top == 0)           // 队列为空
        return NULL;
    pnode = pstack->arr[pstack->top - 1];
    while (pnode !=NULL && pnode->status == 1)
    {                               // 连续删除指向右节点的元素
        pstack->top--;
        pstack->arr[pstack->top] = NULL;
        if (pstack->top > 0)
            pnode = pstack->arr[pstack->top - 1];
        else
            pnode = NULL;
    }
    if (pnode == NULL)
        return NULL;
    pnode->status = 1;              // 将指向左节点的元素的状态改为右节点
    return pnode;
}

PNode ReadInput()
{   
    int N, x;
    char op[8];
    PStack pstack;
    PNode first_node, pnode;
    pstack = (PStack)malloc(sizeof(struct Stack));
    pstack->top = 0;
    
    scanf("%d", &N);
    scanf("%s", op);
    if (op[1] == 'o')
        return NULL;
    scanf("%d", &x);
    //printf("\nread start\n");
    //printf("%s: %d\n", op, x);

    pnode = (PNode)malloc(sizeof(struct Node));
    pnode->left = pnode->right = NULL;
    pnode->status = -1;
    pnode->id = x;
    first_node = pnode;
    push(pstack, pnode);
    //printf("%d %d\n", pnode->left, pnode->right);
    for(int i=1; i<N*2; i++)
    {
        scanf("%s", op);
        if (op[1] == 'u')
        {
            scanf("%d", &x);
            pnode = (PNode)malloc(sizeof(struct Node));
            pnode->left = pnode->right = NULL;
            pnode->status = -1;
            pnode->id = x;
                                    // 根据栈顶元素的指向status 决定左分支还是右分支
            if (pstack->arr[pstack->top - 1]->status == -1)
                pstack->arr[pstack->top - 1]->left = pnode;
            else
                pstack->arr[pstack->top - 1]->right = pnode;
            //printf("father:%d child:%d\n", pstack->arr[pstack->top - 1]->id, pnode->id);
            push(pstack, pnode);
            //printf("%s: %d\n", op, x);
        }
        else  
        {
            //printf("%s\n", op);
            pnode = pop(pstack);
            //if(pnode == NULL)
            //    printf("err pop\n");
            //else
            //    printf("pop: %d\n", pnode->id);
        }
    }
    //printf("read over");
    return first_node;
}

void traverse(PNode pnode, PNode first_node)
{
    if(pnode->left != NULL)
        traverse(pnode->left, first_node);
    if(pnode->right != NULL)
        traverse(pnode->right, first_node);
    if(pnode == first_node)
        printf("%d", pnode->id);
    else
        printf("%d ", pnode->id);
}

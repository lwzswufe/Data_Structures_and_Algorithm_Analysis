/*
04-树6 Complete Binary Search Tree （30 分）
A Binary Search Tree (BST) is recursively defined as a binary
 tree which has the following properties:

The left subtree of a node contains only nodes with keys less 
than the node's key.The right subtree of a node contains only 
nodes with keys greater than or equal to the node's key.Both 
the left and right subtrees must also be binary search trees.
A Complete Binary Tree (CBT) is a tree that is completely filled, 
with the possible exception of the bottom level, which is filled 
from left to right.

Now given a sequence of distinct non-negative integer keys, a 
unique BST can be constructed if it is required that the tree 
must also be a CBT. You are supposed to output the level order 
traversal sequence of this BST.

Input Specification:
Each input file contains one test case. For each case, the first 
line contains a positive integer N (≤1000). Then N distinct 
non-negative integer keys are given in the next line. All the 
numbers in a line are separated by a space and are no greater 
than 2000.

Output Specification:
For each test case, print in one line the level order traversal 
sequence of the corresponding complete binary search tree. All 
the numbers in a line must be separated by a space, and there 
must be no extra space at the end of the line.

Sample Input:
10
1 2 3 4 5 6 7 8 9 0
Sample Output:
6 3 8 1 5 7 9 0 2 4
*/
#include <stdio.h>
#include <stdlib.h>

struct TNode
{
    int data;
    int is_reach;
    struct TNode * father;
    struct TNode * left;
    struct TNode *  right;
};
typedef struct TNode *Position;
int* idx_iter(int, int, int*);
Position create(int, Position);
Position Insert(Position , int);
Position read_tree();
void trverse(Position, int);

int main()
{   
    Position root;
    int N;
    scanf("%d", &N);
    root = read_tree(N);
    trverse(root, N);
    int x;
    scanf("%d", &x);
    return 0;
}

Position create(int X, Position father)
{   // 申请空间 创建节点
    Position new_node;
    new_node = (Position)malloc(sizeof(struct TNode));
    new_node->is_reach = 0;
    new_node->data = X;
    new_node->father = father;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Position read_tree(int N)
{
    Position root = NULL;
    int X;
    for(int i=0; i<N; i++)
    {   
        scanf("%d", &X);
        root = Insert(root, X);
    }
    return root;
}

Position Insert( Position BST, int X )
{
    Position root = BST, new_node;
    if (BST == NULL)
    {
        new_node = create(X, NULL);
        return new_node;
    }
    while (BST != NULL)
    {   
        if (X == BST->data)
            break;

        if(X < BST->data)
        {
            if(BST->left == NULL)
            {   
                new_node = create(X, BST);
                BST->left = new_node;
                break;
            }
            else
                BST = BST->left;
        }
        else
        {
            if(BST->right == NULL)
            {
                new_node = create(X, BST);
                BST->right = new_node;
                break;
            }
            else
                BST = BST->right;
        }
    }
    return root;
}

void trverse(Position root, int N)
{
    int idx_arr[N + 1], idx = 1, node_arr[N + 1], *pidx;
    //printf("N: %d\n", N);
    idx_arr[N] = -1;
    idx_iter(idx, N, idx_arr);
    //for(int i=0; i<=N; i++)
    //    printf("%d, ", idx_arr[i]);
    pidx = idx_arr;
    Position pnode = root;

    while(idx >= 0)
    {   
        if (pnode->left != NULL && pnode->left->is_reach == 0)  // 探索左分支
        {
            pnode = pnode->left;
        }
        else if(pnode->is_reach == 0)                           // 判断当前节点是否访问过
        {   
            idx = *pidx;
            node_arr[idx] = pnode->data;
            pnode->is_reach = 1;
            pidx++;
        }
        else if (pnode->right != NULL && pnode->right->is_reach == 0)   // 访问右分支
        {
            pnode = pnode->right;
        }
        else if (pnode->father != NULL)                         // 返回父节点
        {
            pnode = pnode->father;
        }
        else                                                    // 查询终止
        {
            break;
        }
    }
    for (int i=1; i<N; i++)
        printf("%d ", node_arr[i]);
    printf("%d", node_arr[N]);
}

int* idx_iter(int idx, int N, int *arr)
{   // 储存输出顺序的坐标
    if (idx * 2 <= N)
        arr = idx_iter(idx*2, N, arr);
    *arr = idx;
    arr++;
    if (idx * 2 + 1 <= N)
        arr = idx_iter(idx*2+1, N, arr);
    return arr;
}

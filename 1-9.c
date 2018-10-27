/*
04-树4 是否同一棵二叉搜索树 （25 分）
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树
却可以由多种不同的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插
入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插入序列，你
需要判断它们是否能生成一样的二叉搜索树。

输入格式:
输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是
每个序列插入元素的个数和需要检查的序列个数。第2行给出N个以空格分隔的正整
数，作为初始插入序列。最后L行，每行给出N个插入的元素，属于L个需要检查的
序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入
结束，这组数据不要处理。

输出格式:
对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一
样，输出“Yes”，否则输出“No”。

输入样例:
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0
输出样例:
Yes
No
No
*/
#include <stdio.h>
#include <stdlib.h>

struct TNode
{
    int data;
    int is_check;
    struct TNode * left;
    struct TNode *  right;
};
typedef struct TNode *Position;
typedef Position BinTree;
void reset(BinTree);
void free_tree(BinTree);
void check_arr(BinTree, int*, int);
int check(BinTree, int);
int *read_arr(int);
Position create(int);
BinTree Insert( BinTree BST, int X );
BinTree read_tree(int);

int main()
{
    BinTree BST;
    int N, LEN, *arr;
    scanf("%d", &LEN);
    while(LEN>0)
    //while(1)
    {
        scanf("%d", &N);
        BST = read_tree(LEN);
        for(int i=0; i<N; i++)
        {
            arr = read_arr(LEN);
            check_arr(BST, arr, LEN);
            reset(BST);
        }
        free(arr);
        free_tree(BST);
        scanf("%d", &LEN);
    }
}

void check_arr(BinTree root, int* arr, int N)
{   
    int res;
    for(int i=0; i<N; i++)
    {
        res = check(root, arr[i]);
        if (res <= 0)
        {
            printf("No\n");
            return;
        }
    }
    printf("Yes\n");
}

int* read_arr(int N)
{
    int *arr;
    arr = (int*)malloc(N * sizeof(int));
    for(int i=0; i<N; i++)
        scanf("%d", arr+i);
    return arr;
}

BinTree read_tree(int N)
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

BinTree Insert( BinTree BST, int X )
{
    Position root = BST, new_node;
    if (BST == NULL)
    {
        new_node = create(X);
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
                new_node = create(X);
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
                new_node = create(X);
                BST->right = new_node;
                break;
            }
            else
                BST = BST->right;
        }
    }
    return root;
}

Position create(int X )
{   // 申请空间 创建节点
    Position new_node;
    new_node = (Position)malloc(sizeof(struct TNode));
    new_node->is_check = 0;
    new_node->data = X;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void reset( BinTree BT )
{   // 先序遍历  重置节点检查状态
    if(BT == NULL)
        return;
    BT->is_check = 0;
    if(BT->left != NULL)
        reset(BT->left);
    if(BT->right != NULL)
        reset(BT->right);
}

void free_tree( BinTree BT )
{   // 后序遍历  释放内存
    if(BT == NULL)
        return;
    if(BT->left != NULL)
        free_tree(BT->left);
    if(BT->right != NULL)
        free_tree(BT->right);
    free(BT);
}

int check( BinTree BST, int X )
{   
    while (BST != NULL)
    {   
        //printf("Node:%d X:%d\n", BST->Data, X);
        if(X == BST->data)
        {   
            BST->is_check = 1;
            return 1;
        }
        else if (BST->is_check == 0)
        {
            return -1;
        }
        
        if(X < BST->data)
        {
            if(BST->left == NULL)
                return 0;
            else
                BST = BST->left;
        }
        else
        {
            if(BST->right == NULL)
                return 0;
            else
                BST = BST->right;
        }
    }
    return 0;
}
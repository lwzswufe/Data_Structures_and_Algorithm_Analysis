/*
本题要求实现给定二叉搜索树的5种常用操作。

函数接口定义：
BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );
其中BinTree结构定义如下：

typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};
函数Insert将X插入二叉搜索树BST并返回结果树的根结点指针；
函数Delete将X从二叉搜索树BST中删除，并返回结果树的根结点指针；
          如果X不在树中，则打印一行Not Found并返回原树的根结点指针；
函数Find在二叉搜索树BST中找到X，返回该结点的指针；如果找不到则返回空指针；
函数FindMin返回二叉搜索树BST中最小元结点的指针；
函数FindMax返回二叉搜索树BST中最大元结点的指针。
输入样例：
10
5 8 6 2 4 1 0 10 9 7
5
6 3 10 0 5
5
5 7 0 10 3
输出样例：
Preorder: 5 2 1 0 4 8 6 7 10 9
6 is found
3 is not found
10 is found
10 is the largest key
0 is found
0 is the smallest key
5 is found
Not Found
Inorder: 1 2 4 6 8 9
*/
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ); // 先序遍历，由裁判实现，细节不表 //
void InorderTraversal( BinTree BT );  // 中序遍历，由裁判实现，细节不表 //

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) 
    {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); 
    PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) 
    {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else 
        {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) 
    {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); 
    InorderTraversal(BST); printf("\n");

    return 0;
}

void PreorderTraversal( BinTree BT )
{   // 先序遍历
    if(BT->Left != NULL)
        PreorderTraversal(BT->Left);
    printf("%d ", BT->Data);
    if(BT->Right != NULL)
        PreorderTraversal(BT->Right);
}

void InorderTraversal( BinTree BT )
{   // 中序遍历
    printf("%d ", BT->Data);
    if(BT->Left != NULL)
        PreorderTraversal(BT->Left);
    if(BT->Right != NULL)
        PreorderTraversal(BT->Right);
}

Position Create(ElementType X )
{
    Position new_node;
    new_node = (Position)malloc(sizeof(struct TNode));
    new_node->Data = X;
    new_node->Left = NULL;
    new_node->Right = NULL;
    return new_node;
}

BinTree Insert( BinTree BST, ElementType X )
{
    Position root = BST, new_node;
    while (X != BST->Data)
    {
        if(X < BST->Data)
        {
            if(BST->Left == NULL)
            {   
                new_node = Create(X);
                BST->Left = new_node;
                break;
            }
            else
                BST = BST->Left;
        }
        else
        {
            if(X > BST->Data)
            {
                if(BST->Right == NULL)
                {
                    new_node = Create(X);
                    BST->Right = new_node;
                    break;
                }
                else
                    BST = BST->Right;
            }
            else
            {
                break;
            }
        }
    }
    return root;
}

Position FindFather( BinTree BST, ElementType X)
{   
    Position del_node, root=BST, father_node=NULL, child_node;
    do
    {
        if(X < BST->Data)
        {
            if(BST->Left == NULL)
            {   
                return NULL;
            }
            else
            {   
                father_node = BST;
                BST = BST->Left;
            }
        }
        else
        {
            if(X > BST->Data)
            {
                if(BST->Right == NULL)
                {
                    return NULL;
                }
                else
                {   
                    father_node = BST;
                    BST = BST->Right;
                }
            }
            else
            {
                del_node = BST;
                return father_node;
            }
        }
    }
    while (1);
}

BinTree Delete( BinTree BST, ElementType X )
{   // 函数Delete将X从二叉搜索树BST中删除，并返回结果树的根结点指针；
    // 如果X不在树中，则打印一行Not Found并返回原树的根结点指针；
    Position del_node, root=BST, father_node=NULL, child_node, child_father_node;
    del_node = Find(root, X);
    if (del_node == NULL)
    {
        printf("Not Found\n");
        return BST;
    }
    father_node = FindFather(root, X);
    if (del_node->Left == NULL || del_node->Right == NULL)
    {                                               // 被删除节点至多有一个子节点
        if(father_node == NULL)                     // 被删除节点为根节点
        {                                           // 更新根节点
            if (del_node->Left == NULL)             
                root = del_node->Right;
            else
                root = del_node->Left;
        } 
        else                                        // 用子节点替代被删除的节点
        {   
            if (del_node->Left == NULL)
                child_node = del_node->Right;
            else
                child_node = del_node->Left;
            if (father_node->Left == del_node)
                father_node->Left = child_node;
            else
                father_node->Right = child_node;
        }
    }
    else                                            // 被删除节点有2个子节点
    {
        child_node = FindMax(del_node->Right);      // 寻找右分支最大子节点
        child_father_node = FindFather(del_node, child_node->Data);
        if (child_father_node == NULL)
            child_father_node = del_node;
        if (father_node == NULL)                    // 被删除的节点是根节点
            root = child_node;                      // 设置child_node为根节点
        else
        {                                           // 将child_node放到del_node的父节点下面
            if (father_node->Left == del_node)
                father_node->Left = child_node;
            else
                father_node->Right = child_node;
        }
        father_node->Right = child_node->Left;      // child_node 右节点为空
        child_node->Right = del_node->Right;        // 将child_node放到del_node的子节点上面
        child_node->Left = del_node->Left;
    }
    free(del_node);
    return root;
}

Position Find( BinTree BST, ElementType X )
{   
    while (X != BST->Data)
    {
        if(X < BST->Data)
        {
            if(BST->Left == NULL)
                return NULL;
            else
                BST = BST->Left;
        }
        else
        {
            if(X > BST->Data)
            {
                if(BST->Right == NULL)
                    return NULL;
                else
                    BST = BST->Right;
            }
            else
            {
                return BST;
            }
        }
    }
    return BST;
}

Position FindMin( BinTree BST )
{   // 查找最小元素
    if(BST->Left != NULL)
        FindMin( BST->Left );
    else
        return BST;
}

Position FindMax( BinTree BST )
{   // 查找最大元素
    if(BST->Right != NULL)
        FindMin( BST->Right );
    else
        return BST;
}

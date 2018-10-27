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
struct TNode
{
    ElementType Data;
    struct TNode * Left;
    struct TNode *  Right;
};
typedef struct TNode *Position;
typedef Position BinTree;
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
        printf("delete: %d\n", X);
        BST = Delete(BST, X);
        printf("root: %d\n", BST->Data);
    }
    printf("Inorder:"); 
    InorderTraversal(BST); printf("\n");
    scanf("%d", &X);
    return 0;
}

void PreorderTraversal( BinTree BT )
{   // 先序遍历
    if(BT == NULL)
        return;
    printf("%d ", BT->Data);
    if(BT->Left != NULL)
        PreorderTraversal(BT->Left);
    if(BT->Right != NULL)
        PreorderTraversal(BT->Right);
}

void InorderTraversal( BinTree BT )
{   // 中序遍历
    if(BT == NULL)
        return;
    if(BT->Left != NULL)
        PreorderTraversal(BT->Left);
    printf("%d ", BT->Data);
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
    if (BST == NULL)
    {
        new_node = Create(X);
        return new_node;
    }
    while (BST != NULL)
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

void CopyNode( Position target_node, Position source_node)
{   
    //printf("copy node: %d from node: %d\n", target_node->Data, source_node->Data);
    target_node->Data = source_node->Data;
    target_node->Left = source_node->Left;
    target_node->Right = source_node->Right;
}

BinTree Delete( BinTree BST, ElementType X )
{   // 函数Delete将X从二叉搜索树BST中删除，并返回结果树的根结点指针；
    // 如果X不在树中，则打印一行Not Found并返回原树的根结点指针；
    Position tmp_node;
        
    if (BST == NULL)
    {
        printf("Not Found\n");
        return BST;
    }
    //printf("now node: %d delete node: %d\n", BST->Data, X);
    if (X < BST->Data)
    {
        BST->Left = Delete(BST->Left, X);
    }
    else 
    {
        if (X > BST->Data)
        {
            BST->Right = Delete(BST->Right, X);
        }
        else
        {   
            //printf("now node: %d find node: %d\n", BST->Data, X);
            if (BST->Left != NULL && BST->Right != NULL)
            {                                               // 被删除节点有2个子节点
                tmp_node = FindMax(BST->Left);
                BST->Data = tmp_node->Data;
                BST->Left = Delete(BST->Left, BST->Data);
            }
            else 
            {   
                if (BST->Left != NULL || BST->Right != NULL)
                {                                                // 被删除节点有1个子节点
                    if(BST->Left == NULL)
                    {   
                        tmp_node = BST->Right;
                        CopyNode(BST, BST->Right);
                    }
                    else
                    {
                        tmp_node = BST->Left;
                        CopyNode(BST, BST->Left);
                    }
                    //printf("free single node: %d\n", BST->Data);
                    free(tmp_node);
                }
                else
                {   
                    //printf("free blank node: %d\n", BST->Data);
                    free(BST);
                    BST = NULL;
                }
            }
        }
    }
    // if (BST == NULL)
    //     printf("return -1");
    // else
    //     printf("return %d->", BST->Data);
    return BST;
}

Position Find( BinTree BST, ElementType X )
{   
    while (BST != NULL)
    {   
        //printf("Node:%d X:%d\n", BST->Data, X);
        if(X == BST->Data)
            return BST;
        if(X < BST->Data)
        {
            if(BST->Left == NULL)
                return NULL;
            else
                BST = BST->Left;
        }
        else
        {
            if(BST->Right == NULL)
                return NULL;
            else
                BST = BST->Right;
        }
    }
    return BST;
}

Position FindMin( BinTree BST )
{   // 查找最小元素
    if(BST == NULL)
        return BST;
    if(BST->Left != NULL)
        return FindMin( BST->Left );
    else
        return BST;
}

Position FindMax( BinTree BST )
{   // 查找最大元素
    if(BST == NULL)
        return BST;
    if(BST->Right != NULL)
        return FindMax( BST->Right );
    else
        return BST;
}

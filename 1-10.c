/*
04-树5 Root of AVL Tree （25 分）
An AVL tree is a self-balancing binary search tree. In an AVL tree, 
the heights of the two child subtrees of any node differ by at most 
one; if at any time they differ by more than one, rebalancing is done 
to restore this property. Figures 1-4 illustrate the rotation rules.

Now given a sequence of insertions, you are supposed to tell the root 
of the resulting AVL tree.
Input Specification:
Each input file contains one test case. For each case, the first line 
contains a positive integer N (≤20) which is the total number of keys 
to be inserted. Then N distinct integer keys are given in the next line. 
All the numbers in a line are separated by a space.

Output Specification:
For each test case, print the root of the resulting AVL tree in one line.

Sample Input 1:
5
88 70 61 96 120
Sample Output 1:
70
Sample Input 2:
7
88 70 61 96 120 90 65
Sample Output 2:
88
*/
#include <stdio.h>
#include <stdlib.h>

struct TNode
{
    int data;
    int deepleft;
    int deepright;
    struct TNode * left;
    struct TNode *  right;
};
typedef struct TNode *Position;
int get_deep(Position);
Position create(int);
Position Insert(Position , int);
Position read_tree();
Position modify_tree(Position);

int main()
{   
    Position root;
    root = read_tree();
    root = modify_tree(root);
    printf("%d", root->data);
    int x;
    scanf("%d", &x);
    return 0;
}

Position modify_tree(Position root)
{   
    Position new_root, new_child;
    int deep;
    if(root->left != NULL)
        root->left = modify_tree(root->left);
    if(root->right != NULL)
        root->right = modify_tree(root->right);
    deep = get_deep(root);
    while (root->deepleft - root->deepright >= 2 || root->deepleft - root->deepright <= -2)
    {
        if (root->deepleft - root->deepright >= 2)
        {   
            if (root->left->deepleft > root->left->deepright)
            {
                new_root = root->left;
                root->left = new_root->right;
                new_root->right = root;
                root = new_root;
            }
            else
            {
                new_root = root->left->right;
                new_child = root->left;
                new_child->right = new_root->left;
                root->left = new_root->right;
                new_root->left = new_child;
                new_root->right = root;
                root = new_root;
            }
        }
        //(root->deepright - root->deepleft >= 2)
        else
        {   
            //printf("%d", root->data);
            if (root->right->deepright > root->right->deepleft)
            {
                new_root = root->right;
                root->right = new_root->left;
                new_root->left = root;
                root = new_root;
            }
            else
            {
                new_root = root->right->left;
                new_child = root->right;
                new_child->left = new_root->right;
                root->right = new_root->left;
                new_root->right = new_child;
                new_root->left = root;
                root = new_root;
            }
        }
        deep = get_deep(root);
    }
    return root;
}
Position create(int X )
{   // 申请空间 创建节点
    Position new_node;
    new_node = (Position)malloc(sizeof(struct TNode));
    new_node->deepleft = -1;
    new_node->deepright = -1;
    new_node->data = X;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Position read_tree()
{
    Position root = NULL;
    int X, N;
    scanf("%d", &N);
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
    root = modify_tree(root);
    return root;
}

int get_deep( Position BT )
{   // 后序遍历  释放内存
    if(BT == NULL)
        return 0;
    if(BT->left != NULL)
        BT->deepleft = get_deep(BT->left);
    else
        BT->deepleft = 1;
    if(BT->right != NULL)
        BT->deepright = get_deep(BT->right);
    else
        BT->deepright = 1;
    if (BT->deepleft >= BT->deepright)
        return BT->deepleft + 1;
    else
        return BT->deepright + 1;
}

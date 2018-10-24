/*
03-树1 树的同构 （25 分）
给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，
则我们称两棵树是“同构”的。例如图1给出的两棵树就是同构的，
因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。
现给定两棵树，请你判断它们是否是同构的。
输入格式:
输入给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数N (≤10)，即该树的结点数（此时假设结点从0到N−1编号）；随后N行，第i行对应编号第i个结点，给出该结点中存储的1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出“-”。给出的数据间用一个空格分隔。注意：题目保证每个结点中存储的字母是不同的。

输出格式:
如果两棵树是同构的，输出“Yes”，否则输出“No”。

输入样例1（对应图1）：
8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -
输出样例1:
Yes
输入样例2（对应图2）：
8
B 5 7
F - -
A 0 3
C 6 -
H - -
D - -
G 4 -
E 1 -
8
D 6 -
B 5 -
E - -
H - -
C 0 2
G - 3
F - -
A 1 4
输出样例2:
No
*/
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char name;
    int left;
    int right;
};
typedef struct Node  *PNode;
typedef PNode *PNodeArr; 
PNode * ReadInput();
int get_root(PNodeArr);
int get_pos(char);
int compare(int, int, PNodeArr, PNodeArr);

int main()
{
    PNodeArr tree1, tree2;
    int pos1, pos2, equal;
    tree1 = ReadInput();
    tree2 = ReadInput();
    if (tree1[0]->left * tree2[0]->left == 0)
    {
        if (tree1[0]->left + tree2[0]->left > 0)
            equal = 0;
        else 
            equal = 1;
    }
    else
    {
        pos1 = get_root(tree1);
        pos2 = get_root(tree2);
        equal = compare(pos1, pos2, tree1, tree2);
    }
    if (equal)
        printf("Yes");
    else
        printf("No");
    char c;
    scanf("%c", &c);
    scanf("%c", &c);
    scanf("%c", &c);
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
    char name, left, right;
    scanf("%d", &N);
    PNode pnode;
    PNodeArr pnodeArr;
    pnodeArr = (PNode*)malloc((N+1)*sizeof(PNode));
    pnode = (PNode)malloc(sizeof(struct Node));
    pnode->name = '0';
    pnode->left = pnode->right = N;
    pnodeArr[0] = pnode;
    //printf("%c %d %d\n", pnode->name, pnode->left, pnode->right);
    for(int i=1; i<=N; i++)
    {
        scanf("\n%c %c %c", &name, &left, &right);
        //printf("name:%c left:%c right:%c\n", name, left, right);
        pnode = (PNode)malloc(sizeof(struct Node));
        pnode->name = name;
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
    int flag[N+1];
    for(int i=0; i<=N; i++)
    {
        flag[i] = 0;
    }
    for(int i=1; i<=N; i++)             // 标记子节点
    {   
        printf("%c %d %d\n", pnodeArr[i]->name, pnodeArr[i]->left, pnodeArr[i]->right);
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

int compare(int pos1, int pos2, PNodeArr tree1, PNodeArr tree2)
{   
    if (pos1 + pos2 > 0 && pos1 * pos2 == 0)
        return 0;                       // 子节点数目不一致 一个分支指向0一个分支指向节点
    if (pos1 + pos2 == 0)
        return 1;                       // 都指向0
    if (tree1[pos1]->name != tree2[pos2]->name)
        return 0;                       // 节点不一致
    int cond[4];
                                        // 不交换子节点
    cond[0] = compare(tree1[pos1]->right, tree2[pos2]->right, tree1, tree2);
    cond[1] = compare(tree1[pos1]->left , tree2[pos2]->left , tree1, tree2);
                                        // 交换子节点
    cond[2] = compare(tree1[pos1]->left , tree2[pos2]->right, tree1, tree2);
    cond[3] = compare(tree1[pos1]->right , tree2[pos2]->left , tree1, tree2);
                                        // 两种方式是否完全满足
    if (cond[0] + cond[1] == 2 || cond[2] + cond[3] == 2)
        return 1;
    else
        return 0;
}
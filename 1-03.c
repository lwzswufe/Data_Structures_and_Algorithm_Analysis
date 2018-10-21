/*
02-线性结构2 一元多项式的乘法与加法运算 （20 分）
设计函数分别求两个一元多项式的乘积与和。

输入格式:
输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数
（绝对值均为不超过1000的整数）。数字间以空格分隔。

输出格式:
输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，
但结尾不能有多余空格。零多项式应输出0 0。

输入样例:
4 3 4 -5 2  6 1  -2 0
3 5 20  -7 4  3 1
输出样例:
15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
5 20 -4 4 -5 2 9 1 -2 0
*/

#include <stdio.h>
#include <stdlib.h>

struct LNode
{
    int expon;
    int cof;
    struct LNode * next;
};
typedef struct LNode * PtrLNode;
PtrLNode ReadInput(int N);
PtrLNode Add(PtrLNode, PtrLNode, PtrLNode);
PtrLNode Mul(PtrLNode, PtrLNode, PtrLNode);
PtrLNode Insert(PtrLNode, int, int);
PtrLNode Initial();
void DelZero(PtrLNode);
void Print(PtrLNode);

int main()
{   
    int M, N;
    PtrLNode poly1, poly2, poly_add, poly_mul;
    scanf("%d", &M);
    poly1 = ReadInput(M);
    scanf("%d", &N);
    poly2 = ReadInput(N);
    
    poly_add = Initial();
    poly_mul = Initial();
    
    poly_mul = Mul(poly1, poly2, poly_mul);
    poly_add = Add(poly1, poly2, poly_add);
    
    DelZero(poly_mul);
    DelZero(poly_add);
    
    Print(poly_mul);
    Print(poly_add);
    return 0;
}

PtrLNode Initial()
{   
    PtrLNode L;
    L = (PtrLNode)malloc(sizeof(struct LNode));
    L->expon = 0;
    L->cof = 0;
    L->next = NULL;
    return L;
}


PtrLNode Add(PtrLNode poly1, PtrLNode poly2, PtrLNode poly_add)
{   
    PtrLNode poly_add_st, L;
    poly_add_st = poly_add;

    for(PtrLNode p1=poly1; p1 != NULL; p1 = p1->next)
    {   
        poly_add_st = Insert(poly_add_st, p1->cof, p1->expon);
    }
    for(PtrLNode p2=poly2; p2 != NULL; p2 = p2->next)
    {
        poly_add_st = Insert(poly_add_st, p2->cof, p2->expon);
    }
    return poly_add_st;
}

PtrLNode Insert(PtrLNode poly, int cof, int expon)
{                                                   // 将一个节点按序插入线性表
    PtrLNode L, tmp, past_node, poly_st = poly;
    //printf("%d %d\n", poly->cof, poly->expon);
    if(cof == 0)
        return poly_st;
    else if (poly->next == NULL)                    // 线性表为空
    {
        L = (PtrLNode)malloc(sizeof(struct LNode));
        L->next = NULL;
        L->cof = cof;
        L->expon = expon;
        poly->next = L;
        return poly_st;
    }
    do
    {
        past_node = poly;
        poly = poly->next;
    }
    while(poly != NULL && poly->expon > expon);     // 寻找插入位置
    
    if (poly != NULL && poly->expon == expon)       // 存在相同指数
    {
        poly->cof += cof;
    }
    else                                            // 在当前位置添加元素
    {
        L = (PtrLNode)malloc(sizeof(struct LNode));
        past_node->next = L;
        L->next = poly;
        L->cof = cof;
        L->expon = expon;
    }
    return poly_st;
}

void DelZero(PtrLNode poly)
{   
    //Print(poly);
    PtrLNode past_node = poly, poly_st = poly;
    poly = poly->next;
    while(poly != NULL)                             // 依次寻找
    {   
        if (poly->cof != 0)       
        {
            past_node = poly;
            poly = poly->next;
        }
        else                                        // 删除系数为0的项
        {   
            // printf("delete cof=%d expon=%d\n", poly->cof, poly->expon);
            past_node->next = poly->next;
            free(poly);
            poly = past_node->next;
        }
    }
    //Print(poly_st);
}

PtrLNode Mul(PtrLNode poly1, PtrLNode poly2, PtrLNode poly_mul)
{   
    PtrLNode poly_mul_st, L;
    poly_mul_st = poly_mul;
    
    for(PtrLNode p1=poly1; p1 != NULL; p1 = p1->next)
    {
        for(PtrLNode p2=poly2; p2 != NULL; p2 = p2->next)
        {   
            // printf("%d %d %d %d\n", p1->cof , p2->cof, p1->expon , p2->expon);
            poly_mul_st = Insert(poly_mul_st, p1->cof * p2->cof, p1->expon + p2->expon);
            // Print(poly_mul_st);
        }
    }
    return poly_mul_st;
}


PtrLNode ReadInput(int N)
{   
    PtrLNode L, past_L, first_L=NULL;
    if (N <= 0)
    {
         L = (PtrLNode)malloc(sizeof(struct LNode));
         L->expon = 0;
         L->cof = 0;
         L->next = NULL;
         return L;
    }
    int cof, expon;
    for (int i=0; i<N; )
    {   
        scanf("%d %d", &cof, &expon);
        if (cof == 0)
        {   
            continue;
        }
        else
        {
            i++;
        }
        L = (PtrLNode)malloc(sizeof(struct LNode));
        if (first_L == NULL)
            first_L = L;
        else
            past_L->next = L;
        L->cof = cof;
        L->expon = expon;
        past_L = L;
    }
    past_L->next = NULL;
    return first_L;
}

void Print(PtrLNode poly)
{   
    PtrLNode p=poly;
    if (p == NULL || p->next == NULL)
    {
        printf("0 0\n");
        return;
    }
    else
        p = p-> next;
    for(; p->next != NULL; p = p->next)
    {   
        if (p->cof != 0)
            printf("%d %d ", p->cof, p->expon);
    }
    printf("%d %d\n", p->cof, p->expon);
}

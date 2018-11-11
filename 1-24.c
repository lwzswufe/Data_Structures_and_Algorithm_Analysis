/*
09-排序1 排序 （25 分）
给定N个（长整型范围内的）整数，要求输出从小到大排序后的结果。

本题旨在测试各种不同的排序算法在各种数据情况下的表现。各组测试数据特点如下：

数据1：只有1个元素；
数据2：11个不相同的整数，测试基本正确性；
数据3：103个随机整数；
数据4：104个随机整数；
数据5：105个随机整数；
数据6：105个顺序整数；
数据7：105个逆序整数；
数据8：105个基本有序的整数；
数据9：105个随机正整数，每个数字不超过1000。
输入格式:
输入第一行给出正整数N（≤10^5），随后一行给出N个（长整型范围内的）整数，其间以空格分隔。

输出格式:
在一行中输出从小到大排序后的结果，数字间以1个空格分隔，行末不得有多余空格。

输入样例:
11
4 981 10 -17 0 -20 29 50 8 43 -5
输出样例:
-20 -17 -5 0 4 8 10 29 43 50 981
*/
#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;

void read_input(int N, int *arr);
void print_arr(int N, int *arr);
void Shell_Sort( ElementType A[], int N );
void Heap_Sort( ElementType A[], int N );

int main()
{
    int N;
    scanf("%d", &N);
    int arr[N];
    read_input(N, arr);
    //Shell_Sort( arr, N );
    Heap_Sort( arr, N);
    print_arr(N, arr);
    scanf("%d", &N);
    return 0;
}


void read_input(int N, int *arr)
{
    for(int i=0; i<N; i++)
    {
        scanf("%d", arr+i);
    }
}

void print_arr(int N, int *arr)
{   
    for(int i=0; i<N-1; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("%d\n", arr[N-1]);
}

void Shell_Sort( ElementType A[], int N )
{                                           // 希尔排序 - 用Sedgewick增量序列 
    int Si, D, P, i;
    ElementType Tmp;
                                            // 这里只列出一小部分增量 
    // for (int i=1, a=16, b=12; i<=20; i++, a*=4, b*=2)
    //     Sedgewick[20-i] = a - b + 1;
    int Sedgewick[] = {587521, 260609, 146305, 64769, 36289, 16001, 8929, 3905, 2161, 929, 505, 209, 109, 41, 19, 5, 1, 0};
      
    for ( Si=0; Sedgewick[Si]>=N; Si++ )   // 初始的增量Sedgewick[Si]不能超过待排序列长度
        ; 
 
    for ( D=Sedgewick[Si]; D>0; D=Sedgewick[++Si] )
    {
        for ( P=D; P<N; P++ )               // 间隔为D 执行i与i-D的交换
        { /* 插入排序*/
            Tmp = A[P];
            for ( i=P; i>=D && A[i-D]>Tmp; i-=D )
                A[i] = A[i-D];
            A[i] = Tmp;
        }
    }
}

void Swap( ElementType *a, ElementType *b )
{
     ElementType t = *a; *a = *b; *b = t;
}
  
void PercDown( ElementType A[], int p, int N )
{ // 改编代码4.24的PercDown( MaxHeap H, int p )    
  // 将N个元素的数组中以A[p]为根的子堆调整为最大堆 
    int Parent, Child;
    ElementType X;
 
    X = A[p];                               // 取出根结点存放的值 
    for( Parent=p; (Parent*2+1)<N; Parent=Child ) 
    {
        Child = Parent * 2 + 1;
        if( (Child!=N-1) && (A[Child]<A[Child+1]) ) //若右节点存在且右节点大于左节点
            Child++;                        // Child指向左右子结点的较大者
        if( X >= A[Child] ) 
            break;                          // 找到了合适位置 
        else                                // 下滤X 
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}
 
void Heap_Sort( ElementType A[], int N ) 
{ // 堆排序 
     int i;
       
     for ( i=N/2-1; i>=0; i-- )             // 建立最大堆 自底向上梳理顺序 将大数上浮 小数下沉
         PercDown( A, i, N );
      
     for ( i=N-1; i>0; i-- )                // 删除最大堆顶  每次循环 堆大小减1
     {
         Swap( &A[0], &A[i] ); 
         PercDown( A, 0, i );
     }
}
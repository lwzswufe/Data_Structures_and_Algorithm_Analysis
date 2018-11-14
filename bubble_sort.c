#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;

void read_input(int N, int *arr);
void print_arr(int N, int *arr);
void Bubble_Sort( ElementType A[], int N );

int main()
{
    int N;
    scanf("%d", &N);
    int arr[N];
    read_input(N, arr);
    Bubble_Sort( arr, N);
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


void Swap( ElementType *a, ElementType *b )
{
    ElementType t = *a; *a = *b; *b = t;
}

void Bubble_Sort( ElementType A[], int N ) 
{   
    int flag;
    for(int p=N; p>0; p--)                              // p是未排序部分的大小
    {   
        flag = 0;
        for(int i=1; i<p; i++)                          // 从头开始比较相邻两元素
        {
            if (A[i] < A[i-1])                          // 发现逆序就交换数据
            {
                Swap(&A[i], &A[i-1]);
                flag = 1;
            }
        }
        if (flag == 0)                                  // 若发现队列已经是排好序 就退出程序
            return;
    }
}
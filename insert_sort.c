#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;

void read_input(int N, int *arr);
void print_arr(int N, int *arr);
void Insert_Sort( ElementType A[], int N );

int main()
{
    int N;
    scanf("%d", &N);
    int arr[N];
    read_input(N, arr);
    Insert_Sort( arr, N);
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

void Insert_Sort( ElementType A[], int N ) 
{
    int p, i;
    ElementType tmp;

    for(p=1; p<N; p++)                              // 未排序部分从1开始
    {
        tmp = A[p];                                 // 缓存未排序部分的第一个数字
        for (i=p; i>0 && A[i-1] > tmp; i--)         // 对于已排序的部分 从尾到头查找合适的位置
        {
            A[i] = A[i-1];
        }
        A[i] = tmp;                                 // 插入缓存数据
    }
}
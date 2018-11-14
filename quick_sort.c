#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;

void read_input(int N, int *arr);
void print_arr(int N, int *arr);
void Quick_Sort( ElementType A[], int N );

int main()
{
    int N;
    scanf("%d", &N);
    int arr[N];
    read_input(N, arr);
    Quick_Sort( arr, N);
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

ElementType Get_Pivot( ElementType A[], int L, int R)
{
    int middle = (L + R) / 2;
    if (A[L] > A[middle])
        Swap(&A[L], &A[middle]);
    if (A[L] > A[R])
        Swap(&A[L], &A[R]);
    if (A[middle] > A[R])
        Swap(&A[middle], &A[R]);
    Swap(&A[middle], &A[R-1]);                          // LXXXXXXXPR  =>  LLLLRRRRPR => LLLLPRRRRR
    return A[R-1];                                      // 返回Pivot
}

void Qsort( ElementType A[], int L_st, int R_end)
{   
    int Pivot, L, R;
    if (R_end - L_st > 100)
    {
        Pivot = Get_Pivot(A, L_st, R_end);              // 获取主元
        L = L_st;
        R = R_end - 1;
        while(1)                                        // 从两头开始依次检索 异常点 并交换
        {
            while(A[++L] < Pivot);                      // 从 左 开始查找比 主元大的元素
            while(A[--R] > Pivot);                      // 从 右 开始查找比 主元小的元素
            if (L < R)                                  // 若未到循环终止 交换两点
                Swap(&A[L], &A[R]);
            else
                break;
        }
        Swap(&A[L], &A[R_end - 1]);                     // 交换主元到正确位置 LLLLRRRRPR => LLLLPRRRRR
        Qsort(A, L_st, L - 1);                          // 递归解决左边
        Qsort(A, L + 1, R_end);                         // 递归解决右边
    }
    else
    {
        Insert_Sort(&A[L_st], R_end-L_st+1);
    }
}

void Quick_Sort( ElementType A[], int N ) 
{   
    Qsort(A, 0, N-1);
}
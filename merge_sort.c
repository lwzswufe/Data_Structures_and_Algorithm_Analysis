#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;

void read_input(int N, int *arr);
void print_arr(int N, int *arr);
void Merge_Sort( ElementType A[], int N );

int main()
{
    int N;
    scanf("%d", &N);
    int arr[N];
    read_input(N, arr);
    Merge_Sort( arr, N);
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

void Merge(ElementType A[], ElementType tmpA[], int L, int R, int R_end)
{
    int L_end = R - 1, L_st = L, sorted_L = L;          // 左半区L L_end 右半区 R R_end
                                                        // 合并区域 L_st R_end
    while (L <= L_end && R <= R_end)                    // 若两个半区的数据都还没有取完
    {
        if (A[L] <= A[R])                               // 优先取左半区的数据
        {
            tmpA[sorted_L] = A[L];
            L++;
        }
        else
        {   
            tmpA[sorted_L] = A[R];
            R++;
        }
        sorted_L++;                                     // 递增缓存区'指针'
    }
    while(L <= L_end)                                   // 右半区取完 复制左半区
    {
        tmpA[sorted_L] = A[L];
        L++;
        sorted_L++;
    }
    while(R <= R_end)                                   // 左半区取完 复制右半区
    {
        tmpA[sorted_L] = A[R];
        R++;
        sorted_L++;
    }
    for (int i=L_st; i<=R_end; i++)                     //  从缓存区复制数据到原有内存上
    {
        A[i] = tmpA[i];
    }
}


void Merge_core( ElementType A[], ElementType tmpA[], int L, int R_end)
{
    int Center;
    if (L < R_end)
    {
        Center = ( L + R_end ) / 2;
        Merge_core(A, tmpA, L, Center);                 // 递归解决左边
        Merge_core(A, tmpA, Center + 1, R_end);         // 递归解决右边
        Merge(A, tmpA, L, Center + 1, R_end);           // 合并左右两边
    }
}


void Merge_Sort( ElementType A[], int N ) 
{   
    ElementType * tmpA;
    tmpA = (ElementType*)malloc(N*sizeof(ElementType));
    if (tmpA != NULL)
    {
        Merge_core(A, tmpA, 0, N - 1);
        free(tmpA);
    }
    else
        printf("Error: not enough memery");
}
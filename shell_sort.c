#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;

void read_input(int N, int *arr);
void print_arr(int N, int *arr);
void Shell_Sort( ElementType A[], int N );

int main()
{
    int N;
    scanf("%d", &N);
    int arr[N];
    read_input(N, arr);
    Shell_Sort( arr, N );
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

/*
09-排序2 Insert or Merge （25 分）
According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, 
and growing a sorted output list. Each iteration, insertion sort removes 
one element from the input data, finds the location it belongs within 
the sorted list, and inserts it there. It repeats until no input elements 
remain.

Merge sort works as follows: Divide the unsorted list into N sublists, 
each containing 1 element (a list of 1 element is considered sorted). 
Then repeatedly merge two adjacent sublists to produce new sorted sublists 
until there is only 1 sublist remaining.

Now given the initial sequence of integers, together with a sequence which 
is a result of several iterations of some sorting method, can you tell 
which sorting method we are using?

Input Specification:
Each input file contains one test case. For each case, the first line gives 
a positive integer N (≤100). Then in the next line, N integers are given 
as the initial sequence. The last line contains the partially sorted sequence 
of the N numbers. It is assumed that the target sequence is always ascending. 
All the numbers in a line are separated by a space.

Output Specification:
For each test case, print in the first line either "Insertion Sort" or 
"Merge Sort" to indicate the method used to obtain the partial result. Then 
run this method for one more iteration and output in the second line the 
resuling sequence. It is guaranteed that the answer is unique for each 
test case. All the numbers in a line must be separated by a space, and 
there must be no extra space at the end of the line.

Sample Input 1:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
Sample Output 1:
Insertion Sort
1 2 3 5 7 8 9 4 6 0
Sample Input 2:
10
3 1 2 8 7 5 9 4 0 6
1 3 2 8 5 7 4 9 0 6
Sample Output 2:
Merge Sort
1 2 3 8 4 5 7 9 0 6
*/
#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;

void read_input(int N, int *arr);
void print_arr(int N, int *arr);
int is_insert_sort(int N, int *arr0, int *arr1);
void Insertion_Sort( ElementType A[], int N , int P);
void MergeSort( ElementType A[], int N );

int main()
{
    int N, idx;
    scanf("%d", &N);
    int arr0[N], arr1[N];
    read_input(N, arr0);
    read_input(N, arr1);
    idx = is_insert_sort(N, arr0, arr1);
    if (idx < 0)
    {   
        MergeSort( arr1, N );
        printf("Merge Sort\n");
    }
    else
    {   
        Insertion_Sort(arr1, N, idx);
        printf("Insertion Sort\n");
    }
    print_arr(N, arr1);
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

int is_insert_sort(int N, int *arr0, int *arr1)
{   // 判断是否是插入排序  若是返回已排序列的位置 若不是返回-1
    // 前半部分是已派好序列。后半部分是原序列
    int i, idx;
    for(i=1; i<N && arr1[i-1] < arr1[i]; i++)
        ;
    idx = i;
    for(; i<N && idx >=0; i++)
    {
        if (arr0[i] != arr1[i])
            idx = -1;
    }
    return idx;
}

int mod(int x)
{
    int i = 1;
    while (x % (2 * i) == 0)
    {
        i *= 2;
    }
    return i;
}

int find_width(int N, int *arr1)
{   // 寻找归并排序已经行窗口大小
    int width = N;
    for(int i=0; i<N-1; i++)
    {   
        if (arr1[i] > arr1[i+1] && mod(i+1) < width)
        {
            width = mod(i+1);
        }
    }
    return width;
}



void Swap( ElementType *a, ElementType *b )
{
    ElementType t = *a; *a = *b; *b = t;
}

void Insertion_Sort( ElementType A[], int N , int P)
{ /* 插入排序 */
    int i;
    ElementType Tmp;
    if (P >= N)
        return;
    Tmp = A[P];                     // 取出未排序序列中的第一个元素
    for ( i=P; i>0 && A[i-1]>Tmp; i-- )
            A[i] = A[i-1];          // 依次与已排序序列中元素比较并右移
    A[i] = Tmp;                     // 放进合适的位置 
}

void print_arr(int N, int *arr)
{   
    for(int i=0; i<N-1; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("%d\n", arr[N-1]);
}

void Merge( ElementType A[], ElementType TmpA[], int L, int R, int RightEnd )
{ /* 将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列 */
    int LeftEnd, NumElements, Tmp;
    int i;
      
    LeftEnd = R - 1;                    // 左边终点位置
    Tmp = L;                            // 有序序列的起始位置 
    NumElements = RightEnd - L + 1;
      
    while( L <= LeftEnd && R <= RightEnd ) 
    {
        if ( A[L] <= A[R] )
            TmpA[Tmp++] = A[L++];       // 将左边元素复制到TmpA 
        else
            TmpA[Tmp++] = A[R++];       // 将右边元素复制到TmpA 
    }
 
    while( L <= LeftEnd )
        TmpA[Tmp++] = A[L++];           // 直接复制左边剩下的 
    while( R <= RightEnd )
        TmpA[Tmp++] = A[R++];           // 直接复制右边剩下的 
          
    for( i = 0; i < NumElements; i++, RightEnd -- )
        A[RightEnd] = TmpA[RightEnd];   // 将有序的TmpA[]复制回A[]
}
 
void Msort( ElementType A[], ElementType TmpA[], int L, int RightEnd )
{ // 核心递归排序函数 
    int Center;
      
    if ( L < RightEnd ) 
    {
        Center = (L+RightEnd) / 2;
        //Msort( A, TmpA, L, Center );              // 递归解决左边 
        //Msort( A, TmpA, Center+1, RightEnd );     // 递归解决右边  
        Merge( A, TmpA, L, Center+1, RightEnd );  // 合并两段有序序列 
    }
}
 
void MergeSort( ElementType A[], int N )
{ /* 归并排序 */
    ElementType *TmpA;
    TmpA = (ElementType *)malloc(N*sizeof(ElementType));
    int width, st, ed;
    width = find_width(N, A) * 2;
    //printf("width: %d\n", width);
    if ( TmpA != NULL ) 
    {   
        for (int i=0; i<N; i+=width)
        {   
            st = i;
            ed = i + width - 1;
            if (ed > N - 1)
                ed = N - 1;
            Msort( A, TmpA, st, ed);
        }
        free( TmpA );
    }
    else 
        printf( "空间不足" );
}
/*
09-排序3 Insertion or Heap Sort （25 分）
According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, 
and growing a sorted output list. Each iteration, insertion sort removes 
one element from the input data, finds the location it belongs within 
the sorted list, and inserts it there. It repeats until no input elements 
remain.

Heap sort divides its input into a sorted and an unsorted region, and 
it iteratively shrinks the unsorted region by extracting the largest 
element and moving that to the sorted region. it involves the use of a 
heap data structure rather than a linear-time search to find the maximum.

Now given the initial sequence of integers, together with a sequence 
which is a result of several iterations of some sorting method, can you 
tell which sorting method we are using?

Input Specification:
Each input file contains one test case. For each case, the first line 
gives a positive integer N (≤100). Then in the next line, N integers 
are given as the initial sequence. The last line contains the partially 
sorted sequence of the N numbers. It is assumed that the target sequence 
is always ascending. All the numbers in a line are separated by a space.

Output Specification:
For each test case, print in the first line either "Insertion Sort" or 
"Heap Sort" to indicate the method used to obtain the partial result. 
Then run this method for one more iteration and output in the second 
line the resuling sequence. It is guaranteed that the answer is unique 
for each test case. All the numbers in a line must be separated by a 
space, and there must be no extra space at the end of the line.

Sample Input 1:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
Sample Output 1:
Insertion Sort
1 2 3 5 7 8 9 4 6 0
Sample Input 2:
10
3 1 2 8 7 5 9 4 6 0
6 4 5 1 0 3 2 7 8 9
Sample Output 2:
Heap Sort
5 4 3 1 0 2 6 7 8 9
*/

#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;

void read_input(int N, int *arr);
void print_arr(int N, int *arr);
int is_insert_sort(int N, int *arr0, int *arr1);
void Insertion_Sort( ElementType A[], int N , int P);
void HeapSort(ElementType arr0[], ElementType arr1[], int N);

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
        HeapSort(arr0, arr1, N);
        printf("Heap Sort\n");
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
    int i, idx=1;
    for(i=1; i<N && arr1[i-1] <= arr1[i]; i++)
        ;
    idx = i;
    for(; i<N && idx >=0; i++)
    {
        if (arr0[i] != arr1[i])
            idx = -1;
    }
    //printf("idx=%d\n", idx);
    return idx;
}

int find_width(int N, int *arr1)
{   // 寻找归并排序已经行窗口大小
    int i, width=2;
    for(; width < N; width *= 2)
    {
        for(i=width; i<N; i+=width*2)
        {   
            if (arr1[i-1] > arr1[i])
                return width;
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
    if (N <= 0)
        return;
    for(int i=0; i<N-1; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("%d\n", arr[N-1]);
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
 
int compare(ElementType arr0[], ElementType arr1[], int N)
{
    for (int i=0; i<N; i++)
    {
        if (arr0[i] != arr1[i])
            return 1;
    }
    return 0;
}

void HeapSort(ElementType arr0[], ElementType arr1[], int N)
{ // 堆排序 
    int i;
    for ( i=N/2-1; i>=0; i-- )             // 建立最大堆 自底向上梳理顺序 将大数上浮 小数下沉
        PercDown( arr0, i, N );
         
    for ( i=N-1; i>0&&compare(arr0, arr1, N); i-- )                // 删除最大堆顶  每次循环 堆大小减1
    {
        Swap( &arr0[0], &arr0[i] ); 
        PercDown( arr0, 0, i );
    }
    if (i>0)
    {   
        Swap( &arr1[0], &arr1[i] ); 
        PercDown( arr1, 0, i );
    }
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
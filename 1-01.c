/*
01-复杂度1 最大子列和问题 （20 分）
给定K个整数组成的序列{ N1, N2, ..., NK}，“连续子列”被定义为{ Ni , Ni+1 , ..., Nj }，
其中 1≤i≤j≤K。“最大子列和”则被定义为所有连续子列元素的和中最大者。例如给定序列
{ -2, 11, -4, 13, -5, -2 }，其连续子列{ 11, -4, 13 }有最大的和20。
现要求你编写程序，计算给定整数序列的最大子列和。

本题旨在测试各种不同的算法在各种数据情况下的表现。各组测试数据特点如下：

数据1：与样例等价，测试基本正确性；
数据2：10^2个随机整数；
数据3：10^3个随机整数；
数据4：10^4个随机整数；
数据5：10^5个随机整数；
输入格式:
输入第1行给出正整数K (≤100000)；第2行给出K个整数，其间以空格分隔。

输出格式:
在一行中输出最大子列和。如果序列中所有整数皆为负数，则输出0。

输入样例:
6
-2 11 -4 13 -5 -2
输出样例:
20
*/
#include <stdio.h>

void fun1()
{   
    int N, x, sum_now=0, sum_max=0;
    scanf("%d", &N);
    for (int i=0; i<N; i++)
    {   
        scanf("%d", &x);
        sum_now += x;
        if (sum_now < 0)                    // 若当前子列和小于零 舍弃
        {
            sum_now = 0;
        }
        if (sum_now > sum_max)              // 若当前子列和大于之前最大值 更新最大值
        {
            sum_max = sum_now;
        }
    }
    printf("%d", sum_max);
}


int mid_fun(int* arr, int st, int ed)
{                                           // 计算中最大子列和
    int sum_now=0, sum_right_max=0, sum_left_max=0;
    for(int i=(st+ed)/2-1; i>=st; i--)      // 从中向右扩展
    {
        sum_now += arr[i];
        if (sum_now > sum_right_max)
            sum_right_max = sum_now;
    }

    sum_now = 0;

    for(int i=(st+ed)/2; i<ed; i++)         // 从中向左扩展
    {
        sum_now += arr[i];
        if (sum_now > sum_left_max)
            sum_left_max = sum_now;
    }
    return sum_right_max + sum_left_max;    // 合并左右两部分
}
int sub_fun(int* arr, int st, int ed)
{                                           // 分治算法
    if (ed == st + 1)                       // 递归退出条件
    {
        if (arr[st] > 0)
            return arr[st];
        else
            return 0;
    }
    int right, middle, left, max_sum;
    right = sub_fun(arr, st, (st + ed)/2);  // 计算右最大子列和
    left = sub_fun(arr, (st + ed)/2, ed);   // 计算左最大子列和
    middle = mid_fun(arr, st, ed);          // 计算中最大子列和
                                            // 返回三者最大值
    if (left > middle)
        max_sum = left;
    else
        max_sum = middle;
    if (right > max_sum)
        max_sum = right;
    return max_sum;
}

void fun2()
{
    int N, sum_max=0;
    // scanf("%d", &N);
    // int arr[N];
    // for (int i=0; i<N; i++) 
    //     scanf("%d", arr+i);
    N = 6;
    int arr[6] = {-2,11,-4,13,-5,-2};
    sum_max = sub_fun(arr, 0, N);
    printf("%d", sum_max);
}

int main(int argc, char const *argv[])
{
    fun2();
    return 0;
}

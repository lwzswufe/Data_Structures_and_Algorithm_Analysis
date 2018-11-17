/*
10-排序5 PAT Judge （25 分）
The ranklist of PAT is generated from the status list, which shows the 
scores of the submissions. This time you are supposed to generate the 
ranklist for PAT.

Input Specification:
Each input file contains one test case. For each case, the first line 
contains 3 positive integers, N (≤10^4), the total number of users, 
K (≤5), the total number of problems, and M (≤10^5), the total number 
of submissions. It is then assumed that the user id's are 5-digit numbers 
from 00001 to N, and the problem id's are from 1 to K. The next line 
contains K positive integers p[i] (i=1, ..., K), where p[i] corresponds 
to the full mark of the i-th problem. Then M lines follow, each gives 
the information of a submission in the following format:

user_id problem_id partial_score_obtained
where partial_score_obtained is either −1 if the submission cannot even 
pass the compiler, or is an integer in the range [0, p[problem_id]]. All 
the numbers in a line are separated by a space.

Output Specification:
For each test case, you are supposed to output the ranklist in the following 
format:

rank user_id total_score s[1] ... s[K]
where rank is calculated according to the total_score, and all the users 
with the same total_score obtain the same rank; and s[i] is the partial 
score obtained for the i-th problem. If a user has never submitted a solution 
for a problem, then "-" must be printed at the corresponding position. If a 
user has submitted several solutions to solve one problem, then the highest 
score will be counted.

The ranklist must be printed in non-decreasing order of the ranks. For 
those who have the same rank, users must be sorted in nonincreasing order 
according to the number of perfectly solved problems. And if there is still 
a tie, then they must be printed in increasing order of their id's. For 
those who has never submitted any solution that can pass the compiler, or 
has never submitted any solution, they must NOT be shown on the ranklist. 
It is guaranteed that at least one user can be shown on the ranklist.

Sample Input:
7 4 20          user:7 problem:4 submission:20
20 25 25 30     problem scores
00002 2 12      score equal according to the number of perfectly solved problems
00007 4 17      finally in increasing order of their id's.
00005 1 19
00007 2 25
00005 1 20
00002 2 2
00005 1 15
00001 1 18
00004 3 25
00002 2 25
00005 3 22
00006 4 -1
00001 2 18
00002 1 20
00004 1 15
00002 4 18
00001 3 4
00001 4 2
00005 2 -1              submission cannot even pass the compiler
00004 2 0
Sample Output:
1 00002 63 20 25 - 18   - never submit problem
2 00005 42 20 0 22 -
2 00007 42 - 25 - 17
2 00001 42 18 18 4 2
5 00004 40 15 0 25 -
*/

#include <stdio.h>
#include <stdlib.h>
#define PROBLEM_NUM 5
#define NO_SUBMIT -2
#define NO_COMPILE -1


struct User
{   
    int id;                         // 用户编号
    int perfect;                    // 完美提交个数
    int total_score;
    int is_show;
    int *scores;                    // 各道题的得分
};

typedef struct User *puser;
typedef struct User ElementType;
void read_input(int user_num, int submit_num, int problem_num, puser* user_arr);
void Swap( ElementType *a, ElementType *b );
void print_arr(int user_num, int problem_num, puser* user_arr);
void Insertion_Sort( ElementType* A[], int N);

int main(int argc, char const *argv[])
{
    int user_num, problem_num, submit_num;
    scanf("%d %d %d", &user_num, &problem_num, &submit_num);
    puser user_arr[user_num]; 
    read_input(user_num, submit_num, problem_num, user_arr);
    Insertion_Sort( user_arr, user_num);
    print_arr(user_num, problem_num, user_arr);
    //scanf("%d %d %d", &user_num, &problem_num, &submit_num);
    return 0;
}

void read_input(int user_num, int submit_num, int problem_num, puser* user_arr)
{   
    puser pu;
    int *arr, user_id, problem_id, score;
    int scores[problem_num];

    for (int i=0; i<problem_num; i++)
        scanf("%d", scores+i);

    for(int i=0; i<user_num; i++)                                   // 初始化用户列表
    {
        pu = (puser)malloc(sizeof(struct User));
        arr = (int*)malloc(problem_num * sizeof(int));
        for (int j=0; j<problem_num; j++)
            arr[j] = NO_SUBMIT;
        pu->scores = arr;
        pu->id = i+1;
        pu->is_show = 0;
        pu->perfect = 0;
        pu->total_score = 0;
        user_arr[i] = pu;
    }

    for(int i=0; i<submit_num; i++)                                 // 读取提交数据
    {   
        scanf("%d %d %d", &user_id, &problem_id, &score);
        // printf("user_id: %05d problem_id: %d score:%d\n", user_id, problem_id, score);
        if (score  > user_arr[user_id - 1]->scores[problem_id - 1])
        {
            user_arr[user_id - 1]->scores[problem_id - 1] = score;
        }
    }

    for(int i=0; i<user_num; i++)                                   // 计算用户总分
    {   
        pu = user_arr[i];
        for(int j=0; j<problem_num; j++)
        {
            if (pu->scores[j] == scores[j])
                pu->perfect++;
            if (pu->scores[j] >= 0)
            {
                pu->total_score += pu->scores[j];
                pu->is_show = 1;
            }
        }
    }
}

int Better(ElementType *a, ElementType *b)
{
    if (a->total_score > b->total_score)
        return 1;
    if (a->total_score < b->total_score)
        return 0;
    if (a->perfect > b->perfect)
        return 1;
    if (a->perfect < b->perfect)
        return 0;
    if (a->id < b->id)
        return 1;
    else    
        return 0;
}

void Swap( ElementType *a, ElementType *b )
{
    ElementType t = *a; *a = *b; *b = t;
}

void Insertion_Sort( ElementType* A[], int N)
{ /* 插入排序 */
    int i;
    for (int P=1; P<N; P++)
    {
        for ( i=P; i>0 && Better(A[i], A[i-1]); i-- )
            Swap(A[i], A[i-1]);     // 依次与已排序序列中元素比较并右移
    }
}

void print_arr(int user_num, int problem_num, puser* user_arr)
{   
    int rank = 1, rank_score = -99;
    puser pu;
    for(int i=0; i<user_num; i++)
    {   
        pu = user_arr[i];
        if(!pu->is_show)
            continue;
        if(rank_score != pu->total_score)
        {
            rank = i+1;
            rank_score = pu->total_score;
        }
        printf("%d %05d %d", rank, pu->id, pu->total_score);
        for (int j=0; j<problem_num; j++)
        {
            if (pu->scores[j] >= 0)
                printf(" %d", pu->scores[j]);
            else
            {
                if (pu->scores[j] == NO_COMPILE)
                    printf(" 0");
                else
                    printf(" -");
            }
        }
        printf("\n");
    }
}

/*
11-散列4 Hashing - Hard Version （30 分）
Given a hash table of size N, we can define a hash function H(x)=x%N. 
Suppose that the linear probing is used to solve collisions, we can 
easily obtain the status of the hash table with a given sequence of 
input numbers.

However, now you are asked to solve the reversed problem: reconstruct 
the input sequence from the given status of the hash table. Whenever 
there are multiple choices, the smallest number is always taken.

Input Specification:
Each input file contains one test case. For each test case, the first 
line contains a positive integer N (≤1000), which is the size of the 
hash table. The next line contains N integers, separated by a space. 
A negative integer represents an empty cell in the hash table. It is 
guaranteed that all the non-negative integers are distinct in the table.

Output Specification:
For each test case, print a line that contains the input sequence, with 
the numbers separated by a space. Notice that there must be no extra 
space at the end of each line.

Sample Input:
11
33 1 13 12 34 38 27 22 32 -1 21
Sample Output:
1 13 12 21 33 34 38 27 22 32
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INT 0x7fffffff
typedef int ValueType;
typedef int KeyType;
typedef int Position;
typedef enum EntryType{Legitimate, Empty, Allowed} EntryType;

struct HashTable
{   
    int N;
    int count;
    KeyType *keys;                                  //  关键词名
    EntryType *states;                              //  状态
};
typedef struct HashTable *phash;
int check_pos(phash ph, Position pos_ed);
void check(phash ph);
void insert(phash ph);
void read_input(int N)
{   
    phash ph;
    KeyType *key_arr, key;
    EntryType *state_arr;

    ph = (phash)malloc(sizeof(struct HashTable));
    key_arr = (KeyType*)malloc(N * sizeof(KeyType));
    state_arr = (EntryType*)malloc(N * sizeof(EntryType));

    ph->keys = key_arr;
    ph->states = state_arr;
    ph->N = N;
    int count = 0;
    for(int i=0; i<N; i++)
    {
        scanf("%d", &key);
        ph->keys[i] = key;
        if (key >= 0)
        {   
            count++;
            if (key % N == i)
                ph->states[i] = Allowed;                // 可插入
            else
                ph->states[i] = Empty;                  // 不可插入
        }
        else
            ph->states[i] = Legitimate;                 // 已插入
    }
    ph->count = count;
    for(; count > 0; count--)
    {   
        if (count < ph->count)
            printf(" ");
        insert(ph);
        check(ph);
    }
}

int main()
{   
    int N;
    scanf("%d", &N);
    read_input(N);
    scanf("%d", &N);
}

void insert(phash ph)
{   // 插入元素
    KeyType min_key = MAX_INT;
    Position min_pos = -1;
    for (int i=0; i<ph->N; i++)
    {
        if (ph->states[i] == Allowed && ph->keys[i] < min_key)
        {
            min_key = ph->keys[i];
            min_pos = i;
        }
    }
    if (min_pos >= 0)
    {
        printf("%d", min_key);
        ph->states[min_pos] = Legitimate;
    }
}

void check(phash ph)
{   
    int state;
    for (int i=0; i<ph->N; i++)
    {
        if (ph->states[i] == Empty)
        {
            state = check_pos(ph, i);
            if (state)
                ph->states[i] = Allowed;
        }
    }
}

int check_pos(phash ph, Position pos_ed)
{   
    Position pos = ph->keys[pos_ed] % ph->N;
    while(pos != pos_ed)
    {
        if (ph->states[pos] != Legitimate)
            return 0;
        pos++;
        if (pos >= ph->N)
            pos -= ph->N;
    }
    return 1;
}
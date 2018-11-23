/*
11-散列2 Hashing （25 分）
The task of this problem is simple: insert a sequence of distinct positive 
integers into a hash table, and output the positions of the input numbers. 
The hash function is defined to be H(key)=key%TSize where TSize is the maximum 
size of the hash table. Quadratic probing (with positive increments only)  !!! 仅使用增量序列
is used to solve the collisions.

Note that the table size is better to be prime. If the maximum size given 
by the user is not prime, you must re-define the table size to be the smallest 
prime number which is larger than the size given by the user.

Input Specification:
Each input file contains one test case. For each case, the first line contains 
two positive numbers: MSize (≤10^4) and N (≤MSize) which are the user-defined 
table size and the number of input numbers, respectively. Then N distinct positive 
integers are given in the next line. All the numbers in a line are separated 
by a space.

Output Specification:
For each test case, print the corresponding positions (index starts from 0) of 
the input numbers in one line. All the numbers in a line are separated by a 
space, and there must be no extra space at the end of the line. In case it is 
impossible to insert the number, print "-" instead.

使用平方探测法储存序列 并标记储存不了的序列
Sample Input:
4 4
10 6 4 15
Sample Output:
0 1 4 -
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int ValueType;
typedef int KeyType;
typedef int Position;
typedef enum EntryType{Legitimate, Empty, Deleted} EntryType;
struct HashTable
{   
    int N;
    ValueType *values;                              //  储存值
    KeyType *keys;                                  //  关键词名
    EntryType *states;                              //  状态
};
typedef struct HashTable *phash;
int NextPrime(int x);
Position hash(KeyType key);
Position insert(phash ph, KeyType key);
Position Position_Iteration(Position default_pos, int i);
Position Find(phash ph, KeyType key);
int TABLESIZE;

int NextPrime(int x)
{   
    int is_prime = 1;
    for(int i=x+1; i>0; i++)
    {   
        is_prime = 1;
        for(int p=2; p*p<=i; p++)
        {
            if (i % p == 0)
            {
                is_prime = 0;
                break;
            }
        }
        if (is_prime)
            return i;
    }
    return 0;
}


void read_input(int N)
{   
    phash ph;
    ValueType *value_arr;
    KeyType *key_arr, key;
    EntryType *state_arr;

    ph = (phash)malloc(sizeof(struct HashTable));
    value_arr = (ValueType*)malloc(TABLESIZE * sizeof(ValueType));
    key_arr = (KeyType*)malloc(TABLESIZE * sizeof(KeyType));
    state_arr = (EntryType*)malloc(TABLESIZE * sizeof(EntryType));

    ph->values = value_arr;
    ph->keys = key_arr;
    ph->states = state_arr;
    ph->N = TABLESIZE;

    for(int i=0; i<TABLESIZE; i++)
    {
        value_arr[i] = 0;
        key_arr[i] = -1;
        state_arr[i] = Empty;
    }

    Position pos;
    for(int i=0; i<N; i++)
    {
        scanf("%d", &key);
        pos = insert(ph, key); 
        if (i != 0)
            printf(" ");
        if (pos < 0)
            printf("-");
        else
            printf("%d", pos);
    }
}

int main()
{   
    int M, N;
    scanf("%d %d", &M, &N);
    TABLESIZE = NextPrime(M);
    // printf("tablesize:%d\n", TABLESIZE);
    read_input(N);
    scanf("%d", &N);
}

Position hash(KeyType key)
{   // 散列函数
    return key % TABLESIZE;
}

Position insert(phash ph, KeyType key)
{   // 插入元素
    //printf("insert %s\n", key);
    Position pos = Find(ph, key);
    if (ph->states[pos] != Legitimate)                  // 查找结果为空或已删除 就插入元素 
    {
        ph->states[pos] = Legitimate;
        ph->keys[pos] = key;
        // printf("insert %s at %d\n", key, pos);
    }
    return pos;
}

Position Position_Iteration(Position default_pos, int i)
{   // 平方探测法 位置迭代
    Position pos;
    pos = default_pos + i * i;
    pos %= TABLESIZE;
    if(pos < 0)
        pos += TABLESIZE;
    return pos;
}

Position Find(phash ph, KeyType key)
{   // 查找元素 返回元素位置 或者第一个空位/已删除位置
    Position default_pos, pos;
    int i=1;
    default_pos = pos = hash(key);
    while(ph->states[pos] == Legitimate && ph->keys[pos] != key)
    {
        pos = Position_Iteration(default_pos, i);
        //printf(" test_%d ", pos);
        i++;
        if (i > TABLESIZE * 2)
            return -1;
    }
    // printf("find %d at %d\n", key, pos);
    return pos;
}
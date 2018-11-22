/*
11-散列1 电话聊天狂人 （25 分）
给定大量手机用户通话记录，找出其中通话次数最多的聊天狂人。

输入格式:
输入首先给出正整数N（≤10^​5），为通话记录条数。随后N行，每行给出一条通话记录。
简单起见，这里只列出拨出方和接收方的11位数字构成的手机号码，其中以空格分隔。

输出格式:
在一行中给出聊天狂人的手机号码及其通话次数，其间以空格分隔。如果这样的人不唯一
，则输出狂人中最小的号码及其通话次数，并且附加给出并列狂人的人数。

输入样例:
4
13005711862 13588625832
13505711862 13088625832
13588625832 18087925832
15005713862 13588625832
输出样例:
13588625832 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 39997
#define true 1
#define false 0
typedef int ValueType;
typedef char* KeyType;
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
Position hash(char *str);
Position insert(phash ph, KeyType key);
Position Position_Iteration(Position default_pos, int i);
Position Find(phash ph, KeyType key);

void read_input(int N)
{   
    phash ph;
    ValueType *value_arr;
    KeyType *key_arr;
    EntryType *state_arr;

    ph = (phash)malloc(sizeof(struct HashTable));
    value_arr = (ValueType*)malloc(MAX_SIZE * sizeof(ValueType));
    key_arr = (KeyType*)malloc(MAX_SIZE * sizeof(KeyType));
    state_arr = (EntryType*)malloc(MAX_SIZE * sizeof(EntryType));

    ph->values = value_arr;
    ph->keys = key_arr;
    ph->states = state_arr;
    ph->N = N;

    for(int i=0; i<MAX_SIZE; i++)
    {
        value_arr[i] = 0;
        key_arr[i] = NULL;
        state_arr[i] = Empty;
    }

    char str[14];
    Position pos;
    int max_call=0, max_caller_num=0;
    KeyType caller = NULL;
    for(int i=0; i<N*2; i++)
    {
        scanf("%s", str);
        pos = insert(ph, str); 
        if (value_arr[pos] == max_call && max_call > 0)
        {
            max_caller_num++;
            //printf("%s-%s\n", caller, key_arr[i]);
            if (strcmp(caller, key_arr[pos]) > 0)
                caller = key_arr[pos];
        }
        if (value_arr[pos] > max_call)
        {
            max_call = value_arr[pos];
            max_caller_num = 1;
            caller = key_arr[pos];
        }
    }
    if (caller != NULL)
    {
        printf("%s %d", caller, max_call);
        if (max_caller_num > 1)
            printf(" %d", max_caller_num);
    }
}

int main()
{   
    int N;
    scanf("%d", &N);
    read_input(N);
    scanf("%d", &N);
}

Position hash(char *str)
{   // 散列函数
    //int i=0;
    Position head=0, tail;
    for(int i=0; i<7; i++)
        head += (str[i] - 48);
    tail = head * 10000 + atoi(str + 7);
    //printf("%s hash:%d\n", str, head);
    tail %= MAX_SIZE;
    return tail;
}

Position insert(phash ph, KeyType key)
{   // 插入元素
    //printf("insert %s\n", key);
    Position pos = Find(ph, key);
    if (ph->states[pos] != Legitimate)                  // 查找结果为空或已删除 就插入元素 
    {
        ph->states[pos] = Legitimate;
        char *keystr;
        keystr = (char*)malloc(16*sizeof(char));
        strcpy(keystr, key);
        ph->keys[pos] = keystr;
        // printf("insert %s at %d\n", key, pos);
    }
    ph->values[pos]++;                                  // 递增计数
    //printf("insert %s at %d times %d\n", key, pos, ph->values[pos]);
    return pos;
}

Position Position_Iteration(Position default_pos, int i)
{   // 平方探测法 位置迭代
    Position pos;
    if (i % 2 == 0)
        pos = default_pos + (i / 2) * (i / 2);
    else
        pos = default_pos - (i / 2) * (i / 2);
    pos %= MAX_SIZE;
    if(pos < 0)
        pos += MAX_SIZE;
    return pos;
}

Position Find(phash ph, KeyType key)
{   // 查找元素 返回元素位置 或者第一个空位/已删除位置
    Position default_pos, pos;
    int i=2;
    default_pos = pos = hash(key);
    while(ph->states[pos] == Legitimate && strcmp(ph->keys[pos], key)!=0)
    {
        pos = Position_Iteration(default_pos, i);
        i++;
    }
    //printf("find %s at %d\n", key, pos);
    return pos;
}
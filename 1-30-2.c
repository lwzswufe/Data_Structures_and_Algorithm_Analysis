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
#define MAX_SIZE 9997
#define true 1
#define false 0
typedef int ValueType;
typedef char* KeyType;
typedef int Position;
typedef enum EntryType{Legitimate, Empty, Deleted} EntryType;
struct ENode
{
    ValueType value;
    KeyType key;
    struct ENode* next;
};
typedef struct ENode* pnode;
struct HashTable
{   
    int N;
    pnode* nodeArr;
};
typedef struct HashTable *phash;
Position hash(char *str);
pnode insert(phash ph, KeyType key);
pnode Find(phash ph, KeyType key);

void read_input(int N)
{   
    phash ph;
    pnode *node_arr, new_node, pn, max_node=NULL;

    ph = (phash)malloc(sizeof(struct HashTable));
    node_arr = (pnode*)malloc(MAX_SIZE * sizeof(pnode));

    ph->nodeArr = node_arr;
    ph->N = N;

    for(int i=0; i<MAX_SIZE; i++)
    {   
        new_node = (pnode)malloc(sizeof(struct ENode));
        new_node->value = 0;
        new_node->key = NULL;
        new_node->next = NULL;
        node_arr[i] = new_node;
    }

    char str[14];
    int max_call=0, max_caller_num=0;
    for(int i=0; i<N*2; i++)
    {
        scanf("%s", str);
        pn = insert(ph, str); 
        if (pn->value == max_call)
        {
            max_caller_num++;
            if (strcmp(pn->key, max_node->key) < 0)
                max_node = pn;
        }
        if (pn->value > max_call)
        {
            max_call = pn->value;
            max_node = pn;
            max_caller_num = 1;
        }
    }
    if (max_node != NULL)
    {
        printf("%s %d", max_node->key, max_call);
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

pnode insert(phash ph, KeyType key)
{   // 插入元素
    //printf("insert %s\n", key);
    pnode pn = Find(ph, key);
    pn->value++;                               // 递增计数
    //printf("insert %s at %d times %d\n", key, pos, ph->values[pos]);
    return pn;
}

pnode Find(phash ph, KeyType key)
{   // 查找元素 返回元素位置 或者第一个空位/已删除位置
    Position pos;
    pnode pn, new_node, tmp_node;
    //int cond;
    pos = hash(key);
    pn = ph->nodeArr[pos];
    // printf("insert %s at %d\n", key, pos);

    while (pn->next != NULL && strcmp(pn->next->key, key) > 0)
    {   
        pn = pn->next;
    }
    if (pn->next != NULL && strcmp(pn->next->key, key) == 0)
        return pn->next;

    new_node = (pnode)malloc(sizeof(struct ENode));
    char *keystr;
    keystr = (char*)malloc(16*sizeof(char));
    strcpy(keystr, key);

    new_node->value = 0;
    new_node->key = keystr;

    tmp_node = pn->next;
    pn->next = new_node;
    new_node->next = tmp_node;
    return new_node;
}
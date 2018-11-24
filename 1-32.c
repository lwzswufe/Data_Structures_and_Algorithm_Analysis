/*
11-散列3 QQ帐户的申请与登陆 （25 分）
实现QQ新帐户申请和老帐户登陆的简化版功能。最大挑战是：据说现在的QQ号码已经有10位数了。

输入格式:
输入首先给出一个正整数N（≤10
​5
​​ ），随后给出N行指令。每行指令的格式为：“命令符（空格）QQ号码（空格）密码”。其中命令符
为“N”（代表New）时表示要新申请一个QQ号，后面是新帐户的号码和密码；命令符为“L”（代表
Login）时表示是老帐户登陆，后面是登陆信息。QQ号码为一个不超过10位、但大于1000（据说
QQ老总的号码是1001）的整数。密码为不小于6位、不超过16位、且不包含空格的字符串。

输出格式:
针对每条指令，给出相应的信息：

1）若新申请帐户成功，则输出“New: OK”；
2）若新申请的号码已经存在，则输出“ERROR: Exist”；
3）若老帐户登陆成功，则输出“Login: OK”；
4）若老帐户QQ号码不存在，则输出“ERROR: Not Exist”；
5）若老帐户密码错误，则输出“ERROR: Wrong PW”。

输入样例:
5
L 1234567890 myQQ@qq.com
N 1234567890 myQQ@qq.com
N 1234567890 myQQ@qq.com
L 1234567890 myQQ@qq
L 1234567890 myQQ@qq.com
输出样例:
ERROR: Not Exist
New: OK
ERROR: Exist
ERROR: Wrong PW
Login: OK
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char* ValueType;
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
void insert(phash ph, KeyType key, ValueType value);
void check(phash ph, KeyType key, ValueType value);
Position hash(KeyType key);
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

    // Position pos;
    char password[17];
    char c;
    for(int i=0; i<N; i++)
    {   
        scanf("%c", &c);
        scanf("%c", &c);
        scanf("%d", &key);
        scanf("%s", password);
        //printf("type:%c QQ:%d pwd:%s\n", c, key, password);
        if (c == 'N')
        {
            insert(ph, key, password);
            continue;
        }
        if (c == 'L')
            check(ph, key, password);
        else
            printf("error type:%c QQ:%d pwd:%s\n", c, key, password);
    }
}

int main()
{   
    int N;
    scanf("%d", &N);
    TABLESIZE = NextPrime(N);
    // printf("tablesize:%d\n", TABLESIZE);
    read_input(N);
    scanf("%d", &N);
}

Position hash(KeyType key)
{   // 散列函数
    return key % TABLESIZE;
}

void check(phash ph, KeyType key, ValueType value)
{   // 检查密码
    Position pos = Find(ph, key);
    if (pos < 0 || ph->states[pos] != Legitimate)
    {
        printf("ERROR: Not Exist\n");
        return;
    }
    if (strcmp(ph->values[pos], value) == 0)
        printf("Login: OK\n");
    else
        printf("ERROR: Wrong PW\n");
}

void insert(phash ph, KeyType key, ValueType value)
{   // 插入元素
    //printf("insert %s\n", key);
    Position pos = Find(ph, key);
    if (ph->states[pos] != Legitimate)                  // 查找结果为空或已删除 就插入元素 
    {   
        ValueType pwd;
        pwd = (ValueType)malloc(17 * sizeof(char));
        pwd = strcpy(pwd, value);

        ph->states[pos] = Legitimate;
        ph->keys[pos] = key;
        ph->values[pos] = pwd;
        // printf("insert %s at %d\n", key, pos);
        printf("New: OK\n");
    }
    else
        printf("ERROR: Exist\n");
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
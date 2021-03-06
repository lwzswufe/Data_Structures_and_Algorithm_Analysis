/*
05-树9 Huffman Codes （30 分）
In 1953, David A. Huffman published his paper "A Method for the Construction 
of Minimum-Redundancy Codes", and hence printed his name in the history of 
computer science. As a professor who gives the final exam problem on Huffman 
codes, I am encountering a big problem: the Huffman codes are NOT unique. 
For example, given a string "aaaxuaxz", we can observe that the frequencies 
of the characters 'a', 'x', 'u' and 'z' are 4, 2, 1 and 1, respectively. We 
may either encode the symbols as {'a'=0, 'x'=10, 'u'=110, 'z'=111}, or in 
another way as {'a'=1, 'x'=01, 'u'=001, 'z'=000}, both compress the string 
into 14 bits. Another set of code can be given as {'a'=0, 'x'=11, 'u'=100, 
'z'=101}, but {'a'=0, 'x'=01, 'u'=011, 'z'=001} is NOT correct since "aaaxuaxz" 
and "aazuaxax" can both be decoded from the code 00001011001001. The students 
are submitting all kinds of codes, and I need a computer program to help me 
determine which ones are correct and which ones are not.

Input Specification:
Each input file contains one test case. For each case, the first line gives an 
integer N (2≤N≤63), then followed by a line that contains all the N distinct 
characters and their frequencies in the following format:

c[1] f[1] c[2] f[2] ... c[N] f[N]
where c[i] is a character chosen from {'0' - '9', 'a' - 'z', 'A' - 'Z', '_'}, 
and f[i] is the frequency of c[i] and is an integer no more than 1000. The next 
line gives a positive integer M (≤1000), then followed by M student submissions. 
Each student submission consists of N lines, each in the format:

c[i] code[i]
where c[i] is the i-th character and code[i] is an non-empty string of no more 
than 63 '0's and '1's.

Output Specification:
For each test case, print in each line either "Yes" if the student's submission 
is correct, or "No" if not.

Note: The optimal solution is not necessarily generated by Huffman algorithm. 
Any prefix code with code length being optimal is considered correct.

Sample Input:
7
A 1 B 1 C 1 D 3 E 3 F 6 G 6
4
A 00000
B 00001
C 0001
D 001
E 01
F 10
G 11
A 01010
B 01011
C 0100
D 011
E 10
F 11
G 00
A 000
B 001
C 010
D 011
E 100
F 101
G 110
A 00000
B 00001
C 0001
D 001
E 00
F 10
G 11
Sample Output:
Yes
Yes
No
No
作者: 陈越
单位: 浙江大学
时间限制: 400 ms
内存限制: 64 MB
代码长度限制: 16 KB

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  MIN_INT 0x80000000
struct Heap                 // 最小堆
{
    int *data;
    char *strs;
    int *codearr;
    int size;
    int capacity;
};
typedef struct Heap *pheap;
struct HuffmanTree          // 霍夫曼树
{
    int* father;
    int* weight; 
    char* strs;
    int size;
};
typedef struct HuffmanTree *ptree;

pheap read_heap();
void insert(pheap ph, char c, int n, int pos);
int delete_(pheap ph);
ptree build_tree(pheap);
ptree create_tree(int N);
ptree create(char, int);
int stat(ptree root);
void read_input(ptree root, int, int);
int check_string(int N, char codes_arr[][64]);

int main()
{   
    pheap ph;
    ptree pt;
    int sum_weight, N;
    ph = read_heap();
    N = ph->size;
    pt = build_tree(ph);
    sum_weight = stat(pt);
    read_input(pt, N, sum_weight);
    int x;
    scanf("%d", &x);
    scanf("%d", &x);
    scanf("%d", &x);
    return 0;
}


int check_string(int N, char codes_arr[N][64])
{   // 检验一个编码是否是另一个编码的前缀
    int len[N];
    for(int i=0; i<N; i++)
    {   
        len[i] = strlen(codes_arr[i]);
    }
    for(int i=0; i<N; i++)
    {   
        for(int j=0; j<N; j++)
        {   
            if (i!=j && len[i] <= len[j] && strncmp(codes_arr[i], codes_arr[j], len[i]) == 0)
            {   
                // printf("%s equal %s\n", codes_arr[i], codes_arr[j]);
                return 1;
            }
        }
    }
    return 0;
}

int find(ptree root, char c, int N)
{   // 查找编码的索引
    for(int i=0; i<N; i++)
    {
        if(root->strs[i + 1] == c)
            return i;
    }
    return -1;
}

void read_input(ptree root, int N, int sum_weight)
{   // 读取需要对比的编码
    int K, len[N], sum, idx, count_arr[N];
    scanf("%d", &K);
    char c, codes_arr[N][64];
    for (int i=0; i<K; i++)
    {   
        for(int j=0; j<N; j++)
        {   
            count_arr[j] = 0;
        }
        sum = 0;
        for(int j=0; j<N; j++)
        {
            scanf("\n%c", &c);
            idx = find(root, c, N);
            if (idx < 0)
            {
                sum += 1000;
                continue;
            }
            if (count_arr[idx] > 0)                 // 防止一个点出现两次
                sum += 10000;
            scanf("%s", codes_arr[idx]);
            count_arr[idx]++;
            //printf("read: %s\n", codes_arr[j]);
            len[idx] = strlen(codes_arr[idx]);
            sum += len[idx] * root->weight[idx+1];
            //printf("sum: %d, %d\n", sum, sum_weight);
        }
        //printf("sum: %d, %d\n", sum, sum_weight);
        if (sum != sum_weight || check_string(N, codes_arr))
            printf("No\n");
        else
            printf("Yes\n");
    }
}

void insert(pheap ph, char c, int n, int code)
{   //最小堆插入
    char tmpc;
    int tmpn, tmpf, pos;
    ph->size++;
    pos = ph->size;
    ph->data[pos] = n;
    ph->strs[pos] = c;
    ph->codearr[pos] = code;
    //printf("insert: pos:%d:%c weight:%d\n", code, c, n);
    while(ph->data[pos] < ph->data[pos/2])
    {
        tmpn = ph->data[pos/2];
        tmpc = ph->strs[pos/2];
        tmpf = ph->codearr[pos/2];
        ph->data[pos/2] = ph->data[pos];
        ph->strs[pos/2] = ph->strs[pos];
        ph->codearr[pos/2] = ph->codearr[pos];
        ph->data[pos] = tmpn;
        ph->strs[pos] = tmpc;
        ph->codearr[pos] = tmpf;
        pos /= 2;
    }
}

int delete_(pheap ph)
{   //最小堆删除程序
    char tmpc;
    int tmpn, pos, N, tmpf, code;
    N = ph->size;
    if (N<1)
        return -1;
    code = ph->codearr[1];
    //printf("delete_: pos:%d:%c weight:%d\n", code, ph->strs[1], ph->data[1]);
    ph->data[1] = ph->data[N];
    ph->strs[1] = ph->strs[N];
    ph->codearr[1] = ph->codearr[N];
    ph->size--;
    N--;
    pos = 1;
    while(pos * 2 <= N)
    {   
        pos *= 2;
        if(pos + 1<=N && ph->data[pos] > ph->data[pos+1])
            pos++;
        if(ph->data[pos/2] <= ph->data[pos])
            break;
        tmpn = ph->data[pos/2];
        tmpc = ph->strs[pos/2];
        tmpf = ph->codearr[pos/2];
        ph->data[pos/2] = ph->data[pos];
        ph->strs[pos/2] = ph->strs[pos];
        ph->codearr[pos/2] = ph->codearr[pos];
        ph->data[pos] = tmpn;
        ph->strs[pos] = tmpc;
        ph->codearr[pos] = tmpf;
    }
    return code;
}


pheap read_heap()
{   // 读取字符及其出现频率 构建最小堆
    int N, *arr, n, *codearr;
    char *char_arr, c;
    scanf("%d", &N);
    pheap ph;
    
    arr = (int*)malloc((N+1)*sizeof(int));
    codearr = (int*)malloc((N+1)*sizeof(int));
    char_arr = (char*)malloc((N+2)*sizeof(char));
    arr[0] = MIN_INT;
    char_arr[0] = '>';
    char_arr[N+1] = 0;
    
    ph = (pheap)malloc(sizeof(struct Heap));
    ph->data = arr;
    ph->strs = char_arr;
    ph->codearr = codearr;
    ph->size = 0;
    ph->capacity = N;
    
    for(int i=1; i<=N; i++)
    {
        scanf("%*c%c%*c%d", &c, &n);
        insert(ph, c, n, i);
    }
    // for(int i=1; i<=N; i++)
    // {   
    //     printf("%c:%d\n", ph->strs[i], ph->data[i]);
    // }
    // printf("%s\n", char_arr);
    return ph;
}

ptree create_tree(int N)
{   // 创建霍夫曼编码树
    int *father, *weight;
    char * strs;
    father = (int*)malloc((N*2)*sizeof(int));
    weight = (int*)malloc((N*2)*sizeof(int));
    strs = (char*)malloc((N*2)*sizeof(char));
    ptree pt;
    pt = (ptree)malloc(sizeof(struct HuffmanTree));
    pt->father = father;
    pt->weight = weight;
    pt->strs = strs;
    pt->size = N; 
    return pt;
}

int add_node(ptree pt, int pos1, int pos2)
{   // 在霍夫曼编码树上增加节点
    pt->size++;
    pt->strs[pt->size] = '+';
    pt->weight[pt->size] = pt->weight[pos1] + pt->weight[pos2];
    pt->father[pt->size] = 0;
    pt->father[pos1] = pt->father[pos2] = pt->size;
    return pt->size;
}


ptree build_tree(pheap ph)
{   // 创建霍夫曼编码树
    int N, pos1, pos2, pos;
    ptree root;
    root = create_tree(ph->size);
    N = ph->size;
    for(int i=1; i<=N; i++)
    {   
        pos = ph->codearr[i];
        root->strs[pos] = ph->strs[i];
        root->weight[pos] = ph->data[i];
        root->father[pos] = 0;
        //printf("pos:%d weight:%d code:%d\n", i, ph->data[i], ph->codearr[i]);
    }
    while(ph->size > 1)
    {   
        pos1 = delete_(ph);
        pos2 = delete_(ph);
        //printf("pos1:%d weight:%d pos2:%d weight:%d\n", pos1, root->weight[pos1], pos2, root->weight[pos2]);
        pos = add_node(root, pos1, pos2);
        insert(ph, '+', root->weight[pos], pos);
    }
    // printf("build tree over\n");
    return root;
}


int stat(ptree root)
{   // 计算整棵树的权值
    int sum=0, pos, deep;
    for(int i=1; i<=root->size; i++)
    {
        //printf("%d:%c weight:%d father:%d\n", i, root->strs[i], root->weight[i], root->father[i]);
        pos = i;
        deep = 0;
        while(root->father[pos] != 0)
        {
            pos = root->father[pos];
            deep++;
        }
        if (root->strs[i] != '+')
            sum += deep * root->weight[i];
        //printf("sum: %d\n", sum);
    }
    return sum;
}

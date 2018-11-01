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

void read_input(ptree root, int N, int sum_weight)
{
    int K, len[N], sum;
    scanf("%d", &K);
    char c, codes_arr[N][64];
    for (int i=0; i<K; i++)
    {   
        sum = 0;
        for(int j=0; j<N; j++)
        {
            scanf("\n%c", &c);
            scanf("%s", codes_arr[j]);
            //printf("read: %s\n", codes_arr[j]);
            len[j] = strlen(codes_arr[j]);
            sum += len[j] * root->weight[j+1];
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
{   
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
{   
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
{
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
{   
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
{   
    pt->size++;
    pt->strs[pt->size] = '+';
    pt->weight[pt->size] = pt->weight[pos1] + pt->weight[pos2];
    pt->father[pt->size] = 0;
    pt->father[pos1] = pt->father[pos2] = pt->size;
    return pt->size;
}


ptree build_tree(pheap ph)
{
    int N, pos1, pos2, pos;
    ptree root;
    root = create_tree(ph->size);
    N = ph->size;
    for(int i=1; i<=N; i++)
    {
        root->strs[i] = ph->strs[i];
        root->weight[i] = ph->data[i];
        root->father[i] = 0;
    }
    while(ph->size > 1)
    {   
        pos1 = delete_(ph);
        pos2 = delete_(ph);
        pos = add_node(root, pos1, pos2);
        insert(ph, '+', root->weight[pos], pos);
    }
    // printf("build tree over\n");
    return root;
}


int stat(ptree root)
{   
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

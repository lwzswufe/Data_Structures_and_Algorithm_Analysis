/*
05-树8 File Transfer （25 分）
We have a network of computers and a list of bi-directional connections. 
Each of these connections allows a file transfer from one computer to 
another. Is it possible to send a file from any computer on the network 
to any other?

Input Specification:
Each input file contains one test case. For each test case, the first 
line contains N (2≤N≤10^4), the total number of computers in a network. 
Each computer in the network is then represented by a positive integer 
between 1 and N. Then in the following lines, the input is given in the 
format:

I c1 c2  
where I stands for inputting a connection between c1 and c2; or

C c1 c2    
where C stands for checking if it is possible to transfer files between 
c1 and c2; or

S
where S stands for stopping this case.

Output Specification:
For each C case, print in one line the word "yes" or "no" if it is possible 
or impossible to transfer files between c1 and c2, respectively. At the end 
of each case, print in one line "The network is connected." if there is a path 
between any pair of computers; or "There are k components." where k is the 
number of connected components in this network.

Sample Input 1:
5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
S
Sample Output 1:
no
no
yes
There are 2 components.
Sample Input 2:
5
C 3 2
I 3 2
C 1 5
I 4 5
I 2 4
C 3 5
I 1 3
C 1 5
S
Sample Output 2:
no
no
yes
yes
The network is connected.
*/

#include <stdio.h>
#include <stdlib.h>
#define  MIN_INT 0x80000000
struct Set
{
    int *data;
    int size;
};
typedef struct Set *pset;

pset read_input();
pset create(int);
int get_set(pset, int);
int check_connect(pset, int, int);
void insert(pset, int, int);
void count_set(pset);

int main()
{   
    pset ps;
    ps = read_input();
    count_set(ps);
    //int x;
    //scanf("%d", &x);
    return 0;
}

pset create(int N)
{   // 创建集合
    int *arr;
    arr = (int*)malloc((N+1)*sizeof(int));
    //arr = (int *)calloc((N+1)*sizeof(int));
    for(int i=0; i<=N; i++)
        arr[i] = 0;
    pset ps;
    ps = (pset)malloc(sizeof(struct Set));
    ps->data = arr;
    ps->size = N;
    return ps;
}

void count_set(pset ps)
{   // 统计集合数量
    int count = 0;
    for (int i=1;i<=ps->size;i++)
    {   
        if (ps->data[i] <= 0)
            count++;
        //printf("%d->%d, ", i, ps->data[i]);
    }
    //printf("\nconnectnum: %d\n", count);
    if (count == 1)
        printf("The network is connected.\n");
    if (count > 1)
        printf("There are %d components.\n", count);
}

int get_set(pset ps, int pos)
{   // 确定最终父类类别
    if (pos <= 0 || pos > ps->size)
        return 0;
    while (ps->data[pos] > 0)
    {
        pos = ps->data[pos];
    }
    return pos;
}

int check_connect(pset ps, int pos1, int pos2)
{   // 判断两点是否连接
    int set1, set2;
    set1 = get_set(ps, pos1);
    set2 = get_set(ps, pos2);
    if (set1 > 0 && set1 == set2)
        return 1;
    else
        return 0;
}

void insert(pset ps,int pos1, int pos2)
{   // 插入连接
    int set1, set2;
    set1 = get_set(ps, pos1);
    set2 = get_set(ps, pos2);
    if (set1 == set2)                           // 最终节点指向相同
    {   
        if (set1==0)                            // 都指向0 即未初始化  创造集合
        {
            ps->data[pos1] = -1;                // 指向该节点的数量为 1
            ps->data[pos2] = pos1;              // 该节点指向 pos1
        }
        return;
    }
    if (set1 <= set2)                           // 指向set1的点较多
    {   
        if (set2 > 0)                          
        {
            ps->data[set1] += ps->data[set2];   // 合并指向计数
            ps->data[set2] = set1;                     
        }
        ps->data[pos2] = set1;
        ps->data[set1]--;                       // 指向计数 set2
    }
    else
    {   
        if (set1 > 0)
        {
            ps->data[set2] += ps->data[set1];
            ps->data[set1] = set2;
        }
        ps->data[pos1] = set2;
        ps->data[set2]--;
    }
}


pset read_input()
{   
    int N, C1, C2, is_connect;
    char c='\0';
    pset ps;
    scanf("%d", &N);
    ps = create(N);
    scanf("\n%c", &c);
    while(c != 'S')
    {   
        scanf("%d %d", &C1, &C2);
        if (c=='C')
        {
            is_connect = check_connect(ps, C1, C2);
            if (is_connect)
                printf("yes\n");
            else
                printf("no\n");
        }
        else
        {
            insert(ps, C1, C2);
        }
        scanf("\n%c", &c);
    }
    return ps;
}


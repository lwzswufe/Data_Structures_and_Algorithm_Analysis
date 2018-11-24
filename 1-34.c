/*
KMP 串的模式匹配 （25 分）
给定两个由英文字母组成的字符串 String 和 Pattern，要求找到 Pattern 在 String 中第一次出现
的位置，并将此位置后的 String 的子串输出。如果找不到，则输出“Not Found”。

本题旨在测试各种不同的匹配算法在各种数据情况下的表现。各组测试数据特点如下：

数据0：小规模字符串，测试基本正确性；
数据1：随机数据，String 长度为 10^5，Pattern 长度为 10；
数据2：随机数据，String 长度为 10^5，Pattern 长度为 10^2；
数据3：随机数据，String 长度为 10^5，Pattern 长度为 10^3；
数据4：随机数据，String 长度为 10^5，Pattern 长度为 10^4；
数据5：String 长度为 10^6，Pattern 长度为 10^5​ ；测试尾字符不匹配的情形；
数据6：String 长度为 10^6，Pattern 长度为 10^5​ ；测试首字符不匹配的情形。
输入格式:
输入第一行给出 String，为由英文字母组成的、长度不超过 10^6的字符串。第二行给出一个正整数 N（≤10）
，为待匹配的模式串的个数。随后 N 行，每行给出一个 Pattern，为由英文字母组成的、长度不超过 10^5
​​  的字符串。每个字符串都非空，以回车结束。

输出格式:
对每个 Pattern，按照题面要求输出匹配结果。

输入样例:
abcabcabcabcacabxy
3
abcabcacab
cabcabcd
abcabcabcabcacabxyz
输出样例:
abcabcacabxy
Not Found
Not Found
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NotFound -1

typedef int Position;

void BuildMatch(char* pattern, int* match)
{
    int N, pos;
    N = strlen(pattern);
    match[0] = -1;
    for (int i=1; i<N; i++)
    {   
        pos = match[i - 1];                                 // 匹配前一个字母
        while (pos >= 0 && pattern[i] != pattern[pos+1])    // 迭代匹配符合前一个字母要求的的后一个字母的片段
        {   
            pos = match[pos];
        }
        if (pattern[i] == pattern[pos+1])                   // 找到一个匹配
            match[i] = pos + 1;
        else
            match[i] = -1;
    }
}

Position KMP( char *string, char *pattern )
{
    int N, M, *match, s, p;
    N = strlen(string);
    M = strlen(pattern);
    match = (int*)malloc(N * sizeof(int));
    BuildMatch(pattern, match);
    s = p = 0;
    while( s<N && p<M)
    {
        if(string[s] == pattern[p])                         // 找到匹配 
        {
            s++;
            p++;
        }
        else                                                // 未找到匹配
        {
            if (p > 0)                                      // p更新为上一个字串的位置
                p = match[p-1] + 1;
            else                                            // 无上一个字串 s更新
                s++;
        }
    }
    if (p == M)
        return s - M;
    else
        return NotFound;
}


int main()
{   
    int N;
    char string[1000008], pattern[100008];
    Position pos;
    scanf("%s", string);
    scanf("%d", &N);
    for(int i=0; i<N; i++)
    {   
        scanf("%s", pattern);
        pos = KMP(string, pattern);
        if (pos == NotFound)
            printf("Not Found\n");
        else
            printf("%s\n", &string[pos]);
    }
    scanf("%d", &N);
    return 0;
}


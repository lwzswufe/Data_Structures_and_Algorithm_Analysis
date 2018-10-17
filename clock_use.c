#include <stdio.h>
#include <time.h>

clock_t start, stop;
double duration;

void fun_1()
{
    for(int i=0; i<10000000; i++)
        ;
}


int main()
{
    start = clock();
    fun_1();
    stop = clock();
    duration = (double)(stop - start);
    printf("function use %.3lfms", duration);
}
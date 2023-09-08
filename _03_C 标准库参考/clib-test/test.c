#include <stdio.h>
#include <stdbool.h>
#include <stdalign.h>

struct st
{
    alignas(8) char a;  // 地址位 0
    alignas(4) short b; // 地址位 8
    alignas(32) int c;  // 地址位 4
} st;

_Pragma("nonstandardtreatmenttypeB on");

int Add(int, int);

int Add(int a, int b)
{
    return a + b;
}

typedef int (*pFun)(int, int);

int main()
{
    pFun pf = *&*&*&*&*&*&Add;

    pFun *p = &pf;
    pFun **pp = &p;
    printf("%p\n", &"hello");
    printf("%p   %d\n", pp, (**Add)(1,1));
    printf("%p\n%p\n%p\n%p\n%p\n%p\n%p", Add, pf, (*pf), **pf, ***pf, ****pf, *****Add);
}
/*
000000000061FE10
000000000061FE08   2
0000000000401550
0000000000401550
0000000000401550
0000000000401550
0000000000401550
0000000000401550
0000000000401550
*/
#include <stdio.h>
#include <complex.h>

int b;

[[noreturn]] int foo(int len)
{
    typedef int arr[len];
 
    arr a;
    for (size_t i = 0; i < len; i++)
    {
        a[i] = i;
    }
    return a[len - 1];
}


auto p = &b;
    
int main()
{
    b = 100;
    printf("%d", *p);
    return *p;
}
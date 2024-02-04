#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include <stdbool.h>
#include <tchar.h>
#include <stdatomic.h>

size_t vla_size(int n)
{
    typedef char vla_type[n + 3];
    vla_type b; // variable length array
    return sizeof(
        typeof(b)); // execution-time sizeof, translation-time typeof operation
}

int main()
{
    int *restrict p1;
    int *restrict q1;
    p1 = q1; // undefined behavior0
    {
        int *restrict p2 = p1; // valid
        int *restrict q2 = q1; // valid
        p1 = q2;               // undefined behavior
        p2 = q2;               // undefined behavior
    }
}
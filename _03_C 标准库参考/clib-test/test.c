#include <stdio.h>
#include <stdbool.h>

#pragma pack(1)

typedef struct _st_struct2
{
    char a;  // 地址位 0
    int c;   // 地址位 4
    short b; // 地址位 8
} st_struct2;

typedef struct
{
    bool a : 1;
    bool b : 1;
    bool c : 1;

} BitState;

typedef union 
{
    int a;
    float af;
} u;


int main()
{
    st_struct2 st = {1, 4, 2};
    BitState *bs = &(BitState){10001,1,1};

    u uu = {.af = 1.0001f};

    printf("%.1f , %d\n", uu.af,uu.a);

    printf("%d, %d, %d, SIZE = %d\n", bs->a, bs->b, bs->c, sizeof(bs));

    printf("SIZE = %d\n" // 4
           "Pa = %p\n"   //
           "Pb = %p\n"
           "Pc = %p",
           sizeof(st), &st.a, &st.b, &st.c);
}
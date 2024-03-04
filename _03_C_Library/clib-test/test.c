#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <fenv.h>
#define __STDC_WANT_IEC_60559_TYPES_EXT__

#include <float.h>

typedef int (*pCtypeFun)(int);
void Test_CtypeFun(pCtypeFun, const char *);
void Test_CtypeFun(pCtypeFun pFun, const char *name)
{

    __DEC128_MANT_DIG__
    printf("Test Function [%s] : \n", name);
    int index = 0;
    while (index < 128) // ASCII 0~127
    {
        if (pFun((char)index))
        {
            printf("    [%03d]", index);
            if (isgraph(index))
                printf("%c,\n", index);
            else
                printf("%#.3x,\n", index);
        }
        index++;
    }
    printf("\n");
    
}
//--------------------------------------------------------
int main()
{
    Test_CtypeFun(isblank, "isblank");
}
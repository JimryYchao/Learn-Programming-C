#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef int (*pCtypeFun)(int);
static int isXxx(pCtypeFun pFun, const char *name)
{
    printf("Test Function [%s] : \n", name);
    int index = 0;
    int n = 0;
    while (index < 128) // ASCII 0~127
    {
        if (pFun((char)index))
        {
            n++;
            printf(" [%03d]", index);
            if (isgraph(index))
                printf("%c,", index);
            else
                printf("%#.3x,", index);
            if (n>10){
                printf("\n");
                n = 0;
            }
        }
        index++;
    }
    return printf("\n");
}

#define content "The Quick Brown Fox Jumps Over a Lazy Dog."
typedef int (*Fn)(int);
static void to(const char *cond, Fn fn)
{
    size_t len = strlen(content);
    size_t index = 0;
    char _S[] = content;
    while (index < len)
    {
        _S[index] = (char)fn(_S[index]);
        index++;
    }
    printf("%s : %s\n", cond, _S);
}
static int toXxx()
{
    printf("String  : %s\n", content);
    to("lower", tolower);
    to("upper", toupper);
    return 0;
}

int testCtype(int n)
{
    // isXxx(FuncName, "FuncName");
    pCtypeFun fn;
    switch (n)
    {
    case 0:
        return toXxx();
    case 1:
        return isXxx(isalnum, "isalnum");
    case 2:
        return isXxx(isalpha, "isalpha");
    case 3:
        return isXxx(isblank, "isblank");
    case 4:
        return isXxx(iscntrl, "iscntrl");
    case 5:
        return isXxx(isdigit, "isdigit");
    case 6:
        return isXxx(isgraph, "isgraph");
    case 7:
        return isXxx(islower, "islower");
    case 8:
        return isXxx(isprint, "isprint");
    case 9:
        return isXxx(ispunct, "ispunct");
    case 10:
        return isXxx(isspace, "isspace");
    case 11:
        return isXxx(isupper, "isupper");
    case 12:
        return isXxx(isxdigit, "isxdigit");
    }
}

int main()
{
    // 0 ToXxx
    // 1~12 IsXxx
    testCtype(1);
}
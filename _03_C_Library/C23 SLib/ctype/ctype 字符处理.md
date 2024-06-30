## C 字符处理：ctype.h


`ctype.h` 声明了一些用于分类和映射字符的函数。在所有的情况下，所有的参数都是一个 `int`。这些函数的行为受当前区域设置的影响。

>---
### 字符分类函数

当且仅当这些函数的参数 `c` 的值与对应函数描述中的值一致时，对应函数返回非零（`true`）。


| Specifier  | Description                        | Range ("C" 设置下)                            |
| :--------- | :--------------------------------- | :-------------------------------------------- |
| `isalnum`  | 测试（特定区域的）数字或字母字符。 | [A-Za-z0-9]                                   |
| `isalpha`  | 测试（特定区域的）字母字符。       | [A-Za-z]                                      |
| `isblank`  | 测试（特定区域的）空白字符。       | `' '` 或 `\u020`                              |
| `iscntrl`  | 测试任何的控制字符。               |
| `isdigit`  | 测试任何的十进制数字字符。         | [0-9]                                         |
| `isgraph`  | 测试除空白之外的任何可打印字符。   |
| `islower`  | 测试（特定区域的）小写字母字符。   | [a-z]                                         |
| `isprint`  | 测试任何的可打印字符。             |
| `ispunct`  | 测试（特定区域的）标点符号。       |
| `isspace`  | 测试任何标准空白字符。             | `' '`、`'\t'`、`'\n'`、`'\v'`、`'\f'`、`'\r'` |
| `isupper`  | 测试（特定区域的）大写字母字符。   | [A-Z]                                         |
| `isxdigit` | 测试任何的十六进制数字字符。       | [0-9A-Fa-f]                                   |


```c
#include <ctype.h>
#include <stdio.h>
typedef int (*pCtypeFun)(int);
void Test_CtypeFun(pCtypeFun pFun, const char *name)
{
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
int main()
{
    // Test_CtypeFun(FuncName, "FuncName");
    Test_CtypeFun(isalnum, "isalnum");
}
/*
Test Function [isalnum] : 
[048]0, [049]1, [050]2, [051]3, [052]4, [053]5, [054]6, [055]7, [056]8, [057]9,

[065]A, [066]B, [067]C, [068]D, [069]E, [070]F, [071]G, [072]H, [073]I, [074]J,
[075]K, [076]L, [077]M, [078]N, [079]O, [080]P, [081]Q, [082]R, [083]S, [084]T,
[085]U, [086]V, [087]W, [088]X, [089]Y, [090]Z, 

[097]a, [098]b, [099]c, [100]d, [101]e, [102]f, [103]g, [104]h, [105]i, [106]j,
[107]k, [108]l, [109]m, [110]n, [111]o, [112]p, [113]q, [114]r, [115]s, [116]t,
[117]u, [118]v, [119]w, [120]x, [121]y, [122]z, 
*/
```

>---
### 字符映射函数

| Specifier | Description                    | Range ("C" 设置下) |
| :-------- | :----------------------------- | :----------------- |
| `tolower` | 转换为（特定区域的）小写字符。 | [A-Z] to [a-z]     |
| `toupper` | 转换为（特定区域的）大写字符。 | [a-z] to [A-Z]     |


```c
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define content "The Quick Brown Fox Jumps Over a Lazy Dog."

typedef int (*Fn)(int);
void To(const char *cond, Fn fn)
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
int main()
{
    printf("String  : %s\n", content);
    To("lower", tolower);
    To("upper", toupper);
}
/*
    String  : The Quick Brown Fox Jumps Over a Lazy Dog.
    lower : the quick brown fox jumps over a lazy dog.
    upper : THE QUICK BROWN FOX JUMPS OVER A LAZY DOG.
*/
```

---
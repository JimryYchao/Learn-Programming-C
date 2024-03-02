## C 字符处理（Character handling）：ctype.h

字符处理库，声明了一些用于对字符进行分类和映射的函数。这些函数的行为受当前语言环境的影响。

---
### 字符分类函数（Character classification functions）

#### isalnum （检查字符是否是字母或数字）

```c
int isalnum(int c);
```

`isalnum` 函数测试字符是否为数字或字母（`isalpha` 和 `isdigit` 为真的任何字符，[A-Za-z0-9]）。

```c
#include <ctype.h>
typedef int (*pCtypeFun)(int);
void Test_CtypeFun(pCtypeFun, const char *);
void Test_CtypeFun(pCtypeFun pFun, const char *name)
{
    printf("Test Function [%s] : ", name);
    int index = 0;
    while (index < 128) // ASCII 0~127
    {
        if (pFun((char)index))
        {
            printf("[%03d]", index);
            if (isgraph(index))
                printf("%c,", index);
            else
                printf("%#.3x,", index);
        }
        index++;
    }
    printf("\n");
}
//--------------------------------------------------------
int main()
{
    Test_CtypeFun(isalnum, "isalnum");
}
/*
Test Function [isalnum] : 
[048]0,[049]1,[050]2,[051]3,[052]4,[053]5,[054]6,[055]7,[056]8,[057]9,

[065]A,[066]B,[067]C,[068]D,[069]E,[070]F,[071]G,[072]H,[073]I,[074]J,
[075]K,[076]L,[077]M,[078]N,[079]O,[080]P,[081]Q,[082]R,[083]S,[084]T,
[085]U,[086]V,[087]W,[088]X,[089]Y,[090]Z,

[097]a,[098]b,[099]c,[100]d,[101]e,[102]f,[103]g,[104]h,[105]i,[106]j,
[107]k,[108]l,[109]m,[110]n,[111]o,[112]p,[113]q,[114]r,[115]s,[116]t,
[117]u,[118]v,[119]w,[120]x,[121]y,[122]z,
*/
```

<br>

#### isalpha （检查字符是否是英文字母）

```c
int isalpha(int c)
```

`isalpha` 函数测试 `isupper` 或 `islower` 为真的任何字符，或者是特定于语言环境的一组字母字符中的任何字符，其中 `iscntrl`、`isdigit`、`ispunct` 或 `isspace`都不为真。

在 “C” 语言环境中，`isalpha`仅对 `isupper` 或 `islower` 为真的字符返回真，[A-Za-z]）。



```c
int main()
{
    Test_CtypeFun(isalpha, "isalpha");
}
/*
Test Function [isalpha] : 
[065]A,[066]B,[067]C,[068]D,[069]E,[070]F,[071]G,[072]H,[073]I,[074]J,
[075]K,[076]L,[077]M,[078]N,[079]O,[080]P,[081]Q,[082]R,[083]S,[084]T,
[085]U,[086]V,[087]W,[088]X,[089]Y,[090]Z,

[097]a,[098]b,[099]c,[100]d,[101]e,[102]f,[103]g,[104]h,[105]i,[106]j,
[107]k,[108]l,[109]m,[110]n,[111]o,[112]p,[113]q,[114]r,[115]s,[116]t,
[117]u,[118]v,[119]w,[120]x,[121]y,[122]z,
*/
```

<br>

#### isblank （检查字符是否是空白字符）

```c
int isblank(int c);
```

`isblank` 函数测试标准空白字符（`' '`）、（`\t`）或 `isspace`为 `true` 的特定于本地的一组字符中的任何字符，该字符用于分隔文本行的单词。

标准的空白字符：空格（`' '`）、水平制表符（`'\t'`）、换行符（`'\n'`）、垂直制表符（`'\v'`）、换页符（`'\f'`）、回车符（`'\r'`）。在 "C" 语言环境中，`isblank` 仅对标准空白字符返回 `true`。

```c
int main()
{
    Test_CtypeFun(isblank, "isblank");
}
/*
Test Function [isblank] : 
[009]0x009,[032]0x020,
*/
```

<br>

#### iscntrl （检查字符是否是控制字符）

```c
int iscntrl(int c);
```

`iscntrl` 测试任何控制字符。

```c
int main()
{
    Test_CtypeFun(iscntrl, "iscntrl");
}
/*
Test Function [iscntrl] : 
[000]000,  [001]0x001,[002]0x002,[003]0x003,[004]0x004,[005]0x005,[006]0x006,
[007]0x007,[008]0x008,[009]0x009,[010]0x00a,[011]0x00b,[012]0x00c,[013]0x00d,
[014]0x00e,[015]0x00f,[016]0x010,[017]0x011,[018]0x012,[019]0x013,[020]0x014,
[021]0x015,[022]0x016,[023]0x017,[024]0x018,[025]0x019,[026]0x01a,[027]0x01b,
[028]0x01c,[029]0x01d,[030]0x01e,[031]0x01f,[127]0x07f,
*/
```

<br>

#### isdigit （检查字符是否为数字）

```c
int isdigit(int c);
```

`isdigit` 测试任何十进制数字字符。

```c
int main()
{
    Test_CtypeFun(isdigit, "isdigit");
}
/*
Test Function [isdigit] : 
[048]0,[049]1,[050]2,[051]3,[052]4,[053]5,[054]6,[055]7,[056]8,[057]9,
*/
```

<br>

#### isgraph （检查字符是否是可显示的字符）

```c
int isgraph(int c);
```

`isgraph` 函数测试除空格以外的任何打印字符。

```c
int main()
{
    Test_CtypeFun(isgraph, "isgraph");
}
/*
Test Function [isgraph] : 
[033]!,[034]",[035]#,[036]$,[037]%,[038]&,[039]',[040](,[041]),[042]*,[043]+,
[044],,[045]-,[046].,[047]/,

[048]0,[049]1,[050]2,[051]3,[052]4,[053]5,[054]6,[055]7,[056]8,[057]9,

[058]:,[059];,[060]<,[061]=,[062]>,[063]?,[064]@,

[065]A,[066]B,[067]C,[068]D,[069]E,[070]F,[071]G,[072]H,[073]I,[074]J,[075]K,
[076]L,[077]M,[078]N,[079]O,[080]P,[081]Q,[082]R,[083]S,[084]T,[085]U,[086]V,
[087]W,[088]X,[089]Y,[090]Z,

[091][,[092]\,[093]],[094]^,[095]_,[096]`,

[097]a,[098]b,[099]c,[100]d,[101]e,[102]f,[103]g,[104]h,[105]i,[106]j,[107]k,
[108]l,[109]m,[110]n,[111]o,[112]p,[113]q,[114]r,[115]s,[116]t,[117]u,[118]v,
[119]w,[120]x,[121]y,[122]z,

[123]{,[124]|,[125]},[126]~,
*/
```

<br>

#### islower （检查字符是否是小写字母）

```c
int islower(int c);
```

`islower` 函数测试小写字母或特定于语言环境的一组字符中的任何字符，其中 `iscntrl`、`isdigit`、`ispunct` 或 `isspace` 都不为真。在 "C" 语言环境中，`islower` 仅对小写字母返回 `true`。

```c
int main()
{
    Test_CtypeFun(islower, "islower");
}
/*
Test Function [islower] : 
[097]a,[098]b,[099]c,[100]d,[101]e,[102]f,[103]g,[104]h,[105]i,[106]j,[107]k,
[108]l,[109]m,[110]n,[111]o,[112]p,[113]q,[114]r,[115]s,[116]t,[117]u,[118]v,
[119]w,[120]x,[121]y,[122]z,
*/
```

<br>

#### isprint （检查字符是否可打印）

```c
int isprint(int c);
```

`isprint` 函数测试除空格以外的任何打印字符。

```c
int main()
{
    Test_CtypeFun(isprint, "isprint");
}
/*
Test Function [isprint] : 
[032]0x020,[033]!,[034]",[035]#,[036]$,[037]%,[038]&,[039]',[040](,[041]),
[042]*,[043]+,[044],,[045]-,[046].,[047]/,

[048]0,[049]1,[050]2,[051]3,[052]4,[053]5,[054]6,[055]7,[056]8,[057]9,

[058]:,[059];,[060]<,[061]=,[062]>,[063]?,[064]@,

[065]A,[066]B,[067]C,[068]D,[069]E,[070]F,[071]G,[072]H,[073]I,[074]J,[075]K,
[076]L,[077]M,[078]N,[079]O,[080]P,[081]Q,[082]R,[083]S,[084]T,[085]U,[086]V,
[087]W,[088]X,[089]Y,[090]Z,

[091][,[092]\,[093]],[094]^,[095]_,[096]`,

[097]a,[098]b,[099]c,[100]d,[101]e,[102]f,[103]g,[104]h,[105]i,[106]j,[107]k,
[108]l,[109]m,[110]n,[111]o,[112]p,[113]q,[114]r,[115]s,[116]t,[117]u,[118]v,
[119]w,[120]x,[121]y,[122]z,

[123]{,[124]|,[125]},[126]~,
*/
```

<br>

#### ispunct （检查字符是否是一个标点符号）

```c
int ispunct(int c);
```

`ispunct` 函数测试任何打印字符，该字符是特定于语言环境的一组标点字符之一，且 `isspace`和 `isalnum` 都不为真。

在 "C" 语言环境中，`ispunct` 对每个 `isspace` 和 `isalnum` 都不为真的打印字符返回真。

```c
int main()
{
    Test_CtypeFun(ispunct, "ispunct");
}
/*
Test Function [ispunct] : 
[033]!,[034]",[035]#,[036]$,[037]%,[038]&,[039]',[040](,[041]),[042]*,[043]+,
[044],,[045]-,[046].,[047]/,[058]:,[059];,[060]<,[061]=,[062]>,[063]?,[064]@,
[091][,[092]\,[093]],[094]^,[095]_,[096]`,[123]{,[124]|,[125]},[126]~,
*/
```

<br>

#### isspace （检查字符是否是空白字符）

```c
int isspace(int c);
```

`isspace` 函数测试标准空白字符或 `isalnum` 为 `false` 的特定于语言环境的一组字符中的任何字符。

标准的空白字符：空格（`' '`）、水平制表符（`'\t'`）、换行符（`'\n'`）、垂直制表符（`'\v'`）、换页符（`'\f'`）、回车符（`'\r'`）。在 "C" 语言环境中，`isblank` 仅对标准空白字符返回 `true`。

```c
int main()
{
    Test_CtypeFun(isspace, "isspace");
}
/*
Test Function [isspace] : 
[009]0x009,[010]0x00a,[011]0x00b,[012]0x00c,[013]0x00d,[032]0x020,
*/
```

<br>

#### isupper （检查字符是否是大写字母）

```c
int isupper(int c);
```

`isupper` 函数测试大写字母的任何字符，或者特定于语言环境的一组字符中的任何字符，其中 `iscntrl`、`isdigit`、`ispunct` 或 `isspace` 都不为真。

在 "C" 语言环境中，`isupper` 仅对大写字母返回 `true`。

```c
int main()
{
    Test_CtypeFun(isupper, "isupper");
}
/*
Test Function [isupper] : 
[065]A,[066]B,[067]C,[068]D,[069]E,[070]F,[071]G,[072]H,[073]I,[074]J,[075]K,
[076]L,[077]M,[078]N,[079]O,[080]P,[081]Q,[082]R,[083]S,[084]T,[085]U,[086]V,
[087]W,[088]X,[089]Y,[090]Z,
*/
```

<br>

#### isxdigit （检查字符是否是十六进制的字符）

```c
int isxdigit(int c);
```

`isxdigit` 函数测试任何十六进制数字字符。

```c
int main()
{
    Test_CtypeFun(isxdigit, "isxdigit");
}
/*
Test Function [isxdigit] : 
[048]0,[049]1,[050]2,[051]3,[052]4,[053]5,[054]6,[055]7,[056]8,[057]9,
[065]A,[066]B,[067]C,[068]D,[069]E,[070]F,
[097]a,[098]b,[099]c,[100]d,[101]e,[102]f,
*/
```

---
### 字符映射函数（Character case mapping functions） 

#### tolower （大写字符转换为小写字符）

```c
int tolower(int c);
```

`tolower` 函数将大写字母转换为相应的小写字母。

```c
#define String "The Quick Brown Fox Jumps Over a Lazy Dog."
int main()
{
    int len = strlen(String);
    int index = 0;
    char _S[] = String;
    while (index < len)
    {
        _S[index] = tolower(_S[index]);
        index++;
    }
    printf("String  : %s\n"
           "Tolower : %s",
           String, _S);
}
/*
String  : The Quick Brown Fox Jumps Over a Lazy Dog.
Tolower : the quick brown fox jumps over a lazy dog.
*/
```

<br>

#### toupper （小写字符转换为大写字符）

```c
int toupper(int c);
```

`toupper` 函数将小写字母转换为相应的大写字母。

```c
#define String "The Quick Brown Fox Jumps Over a Lazy Dog."
int main()
{
    int len = strlen(String);
    int index = 0;
    char _S[] = String;
    while (index < len)
    {
        _S[index] = toupper(_S[index]);
        index++;
    }
    printf("String  : %s\n"
           "Toupper : %s",
           String, _S);
}
/*
String  : The Quick Brown Fox Jumps Over a Lazy Dog.
Toupper : THE QUICK BROWN FOX JUMPS OVER A LAZY DOG.
*/
```

---
## C 宽字符分类和映射工具（Wide character classification and mapping utilities）：wctype.h

`wctype.h` 提供有关宽字符分类和字符映射的函数和类型。这些函数的行为收到当前区域设置的 `LC_CTYPE` 类别的影响。

对于下面描述的接受 `wint_t` 类型参数的所有函数，其值应可表示为 `wchar_t` 或应等于宏 `WEOF` 的值。如果此参数具有任何其他值，则行为未定义。

---
### Types and Macro

```c
typedef unsigned short    wint_t;    // 保存与扩展字符集成员相对应的任何值
typedef unsigned short    wctype_t;  // 保存表示特定于区域设置的字符分类的值
typedef wchar_t           wctrans_t; // 保存表示特定于区域设置的字符映射的值

#define WEOF    ((wint_t)(0xFFFF))
```

---
### Functions：宽字符分类函数（Wide character classification utilities）
#### 宽字符分类函数

参考 `ctype.h` 中的字符分类函数，以下提供对应的宽字符版本。

```c
int iswalnum(wint_t wc);            // isalnum  是否为字母或数字
int iswalpha(wint_t wc);            // isalpha  是否为字符
int iswblank(wint_t wc);            // isblank  是否为空白符 L' ' 或 L'\t'
int iswcntrl(wint_t wc);            // iscntrl  是否为控制字符
int iswdigit(wint_t wc);            // isdigit  是否为数字
int iswgraph(wint_t wc);            // isgraph  是否为图形字符
int iswlower(wint_t wc);            // islower  是否为小写字母
int iswprint(wint_t wc);            // isprint  是否为打印字符
int iswpunct(wint_t wc);            // ispunct  是否为标点符号
int iswspace(wint_t wc);            // isspace  是否为空白符
int iswupper(wint_t wc);            // isupper  是否为大写字母
int iswxdigit(wint_t wc);           // isxdigit  是否为十六进制数字字符
```

>---

#### wctype、iswctype（可扩展的宽字符分类函数）

> `wctype`

```c
wctype_t wctype(const char *property);          // 构造本地环境的宽字符类别分类
```

`wctype` 用于构造 `wctype_t` 类型值，它描述为当前区域设置的宽字符分类函数使用的 `LC_CTYPE` 类别，该值可以作为 `iswctype` 函数的第二个参数。如果当前 C 的语言环境不能支持构造 `property` 描述的特定字符分类时，返回 0。

`property` 的以下值在所有 C 本地环境中得到支持

```c
"alnum"	        // 标识 iswalnum 所用的类别
"alpha"	        // 标识 iswalpha 所用的类别
"blank"	        // 标识 iswblank 所用的类别(C99)
"cntrl"	        // 标识 iswcntrl 所用的类别
"digit"	        // 标识 iswdigit 所用的类别
"graph"	        // 标识 iswgraph 所用的类别
"lower"	        // 标识 iswlower 所用的类别
"print"	        // 标识 iswprint 所用的类别
"space"	        // 标识 iswspace 所用的类别
"upper"	        // 标识 iswupper 所用的类别
"xdigit"	    // 标识 iswxdigit 所用的类别
```

> `iswctype`

```c
int iswctype(wint_t wc, wctype_t desc);         // 检查字符是否符合本地环境下的指定宽字符分类
```

`iswctype` 使用 `desc` 所标识的区域特定字符分类，检查宽字符 `wc` 是否符合 `desc` 描述的分类。`LC_CTYPE` 类别的当前设置应与调用返回 `desc` 的 `wctype` 时的设置相同。

当且仅当宽字符 `wc` 的值为 `desc` 描述的属性时，`iswctype` 函数返回非零。如果 `desc`为零，`iswctype` 函数返回零。

```c
#define _CRT_SECURE_NO_WARNINGS 0 // 0
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
const char* classify(wchar_t wc, const char* cat)
{
    return iswctype(wc, wctype(cat)) ? "true" : "false";
}
int main(void)
{
    setlocale(LC_ALL, "zh_cn.UTF-8");
    wchar_t ch = L'水';
    printf("The character \"%lc\" is...\n", ch);
    const char* cats[] = { "digit", "alpha", "space", "cntrl" };
    for (int n = 0; n < 4; ++n)
        printf("%s? %s\n", cats[n], classify(ch, cats[n]));
}
/*
The character "水" is...
digit? false
alpha? true
space? false
cntrl? false
*/
```

---
### Functions：宽字符映射函数

#### towlower、towupper （大小写转换）

```c
wint_t towlower( wint_t wc );       // islower  若可能则转换给定宽字符为小写
wint_t towupper( wint_t wc );       // isupper  若可能则转换给定宽字符为大写
```

>---

#### wctrans、towctrans （可扩展的宽字符大小写映射函数）

> `wctrans`

```c
wctrans_t wctrans(const char* property);     
```

`wctrans` 构造 `wctrans_t` 类型值，它描述当前区域设置的宽字符映射函数使用的 `LC_CTYPE` 类别，该值可以作为 `towctrans` 函数的第二个参数。如果当前 C 的语言环境不能支持构造 `property` 描述的特定字符映射时，返回 0。

`property` 的以下值在所有 C 本地环境中得到支持：

```c
"toupper"	        // 标识 towupper 所用的映射
"tolower"           // 标识 towlower 所用的映射
```

> `iswctrans`

```c
wint_t towctrans(wint_t wc, wctrans_t desc);
```

`towctrans` 函数使用 `desc` 描述的映射返回 `wc` 的映射值。如果 `desc` 为零，则 `towctrans` 函数返回 `wc` 的值。

```c

```

---
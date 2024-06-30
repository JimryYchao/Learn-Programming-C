## C 宽字符分类和映射工具：wctype.h

`wctype.h` 提供有关宽字符分类和字符映射的函数和类型。这些函数的行为收到当前区域设置的 `LC_CTYPE` 类别的影响。

| Specifier | Description |
| :-------- | :---------- |


| `WEOF`      | `((wint_t)(0xFFFF))`                 |

---
### 宽字符分类函数

| Specifier   | Description                                |
| :---------- | :----------------------------------------- |
| `iswalnum`  | 是否为字母或数字                           |
| `iswalpha`  | 是否为字符                                 |
| `iswblank`  | 是否为空白符 `L' '` 或 `L'\t'`             |
| `iswcntrl`  | 是否为控制字符                             |
| `iswdigit`  | 是否为数字                                 |
| `iswgraph`  | 是否为图形字符                             |
| `iswlower`  | 是否为小写字母                             |
| `iswprint`  | 是否为打印字符                             |
| `iswpunct`  | 是否为标点符号                             |
| `iswspace`  | 是否为空白符                               |
| `iswupper`  | 是否为大写字母                             |
| `iswxdigit` | 是否为十六进制数字字符                     |
| `iswctype`  | 检查字符是否符合本地环境下的指定宽字符分类 |
| `wctype`    | 构造本地环境的宽字符类别分类               |
| `wint_t`    | 保存与扩展字符集成员相对应的任何值         |
| `wctype_t`  | 保存表示特定于区域设置的字符分类的值       |


> wctype, iswctype

`iswctype` 使用 `desc` 所标识的区域特定字符分类，检查宽字符 `wc` 是否符合 `desc` 描述的分类。`LC_CTYPE` 类别的当前设置应与调用返回 `desc` 的 `wctype` 时的设置相同。

`wctype` 用于构造 `wctype_t` 类型值，它描述为当前区域设置的宽字符分类函数使用的 `LC_CTYPE` 类别，该值可以作为 `iswctype` 函数的第二个参数。如果当前 C 的语言环境不能支持构造 `property` 描述的特定字符分类时，返回 0。`property` 的以下值在所有 C 本地环境中得到支持

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

>---
### 宽字符映射函数

| Specifier   | Description                              |
| :---------- | :--------------------------------------- |
| `towlower`  | 宽字符小写转换                           |
| `towupper`  | 宽字符大写转换                           |
| `towctrans` | 使用 `desc` 描述的映射返回 `wc` 的映射值 |
| `wctrans`   | 构造本地环境的宽字符映射类别             |
| `wctrans_t` | 保存表示特定于区域设置的字符映射的值     |

> towctrans, wctrans 

`towctrans` 函数使用 `desc` 描述的映射返回 `wc` 的映射值。如果 `desc` 为零，则 `towctrans` 函数返回 `wc` 的值。

`wctrans` 构造 `wctrans_t` 类型值，它描述当前区域设置的宽字符映射函数使用的 `LC_CTYPE` 类别，该值可以作为 `towctrans` 函数的第二个参数。如果当前 C 的语言环境不能支持构造 `property` 描述的特定字符映射时，返回 0。`property` 的以下值在所有 C 本地环境中得到支持：

```c
"toupper"	        // 标识 towupper 所用的映射
"tolower"           // 标识 towlower 所用的映射
```

---
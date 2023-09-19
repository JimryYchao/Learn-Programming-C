## C 常用定义（Common definitions）：stddef.h

`stddef.h` 声明了一些常用的类型和宏定义，并在其他文件中引用。

---
### Types

#### ptrdiff_t （指针差值）

```c
typedef long long ptrdiff_t;
```

- `ptrdiff_t` 两个指针相减的结果的有符号整数类型。

<br>

#### size_t

```c
typedef unsigned long long  size_t;
```

- `size_t` 是 `sizeof` 运算符的结果的无符号整数类型。

<br>

#### max_align_t

```c
typedef struct {
  long long __max_align_ll;
  long double __max_align_ld;
} max_align_t;
```

- `max_align_t` 是对齐要求至少和其他任何一种标量类型一样严格（一样大）的类型。

<br>

#### wchar_t

```c
typedef unsigned short wchar_t;
```

- `wchar_t` 是一个整数类型，其值范围可以表示在支持的语言环境中指定的最大扩展字符集的所有成员的不同代码，其中 null 字符定义为 `\0`。
- 若没有定义宏 `_STDC_MB_MIGHT_NEQ_WC`，则基本字符集的每个成员的代码值应等于其作为整数字符常量中的唯一字符时的值。

---
### Macros

#### NULL

```c
#define NULL   ((void *)0)
```

- `NULL` 扩展为实现定义的空指针常量。

<br>

#### offsetof

```c
#define offsetof(type, member)  ((size_t)&(((type*)0)->member))
```

- `offsetof` 展开为 `size_t` 类型的整数常量表达式，其值为从指定类型结构的起始到指定结构对象的以字节为单位的偏移量。一般不在 `type` 中定义新类型。 
- 如果指定的 `member` 是位域，则行为未定义，无法获取位域成员的地址。 

```c
#include <stdio.h>
#include <stddef.h>
 
struct S {
    char c;
    double d;
};
int main(void)
{
    printf("the first element is at offset %zu\n", offsetof(struct S, c));
    printf("the double is at offset %zu\n", offsetof(struct S, d));
}
```

---
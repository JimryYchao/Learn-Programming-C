## C 常用定义（Common definitions）：stddef.h

```c
#define __STDC_VERSION_STDDEF_H__     202311L
```

`stddef.h` 声明了一些常用的类型和宏定义，并在其他文件中引用。

---
### Types

#### ptrdiff_t （指针差值）

```c
typedef signed long int ptrdiff_t;
```

`ptrdiff_t` 是两个指针相减的结果的有符号整数类型。用于 `ptrdiff_t` 的类型不应具有大于 `signed long int` 的整数转换秩，除非实现支持足够大的对象使其成为必要。

>---

#### size_t

```c
typedef unsigned long int  size_t;
```

`size_t` 是 `sizeof` 运算符的结果的无符号整数类型。用于 `size_t` 的类型不应具有大于 `unsigned long int` 的整数转换秩，除非实现支持足够大的对象使其成为必要。

>---

#### max_align_t

```c
typedef struct {
  long long __max_align_ll;
  long double __max_align_ld;
} max_align_t;
```

`max_align_t` 是一种对象类型，它的对齐是最大的基本对齐。

>---

#### wchar_t

```c
typedef unsigned short wchar_t;
```

`wchar_t` 是一种整数类型，其值的范围可以表示在支持的区域设置中指定的最大扩展字符集的所有成员的不同代码，其中空字符的值为 0。若没有定义宏 `_STDC_MB_MIGHT_NEQ_WC`，则基本字符集的每个成员的代码值应等于其在整数字符常量中用作单独字符时的值。

>---

#### nullptr_t

```c
typedef typeof_unqual(nullptr) nullptr_t
```

`nullptr_t` 是预定义空指针常量 `nullptr` 的类型。它是一种非限定的完整标量类型，不同于所有指针或算术类型，既不是原子类型也不是数组类型，只有一个值 `nullptr`。此类型对象的默认或空初始化等效于 `nullptr` 的初始化。

`nullptr_t` 能隐式转换到任何指针类型或 `bool`，而结果分别为该类型的空指针值或 `false`。除了 `nullptr_t` 自身，没有其他类型能转换或显式转型成 `nullptr_t`。

`sizeof(nullptr_t)` 与 `alignof(nullptr_t)` 分别等于 `sizeof(void*)` 与 `alignof(void*)`

`nullprt_t` 的大小和对齐方式与指向字符类型的指针相同。值 `nullptr` 的对象表示与 `(void*)0` 的相同。若程序产生拥有不同对象表示的 `nullptr_t` 值，则行为未定义。

`nullptr_t` 被认为是标量类型，因此 `nullptr_t` 类型的对象可以出现在 `(void*)0` 有效的许多上下文中：
- `alignas`、`sizeof` 运算符的操作数。
- 作为到指针类型的隐式或显式转换的操作数。
- 作为 `nullptr_t` 类型对象的赋值或初始化中的赋值表达式。
- 作为 `nullptr_t` 类型形参的实参或可变参数列表中的实参。
- `void` 表达式。
- 作为到 `bool` 的隐式或显式转换的操作数。
- 作为 `_Generic` 表达式的操作数。
- 作为 `!`、`&&`、`||` 或条件运算符的操作数。
- 作为 `if` 或迭代语句的控制表达式。

```c
#include <stddef.h>
#include <stdio.h>
 
#define DETECT_NULL_POINTER_CONSTANT(e) \
    _Generic(e,                         \
        void* : puts("void*"),          \
        nullptr_t : puts("nullptr_t"),  \
        default : puts("other")       \
    )
 
int main()
{
    DETECT_NULL_POINTER_CONSTANT(((void*)0));     // void*
    DETECT_NULL_POINTER_CONSTANT(0);              // other
    DETECT_NULL_POINTER_CONSTANT(nullptr);        // nullptr_t
}
```

---
### Macros

#### NULL

```c
#define NULL   ((void *)0)
```

`NULL` 扩展为实现定义的空指针常量。

>---
#### unreachable

```c
void unreachable(void);
```

仿函数宏 `unreachable` 的调用表明永远不会采用导致调用的特定流控制；它展开为一个 `void` 表达式。程序执行不能到达这样的调用。如果在执行期间到达该值，则行为未定义。

下面的代码表示期望函数的参数将是三个枚举值之一，尽管枚举类型允许传递其他非枚举值。某些实现可能会诊断切换后缺少 `return` 语句，但使用 `unreachable` 宏向实现发信号通知该情形不应该是可能的，从而允许更好的诊断和优化属性。

```c
enum Colors { Red, Green, Blue };
int get_channel_index(enum Colors c) {
    switch (c) {
        case Red: return 0;
        case Green: return 1;
        case Blue: return 2;
    }
    unreachable();
}
```

>---

#### offsetof

```c
#define offsetof(type, member-designator)  /* 由实现定义 */
```

`offsetof` 展开为具有 `size_t` 类型的整数常量表达式，其值为从指定类型 `type` 的任何对象的开始到子对象（由 `member-designator` 指定）的以字节为单位的偏移量。一般不在 `type` 中定义新类型。类型和成员应满足 `static type t;`，因此 `&(t.member)` 计算为地址常量。

若在 `type` 中指定的类型含有不在匹配的括号中的逗号（例如 `offsetof(struct Foo { int a, b; }, a)` 通常不能编译），或者指定的成员是位字段，则行为未定义。`typeof` 能用于避免在新类型定义中的逗号的坏效果，例如 `offsetof(typeof(struct { int i, j; }), i)` 为良定义。

如果指定的 `member` 是位域，则行为未定义，无法获取位域成员的地址。不限制 `member` 为直接成员。它能指代给定成员的子对象，例如数组成员的元素。

```c
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdalign.h>

struct S
{
    char c;
    double d[10];
};

int main(void)
{
    printf("the first element is at offset %zu\n", offsetof(typeof(struct S),c));
    
     // member 不限于直接成员，可以是数组成员的元素
    printf("the double is at offset %zu\n", offsetof(typeof(struct S), d[4])); 
}
/*
the first element is at offset 0
the double is at offset 40
*/
```

---
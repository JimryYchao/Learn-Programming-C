## C 可变参数（Variable arguments）：stdarg.h

```c
#define __STDC_VERSION_STDARG_H__       202311L
```

`stdarg.h` 定义了与可变参函数相关的宏。

---
### Type

#### va_list

```c
typedef char * va_list;
```

类型 `va_list` 是一个完整的对象类型，适合于保存宏 `va_start`、`va_arg`、`va_end`、`va_copy` 所需的信息。当需要访问可变参数时，被调用的函数必须声明一个具有 `va_list` 类型的对象 `ap`，`ap` 可以作为参数传递给其他函数；如果该函数调用带有参数 `ap` 的 `va_arg` 宏，则调用函数中的 `ap` 的表示是不确定的，并且在应在进一步引用 `ap` 之前，应将 `ap` 传递给 `va_end` 宏。

---
### Macros：可变参数列表访问

#### va_start

```c
void va_start(va_list ap, ...); 
```

应在函数访问可变参数列表之前调用 `va_start` 宏。`va_start` 用于初始化 `ap` 供 `va_arg` 和 `va_end` 后续使用。在不为同一个 `ap` 调用 `va_end` 宏的情况下，不能调用 `va_start` 或 `va_copy` 来重新初始化 `ap`。

只计算传递给 `va_start` 宏的第一个参数，其他参数可以拓展，并在未指定的上下文中使用。如果任何其他参数扩展为包括不平衡的括号，或未转换为标记的预处理标记，则行为未定义。

```c
#include <stdarg.h>
void miaou (...) {
    va_list vl;
    va_start(vl, 1, 3.0, "12", xd); // diagnostic encouraged
    /* ... */
    va_end(vl);
}
```

> *C23* *前*

```c
void va_start(va_list ap, pre_param);    // C23 前
```

旧版本的 `va_start` 参数 `pre_param` 为可变参数列表前一个参数的标识符，它的类型如果是 `register` 类型、数组类型、函数类型、或与默认参数提升结果类型不兼容的类型，则该行为是未定义的。

```c
#include <stdarg.h>
void neigh (int last_arg, ...) {
    va_list vl;
    va_start(vl, last_arg); // no diagnostic
    /* ... */
    va_end(vl);
}
```

>---

#### va_arg

```c
type va_arg(va_list ap, type);

```

`va_arg` 宏展开为具有指定类型和调用中下一个参数值的表达式。参数 `ap` 必须由 `va_start` 或 `va_copy` 初始化（且没有为同一 `ap` 调用 `va_end` 宏）。每次调用 `va_arg` 宏会修改 `ap`，以便依次返回可变参数列表后续参数的值。如果没有实际的下一个参数，则行为是未定义的。`type` 参数应为对象类型名称。如果 `type` 与下一个参数的类型不兼容，则行为是未定义，除非是：
- 这两种类型都是指向兼容类型的限定或非限定版本的指针；
- 一种类型与有符号整数类型兼容，另一种类型与相应的无符号整数类型兼容，并且该值在两种类型中都可表示；
- 一种类型是指向限定或非限定 `void` 的指针，另一种类型是指向限定或非限定字符类型的指针;
- 下一个参数的类型是 `nullptr_t`，并且 `type` 是指针类型，其具有与指向字符类型的指针相同的表示和对齐要求。

在 `va_start` 宏之后第一次调用 `va_arg` 宏时，返回在参数列表的 `...` 中的第一个参数。连续调用将连续返回其余参数的值。

>---

#### va_copy

```c
void va_copy(va_list dest, va_list src);
```

`va_copy` 宏将 `dest` 初始化为 `src` 的副本，就好像 `va_start` 宏以应用于 `dest`，然后按照与先前达到 `src` 当前状态的 `va_arg` 宏相同的顺序使用。无论是 `va_copy` 还是 `va_start` 宏都不能被调用来重新初始化 `dest`，除非中间对该 `dest` 调用 `va_end` 宏。

>---

#### va_end

```c
void va_end(va_list ap);
```

`va_end` 宏有助于从函数正常返回，该函数的变量参数列表由 `va_start` 宏的展开引用，或者包含 `va_copy` 宏展开的函数初始化的 `va_list ap`。对 `ap_start` 或 `ap_copy` 调用所初始化的 `ap` 对象进行 `va_end(ap)` 清理，使其不再能使用。

若无对应的对 `va_start` 或 `va_copy` 调用，或在调用 `va_start` 或 `va_copy` 的函数返回前没有调用对应的 `va_end` ，则行为未定义。

---
### Example

```c
#include <stdio.h>
#include <stdarg.h>

int add_nums(int count, ...) 
{
    int result = 0;
    va_list args;
    va_start(args, count); // C23 起能省略 count
 
    for (int i = 0; i < count; ++i) {
        result += va_arg(args, int);
    }
    va_end(args);
    return result;
}
 
#if __STDC_VERSION__ > 201710L
// 同上，C23 起合法
int add_nums_c23(...)
{
    int result = 0;
    va_list args;
    va_start(args);
 
    int count = va_arg(args, int);
    for (int i = 0; i < count; ++i) {
        result += va_arg(args, int);
    }
 
    va_end(args);
}
#endif
 
int main(void) 
{
    printf("%d\n", add_nums(4, 25, 25, 50, 50));
#if __STDC_VERSION__ > 201710L
    printf("%d\n", add_nums_C23(4, 25, 25, 50, 50));
#endif
}
```

---
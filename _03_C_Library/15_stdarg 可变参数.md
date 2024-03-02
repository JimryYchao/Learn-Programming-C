## C 可变参数（Variable arguments）：stdarg.h

`stdarg.h` 定义了与可变参函数相关的宏。

---
### Type

#### va_list

```c
typedef char * va_list;
```

- 类型 `va_list` 适合保存宏 `va_start`、`va_arg`、`va_end`、`va_copy` 所需的信息。当需要访问不同的实参时，被调用的函数必须声明一个类型为 `va_list` 的对象 `ap`，并作为参数传递给其他函数。

---
### Macros：访问可变参数列表

#### va_start

```c
void va_start(va_list ap, pre_param); 
```

- `va_start` 用于初始化 `ap` 供 `va_arg` 和 `va_end` 后续使用，在未被 `va_end` 之前可以调用 `va_copy` 对当前的 `ap` 在可变参数列表中的位置进行复制。
- 参数 `pre_param` 为可变参数列表前一个参数的标识符，它的类型如果是 `register` 类型、数组类型、函数类型、或与默认参数提升结果类型不兼容的类型，则该行为是未定义的。

<br>

#### va_arg

```c
type va_arg(va_list ap, type);

```

- `va_arg` 展开为一个表达式，该表达式具有指定的类型和调用中的下一个参数的值。参数 `ap` 由 `va_start` 或 `va_copy` 初始化。每次调用 `va_arg` 会修改 `ap` 的位置，以依次返回可变参数列表的元素。`type` 必须是与下一个元素的类型兼容，否则行为是未定义的，除非是：
  - 从 `void *` 转向 `char *`；
  - 有符号整型到相应的无符号整型（`int` 到 `unsigned int`）。

- `va_arg` 在 `va_start` 宏之后的第一次调用将返回 `pre_param` 指定的参数值之后的参数值。连续调用依次返回剩余参数的值。

<br>

#### va_copy

```c
void va_copy(va_list dest, va_list src);
```

- `va_copy` 将 `dest` 复制当前 `src` 的副本。

<br>

#### va_end

```c
void va_end(va_list ap);
```

- `va_end` 对 `ap_start` 或 `ap_copy` 调用所初始化的 `ap` 对象进行 `va_end(ap)` 清理，使其不再能使用。
- 若无对应的对 `va_start` 或 `va_copy` 调用，或在调用 `va_start` 或 `va_copy` 的函数返回前没有调用对应的 `va_end` ，则行为未定义。


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
// 同上， C23 起合法
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
}
```

---
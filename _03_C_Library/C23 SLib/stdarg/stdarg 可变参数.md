## C 可变参数：stdarg.h

`stdarg.h` 定义了与可变参函数相关的宏。

|Specifier|Description|
|:--|:--
`va_list` | 当需要访问可变参数时，保存宏 `va_start`、`va_arg`、`va_end`、`va_copy` 所需的信息。访问可变参数结束时，将 `va_list` 对象传递给 `va_end`。
|`va_start`| 访问可变参数列表之前调用 `va_start` 宏初始化 `va_list`。
`va_arg` | 从 `va_list` 提取可变参数列表中的元素。连续调用返回其余参数的值。
`va_copy` | 将 `dest` 初始化为 `va_list src` 的副本
`va_end` | 对 `va_list` 做清理工作，使 `va` 后续不可用。

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
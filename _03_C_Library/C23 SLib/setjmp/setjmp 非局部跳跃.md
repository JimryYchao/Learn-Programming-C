## C 非局部跳跃：setjmp.h

`setjmp.h`[[↗]](setjmp_test.c) 定义了 `setjmp`，并声明一个函数和一种类型，用于绕过正常的函数调用和返回规则。

>---
### 保存或恢复调用环境

| Specifier | Description                                                                                                |
| :-------- | :--------------------------------------------------------------------------------------------------------- |
| `jmp_buf` | 用于保存或恢复调用环境所用信息的数组类型。它不包含浮点环境标志、打开文件的状态或抽象机内的任何组件的状态。 |
 `setjmp` |将当前调用环境保存到 `jmp_buf` 类型对象 `env` 中，此对象可以由调用 `longjmp` 函数用来恢复当前执行环境。如果返回来自直接调用，则返回零，并保存执行环境到 `env`；若返回来自对 `longjmp` 函数的调用，则返回非零值。
|`longjmp`|使用相应的 `jmp_buf` 参数，在相同的程序调用中恢复最近一次调用 `setjmp` 宏所保存的环境。跳转完成后，程序在 `setjmp` 处线程继续执行，并返回 `val` 指定的值。如果 `val = 0`，`setjmp` 宏返回 `1`。|


`setjmp` 宏的调用只能出现在以下环境之一：
  - 选择或迭代语句（`if`、`switch`、`for`、`while`、`do while`）的完整控制表达式。
  - 比较或相等运算符的一个操作数，且另一个操作数是整数常量表达式，结果表达式是选择或迭代语句的完整控制表达式。
  - 一元运算符（`!`）非的操作数，结果表达式是选择或迭代语句的完整控制表达式。
  - 表达式语句的完整表达式。可能强制转换为 `void`。
  - 如果调用出现在任何其他上下文，则行为未定义。


```c
#include <stdio.h>
#include <setjmp.h>

// noreturn (c23)
[[noreturn]] void jump(jmp_buf env, int count)
{
    printf("Jump count = %d\n", count);
    longjmp(env, count + 1); // 将在 setjmp 中返回 count+1
}

static volatile int count = 0; 
int main(void)
{
    jmp_buf env;
    if (setjmp(env) < 10)
        jump(env, count++);
}
/*
Jump count = 0
Jump count = 1
Jump count = 2
Jump count = 3
Jump count = 4
Jump count = 5
Jump count = 6
Jump count = 7
Jump count = 8
Jump count = 9
*/
```

---
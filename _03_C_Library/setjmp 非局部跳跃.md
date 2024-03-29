## C 非局部跳跃（Nonlocal jumps）：setjmp.h

```c
#define __STDC_VERSION_SETJMP_H__		202311L
```

`setjmp.h` 定义了 `setjmp`，并声明一个函数和一种类型，用于绕过正常的函数调用和返回规则。

---
### Type

#### jmp_buf

```c
typedef _JPTYPE jmp_buf;
```

`jmp_buf` 是适用于保存并恢复调用环境所用信息的数组类型。存储的信息足以恢复程序在当前块的执行和该块的调用。它不包含浮点环境标志、打开文件的状态或抽象机内的任何组件的状态。

---
### Macro-Function：保存调用环境（Save calling environment）

#### setjmp 

```c
int setjmp(jmp_buf env);
```

`setjmp` 宏将其调用环境保存到 `jmp_buf` 类型对象 `env` 中，此对象可以由调用 `longjmp` 函数用来恢复当前执行环境。

如果返回来自直接调用，则 `setjmp` 返回值为 0，并保存执行环境到 `env`；若返回来自对 `longjmp` 函数的调用，则返回非零值。

`setjmp` 宏的调用只能出现在以下环境之一：
  - 选择或迭代语句（`if`、`switch`、`for`、`while`、`do while`）的完整控制表达式。
  - 比较或相等运算符的一个操作数，且另一个操作数是整数常量表达式，结果表达式是选择或迭代语句的完整控制表达式。
  - 一元运算符（`!`）非的操作数，结果表达式是选择或迭代语句的完整控制表达式。
  - 表达式语句的完整表达式。可能强制转换为 `void`。
  - 如果调用出现在任何其他上下文，则行为未定义。

---
### Function：恢复调用环境（Restore calling environment）

#### longjmp

```c
[[noreturn]] void longjmp(jmp_buf env, int val);
```

`longjmp` 函数使用相应的 `jmp_buf` 参数，在相同的程序调用中恢复最近一次调用 `setjmp` 宏所保存的环境。如果没有这样的调用，或这如果调用来自另一个执行线程，或者如果包含 `setjmp` 宏调用的函数在过渡期间终止了执行，或者如果 `setjmp` 宏的调用在一个具有可变修改类型的标识符的范围内，并且执行在过渡期间离开了该区域，则行为是未定义的。

所有可访问对象都有值，抽象机的所有其他组件都有状态，截至调用 `longjmp` 函数的时间，除了自动存储持续时间的对象的表示，这些对象是包含相应 `setjmp` 宏调用的函数本地的、没有 `volatile` 限定的类型，并且在 `setjmp` 调用和 `longjmp` 调用之间已经改变，是不确定的。

在 `longjmp` 完成后，在 `setjmp` 处线程继续执行，并返回 `val` 指定的值。如果 `val = 0`，`setjmp` 宏返回 `1`。

```c
#include <stdio.h>
#include <setjmp.h>
#include <stdnoreturn.h> 

// noreturn (c23)
[[noreturn]] void jump(jmp_buf env, int count) {
	printf("Jump count = %d\n", count);
	longjmp(env, count + 1);    // 将在 setjmp 中返回 count+1
}

int main(void)
{
	jmp_buf env;
	volatile int count = 0; // 一般为 setjmp 声明 volatile
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
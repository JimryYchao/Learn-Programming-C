## C 非局部跳跃（Nonlocal jumps）：setjmp.h

`setjmp.h` 定义了 `setjmp`，并声明一个函数和一种类型，用于绕过普通函数调用和返回规则。

---
### Type

#### jmp_buf

```c
typedef SETJMP_FLOAT128 jmp_buf;
```

- `jmp_buf` 是适合存储并恢复调用环境所用信息的数组类型。存储的信息足以恢复程序在当前块的执行和该块的调用。它不包含浮点状态标志、打开文件的状态和抽象机内的任何数据的状态。

---
### Macro-Function：保存调用环境（Save calling environment）

#### setjmp 

```c
int setjmp(jmp_buf env);
```

- `setjmp` 将当前执行环境保存到 `jmp_buf` 类型对象 `env` 中，此对象可以由 `longjmp` 用来恢复当前执行环境。
- `setjmp` 只能出现在：
  - 选择或迭代宇语句（`if`、`switch`、`for`、`while`、`do while`）的完整控制表达式。
  - 比较或相等运算符的一个运算数，且另一个运算数为常量表达式，产生的表达式为选择或迭代语句的完整控制表达式。
  - 一元运算符（`!`）非的运算数，其结果为选择或迭代语句的完整控制表达式。
  - 表达式语句的完整表达式。可以将其转换为 `void`。

- 如果返回来自直接调用，则 `setjmp` 返回值为 0，并保存执行环境到 `env`；若进行了非局部跳转则可返回非零值，返回值与传递给 `longjmp` 相同。

---
### Function：恢复调用环境（Restore calling environment）

#### longjmp

```c
_Noreturn void longjmp(jmp_buf env, int val);
```

- `longjmp` 使用 `jmp_buf` 参数，在程序的相同调用中恢复最近一次调用 `setjmp` 宏所保存的环境。如果调用来自另一个执行线程，或者包含 `setjmp` 调用的函数在过渡期间终止了执行，或者 `setjmp` 的调用在具有可变修改类型的标识符的范围内，并且执行在过渡期间离开了该区域，则行为是未定义的。

- 在 `longjmp` 完成后，在 `setjmp` 处线程继续执行，并返回 `val` 指定的值。如果 `val = 0`，`setjmp` 宏返回 `1`。

```c
#include <stdio.h>
#include <setjmp.h>
#include <stdnoreturn.h> 

// noreturn (c11)
noreturn void jump(jmp_buf env, int count) {
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
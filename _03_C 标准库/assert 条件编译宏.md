# assert.h 条件编译宏

---
- [assert.h 条件编译宏](#asserth-条件编译宏)
- [1. assert.h 断言库](#1-asserth-断言库)
- [2. assert()](#2-assert)
- [3. static_assert 静态断言(C11)](#3-static_assert-静态断言c11)

---
# 1. assert.h 断言库

- ```assert.h``` 头文件支持的断言库是一个用于辅助调试程序的小型库, 实质上是将表达式与 0 进行比较
- ```assert.h``` 由 ```assert()``` 宏组成，接受一个整型表达式作为参数。如果表达式求值为假（非零），```assert()``` 宏就在标准错误流（stderr）中写入一条错误信息，并调用 ```abort()``` 函数终止程序（```abort()``` 函数的原型在 ```stdlib.h``` 头文件中）
- assert 宏函数是为了标识出程序中某些条件为真的关键位置，如果其中的一个具体条件为假，就用 abort 语句终止程序
- ```assert()``` 的参数是一个条件表达式或逻辑表达式。如果 ```assert()``` 中止了程序，它首先会显示失败的测试、包含测试的文件名和行号。
- 如果认为已经排除了程序的 bug，在包含 ```assert.h``` 的位置前面：【 ```#define NDEBUG``` 】, 编译器就会禁用文件中的所有 ```assert()``` 语句。

---
# 2. assert()

- assert 能够自动标识文件和问题的行号
- 断言失败将会在 stderr 标准错误流输出表达式与失败的行数, 一般是由于表达式不成立时会断言失败

```c
// #define NDEBUG	/* 取消 assert 断言 */ 
#include <assert.h>

z = x * x - y * y;
assert(z >= 0);

// 相当于
if(z<0){
	puts("z less than 0");
	abort();
}
```

---
# 3. static_assert 静态断言(C11)

- ```assert()``` 表达式是在运行时进行检查
- C11 新增了一个特性：```static_assert``` 声明，可以在编译时检查 ```assert()``` 表达式
- ```assert()``` 可以导致正在运行的程序中止，而 ```static_assert()``` 可以导致程序无法通过编译。
- ```static_assert()``` 只在编译阶段运行，无法获得变量的值。如果对变量进行静态断言，就会导致编译错误。

```c
static_assert(exp, const char* errMessage);
_Static_assert(exp, const char* errMessage);
/*
	当表达式为 false 时, 编译器会产生一条编译错误
	编译错误为 errNessage 用户定义错误
*/
```

> 静态断言

```c
static_assert(sizeof(int) == 4, "64-bit code generation is not supported.");
// 表示如果当前计算机的 int 类型不等于 4 个字节，就会编译报错。
```

---
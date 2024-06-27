## C 诊断（Diagnostics）：assert.h

```c
#define __STDC_VERSION_ASSERT_H__     202311L
```

断言库，在程序中关键的地方进行断言。若为非真，程序将在标准错误流输出一条适当的信息，并且使执行异常终止。

`assert.h` 定义了宏 `assert` 和 `static_assert` 并引用了 `NDEBUG` 用于取消断言。C23 起，`static_assert` 将作为关键字从 `assert.h` 中移除，新增宏定义 `__STDC_VERSION_ASSERT_H__`。

---
### Macro
#### assert （断言宏）

```c
void assert(scalar-Expression); // scalar 表示表达式必须具有标量类型
```

`assert` 执行时如果表达式为 `false`，则 `assert` 将有关失败的特定调用信息输出到标准错误流，然后调用 `abort` 函数。

```c
#include <assert.h>
assert(1 > 2); // Assertion failed!
``` 

>---

#### static_assert （静态断言宏）

```c
#define static_assert(expression, message) _Static_assert(expression, message)
```

静态断言在编译时对表达式断言判断。

```c
#include <assert.h>
static_assert(1 > 2, "Assertion failed!");
```

C23 起，`static_assert` 将作为关键字从 `assert.h` 中移除。

```c
static_assert( scalar-expression );
static_assert( scalar-expression, string-literal );
```

---

### NDEBUG （取消断言）

`NDEBUG` 宏不由 `assert.h` 头文件定义，如果 `NDEBUG` 在 `#include <assert.h>` 之前定义，则表示取消断言。宏 `assert` 被简单地定义为：

```c
#define assert(...) ((void)0)
```

`assert.h` 每次被包含时宏 `assert` 都会根据 `NDEBUG` 的当前状态重新定义。

```c
extern void _assert(char const* _Message, char const* _File, unsigned _Line)

#ifdef NDEBUG
    #define assert(expression) ((void)0)
#else
    #define assert(expression) (void)(
        (!!(expression)) || (_assert(#expression, __FILE__, __LINE__)), 0)
#endif   
```

静态断言 `static_assert` 不受 `NDEBUG` 其影响。

> 取消断言

```c
#define NDEBUG  // 取消断言
#include <assert.h>

int main()
{
    assert(2 > 1);
    assert(1 > 2);
}
```

---
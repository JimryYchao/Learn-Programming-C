## C 断言库：assert.h

断言库，在程序中关键的地方进行断言。若为非真，程序将在标准错误流输出一条适当的信息，并且使执行异常终止。
 `assert.h` 定义了宏 `assert` 和 `static_assert` 并引用了 `NDEBUG` 用于取消断言。

---
### Macro

#### NDEBUG （取消断言）

```c
#define NDEBUG
#include <assert.h> 

extern void _assert(char const* _Message, char const* _File, unsigned _Line)

#ifdef NDEBUG
    #define assert(expression) ((void)0)
#else
    #define assert(expression) (void)(
        (!!(expression)) || (_assert(#expression, __FILE__, __LINE__)), 0)
#endif   
```

如果 `NDEBUG` 在 `#include <assert.h>` 之前定义，表示取消断言。静态断言 `static_assert` 不受其影响。

```c
#define NDEBUG  // 取消断言
#include <assert.h>

int main()
{
    assert(2 > 1);
    assert(1 > 2);
}
```

<br>

#### assert （断言宏）

```c
void assert(scalar-Expression); // scalar 表示表达式必须具有标量类型
```

`assert` 执行时如果表达式为 `false`，则 `assert` 将有关失败的特定调用信息输出到标准错误流，然后调用 `abort` 函数。

```c
#include <assert.h>
assert(1 > 2); // Assertion failed!
```

<br>

#### static_assert （静态断言宏）

```c
#define static_assert(expression, message) _Static_assert(expression, message)
```

静态断言在编译时对表达式断言判断。

```c
#include <assert.h>
static_assert(1 > 2, "Assertion failed!");
```

---
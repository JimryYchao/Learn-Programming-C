### C 断言库：assert.h

 断言库，在程序中关键的地方进行断言。若为非真，程序将在标准错误流输出一条适当的信息，并且使执行异常终止

 `assert.h` 定义了宏 `assert` 和 `static_assert` 并引用了 `NDEBUG` 用于取消断言

---
#### *macro*

```c
extern void _assert(char const* _Message, char const* _File, unsigned _Line)

#ifdef NDEBUG      // NDEBUG 取消断言
    #define assert(expression) ((void)0)
#else
    #assert(expression) (void)(
        (!!(expression)) || (_assert(#expression, __FILE__, __LINE__)), 0)
#endif

#define static_assert(expression, message) _Static_assert(expression, message)
```

---
#### *Test*

```c
#include <stdio.h>
// #define NDEBUG    // 取消断言库诊断

#include <assert.h>
#define ASSERT_FAILED "assert failed."

int test(void)
{
    puts("========== assert.h ==========");
    assert(1 == 1);
    assert(1 > 2);

    static_assert(1 == 1, ASSERT_FAILED);
    static_assert(1 > 2, ASSERT_FAILED);  // 静态断言不受 NDEBUG 宏影响
}
```
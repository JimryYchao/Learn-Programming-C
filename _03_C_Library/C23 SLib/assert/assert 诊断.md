## C 诊断：assert.h

断言库，在程序中关键的地方进行断言。

`assert.h` 定义了宏 `assert` 和 `static_assert` 并引用了 `NDEBUG` 用于取消断言。C23 起，`static_assert` 作为关键字从 `assert.h` 中移除。

>---
### 断言

| Specifier | Description |
| :-------- |:--|
|`assert`|程序执行时断言，失败时（`expr == false`）调用 `abort()` 异常终止程序。|
|`static_assert`|静态断言，断言失败则无法编译。|

```c
#include <assert.h>
assert(1 > 2); 
// Assertion failed!

static_assert(1 > 2, "Assertion failed!");  // 静态断言失败，无法通过编译
```

C23 起，`static_assert` 将作为关键字从 `assert.h` 中移除。

```c
static_assert( scalar-expression );
static_assert( scalar-expression, string-literal );
```

>---
### 取消断言: NDEBUG

如果在 `#include <assert.h>` 之前定义宏  `NDEBUG`，则表示取消断言。宏 `assert` 被简单地定义为 `assert(...) ((void)0)`。静态断言 `static_assert` 不受 `NDEBUG` 影响。

```c
#define NDEBUG  // 取消断言
#include <assert.h>

int main()
{
    assert(2 > 1);  
    assert(1 > 2);  // no assertion, pass
}
```

---
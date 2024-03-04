## C 布尔定义（Boolean type and values）：stdbool.h

`stdbool` 定义了布尔类型的宏和值。C23 起仅提供一个过时的宏定义 `__bool_true_false_are_defined  1`。

---
### Macros

```c
#define bool _Bool

#define true  1
#define false 0

#define __bool_true_false_are_defined 1
```

（C23 前）`true` 和 `false` 的类型为 `int` 而非 `_Bool`，程序可以解除定义，且可以在之后重新定义 `bool`、`true`、`false`。
（C23 起）`true`、`false`、`bool` 作为 C 关键字。`true` 与 `false` 的类型为 `bool`，`stdbool.h` 可能会被移除。`__bool_true_false_are_defined` 已过时。

---
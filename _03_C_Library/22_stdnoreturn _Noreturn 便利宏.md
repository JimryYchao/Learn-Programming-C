## C _Noreturn 便利宏：stdnoreturn.h

`stdnoreturn.h` 定义了 `_Noreturn` 的便利宏。

---
### Macro

#### noreturn

```c
#define noreturn _Noreturn
```

- 宏 `noreturn` 将在 C23 弃用，`_Noreturn` 函数说明符被弃用，应该用 `[[noreturn]]` 属性代替。

---
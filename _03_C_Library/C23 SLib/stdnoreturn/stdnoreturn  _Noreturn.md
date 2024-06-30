## C _Noreturn 便利宏：stdnoreturn.h

`stdnoreturn.h` 定义了 `_Noreturn` 的便利宏。C23 起，`noreturn` 和 `stdnoreturn` 是过时的特性。

宏 `noreturn` 将作为 C 关键字，`_Noreturn` 函数说明符被弃用，应该用 `[[noreturn]]` 属性代替。

```c
[[noreturn]] void abort(void);
```

---
## C 校验整数算数：stdckdint.h

`<stdckdint.h>` 定义了几个用于执行校验整数算术的宏。

>---
### 校验整数操作类型

```c
bool ckd_add(type1 *result, type2 a, type3 b);
bool ckd_sub(type1 *result, type2 a, type3 b);
bool ckd_mul(type1 *result, type2 a, type3 b);
```

这些类型泛型宏对 a 和 b 的数学值进行加法、减法或乘法，将运算结果存储在 `*result` 中。每个操作都像两个操作数都以具有无限范围的有符号整数类型表示一样执行，然后将结果从该整数类型转换为 `type1`。

`type2` 和 `type3` 都应该是除 “普通” `char`、`bool`、位精确整数类型或枚举类型以外的任何整数类型，它们可能相同，也可能不同。`*result` 应为除 “普通” `char`、`bool`、位精确整数类型或枚举类型以外的任何整数类型的可修改左值。

如果这些类型泛型宏返回 `false`，则分配给 `*result` 的值将正确表示操作的数学结果。否则，这些类型泛型宏将返回 `true`。

---
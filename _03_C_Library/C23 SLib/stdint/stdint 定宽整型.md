## C 定宽整数类型：stdint.h


`stdint.h` 定义了具有指定宽度的整数类型，和相应的宏集合。也包含一些其他标准头文件中类型对应的整型的限制。

类型定义一般分为：
  - 具有一定精度宽度的整型（`intN_t`）；
  - 至少具有某些指定宽度的整型（`int_leastN_t`）；
  - 至少具有特定宽度的最快整数类型（`int_fastN_t`）；
  - 整数类型的宽度足以容纳指向对象的指针（`intptr_t`）；
  - 具有最大宽度的整型（`intmax_t`）。

>---
### int types

| Specifier                                                             | Description              |
| :-------------------------------------------------------------------- | :----------------------- |
| `intptr_t`, `uintptr_t`                                               | 保存对象指针的整数类型。 |
| `intmax_t`, `uintmax_t`                                               | 最大宽度整数类型。       |
| `int8_t`, `int16_t`, `int32_t`, `int64_t`                             | 有符号定宽整数类型。     |
| `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`                         | 无符号定宽整数类型。     |
| `int_least8_t`, `int_least16_t`, `int_least32_t`, `int_least64_t`     | 有符号最小宽度整数类型。 |
| `uint_least8_t`, `uint_least16_t`, `uint_least32_t`, `uint_least64_t` | 无符号最小宽度整数类型。 |
| `int_fast8_t`, `int_fast16_t`, `int_fast32_t`, `int_fast64_t`         | 有符号最快最小宽度整型。 |
| `uint_fast8_t`, `uint_fast16_t`, `uint_fast32_t`, `uint_fast64_t`     | 无符号最快最小宽度整型。 |

>---
### 整数类型的宽度

| Specifier                               | Description                        |
| :-------------------------------------- | :--------------------------------- |
| `INTN_WIDTH`, `UINTN_WIDTH`             | 正宽度整数类型的宽度。             |
| `INT_LEASTN_WIDTH`, `UINT_LEASTN_WIDTH` | 最小宽度整数类型的宽度。           |
| `INT_FASTN_WIDTH`, `UINT_FASTN_WIDTH`   | 最快的最小宽度整数类型的宽度。     |
| `INTPTR_WIDTH`, `UINTPTR_WIDTH`         | 能够容纳对象指针的整数类型的宽度。 |
| `INTMAX_WIDTH`, `UINTMAX_WIDTH`         | 最大宽度整数类型的宽度。           |
| `PTRDIFF_WIDTH`                         | `ptrdiff_t` 类型的宽度。           |
| `SIG_ATOMIC_WIDTH`                      | `sig_atomic_t` 类型的宽度。        |
| `SIZE_WIDTH`                            | `size_t` 类型的宽度。              |
| `WCHAR_WIDTH`                           | `wchar_t` 类型的宽度。             |
| `WINT_WIDTH`                            | `wint_t` 类型的宽度。              |


>---
### 整型常量的宏

| Specifier                                                                                    | Description              |
| :------------------------------------------------------------------------------------------- | :----------------------- |
| <code>INT*N*_C</code>, <code>UINT*N*_C</code>                                                | 最小宽度整数常量的函数宏 |
| `INTMAX_C`, `UINTMAX_C`                                                                      | 最大宽度整数常量的函数宏 |
| <code>INT*N*_MIN</code>, <code>INT*N*_MAX</code>, <code>UINT*N*_MAX</code>                   | 精确宽度整型的限制       |
| <code>INT_LEAST*N*_MIN</code>, <code>INT_LEAST*N*_MAX</code>, <code>UINT_LEAST*N*_MAX</code> | 最小宽度整型限制         |
<code>INT_FAST*N*_MIN</code>, <code>INT_FAST*N*_MAX</code>, <code>UINT_FAST*N*_MAX</code>  | 最快最小宽度整型限制
<code>INTPTR_MIN</code>, <code>INTPTR_MAX</code>, <code>UINTPTR_MAX</code> | 保存指针的整型限制
<code>INTMAX_MIN</code>, <code>INTMAX_MAX</code>, <code>UINTMAX_MAX</code>  | 最大宽度整型限制
| `PTRDIFF_MIN`, `PTRDIFF_MAX`                         | `ptrdiff_t` 类型限制。           |
| `SIG_ATOMIC_MIN`, `SIG_ATOMIC_MAX`                      | `sig_atomic_t` 类型限制。        |
| `SIZE_MAX`                            | `size_t` 类型限制。              |
| `WCHAR_MIN`, `WCHAR_MAX`                           | `wchar_t` 类型限制。             |
| `WINT_MIN`, `WINT_MAX`                            | `wint_t` 类型限制。              |

---

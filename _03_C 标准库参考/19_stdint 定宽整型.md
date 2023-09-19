## C 定宽整数类型（Integer types）：stdint.h

`stdint.h` 定义了具有指定宽度的整数类型，和相应的宏集合。也包含一些其他标准头文件中类型对应的整型的限制。

---
### Types

类型定义一般分为：
  - 具有一定精度宽度的整型（`intN_t`）；
  - 至少具有某些指定宽度的整型（`int_leastN_t`）；
  - 至少具有特定宽度的最快整数类型（`int_fastN_t`）；
  - 整数类型的宽度足以容纳指向对象的指针（`intptr_t`）；
  - 具有最大宽度的整型（`intmax_t`）。

在以下描述中，符号 $N$ 表示无前导零的无符号十进制整数（一般为 8，16，32，64... 表示整型的宽度）。

#### 精确宽度整型：int $N$ _t、uint$N$_t

```c
// 有符号定宽整数类型
typedef signed char          int8_t;
typedef short                int16_t;
typedef int                  int32_t;
typedef long long            int64_t;
// 无符号定宽整数类型  
typedef unsigned char        uint8_t;
typedef unsigned short       uint16_t;
typedef unsigned int         uint32_t;
typedef unsigned long long   uint64_t; 
```

<br>

#### 最小宽度整型：int_least$N$_t、uint_least$N$_t

```c
// 有符号最小宽度整数类型
typedef signed char          int_least8_t;
typedef short                int_least16_t;
typedef int                  int_least32_t;
typedef long long            int_least64_t;
// 无符号最小宽度整数类型
typedef unsigned char        uint_least8_t;
typedef unsigned short       uint_least16_t;
typedef unsigned int         uint_least32_t;
typedef unsigned long long   uint_least64_t;
```

<br>

#### 最快的最小宽度整型：int_fast$N$_t、uint_fast$N$_t

```c
// 有符号最快最小宽度整型
typedef signed char          int_fast8_t;
typedef int                  int_fast16_t;
typedef int                  int_fast32_t;
typedef long long            int_fast64_t;
// 无符号最快最小宽度整型
typedef unsigned char        uint_fast8_t;
typedef unsigned int         uint_fast16_t;
typedef unsigned int         uint_fast32_t;
typedef unsigned long long   uint_fast64_t;
```

<br> 

#### 保存对象指针的整数类型：intptr_t、uintptr_t

```c
typedef long long            intptr_t;
typedef unsigned long long   uintptr_t;
```

- 任何有效指向 `void` 的指针都可以转换成 `intptr_t` 或 `uintptr_t` 类型，然后在转换成指向 `void` 的指针，结果与原始指针相等。

#### 最大宽度整数类型：intmax_t、uintmax_t

```c
typedef long long            intmax_t;
typedef unsigned long long   uintmax_t;
```

---
### Macros：不同类型整型对应的限制

#### 精确宽度整型的限制：INT$N$_MIN、INT$N$_MAX、UINT$N$_MAX

```c
#define INT8_MIN         (-127 - 1)
#define INT16_MIN        (-32767 - 1)
#define INT32_MIN        (-2147483647 - 1)
#define INT64_MIN        (-9223372036854775807LL - 1)

#define INT8_MAX         127
#define INT16_MAX        32767
#define INT32_MAX        2147483647
#define INT64_MAX        9223372036854775807LL

#define UINT8_MAX        0xff
#define UINT16_MAX       0xffff
#define UINT32_MAX       0xffffffff
#define UINT64_MAX       0xffffffffffffffff
```

<br>

#### 最小宽度整型限制：INT_LEAST$N$_MIN、INT_LEAST$N$_MAX、UINT_LEAST$N$_MAX

```c
#define INT_LEAST8_MIN   INT8_MIN
#define INT_LEAST16_MIN  INT16_MIN
#define INT_LEAST32_MIN  INT32_MIN
#define INT_LEAST64_MIN  INT64_MIN

#define INT_LEAST8_MAX   INT8_MAX
#define INT_LEAST16_MAX  INT16_MAX
#define INT_LEAST32_MAX  INT32_MAX
#define INT_LEAST64_MAX  INT64_MAX

#define UINT_LEAST8_MAX  UINT8_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_LEAST64_MAX UINT64_MAX
```

<br>

#### 最快最小宽度整型限制：INT_FAST$N$_MIN、INT_FAST$N$_MAX、UINT_FAST$N$_MAX

```c
#define INT_FAST8_MIN    INT8_MIN
#define INT_FAST16_MIN   INT32_MIN
#define INT_FAST32_MIN   INT32_MIN
#define INT_FAST64_MIN   INT64_MIN

#define INT_FAST8_MAX    INT8_MAX
#define INT_FAST16_MAX   INT32_MAX
#define INT_FAST32_MAX   INT32_MAX
#define INT_FAST64_MAX   INT64_MAX

#define UINT_FAST8_MAX   UINT8_MAX
#define UINT_FAST16_MAX  UINT32_MAX
#define UINT_FAST32_MAX  UINT32_MAX
#define UINT_FAST64_MAX  UINT64_MAX
```

#### 保存指针的整型限制：INTPTR_MIN、INTPTR_MAX、UINTPTR_MAX

```c
#define INTPTR_MIN   INT64_MIN
#define INTPTR_MAX   INT64_MAX
#define UINTPTR_MAX  UINT64_MAX
```

#### 最大宽度整型限制：INTMAX_MIN、INTMAX_MAX、UINTMAX_MAX

```c
#define INTMAX_MIN       INT64_MIN
#define INTMAX_MAX       INT64_MAX
#define UINTMAX_MAX      UINT64_MAX
```

---
### Macros：其他整型限制

#### ptrdiff_t 的限制

```c
#define PTRDIFF_MIN      INTPTR_MIN
#define PTRDIFF_MAX      INTPTR_MAX
```

<br>

#### sig_atomic_t 的限制

```c
#define SIG_ATOMIC_MIN   INT32_MIN
#define SIG_ATOMIC_MAX   INT32_MAX
```

<br>

#### size_t 的限制

```c
#define SIZE_MAX    0xffffffffffffffffULL
```

<br>

#### wchar_t 的限制

```c
#define WCHAR_MIN        0x0000
#define WCHAR_MAX        0xffff
```

<br>

#### wint_t 的限制

```c
#define WINT_MIN         0x0000
#define WINT_MAX         0xffff
```

---
### Macros-Functions：用于整型常量的宏

#### 最小宽度整数常量的函数宏：INT*N*_C、UINT*N*_C

```c
#define INT8_C(x)    (x)
#define INT16_C(x)   (x)
#define INT32_C(x)   (x)
#define INT64_C(x)   (x ## LL)

#define UINT8_C(x)   (x)
#define UINT16_C(x)  (x)
#define UINT32_C(x)  (x ## U)
#define UINT64_C(x)  (x ## ULL)
```

- 这些宏展开成拥有其对应的最小宽度整数常量表达式，例如 `UINT64_C(0x123)` 可能扩展为 `0x123ULL`。

<br>

#### 最大宽度整数常量的函数宏：INTMAX_C、UINTMAX_C

```c
#define INTMAX_C(x)  INT64_C(x)
#define UINTMAX_C(x) UINT64_C(x)
```

- 这些宏展开成拥有其参数指定的值和 `intmax_t` / `uintmax_t` 类型的整数常量表达式。

---
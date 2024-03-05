## C 定宽整数类型（Integer types）：stdint.h

```c
#define  __STDC_VERSION_STDINT_H__      202311L
```

`stdint.h` 定义了具有指定宽度的整数类型，和相应的宏集合。也包含一些其他标准头文件中类型对应的整型的限制。

类型定义一般分为：
  - 具有一定精度宽度的整型（`intN_t`）；
  - 至少具有某些指定宽度的整型（`int_leastN_t`）；
  - 至少具有特定宽度的最快整数类型（`int_fastN_t`）；
  - 整数类型的宽度足以容纳指向对象的指针（`intptr_t`）；
  - 具有最大宽度的整型（`intmax_t`）。

---
### Types



在以下描述中，符号 $N$ 表示无前导零的无符号十进制整数（一般为 8，16，32，64... 表示整型的宽度）。

#### 精确宽度整型：int*N*_t、uint*N*_t

`typedef` 名称 <code>int<em>N</em>_t</code> 指定了一个宽度为 *N* 且没有填充位的有符号整数类型。例如 `int8_t` 表示这样一个有符号整数类型，宽度正好为 8 位。

`typedef` 名称 <code>uint<em>N</em>_t</code> 指定了一个宽度为 *N* 且没有填充位的无符号整数类型。例如 `uint24_t` 表示这样一个无符号整数类型，宽度正好为 24 位。

如果一个实现提供了具有特定宽度且没有填充位的标准或扩展整数类型，它应该定义相应的 `typedef` 名称。

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

>---

#### 最小宽度整型：int_least*N*_t、uint_least*N*_t

`typedef` 名称 <code>int_least<em>N</em>_t</code> 指定一个宽度至少为 *N* 的有符号整数类型。因此，`int_least32_t` 表示具有至少 32 位的宽度的有符号整数类型。

`typedef` 名称 <code>uint_least<em>N</em>_t</code> 指定一个宽度至少为 *N* 的无符号整数类型。因此，`uint_least16_t` 表示具有至少 16 位的宽度的无符号整数类型。

如果定义了 `typedef` 名称 <code>int<em>N</em>_t</code>，则 <code>int_least<em>N</em>_t</code> 指定相同的类型。如果定义了 `typedef` 名称 <code>uint<em>N</em>_t</code>，则 <code>uint_least<em>N</em>_t</code> 指定相同的类型。

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

>---

#### 最快的最小宽度整型：int_fast*N*_t、uint_fast*N*_t

以下每种类型都指定了一种整数类型，在所有至少具有指定宽度的整数类型中，该类型通常是操作速度最快的。

`typedef` 名称 <code>int_fast<em>N</em>_t</code> 指定最快的有符号整数类型，其宽度至少为 *N*。`typedef` 名称 <code>uint_fast<em>N</em>_t</code> 指定最快的无符号整数类型，其宽度至少为 *N*。

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

>--- 

#### 保存对象指针的整数类型：intptr_t、uintptr_t

```c
typedef long long            intptr_t;
typedef unsigned long long   uintptr_t;
```

`intptr_t` 指定了一个有符号整数类型；`uintptr_t` 指定了一个有符号整数类型。均非位精确整数类型。任何有效指向 `void` 的指针都可以转换成 `intptr_t` 或 `uintptr_t` 类型，然后在转换成指向 `void` 的指针，结果与原始指针相等。

#### 最大宽度整数类型：intmax_t、uintmax_t

```c
typedef long long            intmax_t;
typedef unsigned long long   uintmax_t;
```

`intmax_t` 指定了一个有符号整数类型，而不是位精确整数类型，能够表示任何有符号整数类型的任何值。可能的例外是有符号位精确整数类型和比 `long long` 宽的有符号扩展整数类型，并且由类型定义引用为精确宽度整数类型。

`uintmax_t` 是与 `intmax_t` 相对于的无符号整数类型。

---
### Macros：特定宽度整数类型的宽度

以下的类对象宏指定在 `stdint.h` 中声明的类型的宽度，每个宏名对应其相似的类型名。任何已定义宏的每个实例都应替换为适合在 `#if` 预处理指令中常用的常量表达式。其实现定义的值应等于或大于下面预给出的值，除非声明恰好是给定值。一个实现应该只定义与它实际定义的 `typedef` 名称相对应的宏。

```c
// 正宽度整数类型的宽度
#define INTN_WIDTH      exactly N
#define UINTN_WIDTH     exactly N

// 最小宽度整数类型的宽度
#define INT_LEASTN_WIDTH      exactly UINT_LEASTN_WIDTH
#define UINT_LEASTN_WIDTH     N

// 最快的最小宽度整数类型的宽度
#define INT_FASTN_WIDTH       exactly UINT_FASTN_WIDTH
#define UINT_FASTN_WIDTH      N

// 能够容纳对象指针的整数类型的宽度
#define INTPTR_WIDTH          exactly UINTPTR_WIDTH
#define UINTPTR_WIDTH         16

// 最大宽度整数类型的宽度
#define INTMAX_WIDTH          exactly UINTMAX_WIDTH
#define UINTMAX_WIDTH         64
```

---
### Macros：其他整数类型的宽度

下面的类对象宏指定了与其他标准头中定义的类型相对应的整数类型的宽度。这些宏的每一个实例都应该用一个适合在 `#if` 预处理指令中使用的常量表达式来替换。其实现定义的值应等于或大于以下预给出的相应值。一个实现应该只定义与它实际提供的 `typedef` 名称相对应的宏。

```c
#define PTRDIFF_WIDTH       16    // ptrdiff_t
#define SIG_ATOMIC_WIDTH    8     // sig_atomic_t
#define SIZE_WIDTH          16    // size_t
#define WCHAR_WIDTH         8     // wchar_t
#define WINT_WIDTH          16    // wint_t
```

---
### Macros-Functions：整型常量的宏

下面的类函数宏扩展为适合于初始化对象的整数常量，这些对象具有与 `stdint.h` 中定义的类型对应的整数类型。每个宏名称对应于其类似的类型名称。

这些宏的任何实例中的参数都应该是一个无后缀的整数常量，其值不超过相应类型的限制。

每次调用其中一个宏都将扩展为一个整数常量表达式。表达式的类型应与根据整数提升转换的相应类型的表达式具有相同的类型。表达式的值应为参数的值。如果该值在类型 `intmax_t`（对于有符号类型）或类型 `uintmax_t`（对于无符号类型）的范围内，则该表达式适用于条件表达式包含预处理指令。

>---
#### 最小宽度整数常量的函数宏：INT*N*_C、UINT*N*_C

宏 <code>INT<em>N</em>_C(value)</code> 扩展为与 <code>int_least<em>N</em>_t</code> 类型对应的整数常量表达式。宏 <code>UINT<em>N</em>_C(value)</code> 扩展为与 <code>uint_least<em>N</em>_t</code> 类型对应的整数常量表达式。例如，如果 `uint_least64_t` 是 `unsigned long long int` 类型的名称，则 `UINT64_C(0x123)` 可以扩展为整数常量 `0x123`。

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

>---

#### 最大宽度整数常量的函数宏：INTMAX_C、UINTMAX_C

这些宏展开成拥有其参数指定的值和 `intmax_t` / `uintmax_t` 类型的整数常量表达式。

```c
#define INTMAX_C(x)  INT64_C(x)
#define UINTMAX_C(x) UINT64_C(x)
```

---
### Macros：整数类型的最大和最小值

#### 精确宽度整型的限制：INT*N*_MIN、INT*N*_MAX、UINT*N*_MAX

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

>---

#### 最小宽度整型限制：INT_LEAST*N*_MIN、INT_LEAST*N*_MAX、UINT_LEAST*N*_MAX

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

>---

#### 最快最小宽度整型限制：INT_FAST*N*_MIN、INT_FAST*N*_MAX、UINT_FAST*N*_MAX

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

>---

#### 保存指针的整型限制：INTPTR_MIN、INTPTR_MAX、UINTPTR_MAX

```c
#define INTPTR_MIN       INT64_MIN
#define INTPTR_MAX       INT64_MAX
#define UINTPTR_MAX      UINT64_MAX
```

>---

#### 最大宽度整型限制：INTMAX_MIN、INTMAX_MAX、UINTMAX_MAX

```c
#define INTMAX_MIN       INT64_MIN
#define INTMAX_MAX       INT64_MAX
#define UINTMAX_MAX      UINT64_MAX
```

>---

#### 其他整数类型的限制

```c
// ptrdiff_t
#define PTRDIFF_MIN      INTPTR_MIN
#define PTRDIFF_MAX      INTPTR_MAX

// sig_atomic_t
#define SIG_ATOMIC_MIN   INT32_MIN
#define SIG_ATOMIC_MAX   INT32_MAX

// size_t
#define SIZE_MAX    0xffffffffffffffffULL

// wchar_t
#define WCHAR_MIN        0x0000
#define WCHAR_MAX        0xffff

// wint_t
#define WINT_MIN         0x0000
#define WINT_MAX         0xffff
```

---

## C 整数类型限制（Sizes of integer types）：limits.h

`limits.h` 定义了一些宏，可以拓展为标准整数类型的各种限制和参数。

---
### Macros：Type

#### MB_LEN_MAX

```c
#define MB_LEN_MAX    5
```

- 该宏扩展到任意多字节字符可具有的最大字节长度。

#### char

```c
#define CHAR_BIT      8
#define SCHAR_MIN   (-128)      // signed char
#define SCHAR_MAX     127       // signed char
#define UCHAR_MAX     0xff      // unsigned char

#ifndef _CHAR_UNSIGNED   // 是否允许 char 保存负值
    #define CHAR_MIN    SCHAR_MIN
    #define CHAR_MAX    SCHAR_MAX
#else
    #define CHAR_MIN    0
    #define CHAR_MAX    UCHAR_MAX
#endif
```

<br> 

#### short int

```c
#define SHRT_MIN    (-32768)    // signed short
#define SHRT_MAX      32767     // signed short
#define USHRT_MAX     0xffff    // unsigned short
```

<br>

#### int

```c
#define INT_MIN     (-2147483647 - 1)
#define INT_MAX       2147483647
#define UINT_MAX      0xffffffff
```

<br>

#### long int

```c
#define LONG_MIN    (-2147483647L - 1)
#define LONG_MAX      2147483647L
#define ULONG_MAX     0xffffffffUL
```

<br>

#### long long int

```c
#define LLONG_MAX     9223372036854775807LL
#define LLONG_MIN   (-9223372036854775807LL - 1)
#define ULLONG_MAX    0xffffffffffffffffULL
```

---
### Macros：Integer

```c
#define _I8_MIN     (-127 - 1)
#define _I8_MAX       127
#define _UI8_MAX      0xffu

#define _I16_MIN    (-32767 - 1)
#define _I16_MAX      32767
#define _UI16_MAX     0xffffu

#define _I32_MIN    (-2147483647 - 1)
#define _I32_MAX      2147483647
#define _UI32_MAX     0xffffffffu

#define _I64_MIN    (-9223372036854775807LL - 1)
#define _I64_MAX      9223372036854775807LL
#define _UI64_MAX     0xffffffffffffffffuLL

#ifndef SIZE_MAX     // 最大本机整数大小
    #ifdef _WIN64
        #define SIZE_MAX  _UI64_MAX
    #else
        #define SIZE_MAX  _UINT_MAX
    #endif
#endif

#define RSIZE_MAX    (SIZE_MAX >> 1)   // 最大安全库整数大小
```

---
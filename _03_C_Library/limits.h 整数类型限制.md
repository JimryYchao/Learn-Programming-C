## C 整数类型限制（Sizes of integer types）：limits.h

```c
#define __STDC_VERSION_LIMITS_H__       202311L
```

`limits.h` 定义了一些宏，可以扩展为标准整数类型的各种限制和参数。

---
### Macros

以下给出的宏的值应替换为适用于条件表达式包含预处理指令的常量表达式。它们的实现定义值应等于或大于所示值。

>---
#### 整数类型的宽度

```c
#define BOOL_WIDTH      1     // bool    
#define CHAR_BIT        8     // 非位域的最小对象的位数（字节）

#define UCHAR_WIDTH     CHAR_BIT        // unsigned char
#define SCHAR_WIDTH     CHAR_BIT        // signed char 
#define CHAR_WIDTH      CHAR_BIT        // char 

#define USHRT_WIDTH     16              // unsigned short
#define SHRT_WIDTH      USHRT_WIDTH     // short

#define UINT_WIDTH      16              // unsigned int
#define INT_WIDTH       UINT_WIDTH      // int

#define ULONG_WIDTH     32              // unsigned long 
#define LONG_WIDTH      ULONG_WIDTH     // long

#define ULLONG_WIDTH    64              // unsigned long long
#define LLONG_WIDTH     ULLONG_WIDTH    // long long

#define BITINT_MAXWIDTH ULLONG_WIDTH    // _BitInt(N), 至少为 ULLONG_WIDTH

#define MB_LEN_MAX      1       // 对于任何支持的区域设置，多字节字符中的最大字节数
```

>---
#### 整数类型的范围限制

```c
#define BOOL_MAX        1       // 2 ^ BOOL_WIDTH − 1

#define UCHAR_MAX       255         // 2 ^ UCHAR_WIDTH − 1
#define SCHAR_MAX       +127        // 2 ^ (SCHAR_WIDTH−1) − 1
#define SCHAR_MIN       -128        // −2 ^ (SCHAR_WIDTH−1)
#define CHAR_MAX        UCHAR_MAX or SCHAR_MAX
#define CHAR_MIN        0 or SCHAR_MIN

#define USHRT_MAX       65535       // 2 ^ USHRT_WIDTH − 1
#define SHRT_MAX        +32767      // 2 ^ (SHRT_WIDTH−1) − 1
#define SHRT_MIN        -32768      // −2 ^ (SHRT_WIDTH−1)

#define UINT_MAX        65535       // 2 ^ UINT_WIDTH − 1
#define INT_MAX         +32767      // 2 ^ (INT_WIDTH−1) − 1
#define INT_MIN         -32768      // −2 ^ (INT_WIDTH−1)

#define ULONG_MAX       4294967295      // 2 ^ ULONG_WIDTH − 1
#define LONG_MAX        +2147483647     // 2 ^ (LONG_WIDTH−1) − 1
#define LONG_MIN        -2147483648     // −2 ^ (LONG_WIDTH−1)

#define ULLONG_MAX      18446744073709551615 // 2 ^ ULLONG_WIDTH − 1
#define LLONG_MAX       +9223372036854775807 // 2 ^ (LLONG_WIDTH−1) − 1
#define LLONG_MIN       -9223372036854775808 // −2 ^ (LLONG_WIDTH−1)
```

---
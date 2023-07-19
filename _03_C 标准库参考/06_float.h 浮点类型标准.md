## [C 浮点类型标准：float.h](./clib-test/s_float.h)

`float.h` 定义了一些有关浮点类型的各种限制和参数的宏常量。

---
### Macros

#### 浮点数的底（整数基）

三种浮点数类型的底。

```c
#define FLT_RADIX  2
```

<br>

#### 浮点数精度

- 浮点数序列化/反序列化所需的十进制精度。

```c
#define DECIMAL_DIG
#define FLT_DECIMAL_DIG
#define DBL_DECIMAL_DIG
#define LDBL_DECIMAL_DIG
```

- 十进制数的浮点数可以被舍入到浮点表示形式并返回到十进制，而不会丢失精度的位数。

```c
#define FLT_DIG
#define DBL_DIG
#define LDBL_DIG
```

- 浮点数所能表示而不损精度的，浮点尾数中的以 `FLT_RADIX` 为底的有效位数。

```c
#define FLT_MANT_DIG
#define DBL_MANT_DIG
#define LDBL_MANT_DIG
```

<br>

#### 一些浮点数的值表示范围限定

- 最小归一化正浮点数。

```c
#define FLT_MIN
#define DBL_MIN
#define LDBL_MIN
```

- 最大可表示的浮点数。

```c
#define FLT_MAX
#define DBL_MAX
#define LDBL_MAX
```

- 最小正值。

```c
#define FLT_TRUE_MIN
#define DBL_TRUE_MIN
#define LDBL_TRUE_MIN
```

- 最小正数 x，以便 `x + 1.0` 不等于 1.0。

```c
#define FLT_EPSILON
#define DBL_EPSILON
#define LDBL_EPSILON
```

<br>

#### 一些浮点数的幂指数限定

- 以 FLT_RADIX 为底的某个数字的幂是一个可表示的浮点数的最大整数。

```c
#define FLT_MAX_EXP
#define DBL_MAX_EXP
#define LDBL_MAX_EXP
```

- 以 FLT_RADIX 为底的某个数字的幂是一个可表示的浮点数的最小负整数。

```c
#define FLT_MIN_EXP
#define DBL_MIN_EXP
#define LDBL_MIN_EXP
```

- 以 10 为底的某个数字的幂是一个可表示的浮点数的最大整数。

```c
#define FLT_MAX_10_EXP
#define DBL_MAX_10_EXP
#define LDBL_MAX_10_EXP
```

- 以 10 为底的某个数字的幂是一个可表示的浮点数的最小负整数。

```c
#define FLT_MIN_10_EXP
#define DBL_MIN_10_EXP
#define LDBL_MIN_10_EXP
```

<br>

#### 其他宏常量表示

- 当前浮点算数的舍入模式

```c
#define FLT_ROUNDS 
/*
    -1   默认舍入方向未知
    0    向零舍入    FE_TOWARDZERO
    1    向最近值    FE_TONEAREST
    2    向正无穷大  FE_UPWARD
    3    向负无穷大  FE_DOWNWARD
    other    实现定义行为
*/
```

- 浮点算数的中间结果所用的扩展精度

```c
#define FLT_EVAL_METHOD 
/*
    0    表示不使用
    1    表示用 double 代替 float
    2    表示用 long double
*/
```

- 类型是否支持非正规数

```c
#define FLT_HAS_SUBNORM
#define DBL_HAS_SUBNORM
#define LDBL_HAS_SUBNORM
/*
    -1   表示不确定
    0    表示不支持
    1    表示支持
*/
```

---
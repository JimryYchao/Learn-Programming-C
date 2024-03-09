## C 浮点类型标准（Characteristics of floating types）：float.h

```c
#define __STDC_VERSION_FLOAT_H__        202311L 
```

`float.h` 定义了一些有关实浮点类型（包括十进制浮点数，标准浮点数）的各种限制和参数的宏常量。头文件中的所有整数值（`FLT_ROUNDS` 除外）都应是适用于条件表达式包含预处理指令的常量表达式

> 一个浮点数由以下模型定义，即 ISO/IEC 60559 格式

- $x = sb^e \sum_{k =1}^p f_k b^{-k}$，$e_{min} \leq e \leq e_{max}$
  - $s$：符号位（$\pm 1$）
  - $b$：指数表示的基数（大于 1 的整数）
  - $e$：指数（介于最小 $e_{min}$ 和 $e_{max}$ 之间的整数）
  - $p$：精度（以 $b$ 为基数的有效位数）
  - $f_k$：小于 $b$ 的非负整数（有效位数）

---
### Macros：标准浮点类型

>---
#### FLT_ROUNDS

标准浮点类型的浮点加法的舍入模式的特征是实现定义的 `FLT_ROUNDS` 值。可以通过 `fenv.h` 中的 `fesetround` 更改舍入模式，并通过 `FLT_ROUNDS` 反映更改。

```c
#define FLT_ROUNDS 
/*
    -1   无法确定
    0    向零舍入    FE_TOWARDZERO
    1    向最近值    FE_TONEAREST
    2    向正无穷大  FE_UPWARD
    3    向负无穷大  FE_DOWNWARD
    4    向远离零方向最接近可表示值舍入  FE_TONEARESTFROMZERO
    other    实现定义行为
*/
```

```c
printf("FLT_ROUNDS = %d\n", FLT_ROUNDS);  // FLT_ROUNDS = 1
fesetround(FE_DOWNWARD);
printf("FLT_ROUNDS = %d\n", FLT_ROUNDS);  // FLT_ROUNDS = 3
```

>---
#### IS_IEC_60559

这些宏表示相应的类型是否具有与 ISO/IEC 60559 格式相同的基（$b$）、精度（$p$）和指数范围（$e_{min} ≤ e ≤ e_{max}$）。

```c
#define FLT_IS_IEC_60559        // 表示标准浮点 float 类型是否符合 60559
#define DBL_IS_IEC_60559        // 表示标准浮点 double 类型是否符合 60559
#define LDBL_IS_IEC_60559       // 表示标准浮点 long double 类型是否符合 60559
/*
    0    类型没有 ISO/IEC 60559 格式的精度和指数范围
    1    类型具有 ISO/IEC 60559 格式的精度和指数范围
*/
```

>---
#### FLT_EVAL_METHOD

由运算符进行通常的算术转换所产生的浮点类型的值，包括由操作数的隐式转换产生的值，以及浮点常量的值，被计算为范围和精度可能大于类型所需的格式。这种格式称为求值格式。在所有情况下，赋值和强制转换运算符都以类型的格式生成值。求值格式的使用程度由 `FLT_EVAL_METHOD` 的值表示。

```c
#define FLT_EVAL_METHOD
/*
    -1   无法确定
    0    将所有操作和常量求值到类型的范围和精度
    1    将 float 和 double 类型的操作和常量求值为 double 类型的范围和精度；
         将 long double 类型的操作和常量求值为 long double 类型的范围和精度
    2    将所有操作和常量的求值为 long double 类型的范围和精度
*/
```

>---
#### HAS_SUBNORM

这些宏的值表示类型是否支持非正规数。C23 起是一个过时的功能。

```c
#define FLT_HAS_SUBNORM         // float 是否支持非正规数
#define DBL_HAS_SUBNORM         // double 是否支持非正规数
#define LDBL_HAS_SUBNORM        // long double 是否支持非正规数
/*
    -1   无法确定
    0    类型不支持非正规数
    1    类型支持非正规数
*/
```

>---
#### Signaling NaN

```c
#define FLT_SNAN
#define DBL_SNAN
#define LDBL_SNAN
```

当前仅当相应类型包含 *signaling NaN* 时才定义，它们扩展为表示 *signaling NaN* 的相应类型的常量表达式。如果一个可选的一元 `+` 或 `-` 运算符后随一个 *signaling NaN* 宏（如 `+/- FLT_SNAN`）被用作在翻译时求值的初始化器，则用一个 *signaling NaN* 值初始化对象。

*signaling NaN* 表示为会触发异常浮点信号的 NaN，另一种非数则是 *quiet NaN*，即不会触发浮点异常信号的 NaN。

>---
#### INFINITY & NAN

```c
#define INFINITY
#define NAN
```

当且仅当实现支持 `float` 类型的无穷大时才定义 `INFINITY`。它扩展为 `float` 类型的常量表达式，表示正无穷大或无符号无穷大。

当且仅当实现支持 `float` 类型的 *quiet NaN* 时才定义 `NAN`。它扩展为 `float` 类型的常量表达式，表示 *quiet NaN*。

>---
#### 标准浮点类型的限制和特性

下列给出的值应替换为常量表达式，其实现定义的值在大小（绝对值）上大于或等于所示值，符号位相同：

```c
// 指数表示的基数，b
#define FLT_RADIX       2       

// 以 FLT_RADIX 位基数浮点有效位数，p
#define FLT_MANT_DIG
#define DBL_MANT_DIG
#define LDBL_MANT_DIG

// 将标准浮点类型的值转换为十进制小数再转换为原值时，至少需要相应类型 DECIMAL_DIG 位小数
#define FLT_DECIMAL_DIG     6
#define DBL_DECIMAL_DIG     10
#define LDBL_DECIMAL_DIG    10

/* 十进制数 n，使得在所支持的浮点类型和所支持的具有以 b 为基数 p 个位数的 ISO/IEC 60559 编码中的
最宽范围内的任何浮点数可以被舍入为具有 n 十进制数值的浮点数，并且在返回时不改变 n 的值：*/
#define DECIMAL_DIG     10    // C23 起，已过时

// 位数 q ，以便 q 十进制数的浮点数可以被舍入到浮点表示形式并返回，而不会丢失精度。
#define FLT_DIG         6
#define DBL_DIG         10
#define LDBL_DIG        10

// 最小负整数，以便 FLT_RADIX 的该数字的幂是一个可表示的浮点数
#define FLT_MIN_EXP
#define DBL_MIN_EXP
#define LDBL_MIN_EXP

// 最小负整数，以便 10 的该数字的幂是一个可表示的浮点数
#define FLT_MIN_10_EXP      -37
#define DBL_MIN_10_EXP      -37
#define LDBL_MIN_10_EXP     -37

// 最大整数，以便 FLT_RADIX 的该数字的幂是一个可表示的浮点数
#define FLT_MAX_EXP
#define DBL_MAX_EXP
#define LDBL_MAX_EXP

// 最大整数，以便 10 的该数字的幂是一个可表示的浮点数
#define FLT_MAX_10_EXP      +37
#define DBL_MAX_10_EXP      +37
#define LDBL_MAX_10_EXP     +37
```

下表中给出的值应替换为常量表达式，其实现定义的值大于或等于所示值：

```c
// 可表示的最大浮点数
#define FLT_MAX         1E+37
#define DBL_MAX         1E+37
#define LDBL_MAX        1E+37

// 最大归一化浮点数
#define FLT_NORM_MAX    1E+37
#define DBL_NORM_MAX    1E+37
#define LDBL_NORM_MAX   1E+37
```


下列给出的值应替换为常量表达式，其实现定义的（正）值在大小上小于或等于所示值：

```c
// 最小正数 x ，以便 x + 1.0 不等于 1.0
#define FLT_EPSILON     1E-5
#define DBL_EPSILON     1E-9
#define LDBL_EPSILON    1E-9

// 最小规范化正浮点数
#define FLT_MIN         1E-37
#define DBL_MIN         1E-37
#define LDBL_MIN        1E-37

// 最小可表示的正浮点数
#define FLT_TRUE_MIN    1E-37   
#define DBL_TRUE_MIN    1E-37   
#define LDBL_TRUE_MIN   1E-37   
```

---
### Macros：十进制浮点类型

下面定义有关十进制浮点类型的特性的宏（可选）当且仅当实现定义了 `__STDC_IEC_60559_DFP__` 时可用。前缀 `DEC32_`、`DEC64_`、`DEC128_` 分别表示 `_Decimal32`、`_Decimal64`、`_Decimal128` 类型。

>---
#### DEC_EVAL_METHOD

`DEC_EVAL_METHOD` 是 `FLT_EVAL_METHOD` 的十进制浮点模拟，它的实现定义的值表示了十进制浮点类型的求值格式的使用：

```c
#ifdef __STDC_IEC_60559_DFP__
#define DEC_EVAL_METHOD
#endif
/*
    -1   无法确定
    0    将所有操作和常量求值到类型的范围和精度
    1    将 _Decimal32 和 _Decimal64 类型的操作和常量求值为 _Decimal64 类型的范围和精度；
         将 _Decimal128 类型的操作和常量求值为 _Decimal128 类型的范围和精度
    2    将所有操作和常量的求值为 _Decimal128 类型的范围和精度
*/
```

>---
#### Decimal signaling NaN

```c
#define DEC32_SNAN
#define DEC64_SNAN
#define DEC128_SNAN
```

扩展为表示 *signaling NaN* 的相应类型的常量表达式。如果一个可选的一元 `+` 或 `-` 运算符后随一个 *signaling NaN* 宏（如 `+/- DEC32_SNAN`）用于初始化一个具有静态或线程存储持续时间的相同类型的对象，则该对象将使用 *signaling NaN* 值初始化对象。

*signaling NaN* 表示为会触发异常浮点信号的 NaN，另一种非数则是 *quiet NaN*，即不会触发浮点异常信号的 NaN。

>---
#### DEC_INFINITY & DEC_NAN

```c
#define DEC_INFINITY
#define DEC_NAN
```

`DEC_INFINITY` 扩展为 `_Decimal32` 类型的表示正无穷大值的常量表达式。

`DEC_NAN` 扩展为 `_Decimal32` 类型的表示 *quiet NaN* 值的常量表达式。

>---
#### 十进制浮点类型的限制和特性

下面给出的整数值应替换为适合条件表达式包含预处理指令使用的常量表达式：

```c
#ifdef __STDC_IEC_60559_DFP__

// 指数表示的基数，b = 10；对于标准浮点类型，此值是实现定义的 FLT_RADIX；
// 对于十进制浮点数，基数为 10 是固有属性

// 十进制系数的位数
#define DEC32_MANT_DIG      7
#define DEC64_MANT_DIG      16
#define DEC128_MANT_DIG     34

// 十进制最小指数
#define DEC32_MIN_EXP -94
#define DEC64_MIN_EXP -382
#define DEC128_MIN_EXP -6142

// 十进制最大指数
#define DEC32_MAX_EXP 97
#define DEC64_MAX_EXP 385
#define DEC128_MAX_EXP 6145

// 最大可表示的有限十进制浮点数（小数点后分别有 6、15 和 33 个9）
#define DEC32_MAX 9.999999E96DF
#define DEC64_MAX 9.999999999999999E384DD
#define DEC128_MAX 9.999999999999999999999999999999999E6144DL

// 最小正数 x ，以便 x + 1.0 不等于 1.0
#define DEC32_EPSILON 1E-6DF
#define DEC64_EPSILON 1E-15DD
#define DEC128_EPSILON 1E-33DL

// 最小规范化十进制浮点数
#define DEC32_MIN 1E-95DF
#define DEC64_MIN 1E-383DD
#define DEC128_MIN 1E-6143DL

// 最小可表示的正十进制浮点数
#define DEC32_TRUE_MIN 0.000001E-95DF
#define DEC64_TRUE_MIN 0.000000000000001E-383DD
#define DEC128_TRUE_MIN 0.000000000000000000000000000000001E-6143DL

#endif
```

---
## C 浮点类型标准：float.h

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

>---
### 一般 Macro 定义

`XXX_` 表示为 `FLT`，`DBL`，`LDBL`，分别表示标准浮点 `float`、`double`、`long double` 对应的宏定义。宏展开为负值时表示不确定。

| Specifier          | Description                                                                                                  | Range            |
| :----------------- | :----------------------------------------------------------------------------------------------------------- | :--------------- |
| `FLT_ROUNDS`       | 浮点舍入模式的特征值，可以通过 `fenv.h` 的 `fesetround` 更改舍入模式，并通过 `FLT_ROUNDS` 反映更改。         |
| `XXX_IS_IEC_60559` | 对应浮点类型是否具有与 ISO/IEC 60559 格式相同的基（$b$）、精度（$p$）和指数范围（$e_{min} ≤ e ≤ e_{max}$）。 | 1 表示具有       |
| `FLT_EVAL_METHOD`  | 浮点中间运算的浮点格式。                                                                                     |
| `XXX_HAS_SUBNORM`  | 对应浮点类型是否支持非正规数。（C23 起弃用）                                                                 | 0 不支持，1 支持 |
| `XXX_SNAN`         | 扩展为表示 *signaling NaN* 的相应类型的常量表达式。                                                          |
| `INFINITY`, `DEC_INFINITY`         | 扩展为 `float`（`_Decimal32`）类型的正无穷大或无符号无穷大。                                                                |
| `NAN`, `DEC_NAN`              | 扩展为 `float`（`_Decimal32`）类型的 *quiet NaN*。                                                                          |



> FLT_ROUNDS

标准浮点类型的浮点加法的舍入模式的特征是实现定义的 `FLT_ROUNDS` 值。

```c
#define FLT_ROUNDS 
/*
    -1   无法确定
    0    FE_TOWARDZERO
    1    FE_TONEAREST
    2    FE_UPWARD
    3    FE_DOWNWARD
    4    FE_TONEARESTFROMZERO
*/
```

```c
printf("FLT_ROUNDS = %d\n", FLT_ROUNDS);  // FLT_ROUNDS = 1
fesetround(FE_DOWNWARD);
printf("FLT_ROUNDS = %d\n", FLT_ROUNDS);  // FLT_ROUNDS = 3
```

> FLT_EVAL_METHOD

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

> DEC_EVAL_METHOD

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
### 标准浮点类型的限制和特性

`XXX_` 表示为 `FLT`，`DBL`，`LDBL`，分别表示标准浮点 `float`、`double`、`long double` 对应的宏定义。实现定义的值在大小（绝对值）上大于或等于 C 标准规定的值，符号位相同。

若实现了十进制浮点数 `XXX` 还可表示 `DEC32`、`DEC64`、`DEC128`，分别表示十进制浮点数 `_Decimal32`、`_Decimal64`、`_Decimal128`。

| Specifier         | Description                                        | Value |
| :---------------- | :------------------------------------------------- | :---- |
| `FLT_RADIX`       | $b$，浮点表示的指数基数。                          | 2     |
| `XXX_MANT_DIG`    | $p$, 以 `FLT_RADIX` 位基数浮点有效位数。           |
| `DECIMAL_DIG`     | 默认（双精度）十进制位数的舍入精度。（C23 起弃用） | 10    |
| `XXX_DECIMAL_DIG` | 相应类型的十进制位数的舍入精度。                   |
| `XXX_DIG`         | 相应类型的精度的小数位数。                         |
| `XXX_MIN_EXP`     | 最小二进制指数。                                   |
| `XXX_MIN_10_EXP`  | 最小十进制指数。                                   | -37   |
| `XXX_MAX_EXP`     | 最大二进制指数。                                   | +37   |
| `XXX_MAX_10_EXP`  | 最大十进制指数。                                   | -37   |
| `XXX_MIN`         | 最小规范化正浮点数。                               |
| `XXX_MAX`         | 可表示的最大浮点数。                               |
| `XXX_TRUE_MIN`    | 最小可表示的正浮点数。                             |
| `XXX_NORM_MAX`    | 最大归一化浮点数。                                 |
| `XXX_EPSILON`     | 使 $x$ + 1.0 不等于 1.0 的最小正数 $x$。           |

---
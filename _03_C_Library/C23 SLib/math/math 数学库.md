## C 数学库：math.h

`math.h` 提供了许多的数学函数，和另外两个具有相同名称但带有 f 和 l 后缀的函数命名，分别代表了 `double`、`float` 和 `long double` 的对应函数。

> defines

| Specifier                      | Description                                                                        |
| :----------------------------- | :--------------------------------------------------------------------------------- |
| `float_t`                      | 至少与 `float` 宽度相同的浮点类型                                                  |
| `double_t`                     | 至少与 `double` 宽度相同的浮点类型，且 `double_t` 类型至少与 `float_t` 宽度相同。  |
| `_Decimal32_t`、`_Decimal64_t` | 至少与 `_Decimal32` 和 `_Decimal64` 宽度相同的浮点类型                             |
| `HUGE_VAL`                     | 浮点类型或十进制浮点类型的无穷大定义，表示在默认舍入模式下溢出时库函数返回的最大值 |

>---

>---
#### 

>---
#### fma 相关宏（可选）

```c
#define FP_FAST_FMA			// double
#define FP_FAST_FMAF		// float
#define FP_FAST_FMAL		// long double

#define FP_FAST_FMAD32		// _Decimal32
#define FP_FAST_FMAD64		// _Decimal64
#define FP_FAST_FMAD128		// _Decimal128
```

这些宏为可选定义，指示 `fma` 函数的执行速度通常与 `double` 操作数的乘法或加法一样快或更快。如果已定义，这些宏将展开展开为 1。

通常，当且仅当 `fma` 函数直接由硬件乘法加指令实现时，才定义 `FP_FAST_FMA` 宏。

>---
#### 其他可选定义宏

以下的宏定义都是可选的。如果定义了，它表示相应的函数通常执行速度与参数类型的相应操作和函数一样快，或者更快，结果类型与参数类型相同，然后转换为更窄的类型。这些宏展开为整数常量 1。

```c
// 标准浮点类型
#define FP_FAST_FADD
#define FP_FAST_FADDL
#define FP_FAST_DADDL

#define FP_FAST_FSUB
#define FP_FAST_FSUBL
#define FP_FAST_DSUBL

#define FP_FAST_FMUL
#define FP_FAST_FMULL
#define FP_FAST_DMULL

#define FP_FAST_FDIV
#define FP_FAST_FDIVL
#define FP_FAST_DDIVL

#define FP_FAST_FSQRT
#define FP_FAST_FSQRTL
#define FP_FAST_DSQRTL

// 十进制浮点类型
#define FP_FAST_D32ADDD64
#define FP_FAST_D32ADDD128
#define FP_FAST_D64ADDD128

#define FP_FAST_D32SUBD64
#define FP_FAST_D32SUBD128
#define FP_FAST_D64SUBD128

#define FP_FAST_D32MULD64
#define FP_FAST_D32MULD128
#define FP_FAST_D64MULD128

#define FP_FAST_D32DIVD64
#define FP_FAST_D32DIVD128
#define FP_FAST_D64DIVD128

#define FP_FAST_D32FMAD64
#define FP_FAST_D32FMAD128
#define FP_FAST_D64FMAD128

#define FP_FAST_D32SQRTD64
#define FP_FAST_D32SQRTD128
#define FP_FAST_D64SQRTD128
```

>---

#### FP_ILOGB

```c
#define FP_ILOGB0
#define FP_ILOGBNAN
```

扩展为整数常量表达式，其值分别由函数 `ilogb(x)` 在 x 为零或 *NaN* 时返回。
  - 当 `x = 0` 时，函数返回 `FP_ILOGB0`，其值为 `INT_MIN` 或 `-INT_MAX`；
  - 当 `x = NaN` 时，函数返回 `FP_ILOGBNAN`，其值为 `INT_MAX` 或 `INT_MIN`；

#### FP_LLOGB

```c
#define FP_LLOGB0
#define FP_LLOGBNAN
```

扩展为整数常量表达式，其值分别由函数 `llogb(x)` 在 x 为零或 *NaN* 时返回。
- 如果 `FP_ILOGB0` 的值为 `INT_MIN`，则 `FP_LLOGB0` 的值应为 `LONG_MIN`；
- 如果 `FP_ILOGB0` 的值为 `-INT_MAX`，则 `FP_LLOGB0` 的值应为 `-LONG_MAX`。
- 如果 `FP_ILOGBNAN` 的值为 `INT_MAX`，则 `FP_LLOGBNAN` 的值应为 `LONG_MAX`；
- 如果 `FP_ILOGBNAN` 的值为 `INT_MIN`，则 `FP_LLOGBNAN` 的值应为 `LONG_MIN`。

对于函数返回：
  - 当 `x = 0` 时，函数返回 `FP_LLOGB0`；
  - 当 `x = NaN` 时，函数返回 `FP_ILOGBNAN`，其值为 `INT_MAX` 或 `INT_MIN`；




>---
### 数学函数的错误处理机制

```c
#define MATH_ERRNO        1
#define MATH_ERREXCEPT    2
#define math_errhandling  (MATH_ERRNO | MATH_ERREXCEPT)
```

`math_errhandling` 扩展为具有 `int` 类型，值为 `MATH_ERRNO`、`MATH_ERREXCEPT`、`(MATH_ERRNO | MATH_ERREXCEPT)` 或 0 的表达式；在托管实现中，该值不得为 0。

如果表达式 `math_errhandling & MATH_ERREXCEPT` 可以为非零，则在 `fenv.h` 中实现定义 `FE_DIVBYZERO`、`FE_INVALID`、`FE_OVERFLOW`。

> *错误处理的条件*

`math.h` 的函数通常不会引发 SIGFPE（浮点异常信号），也不会产生任何浮点异常例如 “invalid”，“divide-by-zero”，或 “overflow”。

*域错误（domain error）*：对于所有函数，当前仅当输入的参数在函数的定义域之外，则会发生域错误：
  - *signaling NaN* 的输入是否导致域错误是由实现定义的。 
  - 如果 `math_errhandling & MATH_ERRNO` 非零，`errno` 获取值 `EDOM`。
  - 如果 `math_errhandling & MATH_ERREXCEPT` 非零，则会引发 “invalid” 无效浮点异常。

*极点错误 / 奇点 / 无穷大（pole error）*：当且仅当数学函数在有限输入参数接近极限时（如 `log(0.0)`）具有无穷大结果发生时，发生极点错误：
  - 如果 `math_errhandling & MATH_ERRNO` 非零，`errno` 获取值 `ERANGE`。
  - 如果 `math_errhandling & MATH_ERREXCEPT` 非零，则会引发 “divide-by-zero” 除以零浮点异常。

*范围错误（range error）*：当且仅当函数的数学结果无法在指定类型的对象中表示时，由于超出类型表示范围，就会发生结果溢出错误。浮点结果上溢（overflow），函数将返回类型宏 `HUGE_VAL/HUGE_VALF/HUGE_VALL` 的值，并具有与函数正确值相同的符号，对于具有超出溢出阈值的数字的降低精度表示的类型，该函数可以返回具有小于该类型的全精度的结果的表示；浮点结果下溢（underflow），函数将返回一个大小不大于指定类型中最小的规范化正数：
  - 如果 `math_errhandling & MATH_ERRNO` 非零，`errno` 获取值 `ERANGE`。
  - 如果 `math_errhandling & MATH_ERREXCEPT` 非零，则会引发 “overflow / underflow” 溢出浮点异常。

如果发生域、极点或范围错误，并且整数表达式 `math_errhandling & MATH_ERRNO` 为零，则应将 `errno` 设置为与错误对应的值或保持不变。如果没有发生这样的错误，则无论 `math_errhandling` 的设置如何，`errno` 都应保持不变。

>---
### Pragma：FP_CONTRACT（浮点收缩）

```c
#pragma STDC FP_CONTRACT on-off-switch
#pragma fp_contract(on | off | default)
```

`fp_contract` 表示是否在浮点算数中使用浮点收缩指令（例如 FMA 混合乘加运算），它可以像单个操作一样求值，从而省略了源代码和表达式求值方法隐含的舍入错误。（一般默认为 `on`）

浮点收缩意味着浮点算数的中间操作被视为具有无限范围和精度，且中间结果无法被追溯和检查中间值，因此由于它作为单个指令实现，因此可能比单独指令更快。例如 FMA 在执行加法之前不会对中间乘积进行舍入，因此结果可能与单独的乘法和加法运算不同。

---
### 浮点值分类与比较

| Specifier        | Description                                                        |
| :--------------- | :----------------------------------------------------------------- |
| `fpclassify`     | 归类浮点值 `arg` 的类别                                            |
| `FP_ZERO`        | 类别零                                                             |
| `FP_SUBNORMAL`   | 非正规                                                             |
| `FP_NORMAL`      | 正规                                                               |
| `FP_INFINITE`    | 无穷大、                                                           |
| `FP_NAN`         | NaN                                                                |
| `iscanonical`    | 确定其参数值是否在其规范表示形式中。                               |
| `isfinite`       | 确定参数值是否具有有限值（零、非正规或正规，而不是无穷或 `NaN`）。 |
| `isinf`          | 确定参数值是否是（正或负）无穷大。                                 |
| `isnan`          | 确定参数值是否为 `NaN`。                                           |
| `isnormal`       | 确定参数值是否是正规值（而不是零、非正规、无穷或 `NaN`）。         |
| `issubnormal`    | 确定参数值是否为非正规值。                                         |
| `issignaling`    | 确定参数值是否为 *signaling* *NaN*。                               |
| `iszero`         | 确定参数值是否为（正、负或无符号）零。                             |
| `signbit`        | 确认符号位                                                         |
| `isgreater`      | (x) > (y)                                                          |
| `isgreaterequal` | (x) >= (y)                                                         |
| `isless`         | (x) < (y)                                                          |
| `islessequal`    | (x) <= (y)                                                         |
| `islessgreater`  | (x) < (y)                                                          |
| `isunordered`    | 是否无序                                                           |
| `iseqsig`        | 相等比较                                                           |

> fpclassify

```c
#include <stdio.h>
#include <math.h>
#include <float.h>

#pragma fenv_access(on)

const char* show_classification(double x) {
    switch (fpclassify(x)) {   // 宏函数：浮点归类
    case FP_INFINITE:  return "Inf";
    case FP_NAN:       return "NaN";
    case FP_NORMAL:    return "normal";
    case FP_SUBNORMAL: return "subnormal";
    case FP_ZERO:      return "zero";
    default:           return "unknown";
    }
}
int main(void)
{
    printf("1.0/0.0 is %s\n", show_classification(1 / 0.0));
    printf("0.0/0.0 is %s\n", show_classification(0.0 / 0.0));
    printf("DBL_MIN/2 is %s\n", show_classification(DBL_MIN / 2));
    printf("-0.0 is %s\n", show_classification(-0.0));
    printf(" 1.0 is %s\n", show_classification(1.0));
}
/*
1.0/0.0 is Inf
0.0/0.0 is NaN
DBL_MIN/2 is subnormal
-0.0 is zero
 1.0 is normal
*/
```

---
### 算数函数

以下函数对于标准浮点类型，某一函数族的无后缀形式、`f` 后缀形式、`l` 后缀形式分别表示以 `double`、`float`、`long double` 类型为参数的函数，例如 `cos`、`cosf`、`cosl`。对于十进制浮点数类型，后缀 `d`*N* 表示对应以宽度为 *N* 十进制浮点类型为参数的函数，例如 `cosd32`、`cosd64`、`cosd128`。

| Specifier                    | Description                                                                                                                                                                                                                               |
| :--------------------------- | :---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `cos`、`sin`、`tan`          | 三角函数                                                                                                                                                                                                                                  |
| `acos`、`asin`、`atan`       | 反三角函数                                                                                                                                                                                                                                |
| `acospi`、`asinpi`、`atanpi` | 测量半圆角度                                                                                                                                                                                                                              |
| `atan2`                      | 计算 $y/x$ 的反正切值                                                                                                                                                                                                                     |
| `atan2pi`                    | 计算在原点由点 (x，y) 和正 X 轴方向的半圈角度。                                                                                                                                                                                           |
| `cospi`、`sinpi`、`tanpi`    | _f_ (pi * x)                                                                                                                                                                                                                              |
| `cosh`、`sinh`、`tanh`       | 双曲函数                                                                                                                                                                                                                                  |
| `acosh`、`asinh`、`atanh`    | 反双曲函数                                                                                                                                                                                                                                |
| `eexp`                       | 计算 $e^x$。如果有限的 x 的幅度太大，则会发生范围错误。                                                                                                                                                                                   |
| `expm1`                      | 计算 $e^x-1$。如果正有限 x 太大或非零 x 太接近零，则会发生范围错误。                                                                                                                                                                      |
| `exp10`                      | 计算 $10^x$。如果有限 x 的幅度太大，则会出现范围错误。                                                                                                                                                                                    |
| `exp10m1`                    | 计算 $10^x-1$。如果正有限 x 太大或非零 x 太接近零，则会发生范围错误。                                                                                                                                                                     |
| `exp2`                       | 计算 $2^x$。如果有限 x 的幅度太大，则会出现范围错误。                                                                                                                                                                                     |
| `exp2m1`                     | 计算 $2^x-1$。如果正有限 x 太大或非零 x 太接近零，则会发生范围错误。                                                                                                                                                                      |
| `frexp`                      | 将浮点数分解为规格化分数和整数指数，整数存储在 `exp` 指向的对象中。                                                                                                                                                                       |
| `ldexp`                      | 返回 $x × 2^p$ 或 $x × 10^p$                                                                                                                                                                                                              |
| `log`                        | 计算 $log_ex$ 的值                                                                                                                                                                                                                        |
| `log10`                      | 计算 $log_{10} x$。                                                                                                                                                                                                                       |
| `log10p1`                    | 计算 $log_{10}(1 + x)$。                                                                                                                                                                                                                  |
| `log1p`                      | 等效于 `logp1`，目的是为了与 `log10p1` 保持名称一致。这些函数计算 $log_e(1 + x)$。                                                                                                                                                        |
| `log2`                       | 计算 $log_{2} x$。                                                                                                                                                                                                                        |
| `log2p1`                     | 计算 $log_{2}(1 + x)$。                                                                                                                                                                                                                   |
| `logb`                       | 提取 x 的指数，作为浮点格式的有符号整数值。                                                                                                                                                                                               |
| `ilogb`                      | 将 x 的指数提取为有符号 `int` 值。                                                                                                                                                                                                        |
| `llogb`                      | 将 x 的指数提取为一个有符号的 `long int` 值。                                                                                                                                                                                             |
| `modf`                       | 将参数值分解为整数和小数部分。                                                                                                                                                                                                            |
| `scalbn`, `scalnln`          | 计算 $x * b ^ n$ 的值                                                                                                                                                                                                                     |
| `sqrt`                       | 平方根                                                                                                                                                                                                                                    |
| `rsqrt`                      | 计算参数的非负平方根的倒数（$1/\sqrt{x}$）                                                                                                                                                                                                |
| `cbrt`                       | 立方根                                                                                                                                                                                                                                    |
| `rootn`                      | 计算 $x^{1/n}$。                                                                                                                                                                                                                          |
| `compoundn`                  | 计算 $(1+x)^n$ 的值。                                                                                                                                                                                                                     |
| `pow`                        | 计算 $x^y$。                                                                                                                                                                                                                              |
| `pown`                       | 计算 $x^n$。                                                                                                                                                                                                                              |
| `powr`                       | 计算 $e^{y log_e x}$。                                                                                                                                                                                                                    |
| `hypot`                      | 计算 $\sqrt{x^2+y^2}$，没有过度的上溢或下溢。                                                                                                                                                                                             |
| `fabs`                       | 绝对值                                                                                                                                                                                                                                    |
| `erf`                        | 计算 x 的误差函数。误差函数：`erf(x)` = $\frac{2}{\sqrt{\pi}} \int_0^{x} e^{-t^2}dt$.                                                                                                                                                     |
| `erfc`                       | 计算 x 的互补误差函数。互补误差函数：`erfc(x)` = `1-erf(x)` = $\frac{2}{\sqrt{\pi}} \int_x^{\infty} e^{-t^2}dt$.                                                                                                                          |
| `tgamma`                     | 计算 x 的伽马函数。                                                                                                                                                                                                                       |
| `lgamma`                     | 计算 x 的伽马绝对值的自然对数。阶乘函数仅针对离散点，伽马函数是对阶乘函数的泛化。`tgamma(x)` = $\Gamma(x) = \int_0^{\infty} t^{x-1} e^{-t}dt$。对于自然数 $x$，有 $x!$ = $\Gamma (x+1)$。`lgamma(x)` 是 `tgamma(x)` 的自然对数，即 $log_e | \Gamma(x) | $。                          |
| `fmod`                       | 函数返回值 `x - ny`，对于某个整数 `n`，如果 `y` 非零，则结果与 `x` 符号相同且 `x - ny < y`。                                                                                                                                              |
| `remainder`                  | 计算 `x - ny`，`n` 是最接近 `x/y` 准确值的整数值，求 `                                                                                                                                                                                    | n - x/y   | = 1/2`，选择作为偶数的 `n`。 |
| remquo                       | 求商求余。对于 `rem = remquo(x,y,*quo)` 满足 `x = y * quo + rem`。                                                                                                                                                                        |




> atan2

`atan2` 函数计算 $y/x$ 的反正切值，使用两个参数的符号来确定返回值的象限。如果两个参数都为零，则可能发生域错误。如果 $x$ 为正且非零值太接近零，则会发生范围错误。函数返回在  $[−π, +π]$ 弧度区间的 $arctan(y/x)$。

四象限反正切函数用于确定点 $(x, y)$ 在直角坐标系的位置。

![](atan2.dio.svg)

定义 `nor` 为有限浮点数 (`FP_NORMAL`)，正有限表示为 `+nor`，负有限表示为 `-nor`：
  - 当 `x = 0, y = 0` 时，函数返回 `0.0`；
  - 当 `x = ±0.0, y > 0` 时，函数返回 `0.5*PI`； 
  - 当 `x = ±0.0, y < 0` 时，函数返回 `-0.5*PI`；
  - 当 `y = ±0.0, x <= -0.0` 或 `y = ±nor, x = -inf` 时，函数返回 `±PI`；
  - 当 `y = ±0.0, x >= 0.0` 或 `y = ±nor, x = inf` 时，函数返回 `±0.0`；
  - 当 `(+nor,+nor)` 或 `(+inf, +inf)` 时，函数返回 `0.25*PI`；
  - 当 `(-nor,+nor)` 或 `(-inf, +inf)` 时，函数返回 `0.75*PI`；
  - 当 `(-nor,-nor)` 或 `(-inf, -inf)` 时，函数返回 `-0.75*PI`；
  - 当 `(+nor,-nor)` 或 `(+inf, -inf)` 时，函数返回 `-0.25*PI`；
  - 任意一个参数为 `NAN` 时，函数返回 `NAN`。

```c
#include <stdio.h>
#include <math.h>
#include <float.h>

#define Atan2(x, y)  printf("The Point("#x","#y") of atan2("#y", "#x") = %+.6f\n", atan2(y, x))

#define inf INFINITY

int main()
{
	puts("\n****** x = 0, y = 0 ******");
	Atan2(0, 0);			// 0.000000

	puts("\n****** x = ±0.0, y > 0 ******");
	Atan2(0.0, 1.0);		// 0.5 * PI
	Atan2(0.0, inf);
	Atan2(-0.0, 1.0);
	Atan2(-0.0, inf);

	puts("\n****** x = ±0.0, y < 0 ******");
	Atan2(0.0, -1.0);		// -0.5 * PI
	Atan2(0.0, -inf);
	Atan2(-0.0, -1.0);
	Atan2(-0.0, -inf);

	puts("\n****** y = ±0.0, x <= -0.0 || y = ±nor, x = -inf ******");
	Atan2(-0.0, 0.0);		// +PI
	Atan2(-1.0, 0.0);
	Atan2(-inf, 0.0);
	Atan2(-inf, 1.0);
	Atan2(-0.0, -0.0);		// -PI
	Atan2(-1.0, -0.0);
	Atan2(-inf, -0.0);
	Atan2(-inf, -1.0);

	puts("\n****** y = ±0.0, x >= 0.0 || y = ±nor, x = inf ******");
	Atan2(0.0, 0.0);		// +0.000000
	Atan2(1.0, 0.0);
	Atan2(inf, 0.0);
	Atan2(inf, 1.0);
	Atan2(0.0, -0.0);		// -0.000000
	Atan2(1.0, -0.0);
	Atan2(inf, -0.0);
	Atan2(inf, -1.0);

	puts("\n****** (+nor,+nor)` 或 (+inf, +inf) ******");
	Atan2(1.0, 1.0);		// 0.25 * PI
	Atan2(inf, inf);

	puts("\n****** (-nor,+nor)` 或 (-inf, +inf) ******");
	Atan2(-1.0, 1.0);		// 0.75 * PI
	Atan2(-inf, inf);

	puts("\n****** (-nor,-nor)` 或 (-inf, -inf) ******");
	Atan2(-1.0, -1.0);		// -0.75 * PI
	Atan2(-inf, -inf);

	puts("\n****** (+nor,-nor)` 或 (+inf, -inf) ******");
	Atan2(1.0, -1.0);		// -0.25 * PI
	Atan2(inf, -inf);
}
```

> frexp, ldexp

```c
#include <stdio.h>
#include <math.h>

void Frexp_Ldexp(double x) {
	int exp;
	double rt = frexp(x, &exp);
	printf("frexp(%f) : value = %f, exp = %d\n", x, rt, exp);
	printf("ldexp(%f) : %f * 2^%d = %f\n", rt, rt, exp, ldexp(rt, exp));
}

int main()
{
	Frexp_Ldexp(10);			// 10 = 0.625 * 2^4

	Frexp_Ldexp(100);			// 100 = 0.781250 * 2^7

	Frexp_Ldexp(100.123);		// 100.123 ≈ 0.782211 * 2^7
}
/*
frexp(10.000000) : value = 0.625000, exp = 4
ldexp(0.625000) : 0.625000 * 2^4 = 10.000000
frexp(100.000000) : value = 0.781250, exp = 7
ldexp(0.781250) : 0.781250 * 2^7 = 100.000000
frexp(100.123000) : value = 0.782211, exp = 7
ldexp(0.782211) : 0.782211 * 2^7 = 100.123000
*/
```

> lgamma, tgamma

```c
#include <stdio.h>
#include <math.h>

int factorial(int x) {
	int mul = 1;
	for (int i = 1; i <= x; i++)
		mul *= i;
	return mul;
}

int main()
{
	printf("tgamma(%f) = %f, lgamma(%f)\n", 9.999999999, tgamma(9.999999999), lgamma(9.999999999));
	printf("tgamma(%f) = %f, lgamma(%f)\n", 10.0, tgamma(10.0), lgamma(10.0));
	printf("%d! = %d", 9, factorial(9));
}
/*
tgamma(10.000000) = 362879.999183, lgamma(12.801827)
tgamma(10.000000) = 362880.000000, lgamma(12.801827)
9! = 362880
*/
```

> fmod, remainder

```c
#include <stdio.h>
#include <math.h>

#define Fmod(x, y) printf("fmod("#x","#y") = %f\n", fmod(x,y));
#define Remainder(x, y) printf("remainder("#x","#y") = %f\n", remainder(x,y));

int main()
{
	Fmod(1.1, 10);
	Remainder(1.1, 10);

	Fmod(-1.1, 10);
	Remainder(-1.1, 10);

	Fmod(-5.00001, 10);
	Remainder(-5.00001, 10);

	Fmod(5.00001, 10);
	Remainder(5.00001, 10);
}
/*
fmod(1.1,10) = 1.100000
remainder(1.1,10) = 1.100000
fmod(-1.1,10) = -1.100000
remainder(-1.1,10) = -1.100000
fmod(-5.00001,10) = -5.000010
remainder(-5.00001,10) = 4.999990
fmod(5.00001,10) = 5.000010
remainder(5.00001,10) = -4.999990
*/
```


>---
### 舍入函数

| Specifier                    | Description                                                                                        |
| :--------------------------- | :------------------------------------------------------------------------------------------------- |
| `ceil`                       | 向上取整，返回不小于 x 的最小整数                                                                  |
| `floor`                      | 向下取整，返回不大于 x 的最大整数                                                                  |
| `nearbyint`                  | 使用当前舍入方向，进行取整，不产生浮点异常                                                         |
| `rint`、`lrint`、`llrint`    | 使用当前舍入方向，进行取整，可能产生浮点异常                                                       |
| `round`、`lround`、`llround` | 四舍五入取整。不受当前舍入模式的影响                                                               |
| `roundeven`                  | 像最接近偶数舍入                                                                                   |
| `trunc`                      | 向零舍入取整                                                                                       |
| `fromfp`、`ufromfp`          | 根据舍入模式舍入到整数                                                                             |
| `fromfpx、ufromfpx`          | 不超过指定宽度的舍入结果与参数 x 的值不同，`fromfpx` 和 `ufromfpx` 函数将引发 “inexact” 浮点异常。 |


> 数学舍入方向宏

```c
#define FP_INT_UPWARD	
#define FP_INT_DOWNWARD	
#define FP_INT_TOWARDZERO	
#define FP_INT_TONEARESTFROMZERO	
#define FP_INT_TONEAREST	
```

这些宏分别表示函数 `ceil`、`floor`、`trunc`、`round`、`roundeven` 的舍入方向，转换为浮点格式的整数值。它们扩展为适合用作 `fromfp`、`ufromfp`、`fromfpx`、`ufromfpx` 函数的第二个参数的不同值的常量表达式。

> rint

```c
#include <stdio.h>
#include <math.h>
#include <fenv.h>

#pragma fenv_access(on)

void show_fpround() {
	switch (fegetround())
	{
	case FE_TONEAREST:	// 向最接近可表示值舍入
		printf("round env = FE_TONEAREST.\n");
		break;
	case FE_DOWNWARD:	// 向负无穷大舍入
		printf("round env = FE_DOWNWARD.\n");
		break;
	case FE_UPWARD:		// 向正无穷大舍入
		printf("round env = FE_UPWARD.\n");
		break;
	case FE_TOWARDZERO:	// 向零舍入
		printf("round env = FE_TOWARDZERO.\n");
		break;
	default:
		printf("round env = unknown.\n");
		break;
	}
}
#define Rint(x) printf("rint("#x") = %.2f\n", rint(x))

void Test_Rint(int round) 
{
	fesetround(round);
	show_fpround();
	Rint(1.11111);
	Rint(1.99999);
	Rint(-1.11111);
	Rint(-1.99999);
}

int main()
{
	Test_Rint(FE_DOWNWARD);
	Test_Rint(FE_DOWNWARD);
	Test_Rint(FE_UPWARD);
	Test_Rint(FE_TOWARDZERO);
}
/*
round env = FE_DOWNWARD.
rint(1.11111) = 1.00
rint(1.99999) = 1.00
rint(-1.11111) = -2.00
rint(-1.99999) = -2.00
round env = FE_DOWNWARD.
rint(1.11111) = 1.00
rint(1.99999) = 1.00
rint(-1.11111) = -2.00
rint(-1.99999) = -2.00
round env = FE_UPWARD.
rint(1.11111) = 2.00
rint(1.99999) = 2.00
rint(-1.11111) = -1.00
rint(-1.99999) = -1.00
round env = FE_TOWARDZERO.
rint(1.11111) = 1.00
rint(1.99999) = 1.00
rint(-1.11111) = -1.00
rint(-1.99999) = -1.00
*/
```

>---
### 浮点操作

| Specifier                      | Description                         |
| :----------------------------- | :---------------------------------- |
| `copysign`                     | 复制符号                            |
| `nan`                          | 转换为 *quiet NAN*                  |
| `nextafter`、`nexttoward`      | 下一个有限浮点值                    |
| `nextup`                       | 确定下一个大于 x 的可表示的浮点值。 |
| `nextdown`                     | 确定下一个小于 x 的可表示的浮点值。 |
| `canonicalize`                 | 规范化浮点数                        |
| `fadd`、`fsub`、`fmul`、`fdiv` | 将结果舍入为更窄类型                |
| `fma`                          | 浮点乘加                            |
| `ffma`                         | 浮点乘加舍入窄                      |
| `fsqrt`                        | 平方根舍入窄                        |



---
### 比较和正差函数

| Specifier          | Description                                                                |
| :----------------- | :------------------------------------------------------------------------- |
| `fmax`、`fmin`     | 最大、最小                                                                 |
| `fmaximum`         | 两数之间的最大值                                                           |
| `fmaximum_mag`     | 两数的模之间的最大值                                                       |
| `fminimum`         | 两数之间的最小值                                                           |
| `fminimum_mag`     | 两数的模之间的最小值                                                       |
| `fmaximum_num`     | 两数之间的最大值。如果一个参数是数字，另一个参数是 *NaN*，则返回数字。     |
| `fmaximum_mag_num` | 两数的模之间的最大值。如果一个参数是数字，另一个参数是 *NaN*，则返回数字。 |
| `fminimum_num`     | 两数之间的最小值。如果一个参数是数字，另一个参数是 *NaN*，则返回数字。     |
| `fminimum_mag_num` | 两数的模之间的最小值。如果一个参数是数字，另一个参数是 *NaN*，则返回数字。 |
| `fdim`             | `x` 与 `y` 之间的正差，即当 $x>y$ 返回 `x-y`，否则（$x<=y$）返回 `+0`。    |

> fmax

`fmaximum` 函数认为 `+0` 大于 `-0`；`fminimum` 函数认为 `-0` 小于 `+0`。

`fminimum_mag` 函数返回两个参数的模的最大值，即：
- 若 $|x| > |y|$ 返回 x；
- 若 $|y| > |x|$ 返回 y；
- 否则返回 `fmaximum(x, y)` 的值。

`fmaximum_mag` 函数返回两个参数的模的最小值，即：
- 若 $|x| < |y|$ 返回 x；
- 若 $|y| < |x|$ 返回 y；
- 否则返回 `fminimum(x, y)` 的值。


---
### 量子函数和量子指数函数
#### quantized*N*

```c
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 quantized32(_Decimal32 x, _Decimal32 y);
_Decimal64 quantized64(_Decimal64 x, _Decimal64 y);
_Decimal128 quantized128(_Decimal128 x, _Decimal128 y);
#endif
```

如果可能的话，`quantized`*N* 函数计算具有 x 和 y 的量子指数的值。
- 如果量子指数正在增加，则值应正确舍入；如果结果与 x 的值不同，则引发 “inexact” 浮点异常。
- 如果量子指数正在减小，并且结果的有效位数比类型允许的位数多，则结果为 *NaN*，引发 “invalid” 浮点异常，并发生域错误。
- 如果一个或两个操作数都是 *NaN*，则结果是 *NaN*。
- 否则，如果只有一个操作数是无限的，则结果为 *NaN*，引发 “invalid” 浮点异常，并发生域错误。
- 如果两个操作数都是无限的，则结果是与 x 符号相同的 `DEC_INFINITY`，并转换为函数的返回类型。
- `quantized`*N* 函数不会引发 “上溢” 和 “下溢” 浮点异常。

`quantized`*N* 函数返回一个数值为 x（除了任何舍入）和量子指数为 y 的值。

>---
#### samequantumd*N*

```c
#ifdef __STDC_IEC_60559_DFP__
bool samequantumd32(_Decimal32 x, _Decimal32 y);
bool samequantumd64(_Decimal64 x, _Decimal64 y);
bool samequantumd128(_Decimal128 x, _Decimal128 y);
#endif
```

`samequantumd`*N* 函数检查 x 和 y 的量子指数是否相同。如果 x 和 y 都是 *NaN*，或者都是无穷大，它们有相同的量子指数；如果恰好有一个操作数是无穷大，或者恰好有一个操作数是 *NaN*，它们则没有相同的量子指数。`samequantumd`*N* 函数不会引发浮点异常。

当 x 和 y 具有相同的量子指数时，函数返回非零，否则返回零。

>---
#### quantumd*N*

```c
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 quantumd32(_Decimal32 x);
_Decimal64 quantumd64(_Decimal64 x);
_Decimal128 quantumd128(_Decimal128 x);
#endif
```

`quantumd`*N* 函数计算有限参数 x 的量子。如果 x 是无限的，则结果为 +∞。

>---
#### llquantexpd*N*

```c
#ifdef __STDC_IEC_60559_DFP__
long long int llquantexpd32(_Decimal32 x);
long long int llquantexpd64(_Decimal64 x);
long long int llquantexpd128(_Decimal128 x);
#endif
```

`llquantexpd`*N* 函数计算有限参数的量子指数，如果 x 是无穷大或 *NaN*，则计算 `LLONG_MIN` 并引发 “invalid” 无效浮点异常，并发生域错误。

---
### Functions：十进制重编码函数

ISO/IEC 60559 指定了两种不同的方案来编码十进制浮点对象的对象表示中的有效数：一种基于十进制编码（将三个十进制数字打包为 10 位），另一种基于二进制编码（作为二进制整数）。实现可以将这些编码方案中的任一种用于其十进制浮点类型。

>---
#### encodedecd*N*

```c
#ifdef __STDC_IEC_60559_DFP__
void encodedecd32(unsigned char encptr[restrict static 4], const _Decimal32 * restrict xptr);
void encodedecd64(unsigned char encptr[restrict static 8], const _Decimal64 * restrict xptr);
void encodedecd128(unsigned char encptr[restrict static 16], const _Decimal128 * restrict xptr);
#endif
```

`encodedecd`*N* 函数转换 `*xptr` 为 ISO/IEC 60559 decimal*N* 编码，编码方案基于有效数的十进制编码，并将所得编码存储为 $N/8$ 元素数组，每个数组元素 8 位，在 `encptr` 指向的对象中。数组中的字节顺序遵循 `__STDC_ENDIAN_NATIVE__` 指定的字节顺序。这些函数保留的值，不会引发浮点异常。如果是非规范的，这些函数可能会也可能不会产生规范编码。

>---
#### decodedecd*N*

```c
#ifdef __STDC_IEC_60559_DFP__
void decodedecd32(_Decimal32 * restrict xptr, const unsigned char encptr[restrict static 4]);
void decodedecd64(_Decimal64 * restrict xptr, const unsigned char encptr[restrict static 8]);
void decodedecd128(_Decimal128 * restrict xptr, const unsigned char encptr[restrict static 16]);
#endif
```

`dencodedecd`*N* 函数将 `encptr` 指向的 $N/8$ 元素数组解释为 ISO/IEC 60559 decimal*N* 编码，编码方案基于有效数的十进制编码，每个数组元素有 8 位。数组中的字节顺序遵循 `__STDC_ENDIAN_NATIVE__`指定的字节顺序。这些函数将给定的编码转换为十进制浮点类型的值，将结果存储在 `xptr` 指向的对象中。这些函数保留编码的值，不会引发浮点异常。如果编码是非规范的，这些函数可能会也可能不会产生规范表示。

>---
#### encodebind*N*

```c
#ifdef __STDC_IEC_60559_DFP__
void encodebind32(unsigned char encptr[restrict static 4], const _Decimal32 * restrict xptr);
void encodebind64(unsigned char encptr[restrict static 8], const _Decimal64 * restrict xptr);
void encodebind128(unsigned char encptr[restrict static 16], const _Decimal128 * restrict xptr);
#endif
```

`encodebind`*N* 函数转换 `*xptr` 为 ISO/IEC 60559 decimal*N* 编码，编码方案基于有效数的二进制编码，并将所得编码存储为 $N/8$ 元素数组，每个数组元素 8 位，在 `encptr` 指向的对象中。数组中的字节顺序遵循 `__STDC_ENDIAN_NATIVE__` 指定的字节顺序。这些函数保留的值，不会引发浮点异常。如果是非规范的，这些函数可能会也可能不会产生规范编码。

>---
#### decodebind*N*

```c
#ifdef __STDC_IEC_60559_DFP__
void decodebind32(_Decimal32 * restrict xptr, const unsigned char encptr[restrict static 4]);
void decodebind64(_Decimal64 * restrict xptr, const unsigned char encptr[restrict static 8]);
void decodebind128(_Decimal128 * restrict xptr, const unsigned char encptr[restrict static 16]);
#endif
```

`decodebind`*N* 函数将 `encptr` 指向的 $N/8$ 元素数组解释为 ISO/IEC 60559 decimal*N* 编码，编码方案基于有效数的二进制编码，每个数组元素有 8 位。数组中的字节顺序遵循 `__STDC_ENDIAN_NATIVE__`指定的字节顺序。这些函数将给定的编码转换为十进制浮点类型的值，将结果存储在 `xptr` 指向的对象中。这些函数保留编码的值，不会引发浮点异常。如果编码是非规范的，这些函数可能会也可能不会产生规范表示。

---
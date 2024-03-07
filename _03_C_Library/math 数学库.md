## C 数学库（Mathematics）：math.h

```c
#define __STDC_VERSION_MATH_H__			202311L
```

`math.h` 提供了许多的数学函数，和另外两个具有相同名称但带有 f 和 l 后缀的函数命名，分别代表了 `double`、`float` 和 `long double` 的对应函数。

---
### Type

#### float_t & double_t

`float _t` 和 `double_t` 表示它们至少与 `float` 和 `double` 宽度相同的浮点类型，且 `double_t` 类型至少与 `float_t` 宽度相同。

`float.h` 的 `FLT_EVAL_METHOD` 表示为在浮点算数的中间结果所用的扩展精度。

```c
#include <float.h>
#if (FLT_EVAL_METHOD == 0)
typedef float float_t;
typedef double double_t;
#elif (FLT_EVAL_METHOD == 1)
typedef double float_t;
typedef double double_t;
#elif (FLT_EVAL_METHOD == 2)
typedef long double float_t;
typedef long double double_t;
#else
// 其他值则是实现定义的
#endif
```

>---
#### _Decimal32_t、_Decimal64_t

`_Decimal32_t`、`_Decimal64_t` 表示它们至少与 `_Decimal32` 和 `_Decimal64` 宽度相同的浮点类型，且 `_Decimal64` 类型至少与 `_Decimal32` 宽度相同。

```c
#define __STDC_WANT_IEC_60559_EXT__   // 前提条件：在 math 库之前定义该宏
#include <math.h>
#ifdef __STDC_WANT_IEC_60559_DFP__
#if (DEC_EVAL_METHOD == 0)
typedef _Decimal32_t _Decimal32;
typedef _Decimal64_t _Decimal64;
#elif (DEC_EVAL_METHOD == 1)
typedef _Decimal32_t _Decimal64;
typedef _Decimal64_t _Decimal64;
#elif (DEC_EVAL_METHOD == 2)
typedef _Decimal32_t _Decimal128;
typedef _Decimal64_t _Decimal128;
#else 
// 其他值则是实现定义的 
#endif
#endif
```

---
### Macros

#### 类型无穷大定义

```c
#define HUGE_VAL   ((double)INFINITY)
#define HUGE_VALF  ((float)INFINITY)
#define HUGE_VALL  ((long double)INFINITY)

#define __STDC_WANT_IEC_60559_EXT__   // 前提条件：在 math 库之前定义该宏
#include <math.h>
#ifdef __STDC_IEC_60559_DFP__
#define HUGE_VAL_D32
#define HUGE_VAL_D64
#define HUGE_VAL_D128
#endif
```

`HUGE_XXX` 分别指示过大而无法以 `double`、`float`、`long double` 类型表示的值（无穷大）。其值是当相应类型的浮点结果在默认舍入模式下溢出时库函数返回的最大值，可以是类型中的最大有限数，也可以是正无穷大或无符号无穷大。

相应的 `HUGE_VAL_XXX` 则表示十进制浮点数类型的正无穷大类型的算数常数表达式。

>---
####  INFINITY、NAN

`INFINITY` 当且仅当实现支持 `float` 时才定义，表示正无穷大或无符号无穷大。

`DEC_INFINITY` 扩展为 `_Decimal32` 类型的表示正无穷大的常量表达式。

`NAN` 当且仅当实现支持浮点类型的 *quiet* *NaN* 时才定义。它扩展为 `float` 类型的算术常数表达式，表示 *quiet* *NaN*。

`DEC_NAN` 扩展为 `_Decimal32` 类型的算术常数表达式，表示 *quiet* *NaN*。

在 `math.h` 中使用宏 `INFINITY`、`DEC_INFINITY`、`NAN` 和 `DEC_NAN` 是一项过时的功能。而应在 `float.h` 中使用相同的宏。

>---

#### 数字分类宏

```c
#define FP_NORMAL       // 指示值为正规浮点数，不是无穷大，非正规，非数或零
#define FP_SUBNORMAL    // 指示值为非正规
#define FP_ZERO         // 指示值为正或负零      
#define FP_INFINITE     // 指示值为正或负无穷大
#define FP_NAN          // 指示值是非数（NaN）
```

表示相互排斥的浮点值类型。 它们扩展为具有不同值的整数常量表达式。实现还可以指定其他实现定义的浮点分类，其中宏定义以 `FP_` 开头，并带有一个大写字母。

>---
#### 数学舍入方向宏

```c
#define FP_INT_UPWARD	
#define FP_INT_DOWNWARD	
#define FP_INT_TOWARDZERO	
#define FP_INT_TONEARESTFROMZERO	
#define FP_INT_TONEAREST	
```

这些宏分别表示函数 `ceil`、`floor`、`trunc`、`round`、`roundeven` 的舍入方向，转换为浮点格式的整数值。它们扩展为适合用作 `fromfp`、`ufromfp`、`fromfpx`、`ufromfpx` 函数的第二个参数的不同值的常量表达式。

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

#### 数学函数的错误处理机制

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

### Pragma：FP_CONTRACT（浮点收缩）

```c
#pragma STDC FP_CONTRACT on-off-switch
#pragma fp_contract(on | off | default)
```

`fp_contract` 表示是否在浮点算数中使用浮点收缩指令（例如 FMA 混合乘加运算），它可以像单个操作一样求值，从而省略了源代码和表达式求值方法隐含的舍入错误。（一般默认为 `on`）

浮点收缩意味着浮点算数的中间操作被视为具有无限范围和精度，且中间结果无法被追溯和检查中间值，因此由于它作为单个指令实现，因此可能比单独指令更快。例如 FMA 在执行加法之前不会对中间乘积进行舍入，因此结果可能与单独的乘法和加法运算不同。

---
### Macro-Functions：分类宏（Classification macros）

#### fpclassify （浮点值归类）

```c
int fpclassify(real-floating arg);
```

宏函数 `fpclassify` 归类浮点值 `arg` 到下列类别中：零（`FP_ZERO`）、非正规（`FP_SUBNORMAL`）、正规（`FP_NORMAL`）、无穷大（`FP_INFINITE`）、 NaN（`FP_NAN`）或其他实现定义类别。`fpclassify` 宏返回与其参数值相对应的数字分类宏的值。

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

>---

#### iscanonical、isfinite、isinf、isnan、isnormal、issubnormal、issignaling、iszero

```c
int iscanonical(real-floating x);
int isfinite(real-floating x);
int isinf(real-floating x);
int isnan(real-floating x);
int isnormal(real-floating x);
int issubnormal(real-floating x);
int issignaling(real-floating x);
int iszero(real-floating x);
```

这些宏函数在满足条件时返回非零值：
  - `iscanonical` 确定其参数值是否在其规范表示形式中。
  - `isfinite` 确定参数值是否具有有限值（零、非正规或正规，而不是无穷或 `NaN`）。
  - `isinf` 确定参数值是否是（正或负）无穷大。
  - `isnan` 确定参数值是否为 `NaN`。
  - `isnormal` 确定参数值是否是正规值（而不是零、非正规、无穷或 `NaN`）。
  - `issubnormal` 确定参数值是否为非正规值。
  - `issignaling` 确定参数值是否为 *signaling* *NaN*。
  - `iszero` 确定参数值是否为（正、负或无符号）零。

```c
#include <stdio.h>
#include <math.h>
#include <float.h>

#pragma fenv_access(on)
#define TRUE "TRUE"
#define FALSE "FALSE"

#define Check_Floating(real_floating) {	                                    \
	printf("Check value : " #real_floating " = %f\n", real_floating);       \
	printf("       isfinite = %s\n", isfinite(real_floating)? TRUE : FALSE);\
	printf("       isinf    = %s\n", isinf(real_floating)? TRUE : FALSE);   \
	printf("       isnan    = %s\n", isnan(real_floating)? TRUE : FALSE);   \
	printf("       isnormal = %s\n", isnormal(real_floating)? TRUE : FALSE);\
	puts("");                                                               \
}
int main(void)
{
	Check_Floating(1 / 0.0);
	Check_Floating(0.0 / 0.0);
	Check_Floating(DBL_MIN / 2);
	Check_Floating(-0.0);
	Check_Floating(1.0);
}
/*
Check value : 1 / 0.0 = inf
       isfinite = FALSE
       isinf    = TRUE
       isnan    = FALSE
       isnormal = FALSE

Check value : 0.0 / 0.0 = -nan(ind)
       isfinite = FALSE
       isinf    = FALSE
       isnan    = TRUE
       isnormal = FALSE

Check value : DBL_MIN / 2 = 0.000000
       isfinite = TRUE
       isinf    = FALSE
       isnan    = FALSE
       isnormal = FALSE

Check value : -0.0 = -0.000000
       isfinite = TRUE
       isinf    = FALSE
       isnan    = FALSE
       isnormal = FALSE

Check value : 1.0 = 1.000000
       isfinite = TRUE
       isinf    = FALSE
       isnan    = FALSE
       isnormal = TRUE
*/
```

>---

#### signbit （确认符号位）

```c
int signbit(real-floating x);
```

`signbit` 确定其参数的符号是否为负。如果参数值是无符号零，则其符号被视为正；参数为负时返回非零值；如果参数值是无符号的，则结果值（零或非零）是由实现定义的。`signbit` 可以检测零、无穷大、`NaN` 的符号。

```c
#include <stdio.h>
#include <math.h>
#include <float.h>

#pragma fenv_access(on)

#define Signbit(real_floating) printf(#real_floating " = %f , signbit(" #real_floating ") = %s\n" ,real_floating, signbit(real_floating)? "-": "+")

int main(void)
{
	// 0
	Signbit(0.0);
	Signbit(+0.0);
	Signbit(-0.0);
	puts("");

	// NAN
	Signbit(0.0 / 0.0);
	Signbit(-0.0 / 0.0);
	Signbit(+(0.0 / 0.0));
	Signbit(-(0.0 / 0.0));
	Signbit(NAN);
	Signbit(+NAN);
	Signbit(-NAN);
	puts("");

	// INFINITY
	Signbit(1 / 0.0);
	Signbit(-1 / 0.0);
	Signbit(+(1 / 0.0));
	Signbit(-(1 / 0.0));
	Signbit(INFINITY);
	Signbit(+INFINITY);
	Signbit(-INFINITY);
}
/*
0.0 = 0.000000 , signbit(0.0) = +
+0.0 = 0.000000 , signbit(+0.0) = +
-0.0 = -0.000000 , signbit(-0.0) = -

0.0 / 0.0 = -nan(ind) , signbit(0.0 / 0.0) = -
-0.0 / 0.0 = -nan(ind) , signbit(-0.0 / 0.0) = -
+(0.0 / 0.0) = -nan(ind) , signbit(+(0.0 / 0.0)) = -
-(0.0 / 0.0) = nan , signbit(-(0.0 / 0.0)) = +
NAN = nan , signbit(NAN) = +
+NAN = nan , signbit(+NAN) = +
-NAN = -nan(ind) , signbit(-NAN) = -

1 / 0.0 = inf , signbit(1 / 0.0) = +
-1 / 0.0 = -inf , signbit(-1 / 0.0) = -
+(1 / 0.0) = inf , signbit(+(1 / 0.0)) = +
-(1 / 0.0) = -inf , signbit(-(1 / 0.0)) = -
INFINITY = inf , signbit(INFINITY) = +
+INFINITY = inf , signbit(+INFINITY) = +
-INFINITY = -inf , signbit(-INFINITY) = -
*/
```


---
### Macro-Functions：比较宏（Comparison macros）

关系运算符和相等运算符支持数值之间的常用数学关系。对于任何有序的数值对，只有一个关系（小于、大于、等于）为真。当参数值为 NaN 时，关系运算符可能引发 “invalid” 浮点异常。对于一个 NaN 和一个数值，或者两个NaN，只有 `isunordered` 无序关系为真。对于 *quiet NaN* 的参数，宏不会引发 “invalid” 浮点异常

*real-floating* 表示参数应该是实浮点类型的表达式（两个参数不需要具有相同的类型）。如果其中一个参数是十进制浮点类型，另一个参数也必须是十进制浮点类型。

#### isgreater、isgreaterequal、isless、islessequal、islessgreater

```c
int isgreater(real-floating x, real-floating y);          // return (x) > (y)
int isgreaterequal(real-floating x, real-floating y);     // return (x) >= (y)
int isless(real-floating x, real-floating y);             // return (x) < (y)
int islessequal(real-floating x, real-floating y);        // return (x) <= (y)
int islessgreater(real-floating x, real-floating y);      // return (x) < (y) || (x) > (y)
```

进行浮点数之间的比较时，在 `x` 和 `y` 是 `isunordered` 无序的并且也不是 *signaling* *NaN* 时不会引发 “invalid” 浮点异常，此时函数返回零。

```c
#include <stdio.h>
#include <math.h>
#include <float.h>

int main(void)
{
	printf("isgreater(2.0,1.0) = %d\n", isgreater(2.0, 1.0));
	printf("isgreater(1.0,2.0) = %d\n", isgreater(1.0, 2.0));
	printf("isgreater(INFINITY,1.0) = %d\n", isgreater(INFINITY, 1.0));
	printf("isgreater(INFINITY,-INFINITY) = %d\n", isgreater(INFINITY, -INFINITY));
	printf("isgreater(-INFINITY,1.0) = %d\n", isgreater(-INFINITY, 1.0));
	printf("isgreater(1.0,NAN) = %d\n", isgreater(1.0, NAN));
	printf("isgreater(-INFINITY,NAN) = %d\n", isgreater(-INFINITY, NAN));
	printf("isgreaterequal(NAN,NAN) = %d\n", isgreaterequal(NAN, NAN));
	printf("isgreaterequal(INFINITY,INFINITY) = %d\n", isgreaterequal(INFINITY, INFINITY));
}
/*
isgreater(2.0,1.0) = 1
isgreater(1.0,2.0) = 0
isgreater(INFINITY,1.0) = 1
isgreater(INFINITY,-INFINITY) = 1
isgreater(-INFINITY,1.0) = 0
isgreater(1.0,NAN) = 0
isgreater(-INFINITY,NAN) = 0
isgreaterequal(NAN,NAN) = 0
isgreaterequal(INFINITY,INFINITY) = 1
*/
```

>---

#### isunordered （是否无序）

```c
int isunordered(real-floating x, real-floating y);
```

`isunordered` 确定浮点数 `x` 与 `y` 之间是否无序。当 `x` 和 `y` 是无序的并且也不是 *signaling* *NaN* 时，它不会引发 “invalid” 浮点异常。

实际上仅当 `x` 或 `y` 为 `NAN` 时返回非零值，否则返回零。因为此时其中至少有一个是 `NAN` 时，此时无法进行有意义的比较。

```c
#include <stdio.h>
#include <math.h>
#include <float.h>

#pragma fenv_access(on)

#define Isunordered(x, y)  printf(#x " and " #y " is unondered = %s\n", isunordered((x),(y))?"True":"False")

int main(void) {

	Isunordered(NAN, 1.0);
	Isunordered(1.0, NAN);
	Isunordered(NAN, NAN);
	Isunordered(-NAN, +NAN);
	Isunordered(1.0, 0.0);
	Isunordered(0.0, 1.0);
	Isunordered(1, 1);
	Isunordered(NAN, INFINITY);
	Isunordered(INFINITY, NAN);
	Isunordered(1, INFINITY);
	Isunordered(INFINITY, 1);
	Isunordered(INFINITY, INFINITY);
	Isunordered(-INFINITY, +INFINITY);
}
/*
NAN and 1.0 is unondered = True
1.0 and NAN is unondered = True
NAN and NAN is unondered = True
-NAN and +NAN is unondered = True
1.0 and 0.0 is unondered = False
0.0 and 1.0 is unondered = False
1 and 1 is unondered = False
NAN and INFINITY is unondered = True
INFINITY and NAN is unondered = True
1 and INFINITY is unondered = False
INFINITY and 1 is unondered = False
INFINITY and INFINITY is unondered = False
-INFINITY and +INFINITY is unondered = False
*/
```

>---
#### iseqsig （相等比较）

```c
int iseqsig(real-floating x, real-floating y);
```

`iseqsig` 宏确定其参数是否相等。如果一个参数是 `NaN`，宏会发生域错误。如果宏的参数相等，则返回 1，否则返回 0。

---
### Functions：三角函数（Trigonometric functions）

以下函数对于标准浮点类型，某一函数族的无后缀形式、`f` 后缀形式、`l` 后缀形式分别表示以 `double`、`float`、`long double` 类型为参数的函数，例如 `cos`、`cosf`、`cosl`。对于十进制浮点数类型，后缀 `d`*N* 表示对应以宽度为 *N* 十进制浮点类型为参数的函数，例如 `cosd32`、`cosd64`、`cosd128`。

>---
#### cos、sin、tan （三角函数）

```c
// 余弦函数 (-inf, +inf) >> [-1, 1]
double cos(double x);     
float cosf(float x);
long double cosl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 cosd32(_Decimal32 x);
_Decimal64 cosd64(_Decimal64 x);
_Decimal128 cosd128(_Decimal128 x);
#endif

// 正弦函数 (-inf, +inf) >> [-1, 1]
double sin(double x);     
float sinf(float x);
long double sinl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 sind32(_Decimal32 x);
_Decimal64 sind64(_Decimal64 x);
_Decimal128 sind128(_Decimal128 x);
#endif

// 正切函数 x≠(π/2)+kπ >> (-inf, +inf)
double tan(double x);     
float tanf(float x);
long double tanl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 tand32(_Decimal32 x);
_Decimal64 tand64(_Decimal64 x);
_Decimal128 tand128(_Decimal128 x);
#endif
```

`cos` 函数计算 x 的余弦（以弧度测量）。

`sin` 函数计算 x 的正弦（以弧度测量）。如果非零 x 太接近零，则会发生范围错误。

`tan` 函数计算 x 的正切值（以弧度为单位）。如果非零 x 太接近零，则会发生范围错误。


```c
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <float.h>

#define Cos(x)	printf("cos("#x") = %f\n", cos(x));
#define Sin(x)  printf("sin("#x") = %f\n", sin(x));
#define Tan(x)  printf("tan("#x") = %f\n", tan(x));

#define PI M_PI

int main() {
	Cos(0);
	Cos(PI);
	Cos(PI / 2);
	Cos(2 * PI);
	Cos(DBL_MAX * 2);
	Cos(NAN);
	Cos(-NAN);
	Cos(INFINITY);
	Cos(-INFINITY);

	Sin(0);
	Sin(PI);
	Sin(PI / 2);
	Sin(2 * PI);

	Tan(0);
	Tan(PI);
	Tan(PI / 2); // 实际 x 为无效值
	Tan(2 * PI);
  Tan(NAN);
	Tan(INFINITY);
}
/*
cos(0) = 1.000000
cos(PI) = -1.000000
cos(PI / 2) = 0.000000
cos(2 * PI) = 1.000000
cos(DBL_MAX * 2) = -nan(ind)
cos(NAN) = nan
cos(-NAN) = -nan(ind)
cos(INFINITY) = -nan(ind)
cos(-INFINITY) = -nan(ind)
sin(0) = 0.000000
sin(PI) = 0.000000
sin(PI / 2) = 1.000000
sin(2 * PI) = -0.000000
tan(0) = 0.000000
tan(PI) = -0.000000
tan(PI / 2) = 16331239353195370.000000
tan(2 * PI) = -0.000000
tan(NAN) = nan
tan(INFINITY) = -nan(ind)
*/
```

>---

#### acos、asin、atan （反三角函数）

```c
// 反余弦函数 [-1, +1] >> [0, PI]
double acos(double x);
float acosf(float x);
long double acosl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 acosd32(_Decimal32 x);
_Decimal64 acosd64(_Decimal64 x);
_Decimal128 acosd128(_Decimal128 x);
#endif  

// 反正弦函数 [-1, +1] >> [-PI/2, PI/2]
double asin(double x);
float asinf(float x);
long double asinl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 asind32(_Decimal32 x);
_Decimal64 asind64(_Decimal64 x);
_Decimal128 asind128(_Decimal128 x);
#endif

// 反正切函数 [-inf, +inf] >> [-PI/2, PI/2]
double atan(double x);
float atanf(float x);
long double atanl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 atand32(_Decimal32 x);
_Decimal64 atand64(_Decimal64 x);
_Decimal128 atand128(_Decimal128 x);
#endif
```

`acos` 函数计算 x 的反余弦值。如果参数不在区间 $[-1，+1]$ 内，则会发生域错误。函数返回 $[0, \pi]$ 弧度区间的值。

`asin` 函数计算 x 的反正弦值。如果参数不在区间 $[-1，+1]$ 内，则会发生域错误。如果非零 x 太接近零，则会发生范围错误。函数返回 $[−π/2 , +π/2 ]$ 弧度区间的值。

`atan` 函数计算 x 的反正切值。如果非零 x 太接近零，则会发生范围错误。函数返回 $[−π/2 , +π/2]$ 弧度区间的值。

```c
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <float.h>

#define ACos(x)  printf("acos("#x") = %f\n", acos(x));
#define ASin(x)  printf("asin("#x") = %f\n", asin(x));
#define ATan(x)  printf("atan("#x") = %f\n", atan(x));

#define PI M_PI

int main() {
	ACos(0);
	ACos(-1);
	ACos(1);
	ACos(DBL_MAX);
	ACos(NAN);
	ACos(-NAN);
	ACos(INFINITY);
	ACos(-INFINITY);

	ASin(0);
	ASin(-1);
	ASin(1);

	ATan(0);
	ATan(NAN);
	ATan(DBL_MAX);
	ATan(INFINITY);
}
/*
acos(0) = 1.570796
acos(-1) = 3.141593
acos(1) = 0.000000
acos(DBL_MAX) = -nan(ind)
acos(NAN) = nan
acos(-NAN) = -nan(ind)
acos(INFINITY) = -nan(ind)
acos(-INFINITY) = -nan(ind)
asin(0) = 0.000000
asin(-1) = -1.570796
asin(1) = 1.570796
atan(0) = 0.000000
atan(NAN) = nan
atan(DBL_MAX) = 1.570796
atan(INFINITY) = 1.570796
*/
```

>---
#### acospi、asinpi、atanpi （测量半圆角度）
 
```c
// acos/pi  [-1, +1] >> [0, 1]
double acospi(double x);
float acospif(float x);
long double acospil(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 acospid32(_Decimal32 x);
_Decimal64 acospid64(_Decimal64 x);
_Decimal128 acospid128(_Decimal128 x);
#endif

// asin/pi  [-1, +1] >> [-1/2, +1/2]
double asinpi(double x);
float asinpif(float x);
long double asinpil(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 asinpid32(_Decimal32 x);
_Decimal64 asinpid64(_Decimal64 x);
_Decimal128 asinpid128(_Decimal128 x);
#endif

// atan/pi  [-inf, +inf] >> [-1/2, 1/2]
double atanpi(double x);
float atanpif(float x);
long double atanpil(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 atanpid32(_Decimal32 x);
_Decimal64 atanpid64(_Decimal64 x);
_Decimal128 atanpid128(_Decimal128 x);
#endif
```

`acospi` 函数计算 x 的 $arccons(x) / π$，从而测量半圈的角度。如果参数不在区间 $[-1，+1]$ 内，则会发生域错误。函数返回 $[0, 1]$ 弧度区间的 $arccos(x) / π$ 值。

`asinpi` 函数计算 x 的 $arcsin(x) / π$，从而测量半圈的角度。如果参数不在区间 $[-1，+1]$ 内，则会发生域错误。如果非零 x 太接近零，则会发生范围错误。函数返回 $[−1/2 , +1/2]$ 弧度区间的 $arcsin(x) / π$ 值。

`atanpi` 函数计算 x 的 $arctan(x) / π$，从而测量半圈的角度。如果非零 x 太接近零，则会发生范围错误。函数返回 $[−1/2 , +1/2]$ 弧度区间的 $arctan(x) / π$ 值。

>---

#### atan2 （四象限反正切函数）

```c
// ((x|-inf,inf), (y|-inf,inf)) >> [-PI, PI] 
double atan2(double y, double x);
float atan2f(float y, float x);
long double atan2l(long double y, long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 atan2d32(_Decimal32 y, _Decimal32 x);
_Decimal64 atan2d64(_Decimal64 y, _Decimal64 x);
_Decimal128 atan2d128(_Decimal128 y, _Decimal128 x);
#endif
```

`atan2` 函数计算 $y/x$ 的反正切值，使用两个参数的符号来确定返回值的象限。如果两个参数都为零，则可能发生域错误。如果 $x$ 为正且非零值太接近零，则会发生范围错误。函数返回在  $[−π, +π]$ 弧度区间的 $arctan(y/x)$。

> 四象限反正切函数 `atan2(y,x)` 值域分布示意

四象限反正切函数用于确定点 $(x, y)$ 在直角坐标系的位置。

![](.img/四象限反正切函数atan2(y,x)值域分布图.png)

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

>---
#### atan2pi

```c
double atan2pi(double y, double x);
float atan2pif(float y, float x);
long double atan2pil(long double y, long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 atan2pid32(_Decimal32 y, _Decimal32 x);
_Decimal64 atan2pid64(_Decimal64 y, _Decimal64 x);
_Decimal128 atan2pid128(_Decimal128 y, _Decimal128 x);
#endif
```

`atan2pi` 函数计算在原点由点 (x，y) 和正 X 轴方向的半圈角度。`atan2pi` 函数计算 `arctan(y/x)/π`，范围为 $[−1，+1]$。如果两个参数都为零，则可能发生域错误。如果 `x` 为正且非零值太接近零，则会发生范围错误。函数返回计算的角度，区间为 $[−1，+1]$。

>---
#### cospi、sinpi、tanpi （_fun_(pi * x)）

```c
// cospi(x)  >>  return cos(pi * x)
double cospi(double x);
float cospif(float x);
long double cospil(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 cospid32(_Decimal32 x);
_Decimal64 cospid64(_Decimal64 x);
_Decimal128 cospid128(_Decimal128 x);
#endif

// sinpi(x)  >>  return sin(pi * x)
double sinpi(double x);
float sinpif(float x);
long double sinpil(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 sinpid32(_Decimal32 x);
_Decimal64 sinpid64(_Decimal64 x);
_Decimal128 sinpid128(_Decimal128 x);
#endif

// tanpi(x)  >>  return tan(pi * x)
double tanpi(double x);
float tanpif(float x);
long double tanpil(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 tanpid32(_Decimal32 x);
_Decimal64 tanpid64(_Decimal64 x);
_Decimal128 tanpid128(_Decimal128 x);
#endif
```

`cospi` 函数计算 $π × x$ 的余弦。`sinpi` 函数计算 $π×x$ 的正弦。

`tanpi` 函数计算 $π × x$ 的正切。如果非零 $x$ 太接近零，则会发生范围错误。对于整数 $n$，如果 $|x|$ 是 $(n + 0.5)$，则可能发生极点错误。
 
---
### Functions：双曲函数（Hyperbolic functions）

#### cosh、sinh、tanh （双曲函数）

```c
// 双曲余弦函数 
double cosh(double x);
float coshf(float x);
long double coshl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 coshd32(_Decimal32 x);
_Decimal64 coshd64(_Decimal64 x);
_Decimal128 coshd128(_Decimal128 x);
#endif

// 双曲正弦函数
double sinh(double x);
float sinhf(float x);
long double sinhl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 sinhd32(_Decimal32 x);
_Decimal64 sinhd64(_Decimal64 x);
_Decimal128 sinhd128(_Decimal128 x);
#endif

// 双曲正切函数
double tanh(double x);
float tanhf(float x);
long double tanhl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 tanhd32(_Decimal32 x);
_Decimal64 tanhd64(_Decimal64 x);
_Decimal128 tanhd128(_Decimal128 x);
#endif
```

`cosh` 函数计算 x 的双曲余弦。如果有限 x 的幅度太大，则会出现范围错误。

`sinh` 函数计算 x 的双曲正弦。如果有限 x 的幅度太大或非零 x 太接近于零，则会出现范围错误。

`tanh` 函数计算 x 的双曲正切。如果非零 x 太接近零，则会发生范围错误。

>---

#### acosh、asinh、atanh （反双曲函数）

```c
// 反双曲余弦函数 (1, +inf) >> [0, +inf]
double acosh(double x);
float acoshf(float x);
long double acoshl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 acoshd32(_Decimal32 x);
_Decimal64 acoshd64(_Decimal64 x);
_Decimal128 acoshd128(_Decimal128 x);
#endif		

// 反双曲正弦函数 [-inf, +inf]
double asinh(double x);
float asinhf(float x);
long double asinhl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 asinhd32(_Decimal32 x);
_Decimal64 asinhd64(_Decimal64 x);
_Decimal128 asinhd128(_Decimal128 x);
#endif

// 反双曲正切函数  
double atanh(double x);
float atanhf(float x);
long double atanhl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 atanhd32(_Decimal32 x);
_Decimal64 atanhd64(_Decimal64 x);
_Decimal128 atanhd128(_Decimal128 x);
#endif
```

`acosh` 函数计算 x 的（非负）反双曲余弦。小于 1 的参数发生域错误。函数在区间 $[0，+∞]$ 中返回。

`asinh` 函数计算 x 的反双曲正弦。如果非零 x 太接近零，则会发生范围错误。

`atanh` 函数计算 x 的反双曲正切。如果参数不在区间 $[-1，+1]$ 内，则会发生域错误。如果参数等于 -1 或 +1，则可能发生极点错误。如果非零 x 太接近零，则会发生范围错误。


---
### Functions：指数、对数函数（Exponential and logarithmic functions）

#### exp、expm1、exp10、exp10m1、exp2、exp2m1 （指数相关）

```c
// 计算 e^x 
double exp(double x);
float expf(float x);
long double expl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 expd32(_Decimal32 x);
_Decimal64 expd64(_Decimal64 x);
_Decimal128 expd128(_Decimal128 x);
#endif

// 计算 e^x -1 
double expm1(double x);
float expm1f(float x);
long double expm1l(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 expm1d32(_Decimal32 x);
_Decimal64 expm1d64(_Decimal64 x);
_Decimal128 expm1d128(_Decimal128 x);
#endif

// 计算 10^x
double exp10(double x);
float exp10f(float x);
long double exp10l(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 exp10d32(_Decimal32 x);
_Decimal64 exp10d64(_Decimal64 x);
_Decimal128 exp10d128(_Decimal128 x);
#endif

// 计算 10^x -1
double exp10m1(double x);
float exp10m1f(float x);
long double exp10m1l(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 exp10m1d32(_Decimal32 x);
_Decimal64 exp10m1d64(_Decimal64 x);
_Decimal128 exp10m1d128(_Decimal128 x);
#endif

// 计算 2^x
double exp2(double x);
float exp2f(float x);
long double exp2l(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 exp2d32(_Decimal32 x);
_Decimal64 exp2d64(_Decimal64 x);
_Decimal128 exp2d128(_Decimal128 x);
#endif

// 计算 2^x -1
#include <math.h>
double exp2m1(double x);
float exp2m1f(float x);
long double exp2m1l(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 exp2m1d32(_Decimal32 x);
_Decimal64 exp2m1d64(_Decimal64 x);
_Decimal128 exp2m1d128(_Decimal128 x);
#endif
```

`eexp` 函数计算 $e^x$。如果有限的 x 的幅度太大，则会发生范围错误。

`expm1` 函数计算 $e^x-1$。如果正有限 x 太大或非零 x 太接近零，则会发生范围错误。

`exp10` 函数计算 $10^x$。如果有限 x 的幅度太大，则会出现范围错误。

`exp10m1` 函数计算 $10^x-1$。如果正有限 x 太大或非零 x 太接近零，则会发生范围错误。

`exp2` 函数计算 $2^x$。如果有限 x 的幅度太大，则会出现范围错误。

`exp2m1` 函数计算 $2^x-1$。如果正有限 x 太大或非零 x 太接近零，则会发生范围错误。


- 对于小量级的 x，`expm1(x)` 计算 $e^x-1$ 比 `exp(x)-1` 更准确。

```c
#include <stdio.h>
#include <math.h>

#define Exp_compare(x) \
printf("exp("#x")-1 = %.25f\n", exp(x) - 1); \
printf("expm1("#x") = %.25f\n", expm1(x))

int main()
{
	Exp_compare(1);
	Exp_compare(10);
	Exp_compare(100);
	Exp_compare(0.1);	// 出现误差
	Exp_compare(0.01);	// 出现误差
	Exp_compare(0.2);	// 出现误差
	Exp_compare(0.25);	// 出现误差
	Exp_compare(0.4);
}
/*
exp(1)-1 = 1.7182818284590450907955983
expm1(1) = 1.7182818284590450907955983
exp(10)-1 = 22025.4657948067178949713706970
expm1(10) = 22025.4657948067178949713706970
exp(100)-1 = 26881171418161356094253400435962903554686976.0000000000000000000000000
expm1(100) = 26881171418161356094253400435962903554686976.0000000000000000000000000
exp(0.1)-1 = 0.1051709180756477124418780
expm1(0.1) = 0.1051709180756476291751511
exp(0.01)-1 = 0.0100501670841679491275045
expm1(0.01) = 0.0100501670841680584150835
exp(0.2)-1 = 0.2214027581601698546620582
expm1(0.2) = 0.2214027581601698546620582
exp(0.25)-1 = 0.2840254166877413943836928
expm1(0.25) = 0.2840254166877415054059952
exp(0.4)-1 = 0.4918246976412703475034505
expm1(0.4) = 0.4918246976412703475034505
*/
```

>---

#### frexp、ldexp （X * 2^exp）

```c
// // 拆分成数和 2 的幂次
double frexp(double value, int *p);
float frexpf(float value, int *p);
long double frexpl(long double value, int *p);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 frexpd32(_Decimal32 value, int *p);
_Decimal64 frexpd64(_Decimal64 value, int *p);
_Decimal128 frexpd128(_Decimal128 value, int *p);
#endif

// 计算数和 2 的幂次乘积
double ldexp(double x, int p);
float ldexpf(float x, int p);
long double ldexpl(long double x, int p);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 ldexpd32(_Decimal32 x, int p);
_Decimal64 ldexpd64(_Decimal64 x, int p);
_Decimal128 ldexpd128(_Decimal128 x, int p);
#endif
```

`frexp` 函数将浮点数分解为规格化分数和整数指数，整数存储在 `exp` 指向的对象中。如果函数的返回类型是标准的浮点类型，则指数是 2 的整数幂。如果函数的返回类型是十进制浮点类型，则指数是 10 的整数次幂。

当 `ldexp` 函数的返回类型为标准浮点类型时，函数返回 $x × 2^p$；当函数的返回类型为十进制浮点类型时，函数返回 $x × 10^p$。对于某个有限的 x，可能会出现范围错误，这取决于 p。


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

>---

#### log、log10、log10p1、log1p、logp1、  log2、log1p （对数相关）

```c
// 自然对数 ln(x)
double log(double x);
float logf(float x);
long double logl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 logd32(_Decimal32 x);
_Decimal64 logd64(_Decimal64 x);
_Decimal128 logd128(_Decimal128 x);
#endif

// 10 为底的对数
double log10(double x);
float log10f(float x);
long double log10l(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 log10d32(_Decimal32 x);
_Decimal64 log10d64(_Decimal64 x);
_Decimal128 log10d128(_Decimal128 x);
#endif

// 计算 log10(1 + x)
double log10p1(double x);
float log10p1f(float x);
long double log10p1l(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 log10p1d32(_Decimal32 x);
_Decimal64 log10p1d64(_Decimal64 x);
_Decimal128 log10p1d128(_Decimal128 x);
#endif

// 计算 ln(x+1)， 等效于 logp1
double log1p(double x);
float log1pf(float x);
long double log1pl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 log1pd32(_Decimal32 x);
_Decimal64 log1pd64(_Decimal64 x);
_Decimal128 log1pd128(_Decimal128 x);
#endif

// 计算 ln(x+1)
double logp1(double x);
float logp1f(float x);
long double logp1l(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 logp1d32(_Decimal32 x);
_Decimal64 logp1d64(_Decimal64 x);
_Decimal128 logp1d128(_Decimal128 x);
#endif

// 2 为底的对数
double log2(double x);
float log2f(float x);
long double log2l(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 log2d32(_Decimal32 x);
_Decimal64 log2d64(_Decimal64 x);
_Decimal128 log2d128(_Decimal128 x);
#endif

// 计算 log2(1 + x)
double log2p1(double x);
float log2p1f(float x);
long double log2p1l(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 log2p1d32(_Decimal32 x);
_Decimal64 log2p1d64(_Decimal64 x);
_Decimal128 log2p1d128(_Decimal128 x);
#endif
```

`log` 函数计算 $log_ex$ 的值，如果参数小于零，则会发生域错误。如果参数为零，则可能发生极点错误。

`log10` 函数计算 $log_{10} x$。如果参数小于零，则发生域错误。如果参数为零，则可能发生极点错误。

`log10p1` 函数计算 $log_{10}(1 + x)$。如果参数小于 -1，则发生域错误。如果参数等于 -1，则可能发生极点错误。如果非零 x 太接近零，则会发生范围错误。

`log1p` 函数等效于 `logp1`，目的是为了与 `log10p1` 保持名称一致。这些函数计算 $log_e(1 + x)$。如果参数小于 -1，则发生域错误。如果参数等于 -1，则可能发生极点错误。如果非零 x 太接近零，则会发生范围错误。

`log2` 函数计算 $log_{2} x$。如果参数小于零，则发生域错误。如果参数为零，则可能发生极点错误。

`log2p1` 函数计算 $log_{2}(1 + x)$。如果参数小于 -1，则发生域错误。如果参数等于 -1，则可能发生极点错误。如果非零 x 太接近零，则会发生范围错误。

对于较小的量级 x, `logp1(x)` 预期比 `log(1+x)` 更准确。

```c
#include <stdio.h>
#include <math.h>

#define Log_Compare(x)							\
	printf("log("#x"+1) = %.25f\n", log((x)+1));	\
	printf("log1p("#x") = %.25f\n", log1p(x))

int main()
{
	Log_Compare(10);
	Log_Compare(100);
	Log_Compare(1000);
	Log_Compare(0.1);			// 出现误差
	Log_Compare(0.01);			// 出现误差
}
/*
log(10+1) = 2.3978952727983706694203647
log1p(10) = 2.3978952727983706694203647
log(100+1) = 4.6151205168412596790972202
log1p(100) = 4.6151205168412596790972202
log(1000+1) = 6.9087547793152204178568354
log1p(1000) = 6.9087547793152204178568354
log(0.1+1) = 0.0953101798043249348602046
log1p(0.1) = 0.0953101798043248654712656
log(0.01+1) = 0.0099503308531680920157036
log1p(0.01) = 0.0099503308531680833420863
*/
```

>---

#### logb、ilogb、llogb （X = 2^exp）

```c
// 提取 x 指数，返回浮点格式的有符号整数值
double logb(double x);
float logbf(float x);
long double logbl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 logbd32(_Decimal32 x);
_Decimal64 logbd64(_Decimal64 x);
_Decimal128 logbd128(_Decimal128 x);
#endif

// 提取 x 指数，返回有符号整数值
int ilogb(double x);
int ilogbf(float x);
int ilogbl(long double x);
#ifdef __STDC_IEC_60559_DFP__
int ilogbd32(_Decimal32 x);
int ilogbd64(_Decimal64 x);
int ilogbd128(_Decimal128 x);
#endif

// 提取 x 指数，返回有符号整数值 long int
long int llogb(double x);
long int llogbf(float x);
long int llogbl(long double x);
#ifdef __STDC_IEC_60559_DFP__
long int llogbd32(_Decimal32 x);
long int llogbd64(_Decimal64 x);
long int llogbd128(_Decimal128 x);
#endif


double logb(double x);			// 
float logbf(float x);
long double logbl(long double x);

int ilogb(double x);			
int ilogbf(float x);	
int ilogbl(long double x);
```

`logb` 函数提取 x 的指数，作为浮点格式的有符号整数值。如果 x 是非正规的，它被当作是正规化的；因此，对于正有限 x，$1 <= x × b^{-logb(x)} < b$，其中，如果函数的返回类型是标准浮点类型，则 b = `FLT_RADIX`；如果函数的返回类型是十进制浮点类型，则 b = 10。如果参数为零，则可能发生域错误或极点错误。

`ilogb` 函数将 x 的指数提取为有符号 `int` 值。若 `x = 0`，则计算值 `FP_ILOGB0`；若 `x = NAN`，则计算值 `FP_ILOGBNAN`；否则，它们相当于调用 `logb` 函数并将返回值转换为 `int` 类型。如果 x 为 0、无穷大或 NaN，可能发生域错误或范围错误。如果正确的值在返回类型的范围之外，则数值结果未指定，并且可能发生域错误或范围错误。

`llogb` 函数将 x 的指数提取为一个有符号的 `long int` 值。如果 x 为零，则计算值 `FP_LLOGB0`；如果 x 为无穷大，则计算值 `LONG_MAX`；如果 x 为 NaN，则计算值 `FP_LLOGBNAN`；否则，它们相当于调用相应的 `logb` 函数并将返回值转换为 `long int` 类型。如果 x 为零、无穷大或 NaN，则可能发生域错误或范围错误。如果正确的值在返回类型的范围之外，则数值结果未指定。

```c
#include <stdio.h>
#include <math.h>

void Logb(double x) {
	double exp = logb(x);
	printf("logb(%.6f) = %.6f\n", x, exp);
	printf("ilogb(%f) = %d\n", x, ilogb(x));
}

int main()
{
	Logb(1);
	Logb(100);
	Logb(0.1);
	Logb(0);
	Logb(INFINITY);
}
/*
logb(1.000000) = 0.000000
ilogb(1.000000) = 0
logb(100.000000) = 6.000000
ilogb(100.000000) = 6
logb(0.100000) = -4.000000
ilogb(0.100000) = -4
logb(0.000000) = -inf
ilogb(0.000000) = -2147483648
logb(inf) = inf
ilogb(inf) = 2147483647
*/
```

>---

#### modf （拆分整数小数）

```c
double modf(double value, double *iptr);
float modff(float value, float *iptr);
long double modfl(long double value, long double *iptr);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 modfd32(_Decimal32 x, _Decimal32 *iptr);
_Decimal64 modfd64(_Decimal64 x, _Decimal64 *iptr);
_Decimal128 modfd128(_Decimal128 x, _Decimal128 *iptr);
#endif
```

`modf` 函数将参数值分解为整数和小数部分。它们将整型部分（以浮点格式）存储在 iptr 所指向的对象中，并返回带符号小数部分。

```c
#include <stdio.h>
#include <math.h>

void Modf(double value) {
	double intptr;
	double rt = modf(value, &intptr);
	printf("%f = (%.f) + (%f)\n", value, intptr, rt);
}

int main()
{
	Modf(1.1);
	Modf(-100.123);
	Modf(0);
	Modf(100);
	Modf(-0.0);
	Modf(NAN);
	Modf(INFINITY);
}
/*
1.100000 = (1) + (0.100000)
-100.123000 = (-100) + (-0.123000)
0.000000 = (0) + (0.000000)
100.000000 = (100) + (0.000000)
-0.000000 = (-0) + (-0.000000)
nan = (nan) + (nan)
inf = (inf) + (0.000000)
*/
```

>---

#### scalbn、scalnln （计算 X × b 的幂）

```c
double scalbn(double x, int n);
float scalbnf(float x, int n);
long double scalbnl(long double x, int n);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 scalbnd32(_Decimal32 x, int n);
_Decimal64 scalbnd64(_Decimal64 x, int n);
_Decimal128 scalbnd128(_Decimal128 x, int n);
#endif

double scalbln(double x, long int n);
float scalblnf(float x, long int n);
long double scalblnl(long double x, long int n);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 scalblnd32(_Decimal32 x, long int n);
_Decimal64 scalblnd64(_Decimal64 x, long int n);
_Decimal128 scalblnd128(_Decimal128 x, long int n);
#endif
```

`scalbn` 和 `scalnln` 用于计算 $x * b ^ n$ 的值，其中，如果函数的返回类型是标准浮点类型，则 b = `FLT_RADIX`；如果函数的返回类型是十进制浮点类型，则 b = 10。根据 n 的不同，对于某个有限的 x 会发生范围错误。

```c
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <limits.h>

#define Scalbn(x, n) printf(#x" * %d ^ "#n" = %f\n", FLT_RADIX, scalbn(x, n))

int main()
{
	Scalbn(1.1, 10);
	Scalbn(1.1, INT_MAX);
	Scalbn(INFINITY, 10);
	Scalbn(1.1, INFINITY);
	Scalbn(INFINITY, INFINITY);
	Scalbn(NAN, 10);
	Scalbn(1.1, NAN);
	Scalbn(NAN, INT_MAX);

	printf("(int)NAN = %d\n", (int)NAN);
	printf("(int)INFINITY = %d\n", (int)INFINITY);
}
/*
1.1 * 2 ^ 10 = 1126.400000
1.1 * 2 ^ INT_MAX = inf
INFINITY * 2 ^ 10 = inf
1.1 * 2 ^ INFINITY = 0.000000
INFINITY * 2 ^ INFINITY = inf
NAN * 2 ^ 10 = nan
1.1 * 2 ^ NAN = 0.000000
NAN * 2 ^ INT_MAX = nan
(int)NAN = 0
(int)INFINITY = 0
*/
```

---
### Functions：幂函数和绝对值函数（Power and absolute-value functions）

#### sqrt （平方根）

```c
double sqrt(double x);		// 平方根，计算 x^(1/2) 
float sqrtf(float x);
long double sqrtl(long double x);
```

>---
#### rsqrt （平方根倒数）

```c
double rsqrt(double x);
float rsqrtf(float x);
long double rsqrtl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 rsqrtd32(_Decimal32 x);
_Decimal64 rsqrtd64(_Decimal64 x);
_Decimal128 rsqrtd128(_Decimal128 x);
#endif
```

`rsqrt` 函数计算参数的非负平方根的倒数（$1/\sqrt{x}$）。如果参数小于零，则发生域错误。如果自变量等于零，则可能发生极点错误。

>---

#### cbrt （立方根）

```c
// 立方根，计算 x^(1/3)
double cbrt(double x);
float cbrtf(float x);
long double cbrtl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 cbrtd32(_Decimal32 x);
_Decimal64 cbrtd64(_Decimal64 x);
_Decimal128 cbrtd128(_Decimal128 x);
#endif
```

>---
#### rootn （n 次根）

```c
double rootn(double x, long long int n);
float rootnf(float x, long long int n);
long double rootnl(long double x, long long int n);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 rootnd32(_Decimal32 x, long long int n);
_Decimal64 rootnd64(_Decimal64 x, long long int n);
_Decimal128 rootnd128(_Decimal128 x, long long int n);
#endif
```

`rootn` 函数计算 $x^{1/n}$。如果 n 为 0 或 x < 0 且 n 为偶数，则发生域错误。如果 n 为 −1，则如果非零有限 x 的幅度太大或太接近零，则会出现范围错误。如果 x 等于零且 n < 0，则可能发生极点错误。

>---
#### compoundn

```c
double compoundn(double x, long long int n);
float compoundnf(float x, long long int n);
long double compoundnl(long double x, long long int n);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 compoundnd32(_Decimal32 x, long long int n);
_Decimal64 compoundnd64(_Decimal64 x, long long int n);
_Decimal128 compoundnd128(_Decimal128 x, long long int n);
#endif
```

`compoundn` 函数计算 $(1+x)^n$ 的值。如果 x < −1，则发生域错误。取决于 n，如果正有限 x 太大或 x 接近但不等于 -1，则会出现范围错误。如果 x 等于 −1 且 n < 0，则可能出现极点错误。

>---

#### pow、pown、powr （数的给定次幂）

```c
// 计算 x^y 的值
double pow(double x, double y);
float powf(float x, float y);
long double powl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 powd32(_Decimal32 x, _Decimal32 y);
_Decimal64 powd64(_Decimal64 x, _Decimal64 y);
_Decimal128 powd128(_Decimal128 x, _Decimal128 y);
#endif

// 计算 x^n
double pown(double x, long long int n);
float pownf(float x, long long int n);
long double pownl(long double x, long long int n);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 pownd32(_Decimal32 x, long long int n);
_Decimal64 pownd64(_Decimal64 x, long long int n);
_Decimal128 pownd128(_Decimal128 x, long long int n);
#endif

// 计算 e^(y * ln(x))
double powr(double y, double x);
float powrf(float y, float x);
long double powrl(long double y, long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 powrd32(_Decimal32 y, _Decimal32 x);
_Decimal64 powrd64(_Decimal64 y, _Decimal64 x);
_Decimal128 powrd128(_Decimal128 y, _Decimal128 x);
#endif
```

`pow` 函数计算 $x^y$。如果 x 是有限的且小于零，并且 y 是有限的且不是整数值，则发生域错误。如果 x 为零且 y 为零，则可能发生域错误。取决于 y，如果非零有限 x 的幅度太大或太接近零，则会发生范围错误。如果 x 为零且 y 小于零，则可能发生域错误或极点错误。

`pown` 函数计算 $x^n$。如果 x 等于 0 且 n < 0，则可能发生极点错误。取决于 n，如果非零有限 x 的幅度太大或太接近零，则会发生距离错误。

`powr` 函数计算 $e^{y log_e x}$。如果 x < 0 或 x 和 y 都为零，则发生域错误。取决于 y，如果正的非零有限 x 太大或太接近零，则会发生范围错误。如果 x 等于零并且有限 y < 0，则可能发生极点错误。

>---

#### hypot （两数平方和的平方根）

```c
// 计算 (x^2 + y^2)^(1/2)
double hypot(double x, double y);
float hypotf(float x, float y);
long double hypotl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 hypotd32(_Decimal32 x, _Decimal32 y);
_Decimal64 hypotd64(_Decimal64 x, _Decimal64 y);
_Decimal128 hypotd128(_Decimal128 x, _Decimal128 y);
#endif	
```

`hypot` 函数计算 $\sqrt{x^2+y^2}$，没有过度的上溢或下溢。对于某些有限参数，会出现范围错误。

>---
#### fabs （绝对值）

```c
// 计算 x 的绝对值
double fabs(double x);
float fabsf(float x);
long double fabsl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fabsd32(_Decimal32 x);
_Decimal64 fabsd64(_Decimal64 x);
_Decimal128 fabsd128(_Decimal128 x);
#endif
```

---
### Functions：误差及伽马函数 （Error and gamma functions）

#### erf、erfc （误差与互补误差函数）

```c
// erf 计算 x 的误差函数
double erf(double x);
float erff(float x);
long double erfl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 erfd32(_Decimal32 x);
_Decimal64 erfd64(_Decimal64 x);
_Decimal128 erfd128(_Decimal128 x);
#endif

// erfc 计算 x 的互补误差函数
double erfc(double x);
float erfcf(float x);
long double erfcl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 erfcd32(_Decimal32 x);
_Decimal64 erfcd64(_Decimal64 x);
_Decimal128 erfcd128(_Decimal128 x);
#endif
```

`erf` 函数计算 x 的误差函数。如果非零 x 太接近零，则会发生范围错误。误差函数：`erf(x)` = $\frac{2}{\sqrt{\pi}} \int_0^{x} e^{-t^2}dt$.

`erfc` 函数计算 x 的互补误差函数。如果正有限 x 太大，则会出现范围错误。互补误差函数：`erfc(x)` = `1-erf(x)` = $\frac{2}{\sqrt{\pi}} \int_x^{\infty} e^{-t^2}dt$.

>---

#### tgamma、lgamma （伽马函数与它的自然对数）

```c
// 伽马函数
double tgamma(double x);
float tgammaf(float x);
long double tgammal(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 tgammad32(_Decimal32 x);
_Decimal64 tgammad64(_Decimal64 x);
_Decimal128 tgammad128(_Decimal128 x);
#endif

// 伽马函数的自然对数
double lgamma(double x);
float lgammaf(float x);
long double lgammal(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 lgammad32(_Decimal32 x);
_Decimal64 lgammad64(_Decimal64 x);
_Decimal128 lgammad128(_Decimal128 x);
#endif
```

`tgamma` 函数计算 x 的伽马函数。如果 x 是负整数或零，可能会出现域错误或极点错误。对于小于零的某个有限 x，如果正有限 x 太大，或者非零 x 太接近零，则会发生范围错误。

`lgamma` 函数计算 x 的伽马绝对值的自然对数。如果正有限 x 太大，则会出现范围错误。如果 x 是负整数或零，则可能发生极点错误。

阶乘函数仅针对离散点，伽马函数是对阶乘函数的泛化。 `tgamma(x)` = $\Gamma(x) = \int_0^{\infty} t^{x-1} e^{-t}dt$。对于自然数 $x$，有 $x!$ = $\Gamma (x+1)$

`lgamma(x)` 是 `tgamma(x)` 的自然对数，即 $log_e|\Gamma(x)|$。

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

---
### Functions：近似整数函数（Nearest integer functions）

#### ceil、floor （取整）

```c
// 向上取整，返回不小于 x 的最小整数 
double ceil(double x);
float ceilf(float x);
long double ceill(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 ceild32(_Decimal32 x);
_Decimal64 ceild64(_Decimal64 x);
_Decimal128 ceild128(_Decimal128 x);
#endif

// 向下取整，返回不大于 x 的最大整数
double floor(double x);
float floorf(float x);
long double floorl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 floord32(_Decimal32 x);
_Decimal64 floord64(_Decimal64 x);
_Decimal128 floord128(_Decimal128 x);
#endif
```

>---

#### nearbyint、rint、lrint、llrint（根据当前舍入方向求近似整数）

```c
// 使用当前舍入方向，进行取整，不产生浮点异常
double nearbyint(double x);
float nearbyintf(float x);
long double nearbyintl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 nearbyintd32(_Decimal32 x);
_Decimal64 nearbyintd64(_Decimal64 x);
_Decimal128 nearbyintd128(_Decimal128 x);
#endif

// 使用当前舍入方向，进行取整，可能产生浮点异常
double rint(double x);
float rintf(float x);
long double rintl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 rintd32(_Decimal32 x);
_Decimal64 rintd64(_Decimal64 x);
_Decimal128 rintd128(_Decimal128 x);
#endif

long int lrint(double x);
long int lrintf(float x);
long int lrintl(long double x);
long long int llrint(double x);
long long int llrintf(float x);
long long int llrintl(long double x);
#ifdef __STDC_IEC_60559_DFP__
long int lrintd32(_Decimal32 x);
long int lrintd64(_Decimal64 x);
long int lrintd128(_Decimal128 x);
long long int llrintd32(_Decimal32 x);
long long int llrintd64(_Decimal64 x);
long long int llrintd128(_Decimal128 x);
#endif
```

`rint` 函数与 `nearbyint` 函数的不同之处在于，如果结果与实参的值不同，`rint` 函数可能会引发 “inexact” 浮点异常。如果舍入值超出返回类型的范围，则数值结果未指定，并且可能发生域错误或范围错误。

这些函数的求近似整数的行为受当前浮点环境舍入方向的影响。

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

#### round、lround、llround （四舍五入取整）

```c
// 浮点数四舍五入到最近的整数
double round(double x);
float roundf(float x);
long double roundl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 roundd32(_Decimal32 x);
_Decimal64 roundd64(_Decimal64 x);
_Decimal128 roundd128(_Decimal128 x);
#endif

#include <math.h>
long int lround(double x);
long int lroundf(float x);
long int lroundl(long double x);
long long int llround(double x);
long long int llroundf(float x);
long long int llroundl(long double x);
#ifdef __STDC_IEC_60559_DFP__
long int lroundd32(_Decimal32 x);
long int lroundd64(_Decimal64 x);
long int lroundd128(_Decimal128 x);
long long int llroundd32(_Decimal32 x);
long long int llroundd64(_Decimal64 x);
long long int llroundd128(_Decimal128 x);
#endif
```

`round`、`lround`、`llround` 函数的行为不受当前舍入模式的影响。如果舍入值超出返回类型的范围，则数值结果未指定，并且可能发生域错误或范围错误。

```c
#include <stdio.h>
#include <math.h>

#define Round(x) printf("round("#x") = %.2f\n", round(x));

int main()
{
	Round(1.1);
	Round(1.6);
	Round(0.5);
	Round(0.499999);
	Round(NAN);
	Round(INFINITY);
}
/*
round(1.1) = 1.00
round(1.6) = 2.00
round(0.5) = 1.00
round(0.499999) = 0.00
round(NAN) = nan
round(INFINITY) = inf
*/
```

>---
#### roundeven （像最接近偶数舍入）

```c
double roundeven(double x);
float roundevenf(float x);
long double roundevenl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 roundevend32(_Decimal32 x);
_Decimal64 roundevend64(_Decimal64 x);
_Decimal128 roundevend128(_Decimal128 x);
#endif
```

`roundeven` 函数将其参数舍入到浮点格式最接近的整数值，将中间情况舍入到偶数（即舍入到最接近的偶数值），不考虑当前舍入方向。


>---

#### trunc （向零舍入取整）

```c
double trunc(double x);
float truncf(float x);
long double truncl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 truncd32(_Decimal32 x);
_Decimal64 truncd64(_Decimal64 x);
_Decimal128 truncd128(_Decimal128 x);
#endif
```

`trunc` 函数将其参数舍入到浮点格式的最接近但不大于实参的整数值，不受当前舍入模式影响。

当 `x = ± 0/inf` 时，返回不修改的参数；当 `x = NAN` 时返回 `NAN`。

```c
#include <stdio.h>
#include <math.h>

#define Trunc(x) printf("Trunc("#x") = %f\n", trunc(x));

int main()
{
	Trunc(1.1111);
	Trunc(1.9999);
	Trunc(-1.1111);
	Trunc(-1.9999);
	Trunc(0);
	Trunc(0.0);
	Trunc(-0.0);

	Trunc(NAN);
	Trunc(-NAN);
	Trunc(INFINITY);
	Trunc(-INFINITY);
}
/*
Trunc(1.1111) = 1.000000
Trunc(1.9999) = 1.000000
Trunc(-1.1111) = -1.000000
Trunc(-1.9999) = -1.000000
Trunc(0) = 0.000000
Trunc(0.0) = 0.000000
Trunc(-0.0) = -0.000000
Trunc(NAN) = nan
Trunc(-NAN) = -nan(ind)
Trunc(INFINITY) = inf
Trunc(-INFINITY) = -inf
*/
```

>---
#### fromfp、ufromfp （根据舍入模式舍入到整数）

```c
// 舍入到有符号整数
double fromfp(double x, int rnd, unsigned int width);
float fromfpf(float x, int rnd, unsigned int width);
long double fromfpl(long double x, int rnd, unsigned int width);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fromfpd32(_Decimal32 x, int rnd, unsigned int width);
_Decimal64 fromfpd64(_Decimal64 x, int rnd, unsigned int width);
_Decimal128 fromfpd128(_Decimal128 x, int rnd, unsigned int width);
#endif

// 舍入到无符号整数
double ufromfp(double x, int rnd, unsigned int width);
float ufromfpf(float x, int rnd, unsigned int width);
long double ufromfpl(long double x, int rnd, unsigned int width);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 ufromfpd32(_Decimal32 x, int rnd, unsigned int width);
_Decimal64 ufromfpd64(_Decimal64 x, int rnd, unsigned int width);
_Decimal128 ufromfpd128(_Decimal128 x, int rnd, unsigned int width);
#endif
```

`fromfp` 和 `ufromfp` 函数分别使用 `rnd` 表示的数学舍入方式将 x 舍入为有符号整数或无符号整数。对于宽度 `width`，如果非零且它的范围在 $[−2^{(width−1)}, 2^{(width−1}) − 1]$（相对于有符号的 `fromfp`）或 $[0, 2^width − 1]$（相对于无符号的 `ufromfp`），函数返回相应的浮点格式的整数值。

如果 `width` 为零或 x 未舍入为对应范围内的整数，则函数返回 *NaN*（x 参数的类型，如果可用），否则返回 x 的值，并发生域错误。如果 `rnd` 参数的值不等于数学舍入方向宏的值，则舍入方向未指定。`fromfp` 和 `ufromfp` 函数不会引发 “inexact” 浮点异常。

```c
// 将 double x 向上舍入为 int 类型，而不引发 “不精确” 浮点异常，是通过以下方式实现的
(int)fromfp(x, FP_INT_UPWARD, INT_WIDTH);

// 定义域错误
ufromfp(-3.0, FP_INT_UPWARD, UINT_WIDTH);	 /* domain error */
```

>---
#### fromfpx、ufromfpx

```c
double fromfpx(double x, int rnd, unsigned int width);
float fromfpxf(float x, int rnd, unsigned int width);
long double fromfpxl(long double x, int rnd, unsigned int width);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fromfpxd32(_Decimal32 x, int rnd, unsigned int width);
_Decimal64 fromfpxd64(_Decimal64 x, int rnd, unsigned int width);
_Decimal128 fromfpxd128(_Decimal128 x, int rnd, unsigned int width);
#endif

double ufromfpx(double x, int rnd, unsigned int width);
float ufromfpxf(float x, int rnd, unsigned int width);
long double ufromfpxl(long double x, int rnd, unsigned int width);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 ufromfpxd32(_Decimal32 x, int rnd, unsigned int width);
_Decimal64 ufromfpxd64(_Decimal64 x, int rnd, unsigned int width);
_Decimal128 ufromfpxd128(_Decimal128 x, int rnd, unsigned int width);
#endif
```

`fromfpx` 和 `ufromfpx` 函数分别与 `fromfp` 和 `ufromfp` 函数的不同之处在于，如果不超过指定宽度的舍入结果与参数 x 的值不同，则 `fromfpx` 和 `ufromfpx` 函数将引发 “inexact” 浮点异常。

---
### Functions：余项函数（Remainder functions）

#### fmod、remainder （求浮点除法的余数）

```c
// 求 x/y 的余数
double fmod(double x, double y);
float fmodf(float x, float y);
long double fmodl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fmodd32(_Decimal32 x, _Decimal32 y);
_Decimal64 fmodd64(_Decimal64 x, _Decimal64 y);
_Decimal128 fmodd128(_Decimal128 x, _Decimal128 y);
#endif

// 求 x REM y（IEC 60559）
double remainder(double x, double y);
float remainderf(float x, float y);
long double remainderl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 remainderd32(_Decimal32 x, _Decimal32 y);
_Decimal64 remainderd64(_Decimal64 x, _Decimal64 y);
_Decimal128 remainderd128(_Decimal128 x, _Decimal128 y);
#endif
```

`fmod` 函数返回值 `x - ny`，对于某个整数 `n`，如果 `y` 非零，则结果与 `x` 符号相同且 `x - ny < y`。如果 `y` 为零，则是发生域错误还是 `fmod` 函数返回零是由实现定义的。

`remainder` 计算 `x - ny`，`n` 是最接近 `x/y` 准确值的整数值，求 `|n - x/y| = 1/2`，选择作为偶数的 `n`。

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

#### remquo （求商求余）

```c
double remquo(double x, double y, int *quo);
float remquof(float x, float y, int *quo);
long double remquol(long double x, long double y, int *quo);
```

`remquo` 与 `remainder` 使用相同的方法计算余数。在 `*quo` 中存储了一个值，其符号与 `x/y` 相同，其大小与 `x/y` 的整数商的大小取 $2^n$ 的模一致，其中 $n$ 是大于等于 3 的整数。

对于 `rem = remquo(x,y,*quo)` 满足 `x = y * quo + rem`。

```c
#include <stdio.h>
#include <math.h>

void Remquo(double x, double y)
{
	int quo;
	double rem = remquo(x, y, &quo);
	printf("Remquo(%f,%f) >>> quo = %d, rem = %f\n", x, y, quo, rem);
	printf("      %f * %d + %f = %f\n", y, quo, rem, y * quo + rem);
}

int main()
{
	Remquo(1.1, 10);
	Remquo(-2, 10);
	Remquo(5.00001, 10);
	Remquo(-5.00001, 10);
}
/*
Remquo(1.100000,10.000000) >>> quo = 0, rem = 1.100000
      10.000000 * 0 + 1.100000 = 1.100000
Remquo(-2.000000,10.000000) >>> quo = 0, rem = -2.000000
      10.000000 * 0 + -2.000000 = -2.000000
Remquo(5.000010,10.000000) >>> quo = 1, rem = -4.999990
      10.000000 * 1 + -4.999990 = 5.000010
Remquo(-5.000010,10.000000) >>> quo = -1, rem = 4.999990
      10.000000 * -1 + 4.999990 = -5.000010
*/
```

---
### Functions：浮点操作（Manipulation functions）

#### copysign （复制符号）

```c
// return = signbit(y)?-1:1 * fabs(x)
double copysign(double x, double y);	
float copysignf(float x, float y);
long double copysignl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 copysignd32(_Decimal32 x, _Decimal32 y);
_Decimal64 copysignd64(_Decimal64 x, _Decimal64 y);
_Decimal128 copysignd128(_Decimal128 x, _Decimal128 y);
#endif
```

`copysign` 函数生成一个大小为 x、符号为 y 的值。如果 x 或 y 是无符号值，则结果的符号（如果有的话）是实现定义的。在表示有符号零但在算术运算中不一致地处理负零的实现中，`copysign` 函数应将零的符号视为正数。

>---

#### nan （转换为 a quiet NAN）

```c
double nan(const char *tagp);
float nanf(const char *tagp);
long double nanl(const char *tagp);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 nand32(const char *tagp);
_Decimal64 nand64(const char *tagp);
_Decimal128 nand128(const char *tagp);
#endif
```

`nan` 函数按照以下方式转换 `tagp` 指向的字符串：
- `nan("n-char-sequence")` 相当于 `strtod("NAN(n-char-sequence)", nullptr)`；
- `nan("")` 相当于 `strtod("NAN()", nullptr)`；
- `nan` 函数将返回 *quiet* *NaN* 值。如果实现不支持，则函数返回零。

>---

#### nextafter、nexttoward （下一个有限浮点值）

```c
double nextafter(double from, double to);
float nextafterf(float from, float to);
long double nextafterl(long double from, long double to);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 nextafterd32(_Decimal32 from, _Decimal32 to);
_Decimal64 nextafterd64(_Decimal64 from, _Decimal64 to);
_Decimal128 nextafterd128(_Decimal128 from, _Decimal128 to);
#endif

double nexttoward(double from, long double to);
float nexttowardf(float from, long double to);
long double nexttowardl(long double from, long double to);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 nexttowardd32(_Decimal32 from, _Decimal128 to);
_Decimal64 nexttowardd64(_Decimal64 from, _Decimal128 to);
_Decimal128 nexttowardd128(_Decimal128 from, _Decimal128 to);
#endif
```

`nextafter` 和 `nexttoward` 首先转换两个参数为函数的类型，然后返回 `from` 到 `to` 方向的下个可表示的浮点数。当 `from = to` 时，`nextafter` 返回 `to`，而 `nexttoward` 返回从 `long double` 转换到函数返回类型的 `to`，且不带范围或精度的损失。
  - 当 `from` 有限，期待的结果无限时，则引发 `FE_INEXACT` 和 `FE_OVERFLOW`。
  - 当 `from` 或 `to` 为 `NAN` 时，结果返回 `NAN`。

```c
#include <math.h>
#include <stdio.h>
#include <float.h>

#define Nextafter(x,y) printf("nextafter("#x","#y") = %.15g (%a)\n", nextafter(x,y),nextafter(x,y))
#define Nexttoward(x,y) printf("nexttoward("#x","#y") = %.15g (%a)\n", nexttoward(x,y),nextafter(x,y))

int main(void)
{
	Nextafter(1, 1);
	Nextafter(1, 10);
	Nexttoward(1, 10);

	Nextafter(+0.0, -0.0);
	Nextafter(-0.0, +0.0);

	Nextafter(DBL_MAX, 1.1);
	Nextafter(1.1, DBL_MAX);
	
	Nextafter(INFINITY, 0);
	Nextafter(-INFINITY, 0);
	Nextafter(INFINITY, -INFINITY);
	Nextafter(INFINITY, INFINITY);
}
/*
nextafter(1,1) = 1 (0x1.0000000000000p+0)
nextafter(1,10) = 1 (0x1.0000000000001p+0)
nexttoward(1,10) = 1 (0x1.0000000000001p+0)

nextafter(+0.0,-0.0) = -0 (-0x0.0000000000000p+0)
nextafter(-0.0,+0.0) = 0 (0x0.0000000000000p+0)

nextafter(DBL_MAX,1.1) = 1.79769313486232e+308 (0x1.ffffffffffffep+1023)
nextafter(1.1,DBL_MAX) = 1.1 (0x1.199999999999bp+0)

nextafter(INFINITY,0) = 1.79769313486232e+308 (0x1.fffffffffffffp+1023)
nextafter(-INFINITY,0) = -1.79769313486232e+308 (-0x1.fffffffffffffp+1023)
nextafter(INFINITY,-INFINITY) = 1.79769313486232e+308 (0x1.fffffffffffffp+1023)
nextafter(INFINITY,INFINITY) = inf (inf)
*/
```

>---
#### nextup

```c
double nextup(double x);
float nextupf(float x);
long double nextupl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 nextupd32(_Decimal32 x);
_Decimal64 nextupd64(_Decimal64 x);
_Decimal128 nextupd128(_Decimal128 x);
#endif
```

`nextup` 函数确定下一个大于 x 的可表示的值。如果 x 是 x 的类型中最小的负数，则 `nextup(x)` 在该类型为有符号零时为 `−0`，否则为 `0`。如果 x 为零，则 `nextup(x)` 是 x 类型中最小值的正数。如果 x 是该类型中最大大小的正数（有限或无限），则 `nextup(x)` 是 x。

>---
#### nextdown

```c
double nextdown(double x);
float nextdownf(float x);
long double nextdownl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 nextdownd32(_Decimal32 x);
_Decimal64 nextdownd64(_Decimal64 x);
_Decimal128 nextdownd128(_Decimal128 x);
#endif
```

`nextdown`  函数确定下一个小于 x 的可表示的值。如果 x 是 x 的类型中最小的正数，则 `nextdown(x)` 在该类型为有符号零时为 `+0`，否则为 0。如果 x 为零，则 `nextdown(x)` 是 x 类型中最小的负数。如果 x 是该类型中最大大小的负数（有限或无限），则 `nextdown(x)` 为 x。

>---
#### canonicalize （规范化浮点数）

```c
int canonicalize(double *cx, const double *x);
int canonicalizef(float *cx, const float *x);
int canonicalizel(long double *cx, const long double *x);
#ifdef __STDC_IEC_60559_DFP__
int canonicalized32(_Decimal32 *cx, const _Decimal32 *x);
int canonicalized64(_Decimal64 *cx, const _Decimal64 *x);
int canonicalized128(_Decimal128 *cx, const _Decimal128 *x);
#endif
```

`canonicalize` 函数试图在参数 `x` 所指向的对象中产生浮点表示的规范版本，就像到指定类型的临时对象一样，并将规范结果存储在参数 `cx` 所指向的对象中。如果输入是 *signaling* *NaN*，则规范化函数旨在存储规范 *quiet* *NaN*。如果未产生规范结果，则 `cx` 所指向的对象不变。

如果一个规范结果存储在 `cx` 指向的对象中，则 `canonicalize` 规范化函数返回零。

---
### Functions：比较和正差函数（Maximum, minimum, and positive difference functions）

#### fmax、fmin	（最大、最小）

```c
// 两数之间的最大值
double fmax(double x, double y);
float fmaxf(float x, float y);
long double fmaxl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fmaxd32(_Decimal32 x, _Decimal32 y);
_Decimal64 fmaxd64(_Decimal64 x, _Decimal64 y);
_Decimal128 fmaxd128(_Decimal128 x, _Decimal128 y);
#endif

// 两数之间的最小值
double fmin(double x, double y);
float fminf(float x, float y);
long double fminl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fmind32(_Decimal32 x, _Decimal32 y);
_Decimal64 fmind64(_Decimal64 x, _Decimal64 y);
_Decimal128 fmind128(_Decimal128 x, _Decimal128 y);
#endif
```

当其中一个数为 `NAN` 时，`NAN` 参数被视为数据缺失，`fmax`、`fmin` 会选择数值参数。如果两个参数都是 *NaN*，函数返回 *NaN*。 

>---
#### fmaximum、fminimum、fmaximum_mag、fminimum_mag

```c
// 两数之间的最大值
double fmaximum(double x, double y);
float fmaximumf(float x, float y);
long double fmaximuml(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fmaximumd32(_Decimal32 x, _Decimal32 y);
_Decimal64 fmaximumd64(_Decimal64 x, _Decimal64 y);
_Decimal128 fmaximumd128(_Decimal128 x, _Decimal128 y);
#endif

// 两数的模之间的最大值
double fmaximum_mag(double x, double y);
float fmaximum_magf(float x, float y);
long double fmaximum_magl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fmaximum_magd32(_Decimal32 x, _Decimal32 y);
_Decimal64 fmaximum_magd64(_Decimal64 x, _Decimal64 y);
_Decimal128 fmaximum_magd128(_Decimal128 x, _Decimal128 y);

// 两数之间的最小值
double fminimum(double x, double y);
float fminimumf(float x, float y);
long double fminimuml(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fminimumd32(_Decimal32 x, _Decimal32 y);
_Decimal64 fminimumd64(_Decimal64 x, _Decimal64 y);
_Decimal128 fminimumd128(_Decimal128 x, _Decimal128 y);
#endif

// 两数的模之间的最小值
double fminimum_mag(double x, double y);
float fminimum_magf(float x, float y);
long double fminimum_magl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fminimum_magd32(_Decimal32 x, _Decimal32 y);
_Decimal64 fminimum_magd64(_Decimal64 x, _Decimal64 y);
_Decimal128 fminimum_magd128(_Decimal128 x, _Decimal128 y);
#endif
```

`fmaximum` 函数认为 `+0` 大于 `-0`；`fminimum` 函数认为 `-0` 小于 `+0`。

`fminimum_mag` 函数返回两个参数的模的最大值，即：
- 若 $|x| > |y|$ 返回 x；
- 若 $|y| > |x|$ 返回 y；
- 否则返回 `fmaximum(x, y)` 的值。

`fmaximum_mag` 函数返回两个参数的模的最小值，即：
- 若 $|x| < |y|$ 返回 x；
- 若 $|y| < |x|$ 返回 y；
- 否则返回 `fminimum(x, y)` 的值。

这些函数像 `math.h` 中的其他函数一样处理 *NaN*。它们与相应的 `fmaximum_num`、`fminimum_num`、`fmaximum_mag_num` 和 `fminimum_mag_num` 函数的区别在于它们对 *NaN* 的处理。

>---
#### fmaximum_num、fminimum_num、fmaximum_mag_num、fminimum_mag_num

```c
// 两数之间的最大值
double fmaximum_num(double x, double y);
float fmaximum_numf(float x, float y);
long double fmaximum_numl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fmaximum_numd32(_Decimal32 x, _Decimal32 y);
_Decimal64 fmaximum_numd64(_Decimal64 x, _Decimal64 y);
_Decimal128 fmaximum_numd128(_Decimal128 x, _Decimal128 y);
#endif

// 两数的模之间的最大值

double fmaximum_mag_num(double x, double y);
float fmaximum_mag_numf(float x, float y);
long double fmaximum_mag_numl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fmaximum_mag_numd32(_Decimal32 x, _Decimal32 y);
_Decimal64 fmaximum_mag_numd64(_Decimal64 x, _Decimal64 y);
_Decimal128 fmaximum_mag_numd128(_Decimal128 x, _Decimal128 y);
#endif

// 两数之间的最小值
double fminimum_num(double x, double y);
float fminimum_numf(float x, float y);
long double fminimum_numl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fminimum_numd32(_Decimal32 x, _Decimal32 y);
_Decimal64 fminimum_numd64(_Decimal64 x, _Decimal64 y);
_Decimal128 fminimum_numd128(_Decimal128 x, _Decimal128 y);
#endif

// 两数的模之间的最小值
```

`fmaximum_num` 函数确定其数值参数的最大值。如果一个参数是数字，另一个参数是 *NaN*，则返回数字。

`fmaximum_mag_num` 函数确定其两个参数的模的最大值。如果一个参数是数字，另一个参数是 *NaN*，则返回数字。

`fminimum_num` 函数确定其数值参数的最小值。如果一个参数是数字，另一个参数是 *NaN*，则返回数字。

`fminimum_mag_num` 函数确定其两个参数的模的最小值。如果一个参数是数字，另一个参数是 *NaN*，则返回数字。

如果一个参数是数字，另一个参数是 *quiet* or *signaling* *NaN*，则这些函数返回数字。如果两个参数都是 *NaN*，则返回 *quiet* *NaN*。如果一个参数是一个 *signaling* *NaN*，则会引发 “invalid” 浮点异常（即使当另一个参数是一个数字时，该函数返回该数字）。

>---

#### fdim （正差）

```c
// 确定两数的非负数差（max(0, x-y)）
double fdim(double x, double y);	
float fdimf(float x, float y);
long double fdiml(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fdimd32(_Decimal32 x, _Decimal32 y);
_Decimal64 fdimd64(_Decimal64 x, _Decimal64 y);
_Decimal128 fdimd128(_Decimal128 x, _Decimal128 y);
#endif
```

`fdim` 返回 `x` 与 `y` 之间的正差，即当 $x>y$ 返回 `x-y`，否则（$x<=y$）返回 `+0`。

```c
#include <math.h>
#include <stdio.h>
#include <float.h>

#define Fdim(x,y) printf("fdim("#x","#y") = %+g\n",fdim(x,y))

int main(void)
{
	Fdim(1, 1);			// +0
	Fdim(1, 10);		// +0	
	Fdim(10, 1);		// +9
	
	Fdim(+0.0, -0.0);	// +0
	Fdim(-0.0, +0.0);	// +0
	
	Fdim(DBL_MAX, 1.1);	// +1.79769e+308
	Fdim(1.1, DBL_MAX); // +0
	
	Fdim(INFINITY, 0);	// +inf
	Fdim(-INFINITY, 0);	// +0
	Fdim(INFINITY, -INFINITY);	// +inf
	Fdim(INFINITY, INFINITY);	// +0
}
```

---
### Functions：浮点乘加运算（Floating multiply-add）

#### fma （浮点乘加）

```c
// return (x * y) + z
double fma(double x, double y, double z);
float fmaf(float x, float y, float z);
long double fmal(long double x, long double y, long double z);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 fmad32(_Decimal32 x, _Decimal32 y, _Decimal32 z);
_Decimal64 fmad64(_Decimal64 x, _Decimal64 y, _Decimal64 z);
_Decimal128 fmad128(_Decimal128 x, _Decimal128 y, _Decimal128 z);
#endif
```

`fma` 进行三元运算 $（x × y）+ z$，将两个操作合并到一个操作，计算的结果具有无限精度（中间值不进行舍入），并根据当前的舍入模式舍入一次返回类型。对于某些有限参数，会出现范围错误。对于某些无限参数，会发生域错误。

---
### Functions：将结果舍入为更窄类型

#### fadd、fsub、fmul、fdiv

```c
// 加
float fadd(double x, double y);
float faddl(long double x, long double y);
double daddl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 d32addd64(_Decimal64 x, _Decimal64 y);
_Decimal32 d32addd128(_Decimal128 x, _Decimal128 y);
_Decimal64 d64addd128(_Decimal128 x, _Decimal128 y);
#endif

// 减
float fsub(double x, double y);
float fsubl(long double x, long double y);
double dsubl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 d32subd64(_Decimal64 x, _Decimal64 y);
_Decimal32 d32subd128(_Decimal128 x, _Decimal128 y);
_Decimal64 d64subd128(_Decimal128 x, _Decimal128 y);
#endif

// 乘
float fmul(double x, double y);
float fmull(long double x, long double y);
double dmull(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 d32muld64(_Decimal64 x, _Decimal64 y);
_Decimal32 d32muld128(_Decimal128 x, _Decimal128 y);
_Decimal64 d64muld128(_Decimal128 x, _Decimal128 y);
#endif

// 除
float fdiv(double x, double y);
float fdivl(long double x, long double y);
double ddivl(long double x, long double y);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 d32divd64(_Decimal64 x, _Decimal64 y);
_Decimal32 d32divd128(_Decimal128 x, _Decimal128 y);
_Decimal64 d64divd128(_Decimal128 x, _Decimal128 y);
#endif
```

这些函数将结果舍入为返回类型，该类型通常比参数类型窄。函数计算的中间值（好像）到无限精度，并根据当前舍入模式舍入一次返回类型。对于某些有限参数，会出现范围错误。对于无穷多个参数，可能会发生域错误。

>---
#### ffma （浮点乘加舍入窄）

```c
float ffma(double x, double y, double z);
float ffmal(long double x, long double y, long double z);
double dfmal(long double x, long double y, long double z);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 d32fmad64(_Decimal64 x, _Decimal64 y, _Decimal64 z);
_Decimal32 d32fmad128(_Decimal128 x, _Decimal128 y, _Decimal128 z);
_Decimal64 d64fmad128(_Decimal128 x, _Decimal128 y, _Decimal128 z);
#endif
```
 
`ffma` 函数计算 $(x × y)+ z$（好像）到无限精度，并根据当前舍入模式舍入一次返回类型。对于某些有限参数，会出现范围错误。对于无限参数，可能会发生域错误。

>---
#### fsqrt （平方根舍入窄）

```c
float fsqrt(double x);
float fsqrtl(long double x);
double dsqrtl(long double x);
#ifdef __STDC_IEC_60559_DFP__
_Decimal32 d32sqrtd64(_Decimal64 x);
_Decimal32 d32sqrtd128(_Decimal128 x);
_Decimal64 d64sqrtd128(_Decimal128 x);
#endif
```

`fsqrt` 函数计算 x 的平方根，四舍五入到函数的返回类型。它们计算平方根（好像）到无限精度，并根据当前舍入模式舍入一次返回类型。对于某些有限的正参数，会出现范围误差。如果参数小于零，则发生域错误。

---
### Functions：量子函数和量子指数函数

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
## C 数学函数：math.h

`math.h` 提供了许多的数学函数，和另外两个具有相同名称但带有 f 和 l 后缀的函数命名，分别代表了 `double`、`float` 和 `long double` 的对应函数。

---
### Type

#### float_t & double_t

- `float _t` 和 `double_t` 表示它们至少与 `float` 和 `double` 宽度相同的浮点类型，且 `double_t` 类型至少与 `float_t` 宽度相同。
  - 如果 `FLT_EVAL_METHOD` 等于 0，`float_t` 和 `double_t` 分别为 `float` 和 `double`。
  - 如果 `FLT_EVAL_METHOD` 等于 1，`float_t` 和 `double_t` 都是 `double`。
  - 如果 `FLT_EVAL_METHOD` 等于 0，`float_t` 和 `double_t` 都是 `long double`。
  - 对于 `FLT_EVAL_METHOD` 的其他值，它们都是默认的实现定义。

```c
#if defined (__x86_64__) || defined(__FLT_EVAL_METHOD__)  
# if defined (__x86_64__) || ( __FLT_EVAL_METHOD__== 0)
typedef float float_t;
typedef double double_t;
# elif (__FLT_EVAL_METHOD__ == 1)
typedef double float_t;
typedef double double_t;
# else /* (__FLT_EVAL_METHOD__ == 2) default ix87 FPU */
typedef long double float_t;
typedef long double double_t;
#endif
#else /* ix87 FPU default */
typedef long double float_t;
typedef long double double_t;
#endif
```

- `float.h` 的 `FLT_EVAL_METHOD` 表示为在浮点算数的中间结果所用的扩展精度。

---
### Macros

#### 无穷大定义

```c
#ifndef _HUGE_ENUF
    #define _HUGE_ENUF  1e+300  // 用于保证 _HUGE_ENUF * _HUGE_ENUF 
#endif

#define INFINITY  ((float)(_HUGE_ENUF * _HUGE_ENUF))
```

- `INFINITY` 表示正无穷大或无符号无穷大，或为转换为溢出时的 `float` 类型正常量。

```c
#define HUGE_VAL   ((double)INFINITY)
#define HUGE_VALF  ((float)INFINITY)
#define HUGE_VALL  ((long double)INFINITY)
```

- `HUGE_XXX` 分别指示过大而无法以 `double`、`float`、`long double` 类型表示的值（无穷大）。

<br>

#### 非数值定义

```c
#define NAN     ((float)(INFINITY * 0.0F))
```

- `NAN` 表示未定义或不可表示的值。它展开为 `float` 类型的常量表达式，表示一个 quiet NaN。

<br>

#### 数字分类宏

```c
#define FP_NORMAL       // 指示值为正规浮点数，不是无穷大，非正规，非数或零
#define FP_SUBNORMAL    // 指示值为非正规
#define FP_ZERO         // 指示值为正或负零      
#define FP_INFINITE     // 指示值为正或负无穷大
#define FP_NAN          // 指示值是非数（NaN）
```

- `fpclassify(real-floating x)` 宏函数的返回值，用于指示浮点数的类别。

<br>

#### FP_FAST_FMA

```c
#define FP_FAST_FMA
#define FP_FAST_FMAF
#define FP_FAST_FMAL
```

- 这些宏为可选定义，如果定义，则指示 `fma` 函数的执行速度通常与双操作数的乘法或加法一样快或更快。通常展开为 1。
- 通常，当且仅当 `fma` 函数直接由硬件乘法加指令实现时，才定义 `FP_FAST_FMA` 宏。

<br>

#### FP_ILOGB

```c
#define FP_ILOGB0
#define FP_ILOGBNAN
```

- 在函数 `ilogb(double x)`、`ilogbf(float x)`、`ilogbl(long double x)` 中：
  - 当 `x = 0` 时，函数返回 `FP_ILOGB0`，其值为 `INT_MIN` 或 `INT_MAX`；
  - 当 `x = NaN` 时，函数返回 `FP_ILOGBNAN`，其值为 `INT_MAX` 或 `INT_MIN`；
  - 当 `x = inf` 时，函数返回 `INT_MAX`。

<br>

#### 数学函数的错误处理机制

```c
#define MATH_ERRNO        1
#define MATH_ERREXCEPT    2
#define math_errhandling  (MATH_ERRNO | MATH_ERREXCEPT)
```

- `math_errhandling` 展开为一个表达式，在程序运行期间，该值是恒定的。如果表达式 `math_errhandling & MATH_ERREXCEPT` 可以为非零，则在 `fenv.h` 中实现定义 `FE_DIVBYZERO`、`FE_INVALID`、`FE_OVERFLOW`。

> *错误处理的条件*

- `math.h` 的函数通常不会引发 SIGFPE（浮点异常信号），也不会产生任何浮点异常例如 “invalid”，“divide-by-zero”，或 “overflow”。

* *域错误（domain error）*：对于所有函数，当前仅当输入的参数在函数的定义域之外，则会发生域错误：
  - 如果 `math_errhandling & MATH_ERRNO` 非零，`errno` 获取值 `EDOM`。
  - 如果 `math_errhandling & MATH_ERREXCEPT` 非零，则会引发 “invalid” 无效浮点异常。

- *极点误差 / 奇点 / 无穷大（pole error）*：当且仅当数学函数在有限输入参数接近极限时（如 `log(0.0)`）具有无穷大结果发生时，发生极点误差：
  - 如果 `math_errhandling & MATH_ERRNO` 非零，`errno` 获取值 `ERANGE`。
  - 如果 `math_errhandling & MATH_ERREXCEPT` 非零，则会引发 “divide-by-zero” 除零浮点异常。

* *范围误差（range error）*：当且仅当函数的数学结果无法在指定类型的对象中表示时，由于超出类型表示范围，就会发生结果溢出错误。浮点结果上溢（overflow），函数将返回类型宏 `HUGE_VAL/HUGE_VALF/HUGE_VALL` 的值，并具有与函数正确值相同的符号；浮点结果下溢（underflow），函数将返回一个大小不大于指定类型中最小的规范化正数：
  - 如果 `math_errhandling & MATH_ERRNO` 非零，`errno` 获取值 `ERANGE`。
  - 如果 `math_errhandling & MATH_ERREXCEPT` 非零，则会引发 “overflow / underflow” 溢出浮点异常。

### Pragma：fp_contract（浮点收缩）

```c
#pragma fp_contract(on | off | default)
```

- `fp_contract` 表示是否在浮点算数中使用浮点收缩指令（例如 FMA 混合乘加运算），它可以像单个操作一样求值，从而省略了源代码和表达式求值方法隐含的舍入错误。（一般默认为 `on`）
- 浮点收缩意味着浮点算数的中间操作被视为具有无限范围和精度，且中间结果无法被追溯和检查中间值，因此由于它作为单个指令实现，因此可能比单独指令更快。例如 FMA 在执行加法之前不会对中间乘积进行舍入，因此结果可能与单独的乘法和加法运算不同。

---
### Macro-Functions：分类宏（Classification macros）

#### fpclassify （浮点值归类）

```c
int fpclassify(real-floating arg);
```

- 宏函数 `fpclassify` 归类浮点值 `arg` 到下列类别中：零（`FP_ZERO`）、非正规（`FP_SUBNORMAL`）、正规（`FP_NORMAL`）、无穷大（`FP_INFINITE`）、 NaN（`FP_NAN`）或实现定义类别。该宏返回整数值。

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

<br>

#### isfinite、isinf、isnan、isnormal

```c
int isfinite(real-floating x);
int isinf(real-floating x);
int isnan(real-floating x);
int isnormal(real-floating x);
```

- 这些宏函数在满足条件时返回非零值：
  - `isfinite` 确定参数是否具有有限值（零、非正规或正规，而不是无穷或 `NaN`）。
  - `isinf` 确定参数是否是无穷大（正或负）。
  - `isnan` 确定参数是否为 `NaN`。
  - `isnormal` 确定参数是否是正规值（而不是零、非正规、无穷或 `NaN`）。

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

<br>

#### signbit （确认符号位）

```c
int signbit(real-floating x);
```

- `signbit` 确定其参数的符号是否为负。为负时返回非零值。`signbit` 可以检测零、无穷大、`NaN` 的符号。

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

#### isgreater、isgreaterequal、isless、islessequal、islessgreater

```c
int isgreater(x, y);          // return (x) > (y)
int isgreaterequal(x, y);     // return (x) >= (y)
int isless(x, y);             // return (x) < (y)
int islessequal(x, y);        // return (x) <= (y)
int islessgreater(x, y);      // return (x) < (y) || (x) > (y)
```

- 进行浮点数之间的比较时，若一或两个参数为 `NAN` 时，内联的比较运算符可能会引发 `FE_INVALID`，此时返回零。

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


<br>

#### isunordered （是否无序）

```c
int isunordered(x, y);
```

- 确定浮点数 `x` 与 `y` 之间是否无序。
- 实际上当 `x` 或 `y` 为 `NAN` 时返回非零值，否则返回 0。因为此时其中至少有一个是 `NAN` 时，此时无法进行有意义的比较

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

---
### Functions：三角函数（Trigonometric functions）

#### cos、sin、tan （三角函数）

```c
double cos(double x);     // 余弦函数 (-inf, +inf) >> [-1, 1]
double sin(double x);     // 正弦函数 (-inf, +inf) >> [-1, 1]
double tan(double x);     // 正切函数 x≠(π/2)+kπ >> (-inf, +inf)

float cosf(float x);
float sinf(float x);
float tanf(float x);

long double cosl(long double x);
long double sinl(long double x);
long double tanl(long double x);
```

- 这些三角函数的返回值的单位为弧度。

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

<br>

#### acos、asin、atan、atan2 （反三角函数）

```c
double acos(double x);     // 反余弦函数 [-1, +1] >> [0, PI]
double asin(double x);     // 反正弦函数 [-1, +1] >> [-PI/2, PI/2]
double atan(double x);     // 反正切函数 [-inf, +inf] >> [-PI/2, PI/2]

float acosf(float x);
float asinf(float x);
float atanf(float x);

long double acosl(long double x);
long double asinl(long double x);
long double atanl(long double x);
```

- 这些反三角函数的返回值单位为弧度。

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

<br>

#### atan2 （四象限反正切函数）

```c
double atan2(double y, double x);     // ((x|-inf,inf), (y|-inf,inf)) >> [-PI, PI] 
float atan2f(float y, float x);
long double atan2l(long double x, long double y);
```

四象限反正切函数用于确定点 $(x, y)$ 在直角坐标系的位置。

> 四象限反正切函数 `atan2(y,x)` 值域分布示意

![](.img/四象限反正切函数atan2(y,x)值域分布图.png)

- 定义 `nor` 为有限浮点数 (`FP_NORMAL`)，正有限表示为 `+nor`，负有限表示为 `-nor`：
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

---
### Functions：双曲函数（Hyperbolic functions）

#### cosh、sinh、tanh （双曲函数）

```c
double cosh(double x);		// 双曲余弦函数 
double sinh(double x);		// 双曲正弦函数
double tanh(double x);		// 双曲正切函数

float coshf(float x);
float sinhf(float x);
float tanhf(float x);

long double coshl(long double x);
long double sinhl(long double x);
long double tanhl(long double x);
```

<br>

#### acosh、asinh、atanh （反双曲函数）

```c
double acosh(double x);		// 反双曲余弦函数 
double asinh(double x);		// 反双曲正弦函数
double atanh(double x);		// 反双曲正切函数

float acoshf(float x);
float asinhf(float x);
float atanhf(float x);

long double acoshl(long double x);
long double asinhl(long double x);
long double atanhl(long double x);
```

---
### Functions：指数函数（Exponential functions）

#### exp、exp2、expm1

#### log、log10、log2、log1p
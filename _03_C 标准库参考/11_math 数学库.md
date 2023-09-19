## C 数学库（Mathematics）：math.h

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
### Functions：指数、对数函数（Exponential and logarithmic functions）

#### exp、exp2、expm1 （指数相关）

```c
double exp(double x);			// 计算 e^x 
double exp2(double x);			// 计算 2^x 
double expm1(double x);			// 计算 e^x-1

float expf(float x);	
float exp2f(float x);
float expm1f(float x);

long double expl(long double x);	
long double exp2l(long double x);
long double expm1l(long double x);
```

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

<br>

#### frexp、ldexp （X * 2^exp）

```c
double frexp(double value, int *exp);			// 拆分成数和 2 的幂次
double ldexp(double x, int exp);				// 计算数和 2 的幂次乘积

float frexpf(float value, int *exp);
float ldexpf(float x, int exp);

long double frexpl(long double value, int *exp);
long double ldexpl(long double x, int exp);
```

- `frexp` 函数将浮点数分解为标准化分数和 2 的整数次幂，整数存储在 `exp` 指向的对象中。
- `ldexp` 函数计算 `x` 与 2 的 `exp` 次幂的乘积。

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

<br>

#### log、log10、log2、log1p （对数相关）

```c
double log(double x);			// 自然对数 ln(x)
double log10(double x);			// 10 为底的对数
double log2(double x);			// 2 为底的对数
double log1p(double x);			// 计算 ln(x+1)

float logf(float x);
float log10f(float x);
float log2f(float x);
float log1pf(float x);

long double logl(long double x);
long double log10l(long double x);
long double log2l(long double x);
long double log1pl(long double x);
```

- 对于较小的量级 x, `log1p(x)` 预计比 `log(1+x)` 更准确。

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

<br>

#### logb、ilogb （X = 2^exp）

```c
double logb(double x);			// 提取 x 的指数，返回浮点格式的有符号整数值
float logbf(float x);
long double logbl(long double x);

int ilogb(double x);			// 提取 x 指数，返回有符号整数值
int ilogbf(float x);	
int ilogbl(long double x);
```

- `logb` 函数提取 `x` 的指数，作为浮点格式的有符号整数值。如果 `x` 是次正规的，它被当作是标准化的；因此，对于正有限 `x`，1 <= `x` * `FLT_RADIX` $^{-logb(x)}$ < `FLT_RADIX`
 
- 对于 `ilogb` 函数：
  - 当 `x = 0`，函数返回 `FP_ILOGB0`；
  - 当 `x = INFINITY`，函数返回 `INT_MAX`；
  - 当 `x = NAN`，函数返回 `FP_ILOGBNAN`；

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

<br>

#### modf （拆分整数小数）

```c
double modf(double value, double *iptr);
float modff(float value, float *iptr);
long double modfl(long double value, long double *iptr);
```

- `modf` 函数将参数值分解为整数和小数部分。它们将整型部分（以浮点格式）存储在 iptr 所指向的对象中，并返回带符号小数部分。

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

<br>

#### scalbn、scalnln （高效计算数 × FLT_RADIX 的幂）

```c
double scalbn(double x, int n);
double scalbln(double x, long int n);

float scalbnf(float x, int n);
float scalblnf(float x, long int n);

long double scalbnl(long double x, int n);
long double scalblnl(long double x, long int n);
```

- `scalbn` 用于计算 `x * FLT_RADIX ^ n` 的值。

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

<br>

#### cbrt （立方根）

```c
double cbrt(double x);		// 立方根，计算 x^(1/3)
float cbrtf(float x);
long double cbrtl(long double x);
```

<br>

#### pow （数的给定次幂）

```c
double pow(double x, double y);		// 计算 x^y 的值
float powf(float x, float y);
long double powl(long double x, long double y);
```

<br>

#### hypot （两数平方和的平方根）

```c
double hypot(double x, double y);	// 计算 (x^2 + y^2)^(1/2)
float hypotf(float x, float y);
long double hypotl(long double x, long double y);
```

<br>

#### fabs （绝对值）

```c
double fabs(double x);		// 计算 x 的绝对值
float fabsf(float x);
long double fabsl(long double x);
```

---
### Functions：误差及伽马函数 （Error and gamma functions）

#### erf、erfc （误差与互补误差函数）

```c
double erf(double x);		// 计算 x 的误差函数
double erfc(double x);		// 计算 x 的互补误差函数

float erff(float x);
float erfcf(float x);

long double erfl(long double x);
long double erfcl(long double x);
```

- 误差函数：`erf(x)` = $\frac{2}{\sqrt{\pi}} \int_0^{x} e^{-t^2}dt$.
- 互补误差函数：`erfc(x)` = `1-erf(x)` = $\frac{2}{\sqrt{\pi}} \int_x^{\infty} e^{-t^2}dt$.

<br>

#### tgamma、lgamma （伽马函数与它的自然对数）

```c
double tgamma(double x);		// 伽马函数
double lgamma(double x);		// 伽马函数的自然对数

float tgammaf(float x);
float lgammaf(float x);

long double tgammal(long double x);
long double lgammal(long double x);
```

- 阶乘函数仅针对离散点，伽马函数是对阶乘函数的泛化。 `tgamma(x)` = $\Gamma(x) = \int_0^{\infty} t^{x-1} e^{-t}dt$.
- 对于自然数 $x$，有 $x!$ = $\Gamma (x+1)$

- `lgamma(x)` 是 `tgamma(x)` 的自然对数，即 $log_e|\Gamma(x)|$。

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
double ceil(double x);		// 向上取整，返回不小于 x 的最小整数 
double floor(double x);		// 向下取整，返回不大于 x 的最大整数

float ceilf(float x);
float floorf(float x);

long double ceill(long double x);
long double floorl(long double x);
```

<br>

#### nearbyint、rint、lrint、llrint（根据当前舍入方向求近似整数）

```c
double nearbyint(double x);		// 使用当前舍入方向，进行取整，不产生浮点异常
float nearbyintf(float x);
long double nearbyintl(long double x);

double rint(double x);			// 使用当前舍入方向，进行取整，可能产生浮点异常
long int lrint(double x);
long long int llrint(double x);

float rintf(float x);
long int lrintf(float x);
long long int llrintf(float x);

long double rintl(long double x);
long int lrintl(long double x);
long long int llrintl(long double x);
```

- 这些函数的求近似整数的行为受当前浮点环境舍入方向（`FE_TONEAREST`、`FE_DOWNWARD`、`FE_UPWARD`、`FE_TOWARDZERO`）的影响。
- `rint` 函数与 `nearbyint` 函数的不同之处在于，如果结果与实参的值不同，`rint` 函数可能会引发 “inexact” 浮点异常。

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

<br>

#### round、lround、llround （四舍五入取整）

```c
double round(double x);		// 浮点数四舍五入到最近的整数
long int lround(double x);
long long int llround(double x);

float roundf(float x);
long int lroundf(float x);
long long int llroundf(float x);

long double roundl(long double x);
long int lroundl(long double x);
long long int llroundl(long double x);
```

- `round`、`lround`、`llround` 函数的行为不受当前舍入模式的影响。

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

<br>

#### trunc （向零舍入取整）

```c
double trunc(double x);
float truncf(float x);
long double truncl(long double x);
```

- `trunc` 计算绝对值不大于 `x` 的最接近整数，等价于向零舍入取整，且不受当前舍入模式影响。
- 当 `x = ± 0/inf` 时，返回不修改的参数；当 `x = NAN` 时返回 `NAN`。

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

---
### Functions：余项函数（Remainder functions）

#### fmod、remainder （求浮点除法的余数）

```c
double fmod(double x, double y);	// 求 x/y 的余数
double remainder(double x, double y);	// 求 x REM y（IEC 60559）

float fmodf(float x, float y);
float remainderf(float x, float y);

long double fmodl(long double x, long double y);
long double remainderl(long double x, long double y);
```

- `fmod` 函数返回值 `x - ny`，对于某个整数 `n`，如果 `y` 非零，则结果与 `x` 符号相同且 `x - ny < y`。如果 `y` 为零，则是发生域错误还是 `fmod` 函数返回零是由实现定义的。

- `remainder` 计算 `x - ny`，`n` 是最接近 `x/y` 准确值的整数值，求 `|n - x/y| = 1/2`，选择作为偶数的 `n`。

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

<br>

#### remquo （求商求余）

```c
double remquo(double x, double y, int *quo);
float remquof(float x, float y, int *quo);
long double remquol(long double x, long double y, int *quo);
```

- `remquo` 与 `remainder` 使用相同的方法计算余数。在 `*quo` 中存储了一个值，其符号与 `x/y` 相同，其大小与 `x/y` 的整数商的大小取 $2^n$ 的模一致，其中 $n$ 是大于等于 3 的整数。
- 对于 `rem = remquo(x,y,*quo)` 满足 `x = y * quo + rem`。

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
double copysign(double x, double y);	// return = signbit(y)?-1:1 * fabs(x)
float copysignf(float x, float y);
long double copysignl(long double x, long double y);
```

- `copysign` 返回一个大小为 `|x|`，并复制 `y` 的符号。等价于 `signbit(y)?-1:1 * fabs(x)`。

<br>

#### nan （转换为 a quiet NAN）

```c
double nan(const char *tagp);
float nanf(const char *tagp);
long double nanl(const char *tagp);
```

- `nan("n-char-sequence")` 相当于 `strtod("NAN(n-char-sequence)", (char**)NULL)`；
- `nan("")` 相当于 `strtod("NAN()", (char**)NULL)`；
- `nan` 函数将返回 `quiet NaN` 值。

<br>

#### nextafter、nexttoward （下一个有限浮点值）

```c
double nextafter(double from, double to);	
double nexttoward(double from, long double to);

float nextafterf(float from, float to);
float nexttowardf(float from, long double to);

long double nextafterl(long double from, long double to);
long double nexttowardl(long double from, long double to);
```

- `nextafter` 和 `nexttoward` 首先转换两个参数为函数的类型，然后返回 `from` 到 `to` 方向的下个可表示的浮点数。当 `from = to` 时，`nextafter` 返回 `to`，而 `nexttoward` 返回从 `long double` 转换到函数返回类型的 `to`，且不带范围或精度的损失。
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

---
### Functions：比较和正差函数（Maximum, minimum, and positive difference functions）

#### fmax、fmin	（最大、最小）

```c
double fmax(double x, double y);	// 两数之间的最大值
double fmin(double x, double y);	// 两数之间的最小值

float fmaxf(float x, float y);
float fminf(float x, float y);

long double fmaxl(long double x, long double y);
long double fminl(long double x, long double y);
```

- 当其中一个数为 `NAN` 时，`NAN` 参数被视为数据缺失，`fmax`、`fmin` 会选择数值参数，

<br>

#### fdim （正差）

```c
double fdim(double x, double y);	// 确定两数的非负数差（max(0, x-y)）
float fdimf(float x, float y);
long double fdiml(long double x, long double y);
```

- `fdim` 返回 `x` 与 `y` 之间的正差，即当 `x>y` 返回 `x-y`，否则（`x<=y`）返回 `+0`。

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
double fma(double x, double y, double z);	// return (x * y) + z
float fmaf(float x, float y, float z);
long double fmal(long double x, long double y, long double z);
```

- `fma` 进行三元运算，将两个操作合并到一个操作，计算的结果具有无限精度（中间值不进行舍入），并根据当前的舍入模式返回结果。

---
## C 浮点环境（Floating-point environment）：fenv.h

```c
#define __STDC_VERSION_FENV_H__     202311L 
```

`fenv.h` 定义了一些宏，和声明了提供对浮点环境的访问的类型和函数。浮点环境是指实现支持的任何浮点状态标志及控制模式的总称。

浮点状态标志是一个系统变量，其值在引发浮点异常时被设置且不会被清除，这是异常浮点算数提供辅助信息的副作用。浮点控制模式是一个系统变量，用户可以设置它的值来影响浮点运算的后续行为。

浮点控制模式可以是常量或动态的。动态浮点环境包括动态浮点控制模式和浮点状态标志。

动态浮点环境具有线程存储持续时间。线程的动态浮点环境的初始状态是创建它的线程的浮点环境在创建时的当前状态，它在线程创建时初始化。

某些编程约定支持动态浮点环境的预期使用模型：
- 函数调用不改变其调用方的浮点控制模式，不清除其调用方的浮点状态标志，也不依赖于其调用方的浮点状态标志的状态，除非该函数被如下记录；
- 假定函数调用需要默认的浮点控制模式，除非文档另有说明；
- 假定函数调用具有引发浮点异常的可能性，除非其文档另有说明；

<!-- 仅若设置 `#pragma STDC FENV_ACCESS` 为 ON ，浮点环境的访问及修改才有意义。 -->

---
### Type

`fenv_t` 表示整个动态浮点环境。
`femode_t` 表示实现支持的动态浮点控制模式的集合，包括动态舍入方向模式。
`fexcept_t` 集中表示浮点状态标志，包括实现与这些标志相关联的任何状态。

---

### Macros

#### 浮点异常

```c
#define FE_INVALID     0x01     // 出现于之前浮点运算的定义域错误
#define FE_DIVBYZERO   0x04     // 出现于之前浮点运算的极点错误 
#define FE_OVERFLOW    0x08     // 之前浮点运算的结果过大而无法表示
#define FE_UNDERFLOW   0x10     // 之前浮点运算的结果为有精度损失的非正规值
#define FE_INEXACT     0x20     // 不准确结果：必须舍入以存储之前浮点运算的结果
#define FE_ALL_EXCEPT (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW | FE_INEXACT)
```

实现定义的其他浮点异常（宏定义以 `FE_` 开头，并以大写字母开头）也可以由实现指定。这些定义的扩展为具有值的整数常量表达式，使得宏的所有组合的按位 OR 产生不同的值，并且此外，宏的所有组合的按位 AND 产生零。

`FE_ALL_EXCEPT` 是由实现定义的所有浮点异常宏的按位 OR。如果未定义此类宏，则 `FE_ALL_EXCEPT` 应定义为 0。

> Test

```c
// MSVC
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <fenv.h>

#pragma fenv_access(on)  // 开启浮点环境控制模式
void show_fe_exceptions(void)
{
    printf("exceptions raised:");
    if (fetestexcept(FE_DIVBYZERO)) printf(" FE_DIVBYZERO");
    if (fetestexcept(FE_INEXACT))   printf(" FE_INEXACT");
    if (fetestexcept(FE_INVALID))   printf(" FE_INVALID");
    if (fetestexcept(FE_OVERFLOW))  printf(" FE_OVERFLOW");
    if (fetestexcept(FE_UNDERFLOW)) printf(" FE_UNDERFLOW");
    feclearexcept(FE_ALL_EXCEPT);
    printf("\n");
}

int main(void)
{
    printf("0.0/0.0 = %f\n", 0.0 / 0.0);
    show_fe_exceptions();

    printf("1.0/0.0 = %f\n", 1.0 / 0.0);
    show_fe_exceptions();

    printf("1.0/10.0 = %f\n", 1.0 / 10.0);
    show_fe_exceptions();

    printf("sqrt(-1) = %f\n", sqrt(-1));
    show_fe_exceptions();

    printf("DBL_MAX*2.0 = %f\n", DBL_MAX * 2.0);
    show_fe_exceptions();

    printf("nextafter(DBL_MIN/pow(2.0,52),0.0) = %.1f\n", nextafter(DBL_MIN / pow(2.0, 52), 0.0));
    show_fe_exceptions();
}
/*
0.0/0.0 = -nan(ind)
exceptions raised: FE_INVALID
1.0/0.0 = inf
exceptions raised: FE_DIVBYZERO
1.0/10.0 = 0.100000
exceptions raised: FE_INEXACT
sqrt(-1) = -nan(ind)
exceptions raised: FE_INVALID
DBL_MAX*2.0 = inf
exceptions raised: FE_INEXACT FE_OVERFLOW
nextafter(DBL_MIN/pow(2.0,52),0.0) = 0.0
exceptions raised: FE_INEXACT FE_UNDERFLOW
*/
```

>---
#### 动态浮点控制模式

```c
#define FE_DFL_MODE
```

`FE_DFL_MODE` 表示实现支持的动态浮点控制模式集合的默认状态，且具有类型 `const femode_t *`。动态模式集合的其他实现定义状态（宏定义以 `FE_` 和大写字母开头，类型为 `const femode_t *`）也可以由实现指定。

>---

#### 浮点舍入方向

```c
#define FE_DOWNWARD             // 向负无穷大舍入
#define FE_TONEAREST            // 向最接近可表示值舍入
#define FE_TONEARESTFROMZERO    // 向远离零方向最接近可表示值舍入
#define FE_TOWARDZERO           // 向零舍入
#define FE_UPWARD               // 向正无穷大舍入
```

当且仅当实现支持通过 `fegetround` 和 `fesetround` 函数获取和设置所表示的舍入方向时才定义。定义的宏展开为整型常量表达式，其值为不同的非负值。其他实现定义的舍入方向（宏定义以 `FE_` 和大写字母开头）也可以由实现指定。

> 如果实现支持十进制浮点类型，则：

```c
#define FE_DEC_DOWNWARD             // 向负无穷大舍入
#define FE_DEC_TONEAREST            // 向最接近可表示值舍入
#define FE_DEC_TONEARESTFROMZERO    // 向零方向最接近可表示值舍入
#define FE_DEC_TOWARDZERO           // 向零舍入
#define FE_DEC_UPWARD               // 向正无穷大舍入
```

这些宏定义为与 `fe_dec_getround` 和 `fe_dec_setround` 函数一起使用，以获取和设置十进制浮点运算的动态舍入方向模式。除非另有说明，小数舍入方向影响所有产生小数浮点类型结果的（不精确）运算，以及所有产生整数或字符序列结果并具有小数浮点类型操作数的运算。这些宏扩展为整型常量表达式，其值为不同的非负值。

在转换过程中，十进制浮点运算的常量舍入方向模式在指定的位置有效。在其他位置，在转换期间，小数舍入方向模式为 `FE_DEC_TONEAREST`。在程序启动时，十进制浮点运算的动态舍入方向模式初始化为 `FE_DEC_TONEAREST`。


> 当前舍入模式影响案例

```c
// 常量表达式之外的浮点数算数运算符结果
double x = 1;
x/10;  // 0.09999999999999999167332731531132594682276248931884765625
      // 或 0.1000000000000000055511151231257827021181583404541015625

// 标准库数学函数的返回值
sqrt(2); // 1.41421356237309492343001693370752036571502685546875
      // 或 1.4142135623730951454746218587388284504413604736328125

// 浮点到浮点的隐式转换及转换类型
double d = 1 + DBL_EPSILON;
float f = d; //  1.00000000000000000000000
           // 或 1.00000011920928955078125

// 字符串转换，strtod 或 printf
strtof("0.1", NULL); // 0.0999999940395355224609375
                  // 或 0.100000001490116119384765625

// 库摄入函数 nearbyint，rint，lrint
lrint(2.1); // 2 或 3
```

> 当前舍入模式不影响

- 浮点到整数的隐式转换或转型（始终向零）。
- 编译时执行的常量表达式中浮点算数运算符的结果（始终向最接近）。
- 库函数 `round`、`lround`、`llround`、`ceil`、`floor`、`trunc`。

> Test

```c
#include <stdio.h>
#include <stdlib.h>
#include <fenv.h>
#include <math.h>

#pragma fenv_access(on)

int main()
{
    fesetround(FE_DOWNWARD);
    puts("rounding down: ");
    printf("           pi = %.22f\n", acosf(-1));
    printf("strtof(\"1.1\") = %.22f\n", strtof("1.1", NULL));
    printf("    rint(2.1) = %.22f\n\n", rintf(2.1));
    fesetround(FE_UPWARD);
    puts("rounding up: ");
    printf("           pi = %.22f\n", acosf(-1));
    printf("strtof(\"1.1\") = %.22f\n", strtof("1.1", NULL));
    printf("    rint(2.1) = %.22f\n", rintf(2.1));
}
/*
rounding down: 
           pi = 3.1415925025939941406250
strtof("1.1") = 1.0999999046325683593750
    rint(2.1) = 2.0000000000000000000000
 
rounding up: 
           pi = 3.1415927410125732421875
strtof("1.1") = 1.1000000238418579101563
    rint(2.1) = 3.0000000000000000000000
*/
```

>---

#### 默认动态浮点环境

```c
#define FE_DFL_ENV      ((const fenv_t *) 0)
```

宏常量 `FE_DFL_ENV` 展开成 `const fenv_t *` 类型表达式，表示默认的动态浮点环境，表示在程序启动时加载的浮点环境的完整副本。它可以用作 `fenv.h` 中管理动态浮点环境函数的参数。

实现还可以指定其他实现定义的环境，其中宏定义以 `FE_` 开头，并带有一个前缀字母，类型为 `const fenv_t *`。

```c
#include <stdio.h>
#include <fenv.h>
 
#pragma fenv_access(on) // 开启浮点环境控制模式
// 浮点异常
void show_fe_exceptions(void)
{
    printf("current exceptions raised: ");
    if(fetestexcept(FE_DIVBYZERO))     printf(" FE_DIVBYZERO");
    if(fetestexcept(FE_INEXACT))       printf(" FE_INEXACT");
    if(fetestexcept(FE_INVALID))       printf(" FE_INVALID");
    if(fetestexcept(FE_OVERFLOW))      printf(" FE_OVERFLOW");
    if(fetestexcept(FE_UNDERFLOW))     printf(" FE_UNDERFLOW");
    if(fetestexcept(FE_ALL_EXCEPT)==0) printf(" none");
    printf("\n");
}
// 浮点舍入方向
void show_fe_rounding_method(void)
{
    printf("current rounding method:    ");
    switch (fegetround()) {
           case FE_TONEAREST:  printf ("FE_TONEAREST");  break;
           case FE_DOWNWARD:   printf ("FE_DOWNWARD");   break;
           case FE_UPWARD:     printf ("FE_UPWARD");     break;
           case FE_TOWARDZERO: printf ("FE_TOWARDZERO"); break;
           default:            printf ("unknown");
    };
    printf("\n");
}
// 打印当前的浮点环境
void show_fe_environment(void)
{
    show_fe_exceptions();
    show_fe_rounding_method();
} 
 
int main(void)
{
    printf("On startup:\n");
    show_fe_environment();
 
    // 更改环境
    fesetround(FE_DOWNWARD);     // 更改舍入模式
    feraiseexcept(FE_INVALID);   // 引发异常
    printf("\nBefore restoration:\n");
    show_fe_environment();
 
    fesetenv(FE_DFL_ENV);    // 恢复
    printf("\nAfter restoring default environment:\n");
    show_fe_environment();
}
/*
On startup:
current exceptions raised:  none
current rounding method:    FE_TONEAREST
 
Before restoration:
current exceptions raised:  FE_INVALID
current rounding method:    FE_DOWNWARD
 
After restoring default environment:
current exceptions raised:  none
current rounding method:    FE_TONEAREST
*/
```

---
### Pragma

#### FENV_ACCESS （设置浮点控制模式）

```c
#include <fenv.h>
#pragma STDC FENV_ACCESS  on-off-switch  // ON / OFF / DEFAULT
#pragma fenv_access (on / off / default) 
```

`#pragma fenv_access(on | off) ` 提供了一种方法来通知程序何时可以访问浮点环境来测试浮点状态标志或在非默认浮点控制模式下运行。默认状态（ "on" 或 "off" ）是实现定义的。

杂注应出现在外部声明之外或在复合语句中的所有显式声明和语句之前。当在外部声明之外时，杂注从其出现开始生效，直到遇到另一个 `FENV_ACCESS` 杂注，或者直到翻译单元结束。当在复合语句中时，杂注从其出现开始生效，直到遇到另一个 `FENV_ACCESS` 杂注（包括在嵌套复合语句中），或者直到复合语句结束。在复合语句结束时，杂注的状态将恢复到复合语句之前的状态。

如果在任何其他上下文中使用该杂注，则行为未定义。如果程序的一部分测试浮点状态标志，或者使用除 `FENV_ROUND` 之外的任何方法建立或执行非默认浮点模式设置，但是使用 `FENV_ACCESS` 编译器的状态 “off” 进行转换，则该行为是未定义的。

```c
#include <fenv.h>
void f(double v)
{
    #pragma STDC FENV_ACCESS ON
    void g(double);
    void h(double);
    /* ... */
    g(x + 1);
    h(x + 1);
    /* ... */
}
```

>---

#### FENV_ROUND （设置浮点舍入方向）

```c
#include <fenv.h>
#pragma STDC FENV_ROUND direction
#pragma STDC FENV_ROUND FE_DYNAMIC
```

`FENV_ROUND` 杂注提供了一种方法，用于为翻译单元或复合语句中的标准浮点类型的浮点操作指定常量舍入方向。

杂注应该出现在外部声明之外，或者出现在复合语句中的所有显式声明和语句之前。当在外部声明之外时，杂注从其出现开始生效，直到遇到另一个 `FENV_ROUND` 杂注，或者直到翻译单元结束。当在复合语句中时，杂注从其出现开始生效，直到遇到另一个 `FENV_ROUND` 杂注（包括在嵌套复合语句中），或者直到复合语句结束；在复合语句结束时，静态舍入模式恢复到复合语句之前的状态。如果在任何其他上下文中使用此杂注，则其行为未定义。

`direction` 方向应为标准浮点舍入方向宏之一（`FE_DOWNWARD`、`FE_TONEAREST`、`FE_TONEARESTFROMZERO`、`FE_TOWARDZERO`、`FE_UPWARD`），用于标准浮点类型的操作，以指定一个恒定的舍入模式；或者设置 `FE_DYNAMIC` 指定动态舍入。如果指定其他任何值，则行为未定义。如果没有 `FENV_ROUND` 杂注生效或指定方向为 `FE_DYNAMIC`，则舍入将根据动态环境指定的模式进行，该模式是在线程创建时或通过 `fesetround`、`fesetmode`、`fesetenv` 或 `feupdateenv` 函数设置。如果指定了舍入方向为 `FE_DYNAMIC`，并且 `FENV_ACCESS` 为 "off"，则编译器可能会认为默认的舍入模式是有效的。

`FENV_ROUND` 杂注影响标准浮点类型的操作。在建立恒定舍入模式的 `FENV_ROUND` 杂注范围内，浮点运算符、隐式转换（包括将比其语义范围更宽的格式表示的值转换为其语义类型，如通过分类宏完成的）以及调用下表中所示的函数（其中宏替换尚未被抑制），应根据指定的恒定舍入模式进行求值。除了下表之外的函数和未被抑制的宏替换不受恒定舍入模式的影响，它们只受动态模式的影响。标准浮点类型的浮点常量出现在恒定舍入模式范围内时，应根据该模式进行解释。

下表列出的函数族表示所有标准浮点类型的函数，其中函数族由不带后缀的函数名表示。例如，`acos` 表示函数 `acos`、`acosf` 和 `acosl`。

| Header     | Function families                                                                                |
| :--------- | :----------------------------------------------------------------------------------------------- |
| <math.h>   | `acos`, `acospi`, `asin`, `asinpi`, `atan`, `atan2`, `atan2pi`, `atanpi`                         |
| <math.h>   | `cos`, `cospi`, `sin`, `sinpi`, `tan`, `tanpi`                                                   |
| <math.h>   | `acosh`, `asinh`, `atanh`                                                                        |
| <math.h>   | `cosh`, `sinh`, `tanh`                                                                           |
| <math.h>   | `exp`, `exp10`, `exp10m1`, `exp2`, `exp2m1`, `expm1`                                             |
| <math.h>   | `log`, `log10`, `log10p1`, `log1p`, `log2`, `log2p1`, `logp1`                                    |
| <math.h>   | `scalbn`, `scalbln`, `ldexp`                                                                     |
| <math.h>   | `cbrt`, `compoundn`, `hypot`, `pow`, `pown`, `powr`, `rootn`, `rsqrt`, `sqrt`                    |
| <math.h>   | `erf`, `erfc`                                                                                    |
| <math.h>   | `lgamma`, `tgamma`                                                                               |
| <math.h>   | `rint`, `nearbyint`, `lrint`, `llrint`                                                           |
| <math.h>   | `fdim`                                                                                           |
| <math.h>   | `fma`                                                                                            |
| <math.h>   | `fadd`, `dadd`, `fsub`, `dsub`, `fmul`, `dmul`, `fdiv`, `ddiv`, `ffma`, `dfma`, `fsqrt`, `dsqrt` |
| <stdlib.h> | `atof`, `strfrom`, `strto`                                                                       |
| <wchar.h>  | `wcsto`                                                                                          |
| <stdio.h>  | `printf` and `scanf` families                                                                    |
| <wchar.h>  | `wprintf` and `wscanf` families                                                                  |

> 常数舍入模式可以使用动态舍入模式实现，但此方法不会根据所需的常数舍入模式解释不精确的浮点常数

```c
static inline int __swapround(const int new) {
    const int old = fegetround();
    fesetround(new);
    return old;
}
```

>---
#### FENV_DEC_ROUND （设置十进制浮点舍入方向）

```c
#include <fenv.h>
#ifdef __STDC_IEC_60559_DFP__
#pragma STDC FENV_DEC_ROUND dec-direction
#endif
```

`FENV_DEC_ROUND` 杂注是类似于 `FENV_ROUND` 杂注的十进制浮点版本。如果 `FLT_RADIX` 不为 10，则 `FENV_DEC_ROUND` 杂注只影响十进制浮点类型的操作符、函数和浮点常量。受影响的函数列于下表。如果 `FLT_RADIX` 为 10，则 `FENV_ROUND` 和 `FENV_DEC_ROUND` 杂注是否改变标准和十进制浮点操作的舍入方向是由实现定义的。

*dec-direction* 应该是在浮点舍入方向宏中定义的十进制舍入方向宏名称之一（`FE_DEC_DOWNWARD`、`FE_DEC_TONEAREST`、`FE_DEC_TONEARESTFROMZERO`、`FE_DEC_TOWARDZERO`、`FE_DEC_UPWARD`），用于指定恒定模式，或者是 `FE_DEC_DYNAMIC`，用于指定动态舍入。相应的动态舍入模式可以通过调用 `fe_dec_setround` 来建立。

下表中列出的函数族表示所有十进制浮点类型的函数，其中函数族由函数名表示，不带后缀。例如，`acos` 表示函数 `acosd32`、`acosd64` 和 `acosd128`。

| Header     | Function families                                                                                |
| :--------- | :----------------------------------------------------------------------------------------------- |
| <math.h>   | `acos`, `acospi`, `asin`, `asinpi`, `atan`, `atan2`, `atan2pi`, `atanpi`                         |
| <math.h>   | `cos`, `cospi`, `sin`, `sinpi`, `tan`, `tanpi`                                                   |
| <math.h>   | `acosh`, `asinh`, `atanh`                                                                        |
| <math.h>   | `cosh`, `sinh`, `tanh`                                                                           |
| <math.h>   | `exp`, `exp10`, `exp10m1`, `exp2`, `exp2m1`, `expm1`                                             |
| <math.h>   | `log`, `log10`, `log10p1`, `log1p`, `log2`, `log2p1`, `logp1`                                    |
| <math.h>   | `scalbn`, `scalbln`, `ldexp`                                                                     |
| <math.h>   | `cbrt`, `compoundn`, `hypot`, `pow`, `pown`, `powr`, `rootn`, `rsqrt`, `sqrt`                    |
| <math.h>   | `erf`, `erfc`                                                                                    |
| <math.h>   | `lgamma`, `tgamma`                                                                               |
| <math.h>   | `rint`, `nearbyint`, `lrint`, `llrint`                                                           |
| <math.h>   | `fdim`                                                                                           |
| <math.h>   | `fma`                                                                                            |
| <math.h>   | `d32add`, `d64add`, `d32sub`, `d64sub`, `d32mul`, `d64mul`, `d32div`, `d64div`, `d32fma`, `d64fma`, `d32sqrt`, `d64sqrt` |
| <stdlib.h> | `strfrom`, `strto`                                                                       |
| <wchar.h>  | `wcsto`                                                                                          |
| <stdio.h>  | `printf` and `scanf` families                                                                    |
| <wchar.h>  | `wprintf` and `wscanf` families                                                                  |

---
### Functions：浮点异常（Floating-point exceptions）

浮点异常函数提供对浮点状态标志的访问。函数的 `int` 输入参数表示对浮点异常的子集（0 或者是一个或多个浮点异常宏的位或，如 `FE_OVERFLOW | FE_INEXACT`）。对于其他参数值，则是未定义行为。

>---

#### feclearexcept （清除浮点异常位 ）

```c
int feclearexcept(int excepts);
```

`feclearexcept` 函数尝试清除由其参数表示的受支持的浮点异常。当参数为零或所有指定的异常都被成功清除，函数返回零。否则返回一个非零值。

```c
#include <fenv.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
 
/*
 * 可能的 hypot (三角斜边) 实现，它会活用许多高级浮点特性。
 */
double hypot_demo(double a, double b)
{
  const int range_problem = FE_OVERFLOW | FE_UNDERFLOW;
  feclearexcept(range_problem);  // 清除浮点异常位
  
  /* 尝试快速算法 */
  double result = sqrt(a * a + b * b);
  // 若未上溢或下溢
  if (!fetestexcept(range_problem))  
    return result;                   

  /* 做更多复杂计算以避免上溢或下溢 */
  int a_exponent,b_exponent;
  frexp(a, &a_exponent);
  frexp(b, &b_exponent);
  if (a_exponent - b_exponent > DBL_MAX_EXP)
    return fabs(a) + fabs(b);        // 我们可以忽略小值
    
  /* 令 fabs(a) 的规模接近 1 */
  double a_scaled = scalbn(a, -a_exponent);
  double b_scaled = scalbn(b, -a_exponent);
  // 现在上溢和下溢是不可能的
  result = sqrt(a_scaled * a_scaled + b_scaled * b_scaled);
  // 撤销规模化
  return scalbn(result, a_exponent);
}
 
int main(void)
{
  // 通常情况选择较快的路线
  printf("hypot(%f, %f) = %f\n", 3.0, 4.0, hypot_demo(3.0, 4.0));
  // 极限情形会选择较慢但更准确的路线
  printf("hypot(%e, %e) = %e\n", DBL_MAX / 2.0, DBL_MAX / 2.0, 
        hypot_demo(DBL_MAX / 2.0, DBL_MAX / 2.0));
 
  return 0;
}
/*
hypot(3.000000, 4.000000) = 5.000000
hypot(8.988466e+307, 8.988466e+307) = 1.271161e+308
*/
```

>---

#### fegetexceptflag & fesetexceptflag （获取或设置指定的浮点异常标志）

```c
int fegetexceptflag(fexcept_t *flagp, int excepts);
int fesetexceptflag(const fexcept_t *flagp, int excepts);
```

`fegetexceptflag` 函数尝试在参数 `flagp` 所指向的对象中存储由参数 `excepts` 指示的浮点异常标志的完整内容，它是浮点异常宏的按位或。当成功存储时返回零，否则返回非零值。

`fesetexceptflag` 函数尝试从 `flagp` 存储的状态复制列于 `excepts` 所指示的浮点异常标志到浮点环境，它不引发任何异常，仅修改标志的状态。`*flagp` 的值必须在之前调用 `fegetexceptflag` 时设置过。如果 `excepts` 为零，或者所有指定的标志都已成功的设置为相应的状态，则函数返回零，否则返回非零值。

浮点异常标志的完整内容不必是指示是否引发或清除异常的布尔值。它可以是结构体，包含布尔状态和触发了异常的代码地址。这些函数获取所有这些内容并以实现定义格式于 `flagp` 获取或存储它。

```c
#include <stdio.h>
#include <fenv.h>
 
#pragma fenv_access(on)
 
void show_fe_exceptions(void)
{
    printf("current exceptions raised: ");
    if(fetestexcept(FE_DIVBYZERO))     printf(" FE_DIVBYZERO");
    if(fetestexcept(FE_INEXACT))       printf(" FE_INEXACT");
    if(fetestexcept(FE_INVALID))       printf(" FE_INVALID");
    if(fetestexcept(FE_OVERFLOW))      printf(" FE_OVERFLOW");
    if(fetestexcept(FE_UNDERFLOW))     printf(" FE_UNDERFLOW");
    if(fetestexcept(FE_ALL_EXCEPT)==0) printf(" none");
    printf("\n");
}
 
int main(void)
{
    fexcept_t excepts;
 
    /* 设置“当前”异常标志集合。 */
    feraiseexcept(FE_INVALID);
    show_fe_exceptions();
 
    /* 保存当前异常标志。 */
    fegetexceptflag(&excepts,FE_ALL_EXCEPT);
 
    /* 临时引发二个其他异常。 */
    feclearexcept(FE_ALL_EXCEPT);
    feraiseexcept(FE_OVERFLOW | FE_INEXACT);
    show_fe_exceptions();
 
    /* 恢复先前的异常标志。 */
    fesetexceptflag(&excepts,FE_ALL_EXCEPT);
    show_fe_exceptions();
 
    return 0;
}
/*
current exceptions raised: FE_INVALID
current exceptions raised: FE_INEXACT FE_OVERFLOW
current exceptions raised: FE_INVALID
*/
```

>---

#### feraiseexcept （引发指定浮点异常）

```c
int feraiseexcept(int excepts);
```

`feraiseexcept` 函数试图引发由 `excepts` 指示的受支持的浮点异常。若异常之一为 `FE_OVERFLOW` 或 `FE_UNDERFLOW` ，则此函数是否额外引发 `FE_INEXACT` 由实现定义。异常的引发顺序未指定。若所有由 `excepts` 指定的异常都被成功引发，或 `excepts` 值为零，函数返回零；否则返回非零值。

```c
#include <stdio.h>
#include <fenv.h>
 
#pragma fenv_access(on)
 
void show_fe_exceptions(void)
{
    printf("current exceptions raised: ");
    if(fetestexcept(FE_DIVBYZERO))     printf(" FE_DIVBYZERO");
    if(fetestexcept(FE_INEXACT))       printf(" FE_INEXACT");
    if(fetestexcept(FE_INVALID))       printf(" FE_INVALID");
    if(fetestexcept(FE_OVERFLOW))      printf(" FE_OVERFLOW");
    if(fetestexcept(FE_UNDERFLOW))     printf(" FE_UNDERFLOW");
    if(fetestexcept(FE_ALL_EXCEPT)==0) printf(" none");
    feclearexcept(FE_ALL_EXCEPT);
    printf("\n");
}
 
double some_computation(void)
{
    /* 计算达到引发上溢的状态。 */
    int r = feraiseexcept(FE_OVERFLOW | FE_INEXACT);
    printf("feraiseexcept() %s\n", (r?"fails":"succeeds"));
    return 0.0;
}
 
int main(void)
{
    some_computation();
    show_fe_exceptions();
 
    return 0;
}
/*
feraiseexcept() succeeds
current exceptions raised:  FE_INEXACT FE_OVERFLOW
*/
```

>---
#### fetestexceptflag （确认指定的浮点异常标志内容）

```c
int fetestexceptflag(const fexcept_t *flagp, int excepts);
```

`fetestexceptflag` 函数确定在 `flagp` 指向的对象中设置了指定的浮点异常标志子集中的哪些。`*flagp` 的值必须在之前调用 `fegetexceptflag` 函数时设置过，函数的第二个参数至少表示由参数 `excepts` 表示的那些浮点异常。`excepts` 参数指定要查询的浮点状态标志。

`fetestexceptflag` 函数返回与 `*flagp` 中设置的浮点异常相对应的 `excepts` 中包含的浮点异常宏的按位 OR 值。

>---
#### fetestexcept （确认浮点异常状态是否设置）

```c
int fetestexcept(int excepts);
```

`fetestexcept` 函数用于确定当前设置了指定的浮点异常标志子集的哪一个。`excepts` 参数指定要查询的浮点状态标志。函数返回浮点异常宏的按位 OR 值，该浮点异常宏对应于 `excepts` 中包含的当前设置的浮点异常。

```c
#include <stdio.h>
#include <math.h>
#include <fenv.h>
#include <float.h>
 
#pragma fenv_access(on)
 
void show_fe_exceptions(void)
{
    printf("current exceptions raised: ");
    if(fetestexcept(FE_DIVBYZERO))     printf(" FE_DIVBYZERO");
    if(fetestexcept(FE_INEXACT))       printf(" FE_INEXACT");
    if(fetestexcept(FE_INVALID))       printf(" FE_INVALID");
    if(fetestexcept(FE_OVERFLOW))      printf(" FE_OVERFLOW");
    if(fetestexcept(FE_UNDERFLOW))     printf(" FE_UNDERFLOW");
    if(fetestexcept(FE_ALL_EXCEPT)==0) printf(" none");
    printf("\n");
}
 
int main(void)
{
    /* 显示默认浮点标志集合。 */
    show_fe_exceptions();
 
    /* 进行一些引发浮点异常的计算。 */
    printf("1.0/0.0     = %f\n", 1.0/0.0);        /* FE_DIVBYZERO            */
    printf("1.0/10.0    = %f\n", 1.0/10.0);       /* FE_INEXACT              */
    printf("sqrt(-1)    = %f\n", sqrt(-1));       /* FE_INVALID              */
    printf("DBL_MAX*2.0 = %f\n", DBL_MAX*2.0);    /* FE_INEXACT FE_OVERFLOW  */
    printf("nextafter(DBL_MIN/pow(2.0,52),0.0) = %.1f\n",
           nextafter(DBL_MIN/pow(2.0,52),0.0));   /* FE_INEXACT FE_UNDERFLOW */
    show_fe_exceptions();
 
    return 0;
}
/*
current exceptions raised:  none
1.0/0.0     = inf
1.0/10.0    = 0.100000
sqrt(-1)    = -nan(ind)
DBL_MAX*2.0 = inf
nextafter(DBL_MIN/pow(2.0,52),0.0) = 0.0
current exceptions raised:  FE_DIVBYZERO FE_INEXACT FE_INVALID FE_OVERFLOW FE_UNDERFLOW
*/
```

---
### Functions：浮点舍入方向（Rounding direction modes）

#### fegetmode & fesetmode （管理动态浮点控制模式）

```c
int fegetmode(femode_t *modep);
int fesetmode(const femode_t *modep);
```

`fegetmode` 函数尝试将所有动态浮点控制模式存储在 `modep` 指向的对象中。成功存储时返回零，否则返回一个非零值。

`fesetmode` 函数尝试设置由 `modep` 指向的对象表示的动态浮点模式。参数 `modep` 应指向通过调用 `fegetmode` 设置的对象，或等于 `FE_DEL_MODE` 或其他实现定义的动态浮点模式状态宏。当设置成功时，函数返回零；否则返回非零值。

>---

#### fegetround & fesetround （提供浮点舍入方向模式的控制）

```c
int fegetround(void);
int fesetround(int round);
```

`fegetround` 函数获取当前动态浮点舍入方向模式的当前值，即表示当前动态舍入方向的舍入方向宏。如果没有这样的舍入方向宏或者当前动态舍入方向不可确定时，则返回负值。

`fesetround` 函数设置由参数 `round` 表示的舍入方向。如果参数不等于舍入方向宏的值，则不会更改舍入方向。当且仅当动态舍入模式设置为请求的舍入方向时，函数返回零。

```c
#include <stdio.h>
#include <math.h>
#include <fenv.h>
 
#pragma fenv_access(on)

void show_fe_current_rounding_method(void)
{
    printf("current rounding method:  ");
    switch (fegetround()) {
           case FE_TONEAREST:  printf ("FE_TONEAREST");  break;
           case FE_DOWNWARD:   printf ("FE_DOWNWARD");   break;
           case FE_UPWARD:     printf ("FE_UPWARD");     break;
           case FE_TOWARDZERO: printf ("FE_TOWARDZERO"); break;
           default:            printf ("unknown");
    };
    printf("\n");
}
 
int main(void)
{
    /* 默认舍入方法 */
    show_fe_current_rounding_method();
    printf("+11.5 -> %+4.1f\n", rint(+11.5)); /* 两整数的中央值 */
    printf("+12.5 -> %+4.1f\n", rint(+12.5)); /* 两整数的中央值 */
 
    /* 保存舍入方法。 */
    int curr_method = fegetround();
 
    /* 临时更改当前舍入方法。 */
    fesetround(FE_DOWNWARD);
    show_fe_current_rounding_method();
    printf("+11.5 -> %+4.1f\n", rint(+11.5));
    printf("+12.5 -> %+4.1f\n", rint(+12.5));
 
    /* 恢复舍入方法。 */
    fesetround(curr_method);
    show_fe_current_rounding_method(); 
 
    return 0;
}
/*
current rounding method:  FE_TONEAREST
+11.5 -> +12.0
+12.5 -> +12.0
current rounding method:  FE_DOWNWARD
+11.5 -> +11.0
+12.5 -> +12.0
current rounding method:  FE_TONEAREST
*/
```

>---
#### fe_dec_getround & fe_dec_setround （提供十进制浮点舍入方向模式的控制）

```c
#include <fenv.h>
#ifdef __STDC_IEC_60559_DFP__
int fe_dec_getround(void);
int fe_dec_setround(int rnd);
#endif
```

`fe_dec_getround` 函数获取十进制浮点运算的动态舍入方向模式的舍入方向宏的当前值。如果没有此类舍入宏或当前舍入方向不确定时，则返回负值。

`fe_dec_setround` 函数将十进制浮点运算的动态舍入方向模式设置为由参数 `rnd` 表示的舍入方向。如果参数不等于十进制舍入方向宏的值，则舍入方向不更改。当且仅当参数等于十进制舍入方向宏时，`fe_dec_setround` 函数返回零。

如果 `FLT_RADIX` 不为 10，则由 `fesetround` 函数改变的舍入方向与 `fe_dec_setround` 函数改变的舍入方向无关；否则如果 `FLT_RADIX` 为 10，则 `fesetround` 和 `fe_dec_setround` 函数是否改变标准浮点和十进制浮点操作的舍入方向是由实现定义的。

---
### Functions：浮点环境（Environment）

这些函数用来统一管理浮点环境（状态标志和控制模式）。

>---

#### fegetenv & fesetenv （保存或恢复当前浮点环境）

```c
int fegetenv(fenv_t *envp);
int fesetenv(const fenv_t *envp);
```

`fegetenv` 函数尝试将当前动态浮点环境存储到 `envp` 所指向的对象中。成功存储时返回零，否则返回非零值。

`fesetenv` 函数尝试设置由 `envp` 指向的对象表示的动态浮点环境。参数 `envp` 的值必须是通过调用 `fegetenv` 或 `feholdexcept` 设置的对象，或等于动态浮点环境宏。`fesetenv` 仅安装由 `envp` 表示的浮点环境宏标记的状态，并且不会引发这些浮点异常。成功设置时返回零，否则返回非零值。

```c
#include <stdio.h>
#include <math.h>
#include <fenv.h>
 
#pragma fenv_access(on)
 
void show_fe_exceptions(void)
{
    printf("current exceptions raised: ");
    if(fetestexcept(FE_DIVBYZERO))     printf(" FE_DIVBYZERO");
    if(fetestexcept(FE_INEXACT))       printf(" FE_INEXACT");
    if(fetestexcept(FE_INVALID))       printf(" FE_INVALID");
    if(fetestexcept(FE_OVERFLOW))      printf(" FE_OVERFLOW");
    if(fetestexcept(FE_UNDERFLOW))     printf(" FE_UNDERFLOW");
    if(fetestexcept(FE_ALL_EXCEPT)==0) printf(" none");
    printf("\n");
}
 
void show_fe_rounding_method(void)
{
    printf("current rounding method:    ");
    switch (fegetround()) {
           case FE_TONEAREST:  printf ("FE_TONEAREST");  break;
           case FE_DOWNWARD:   printf ("FE_DOWNWARD");   break;
           case FE_UPWARD:     printf ("FE_UPWARD");     break;
           case FE_TOWARDZERO: printf ("FE_TOWARDZERO"); break;
           default:            printf ("unknown");
    };
    printf("\n");
}
 
void show_fe_environment(void)
{
    show_fe_exceptions();
    show_fe_rounding_method();
}    
 
int main(void)
{
    fenv_t curr_env;
    int rtn;
 
    /* 显示默认环境。 */
    show_fe_environment();
    printf("\n");
 
    /* 在默认环境下做一些计算。 */
    printf("+11.5 -> %+4.1f\n", rint(+11.5)); /* 两整数的中央值 */
    printf("+12.5 -> %+4.1f\n", rint(+12.5)); /* 两整数的中央值 */
    show_fe_environment();
    printf("\n");
 
    /* 保存当前环境。 */
    rtn = fegetenv(&curr_env);
 
    /* 以新舍入方法进行一些计算。 */
    feclearexcept(FE_ALL_EXCEPT);
    fesetround(FE_DOWNWARD);
    printf("1.0/0.0 = %f\n", 1.0/0.0);
    printf("+11.5 -> %+4.1f\n", rint(+11.5));
    printf("+12.5 -> %+4.1f\n", rint(+12.5));
    show_fe_environment();
    printf("\n");
 
    /* 恢复先前环境。 */
    rtn = fesetenv(&curr_env);
    show_fe_environment();
 
    return 0;
}
/*
current exceptions raised:  none
current rounding method:    FE_TONEAREST

+11.5 -> +12.0
+12.5 -> +12.0
current exceptions raised:  FE_INEXACT
current rounding method:    FE_TONEAREST

1.0/0.0 = inf
+11.5 -> +11.0
+12.5 -> +12.0
current exceptions raised:  FE_DIVBYZERO FE_INEXACT
current rounding method:    FE_DOWNWARD

current exceptions raised:  FE_INEXACT
current rounding method:    FE_TONEAREST
*/
```

>---

#### feholdexcept & feupdateenv

```c
int feholdexcept(fenv_t *envp);
int feupdateenv(const fenv_t *envp);
```

`feholdexcept` 函数将当前动态浮点环境保存在 `envp` 所指的对象中，清除浮点状态标志，然后为所有浮点异常安装不间断（浮点异常时继续）模式（如果可用）。当前仅当设置成功时返回零。

`feupdateenv` 函数尝试将当前引发的浮点异常保存在其自动存储中，安装由 `envp` 所指向的对象表示的动态浮点环境，然后引发已保存的浮点异常。参数 `envp` 应指向通过调用 `fegetenv` 或 `feholdexcept` 设置的对象，或等于动态浮点环境宏。如果所有操作都成功执行，则函数返回零，否则返回非零值。

```c
#include <stdio.h>
#include <fenv.h>
#include <float.h>

#pragma fenv_access(on)

void show_fe_exceptions(void)
{
    printf("current exceptions raised: ");
    if (fetestexcept(FE_DIVBYZERO))     printf(" FE_DIVBYZERO");
    if (fetestexcept(FE_INEXACT))       printf(" FE_INEXACT");
    if (fetestexcept(FE_INVALID))       printf(" FE_INVALID");
    if (fetestexcept(FE_OVERFLOW))      printf(" FE_OVERFLOW");
    if (fetestexcept(FE_UNDERFLOW))     printf(" FE_UNDERFLOW");
    if (fetestexcept(FE_ALL_EXCEPT) == 0) printf(" none");
    printf("\n");
}

double x2(double x)   /* 乘二 */
{
    fenv_t curr_excepts;

    /* 保存并清除当前浮点异常。 */
    feholdexcept(&curr_excepts);

    /* 引发不准确和上溢异常。 */
    printf("In x2():  x = %f\n", x = x * 2.0);
    show_fe_exceptions();

    /* 从调用方隐藏上溢异常 */
    feclearexcept(FE_OVERFLOW);   

    /* 将调用方的异常（ FE_INVALID ）并入剩下的 x2 的异常（ FE_OVERFLOW）。 */
    feupdateenv(&curr_excepts);
    return x;
}

int main(void)
{
    feclearexcept(FE_ALL_EXCEPT);
    feraiseexcept(FE_INVALID);   /* 一些有非法参数的计算 */
    show_fe_exceptions();

    printf("x2(DBL_MAX) = %f\n", x2(DBL_MAX));
    show_fe_exceptions();

    return 0;
}
/*
current exceptions raised:  FE_INVALID
In x2():  x = inf
current exceptions raised:  FE_INEXACT FE_OVERFLOW
x2(DBL_MAX) = inf
current exceptions raised:  FE_INEXACT FE_INVALID
*/
```

---
## C 浮点环境：fenv.h


`fenv.h`[[↗]](fenv_test.c) 定义了一些宏，和声明了提供对浮点环境的访问的类型和函数。浮点环境是指实现支持的任何浮点状态标志及控制模式的总称。

浮点状态标志是一个系统变量，其值在引发浮点异常时被设置且不会被清除，这是异常浮点算数提供辅助信息的副作用。浮点控制模式是一个系统变量，用户可以设置它的值来影响浮点运算的后续行为。

浮点控制模式可以是常量或动态的。动态浮点环境包括动态浮点控制模式和浮点状态标志。

动态浮点环境具有线程存储持续时间。线程的动态浮点环境的初始状态是创建它的线程的浮点环境在创建时的当前状态，它在线程创建时初始化。

某些编程约定支持动态浮点环境的预期使用模型：
- 函数调用不改变其调用方的浮点控制模式，不清除其调用方的浮点状态标志，也不依赖于其调用方的浮点状态标志的状态，除非该函数被如下记录；
- 假定函数调用需要默认的浮点控制模式，除非文档另有说明；
- 假定函数调用具有引发浮点异常的可能性，除非其文档另有说明；

<!-- 仅若设置 `#pragma STDC FENV_ACCESS` 为 ON ，浮点环境的访问及修改才有意义。 -->

>---
### Types

| Specifier | Description |
| :-------- | :---------- |


>---
### 浮点异常

| Specifier            | Description                                                                                     | Return                                          |
| :------------------- | :---------------------------------------------------------------------------------------------- | :---------------------------------------------- |
| `FE_INVALID`         | 出现于之前浮点运算的定义域错误。                                                                |
| `FE_DIVBYZERO`       | 出现于之前浮点运算的极点错误。                                                                  |
| `FE_OVERFLOW`        | 之前浮点运算的结果过大而无法表示。                                                              |
| `FE_UNDERFLOW`       | 之前浮点运算的结果为有精度损失的非正规值。                                                      |
| `FE_INEXACT`         | 不准确结果，必须舍入以存储之前浮点运算的结果。                                                  |
| `FE_ALL_EXCEPT`      | `(FE_INVALID \| FE_DIVBYZERO \| FE_OVERFLOW \| FE_UNDERFLOW \| FE_INEXACT)`                     |
| `fexcept_t`          | 集中表示浮点状态标志，包括实现与这些标志相关联的任何状态。                                      |
| `feclearexcept`      | 清除当前浮点异常位。                                                                            | 成功返回零。                                    |
| `fegetexceptflag`    | 在一个 `fexcept_t*` 对象中存储由 `excepts` 指示的浮点异常标志的完整内容。                       | 成功时返回零                                    |
| `fesetexceptflag`    | 尝试从 `fexcept_t* flagp` 存储的浮点异常状态，设置由 `excepts` 所指示的浮点异常标志到浮点环境。 | 成功时返回零。                                  |
| `feraiseexcept`      | 引发由 `excepts` 指定的浮点异常。                                                               |
| `fetestexceptflag`、 | 测试在 `fexcept_t *flagp` 中存储了由 `excepts` 指定的标志子集中的哪些浮点异常标志。             | 返回 `*flagp` 浮点异常集和 `excepts` 的按位或。 |  |
| `fetestexcept`       | 测试在 `excepts` 标志集中的哪些浮点异常状态被设置。                                             | 返回当前浮点异常和 `excepts` 的按位或。         |


其他浮点异常（以 `FE_` 开头）也可以由实现指定。`FE_ALL_EXCEPT` 是所有浮点异常宏的按位 OR，如果未定义则值为零。

```c
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <fenv.h>
#include <string.h>
#include <errno.h>

#pragma STDC FENV_ACCESS ON // 开启浮点环境控制模式
void show_fe_exceptions(void)
{
    if (errno != 0)
    {
        perror(strerror(errno));
        errno = 0, printf("\n");
        return;
    }
    printf("exceptions raised:");
    if (fetestexcept(FE_DIVBYZERO))
        printf(" FE_DIVBYZERO");
    if (fetestexcept(FE_INEXACT))
        printf(" FE_INEXACT");
    if (fetestexcept(FE_INVALID))
        printf(" FE_INVALID");
    if (fetestexcept(FE_DENORMAL))  // GNU
        printf(" FE_DENORMAL");
    if (fetestexcept(FE_OVERFLOW))
        printf(" FE_OVERFLOW");
    if (fetestexcept(FE_UNDERFLOW))
        printf(" FE_UNDERFLOW");
    feclearexcept(FE_ALL_EXCEPT);
    printf("\n\n");
}

void main(void)
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
0.0/0.0 = nan
exceptions raised: FE_INVALID
1.0/0.0 = inf
exceptions raised: FE_DIVBYZERO
1.0/10.0 = 0.100000
exceptions raised: FE_INEXACT
sqrt(-1) = nan
Domain error: Domain error
DBL_MAX*2.0 = inf
exceptions raised: FE_INEXACT FE_OVERFLOW
nextafter(DBL_MIN/pow(2.0,52),0.0) = 0.0
exceptions raised: FE_DENORMAL
*/
```

>---
### 浮点舍入方向

| Specifier              | Description                      | Return                 |
| :--------------------- | :------------------------------- | :--------------------- |
| `FE_DOWNWARD`          | 向负无穷大舍入。                 |
| `FE_TONEAREST`         | 向最接近可表示值舍入。           |
| `FE_TOWARDZERO`        | 向零舍入。                       |
| `FE_UPWARD`            | 向正无穷大舍入。                 |
| `FE_TONEARESTFROMZERO` | 向远离零方向最接近可表示值舍入。 |
| `fegetround`           | 获取当前动态浮点舍入方向的模式。 | 不确定时返回负值。     |
| `fesetround`           | 设置当前动态浮点舍入方向模式。   | 设置成功时返回参数值。 |


如果支持十进制浮点数：
| Specifier                  | Description                            |
| :------------------------- | :------------------------------------- |
| `FE_DEC_DOWNWARD`          | 向负无穷大舍入。                       |
| `FE_DEC_TONEAREST`         | 向最接近可表示值舍入。                 |
| `FE_DEC_TOWARDZERO`        | 向零舍入。                             |
| `FE_DEC_UPWARD`            | 向正无穷大舍入。                       |
| `FE_DEC_TONEARESTFROMZERO` | 向零方向最接近可表示值舍入。           |
| `fe_dec_getround`          | 获取当前十进制动态浮点舍入方向的模式。 | 不确定时返回负值。     |
| `fe_dec_setround`          | 设置当前十进制动态浮点舍入方向模式。   | 设置成功时返回参数值。 |


当且仅当实现支持通过 `fegetround` 和 `fesetround` 函数获取和设置所表示的舍入方向时才定义。定义的宏展开为非负相异的整型常量。其他舍入方向（以 `FE_`开头）可以由实现指定。

十进制浮点数的舍入方向宏与 `fe_dec_getround` 和 `fe_dec_setround` 函数一起使用。在程序启动时，十进制浮点运算的动态舍入方向模式初始化为 `FE_DEC_TONEAREST`。

不受当前舍入模式影响的操作：

- 浮点到整数的隐式转换或转型（始终向零）。
- 编译时执行的常量表达式中浮点算数运算符的结果（始终向最接近）。
- 库函数 `round`、`lround`、`llround`、`ceil`、`floor`、`trunc`。

```c
#include <stdio.h>
#include <math.h>
#include <fenv.h>
#pragma STDC FENV_ACCESS ON
 
void show_fe_cur_rounding(void)
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
 
void main(void)
{
   /* 默认舍入方法 */
    show_fe_cur_rounding();
    printf("+11.5 -> %+4.1f\n", rint(+11.5)); /* 两整数的中央值 */
    printf("+12.5 -> %+4.1f\n", rint(+12.5)); /* 两整数的中央值 */
 
    /* 更改当前舍入方法。 */
    fesetround(FE_DOWNWARD);
    show_fe_cur_rounding();
    printf("+11.5 -> %+4.1f\n", rint(+11.5));
    printf("+12.5 -> %+4.1f\n", rint(+12.5));
 
    return 0;
}
/*
current rounding method:  FE_TONEAREST
+11.5 -> +12.0
+12.5 -> +12.0
current rounding method:  FE_DOWNWARD
+11.5 -> +11.0
+12.5 -> +12.0
*/
```

>---
### 动态浮点环境

| Specifier      | Description                                                                                                                        | Return         |
| :------------- | :--------------------------------------------------------------------------------------------------------------------------------- | :------------- |
| `fenv_t`       | 表示整个动态浮点环境。                                                                                                             |
| `FE_DFL_ENV`   | 默认的动态浮点环境。可以用作 `fenv.h` 中管理动态浮点环境函数的参数，例如 `fesetenv`。                                             |
| `fegetenv`     | 尝试存储当前动态浮点环境到 `fenv_t *envp`。                                                                                        | 成功时返回零。 |
| `fesetenv`     | 设置由 `*envp` 对象表示的动态浮点环境。                                                                                            |
| `feholdexcept` | 将当前动态浮点环境保存在 `envp` 所指的对象中，并清除浮点状态标志。（如果可用）然后为所有浮点异常安装不间断（浮点异常时继续）模式。 | 成功时返回零。 |
| `feupdateenv`  | 尝试将当前引发的浮点异常保存在其自动存储中，安装由 `envp` 所指向的对象表示的动态浮点环境，然后引发已保存的浮点异常。               | 成功时返回零。 |

```c
// 打印当前的浮点环境
void show_fe_environment(void)
{
    show_fe_cur_rounding();
    show_fe_exceptions();
} 
 
int main(void)
{
    if (FENV_TEST != 4)
        return;
    fenv_t curr_env;
    /* 显示默认环境。 */
    show_fe_environment();
    /* 在默认环境下做一些计算。 */
    printf("+11.5 -> %+4.1f\n", rint(+11.5)); /* 两整数的中央值 */
    printf("+12.5 -> %+4.1f\n", rint(+12.5)); /* 两整数的中央值 */
    show_fe_environment();
    /* 保存当前环境。 */
    fegetenv(&curr_env);
    /* 以新舍入方法进行一些计算。 */
    feclearexcept(FE_ALL_EXCEPT);
    fesetround(FE_DOWNWARD);
    printf("1.0/0.0 = %f\n", 1.0 / 0.0);
    printf("+11.5 -> %+4.1f\n", rint(+11.5));
    printf("+12.5 -> %+4.1f\n", rint(+12.5));
    show_fe_environment();
    /* 恢复先前环境。 */
    fesetenv(&curr_env);
    show_fe_environment();
}
/*
current rounding method:  FE_TONEAREST
current exceptions raised:  none

+11.5 -> +12.0
+12.5 -> +12.0
current rounding method:  FE_TONEAREST
current exceptions raised:  FE_INEXACT

1.0/0.0 = inf
+11.5 -> +11.0
+12.5 -> +12.0
current rounding method:  FE_DOWNWARD
current exceptions raised:  FE_DIVBYZERO FE_INEXACT

current rounding method:  FE_TONEAREST
current exceptions raised:  FE_DIVBYZERO FE_INEXACT
*/
```


>---
### 动态浮点控制模式

| Specifier     | Description                                                  | Return         |
| :------------ | :----------------------------------------------------------- | :------------- |
| `femode_t`    | 表示实现支持的动态浮点控制模式的集合，包括动态舍入方向模式。 |
| `FE_DFL_MODE` | 默认的动态浮点控制模式集合。                                 |
| `fegetmode`   | 尝试存储当前动态浮点控制模式到 `femode_t *modep`。           | 成功时返回零。 |
| `fesetmode`   | 设置由 `*modep` 对象表示的动态浮点模式。                     | 成功时返回零。 |


>---
### Pragma

#### FENV_ACCESS （设置浮点控制模式）

```c
#include <fenv.h>
#pragma STDC FENV_ACCESS  on-off-switch  // ON / OFF / DEFAULT
// #pragma fenv_access (on / off / default) 
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

| Header     | Function families                                                                                                        |
| :--------- | :----------------------------------------------------------------------------------------------------------------------- |
| <math.h>   | `acos`, `acospi`, `asin`, `asinpi`, `atan`, `atan2`, `atan2pi`, `atanpi`                                                 |
| <math.h>   | `cos`, `cospi`, `sin`, `sinpi`, `tan`, `tanpi`                                                                           |
| <math.h>   | `acosh`, `asinh`, `atanh`                                                                                                |
| <math.h>   | `cosh`, `sinh`, `tanh`                                                                                                   |
| <math.h>   | `exp`, `exp10`, `exp10m1`, `exp2`, `exp2m1`, `expm1`                                                                     |
| <math.h>   | `log`, `log10`, `log10p1`, `log1p`, `log2`, `log2p1`, `logp1`                                                            |
| <math.h>   | `scalbn`, `scalbln`, `ldexp`                                                                                             |
| <math.h>   | `cbrt`, `compoundn`, `hypot`, `pow`, `pown`, `powr`, `rootn`, `rsqrt`, `sqrt`                                            |
| <math.h>   | `erf`, `erfc`                                                                                                            |
| <math.h>   | `lgamma`, `tgamma`                                                                                                       |
| <math.h>   | `rint`, `nearbyint`, `lrint`, `llrint`                                                                                   |
| <math.h>   | `fdim`                                                                                                                   |
| <math.h>   | `fma`                                                                                                                    |
| <math.h>   | `d32add`, `d64add`, `d32sub`, `d64sub`, `d32mul`, `d64mul`, `d32div`, `d64div`, `d32fma`, `d64fma`, `d32sqrt`, `d64sqrt` |
| <stdlib.h> | `strfrom`, `strto`                                                                                                       |
| <wchar.h>  | `wcsto`                                                                                                                  |
| <stdio.h>  | `printf` and `scanf` families                                                                                            |
| <wchar.h>  | `wprintf` and `wscanf` families                                                                                          |


---
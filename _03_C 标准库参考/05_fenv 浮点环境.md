## C 浮点环境：fenv.h

浮点环境是浮点状态标志及实现所支持的控制模式的集合。浮点环境具有线程存储持续时间。线程的浮点环境的初始状态是创建它的线程的浮点环境在创建时的当前状态。

浮点运算会修改指示反常值或补助信息的浮点状态标志。浮点控制模式影响浮点运算的结果。

浮点状态标志是一个系统变量。它的值在引发浮点异常时被设置且不会被清除，这是异常浮点算数提供辅助信息的副作用。用户可以设置它的值来影响浮点运算的后续行为。

仅若设置 `#pragma STDC FENV_ACCESS` 为 ON ，浮点环境的访问及修改才有意义。

---
### Type

`fenv_t` 表示整体浮点环境的类型。

`fexcept_t` 集中表示所有浮点异常状态标志的类型。

---
### Pragma: fenv_access （设置浮点控制模式）

```c
#include <fenv.h>
#pragma fenv_access(on | off)  // ON or OFF
```

`#pragma fenv_access(on | off) ` 提供了一种方法来通知程序何时可以访问浮点环境来测试浮点状态标志或在非默认浮点控制模式下运行。

---

### Macros

#### 浮点异常

```c
#define FE_INVALID     0x01     // 出现于之前浮点运算的定义域错误
#define FE_DIVBYZERO   0x04     // 出现于之前浮点运算的极点错误 
#define FE_OVERFLOW    0x08     // 之前浮点运算的结果过大而无法表示
#define FE_UNDERFLOW   0x10     // 之前浮点运算的结果为有精度损失的非正规值
#define FE_INEXACT     0x20     // 不准确结果：必须舍入以存储之前浮点运算的结果

// 所有受支持浮点异常的按位或
#define FE_ALL_EXCEPT (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW | FE_INEXACT)
```

> Test

```c
// MSVC
#include <stdio.h>asdasdaw
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

<br>

#### 浮点舍入方向

```c
/* FPU control word rounding flags */
#define FE_TONEAREST    0x0000    // 向最接近可表示值舍入
#define FE_DOWNWARD     0x0400    // 向负无穷大舍入
#define FE_UPWARD       0x0800    // 向正无穷大舍入
#define FE_TOWARDZERO   0x0c00    // 向零舍入
```
 
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

<br>

#### 默认浮点环境

```c
/* The FE_DFL_ENV macro is required by standard.
  fesetenv will use the environment set at app startup.*/
#define FE_DFL_ENV ((const fenv_t *) 0)
```

宏常量 `FE_DFL_ENV` 展开成 `const fenv_t*` 类型表达式，指向默认浮点环境，表示在程序启动时加载的浮点环境的完整副本。

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
### Functions：浮点异常（Floating-point exceptions）

浮点异常函数提供对浮点状态标志的访问。函数的 `int` 输入参数表示对浮点异常的子集（0 或者是一个或多个浮点异常宏的位或，如 `FE_OVERFLOW | FE_INEXACT`）。对于其他参数值，则是未定义行为。

#### feclearexcept （清除浮点异常位 ）

```c
int feclearexcept(int excepts);
```

`feclearexcept` 函数尝试清除由其参数表示的受支持的浮点异常。当参数列表为零或所有指定的异常都被成功清除，函数返回零。否则返回一个非零值。

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

<br>

#### fegetexceptflag & fesetexceptflag （获取或设置指定的浮点异常标志）

```c
int fegetexceptflag(fexcept_t *flagp, int excepts);
int fesetexceptflag(const fexcept_t *flagp, int excepts);
```

`fegetexceptflag` 函数尝试在参数 `flagp` 所指向的对象中存储由参数 `except` 指示的浮点异常标志的完整内容，它是浮点异常宏的按位或。

`fesetexceptflag` 函数尝试从 `flagp` 存储的状态复制列于 `except` 所指示的浮点异常标志到浮点环境，它不引发任何异常，仅修改标志的状态。

浮点异常标志的完整内容不必是指示是否引发或清除异常的布尔值。它可以是结构体，包含布尔状态和触发了异常的代码地址。这些函数获取所有这些内容并以实现定义格式于 `flagp` 获取或存储它。当成功存储/设置时将返回零。

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

<br>

#### feraiseexcept （引发指定浮点异常）

```c
int feraiseexcept(int excepts);
```

`feraiseexcept` 函数试图引发由 `excepts` 的浮点异常。若异常之一为 `FE_OVERFLOW` 或 `FE_UNDERFLOW` ，则此函数可以额外引发 `FE_INEXACT` 。异常的引发顺序未指定，除了 `FE_OVERFLOW` 和 `FE_UNDERFLOW` 一定先于 `FE_INEXACT` 引发。若引发了所有列出的异常，则返回 ​0​ ，否则返回非零值

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

<br>

#### fetestexcept （确认浮点异常状态是否设置）

```c
int fetestexcept(int excepts);
```

`fetestexcept` 函数用于确定当前设置了浮点异常标志的哪个指定子集。返回包含于 `excepts` 中对应于当前设置的浮点异常中的浮点异常宏的按位或。

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

#### fegetround & fesetround （获得或设置数字的舍入方向）

```c
int fegetround(void);
int fesetround(int round);
```

`fegetround` 函数获取当前浮点舍入方向宏，如果没有这样的舍入方向宏或者当前舍入方向不可确定时，则返回负值。

`fesetround` 函数建立由参数 `round` 表示的舍入方向。如果参数不等于舍入方向宏的值，则不会更改舍入方向。舍入方向成功建立时返回零。

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

---
### Functions：浮点环境（Environment）

这些函数用来管理浮点环境（状态标志和控制模式）。

#### fegetenv & fesetenv （保存或恢复当前浮点环境）

```c
int fegetenv(fenv_t *envp);
int fesetenv(const fenv_t *envp);
```

`fegetenv` 函数试图将当前的浮点环境存储到 `envp` 所指向的对象中。成功存储时返回零。

`fesetenv` 函数试图建立由 `envp` 表示的浮点环境状态。`envp` 的值必须是通过调用 `fegetenv` 或 `feholdexcept` 设置的对象或是浮点宏常量。`fesetenv` 仅安装 `envp` 表示的浮点环境宏标记的状态，并且不会引发这些浮点异常。成功设置时返回零。

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

<br>

#### feholdexcept & feupdateenv

```c
int feholdexcept(fenv_t *envp);
int feupdateenv(const fenv_t *envp);
```

`feholdexcept` 函数将当前浮点环境保存在 `envp` 对象中，清除浮点状态标志，然后为所有浮点异常安装不间断模式（继续处理浮点异常）。当前仅当设置成功时返回零。

`feupdateenv` 函数尝试将当前引发的浮点异常保存在其自动存储中，安装由 `envp` 表示的浮点环境，然后引发保存的浮点异常。`envp` 必须是 `fegetenv` 或 `feholdexcept` 设置的对象，或者是一个浮点环境宏。

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
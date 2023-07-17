#include "_test_head.h"
#include <fenv.h>
#include <float.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#pragma STDC FENV_ACCESS ON

static void Test_FE_Exceptions();
static void Test_FE_Rounding();
static void Test_FE_Environment();

static void show_fe_exceptions(bool);
static void show_fe_rounding_method(void);
static void show_fe_environment();

void Test_C_Lib()
{
    Test_FE_Exceptions();

    Test_FE_Rounding();

    Test_FE_Environment();
}

void show_fe_environment(void)
{
    show_fe_exceptions(false);
    show_fe_rounding_method();
}

static void show_fe_rounding_method(void)
{
    printf("current rounding method:    ");
    switch (fegetround())
    {
    case FE_TONEAREST:
        printf("FE_TONEAREST"); // 向最接近舍入
        break;
    case FE_DOWNWARD:
        printf("FE_DOWNWARD"); // 向负无穷大舍入
        break;
    case FE_UPWARD:
        printf("FE_UPWARD"); // 向正无穷大舍入
        break;
    case FE_TOWARDZERO:
        printf("FE_TOWARDZERO"); // 向零舍入
        break;
    default:
        printf("unknown");
    };
    printf("\n");
}
static void show_fe_exceptions(bool isClearFlags)
{
    printf("current exceptions raised: ");
    if (fetestexcept(FE_DIVBYZERO)) // 极点错误
        printf(" FE_DIVBYZERO");
    if (fetestexcept(FE_INEXACT)) // 不准确结果
        printf(" FE_INEXACT");
    if (fetestexcept(FE_INVALID)) // 定义域错误
        printf(" FE_INVALID");
    if (fetestexcept(FE_OVERFLOW)) // 结果上溢
        printf(" FE_OVERFLOW");
    if (fetestexcept(FE_UNDERFLOW)) // 结果下溢
        printf(" FE_UNDERFLOW");
    if (fetestexcept(FE_ALL_EXCEPT) == 0)
        printf(" none");
    if (isClearFlags)
        feclearexcept(FE_ALL_EXCEPT);
    printf("\n");
}

void Test_FE_Exceptions()
{
    puts("==== Test Floating-point Exceptions ====");

    puts("--- test Macros ----");
    printf("0.0/0.0 = %f\n", 0.0 / 0.0);
    show_fe_exceptions(true);
    printf("1.0/0.0 = %f\n", 1.0 / 0.0);
    show_fe_exceptions(true);
    printf("1.0/10.0 = %f\n", 1.0 / 10.0);
    show_fe_exceptions(true);
    printf("sqrt(-1) = %f\n", sqrt(-1));
    show_fe_exceptions(true);
    printf("DBL_MAX*2.0 = %f\n", DBL_MAX * 2.0);
    show_fe_exceptions(true);
    printf("nextafter(DBL_MIN/pow(2.0,52),0.0) = %.1f\n", nextafter(DBL_MIN / pow(2.0, 52), 0.0));
    show_fe_exceptions(true);

    puts("--- test Macros ----");
    fexcept_t excepts;
    /* 设置 “当前” 异常标志集合。 */
    feraiseexcept(FE_INVALID);
    show_fe_exceptions(false);
    /* 保存当前异常标志。 */
    fegetexceptflag(&excepts, FE_ALL_EXCEPT);
    /* 临时引发二个其他异常。 */
    feclearexcept(FE_ALL_EXCEPT);
    feraiseexcept(FE_OVERFLOW | FE_INEXACT);
    show_fe_exceptions(false);
    /* 恢复先前的异常标志。 */
    fesetexceptflag(&excepts, FE_ALL_EXCEPT);
    show_fe_exceptions(false);

    puts("==== Test End ====\n");
}

void Test_FE_Rounding()
{
    puts("==== Test Rounding ====");
    feclearexcept(FE_ALL_EXCEPT);

    /* 默认舍入方法 */
    show_fe_rounding_method();
    printf("+11.5 -> %+4.1f\n", rint(+11.5)); /* 两整数的中央值 */
    printf("+12.5 -> %+4.1f\n", rint(+12.5)); /* 两整数的中央值 */
    /* 保存舍入方法。 */
    int curr_method = fegetround();
    /* 临时更改当前舍入方法。 */
    fesetround(FE_DOWNWARD);
    show_fe_rounding_method();
    printf("+11.5 -> %+4.1f\n", rint(+11.5));
    printf("+12.5 -> %+4.1f\n", rint(+12.5));
    /* 恢复舍入方法。 */
    fesetround(curr_method);
    show_fe_rounding_method();

    puts("==== End Test ====\n");
}

void Test_FE_Environment()
{
    puts("==== Test Environment ====");
    puts("--- test feholdexcept & feupdateenv ---");
    fenv_t curr_excepts;
    double x = DBL_MAX;

    feclearexcept(FE_ALL_EXCEPT);
    feraiseexcept(FE_INVALID); /* 设置一些有非法参数的计算 */
    show_fe_exceptions(false);

    /* 保存并清除当前浮点异常。 */
    feholdexcept(&curr_excepts);
    /* 引发不准确和上溢异常。 */
    printf("In x2():  x = %f\n", x = x * 2.0);
    show_fe_exceptions(false);
    feclearexcept(FE_INEXACT); /* 从调用方隐藏不准确异常 */
    /* 将调用方的异常（ FE_INVALID ）并入剩下的 x2 的异常（ FE_OVERFLOW）。 */
    feupdateenv(&curr_excepts);

    printf("x2(DBL_MAX) = %f\n", x);
    show_fe_exceptions(false);

    feclearexcept(FE_ALL_EXCEPT);

    puts("--- test fegetenv & fesetenv ---");
    fenv_t curr_env;
    int env_rtn;

     /* 显示默认环境。 */
    show_fe_environment();
    printf("\n");
 
    /* 在默认环境下做一些计算。 */
    printf("+11.5 -> %+4.1f\n", rint(+11.5)); /* 两整数的中央值 */
    printf("+12.5 -> %+4.1f\n", rint(+12.5)); /* 两整数的中央值 */
    show_fe_environment();
    printf("\n");
 
    /* 保存当前环境。 */
    env_rtn = fegetenv(&curr_env);
 
    /* 以新舍入方法进行一些计算。 */
    feclearexcept(FE_ALL_EXCEPT);
    fesetround(FE_DOWNWARD);
    printf("1.0/0.0 = %f\n", 1.0/0.0);
    printf("+11.5 -> %+4.1f\n", rint(+11.5));
    printf("+12.5 -> %+4.1f\n", rint(+12.5));
    show_fe_environment();
    printf("\n");
 
    /* 恢复先前环境。 */
    env_rtn = fesetenv(&curr_env);
    show_fe_environment();

    puts("==== End Test ====\n");
}

int main(int argc, char const *argv[])
{
    Test_C_Lib();
    
    return 0;
}

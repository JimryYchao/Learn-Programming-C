#include <stdio.h>
#include <math.h>
#include <float.h>
#include <fenv.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#pragma STDC FENV_ACCESS ON // 开启浮点环境控制模式
static int FENV_TEST = 0;

//! test float exception

//? fetestexcept
static void show_fe_exceptions(void)
{
    printf("current exceptions raised: ");
    if (fetestexcept(FE_DIVBYZERO))
        printf(" FE_DIVBYZERO");
    if (fetestexcept(FE_INEXACT))
        printf(" FE_INEXACT");
    if (fetestexcept(FE_INVALID))
        printf(" FE_INVALID");
    if (fetestexcept(FE_OVERFLOW))
        printf(" FE_OVERFLOW");
    if (fetestexcept(FE_UNDERFLOW))
        printf(" FE_UNDERFLOW");
    if (fetestexcept(FE_ALL_EXCEPT) == 0)
        printf(" none");
    if (fetestexcept(FE_UNDERFLOW))
        printf(" FE_UNDERFLOW");
    printf("\n\n");
}

//? feclearexcept
static void showAndClear_fe_exceptions(void)
{
    if (errno != 0)
    {
        perror(strerror(errno));
        errno = 0;
    }
    show_fe_exceptions();
    feclearexcept(FE_ALL_EXCEPT);
}

//? feraiseexcept, fegetexceptflag, fesetexceptflag
void testFE_raiseExcept()
{
    if (FENV_TEST != 1)
        return;

    fexcept_t excepts;
    //? 设置“当前”异常标志集合
    feraiseexcept(FE_INVALID);
    show_fe_exceptions();
    //? 保存当前异常标志
    fegetexceptflag(&excepts, FE_ALL_EXCEPT);
    //? 临时引发二个其他异常
    feclearexcept(FE_ALL_EXCEPT);
    feraiseexcept(FE_OVERFLOW | FE_INEXACT);
    show_fe_exceptions();
    //? 恢复先前的异常标志
    fesetexceptflag(&excepts, FE_ALL_EXCEPT);
    show_fe_exceptions();
}

void testFE_Exceptions()
{
    if (FENV_TEST != 2)
        return;
    /* 显示默认浮点标志集合。 */
    show_fe_exceptions();

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

//! test float round

static void show_fe_cur_rounding(void)
{
    printf("current rounding method:  ");
    switch (fegetround())
    {
    case FE_TONEAREST:
        printf("FE_TONEAREST");
        break;
    case FE_DOWNWARD:
        printf("FE_DOWNWARD");
        break;
    case FE_UPWARD:
        printf("FE_UPWARD");
        break;
    case FE_TOWARDZERO:
        printf("FE_TOWARDZERO");
        break;
    default:
        printf("unknown");
    };
    printf("\n");
}

static void show_fe_environment(void)
{
    show_fe_cur_rounding();
    show_fe_exceptions();
}

void testFE_Round()
{
    if (FENV_TEST != 3)
        return;
    /* 默认舍入方法 */
    show_fe_cur_rounding();
    printf("+11.5 -> %+4.1f\n", rint(+11.5)); /* 两整数的中央值 */
    printf("+12.5 -> %+4.1f\n", rint(+12.5)); /* 两整数的中央值 */

    /* 更改当前舍入方法。 */
    fesetround(FE_DOWNWARD);
    show_fe_cur_rounding();
    printf("+11.5 -> %+4.1f\n", rint(+11.5));
    printf("+12.5 -> %+4.1f\n", rint(+12.5));
}

//! test float env

void testFE_GetAndSet_FloatEnv()
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

static double x2(double x) /* 乘二 */
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

void testFE_HoldUpdate_FloatEnv()
{
    if (FENV_TEST != 5)
        return;
    feclearexcept(FE_ALL_EXCEPT);
    feraiseexcept(FE_INVALID); /* 一些有非法参数的计算 */
    show_fe_exceptions();

    printf("x2(DBL_MAX) = %f\n", x2(DBL_MAX));
    show_fe_exceptions();
}

//! test float mode  (pre-define)
void testFE_FloatMode();

int main()
{
    FENV_TEST = 4;  // 1~5

    testFE_raiseExcept();

    testFE_Exceptions();

    testFE_Round();

    testFE_GetAndSet_FloatEnv();

    testFE_HoldUpdate_FloatEnv();
}
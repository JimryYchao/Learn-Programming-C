#include <float.h>
#include <fenv.h>
#define printf __mingw_printf // win 平台下输出 long double

#include <stdio.h>

int main()
{
    // 浮点数的底
    printf("FLT_RADIX  = %d\n", FLT_RADIX);

    puts("");

    // 浮点数的精度
    printf("DECIMAL_DIG  = %d\n", DECIMAL_DIG);

    printf("FLT_DECIMAL_DIG  = %d\n", FLT_DECIMAL_DIG);
    printf("DBL_DECIMAL_DIG  = %d\n", DBL_DECIMAL_DIG);
    printf("LDBL_DECIMAL_DIG  = %d\n", LDBL_DECIMAL_DIG);

    printf("FLT_DIG  = %d\n", FLT_DIG);
    printf("DBL_DIG  = %d\n", DBL_DIG);
    printf("LDBL_DIG  = %d\n", LDBL_DIG);

    printf("FLT_MANT_DIG  = %d\n", FLT_MANT_DIG);
    printf("DBL_MANT_DIG  = %d\n", DBL_MANT_DIG);
    printf("LDBL_MANT_DIG  = %d\n", LDBL_MANT_DIG);

    puts("");

    // 浮点数的值范围限定
    printf("FLT_MIN  = %e\n", FLT_MIN);
    printf("DBL_MIN  = %e\n", DBL_MIN);
    printf("LDBL_MIN  = %Le\n", LDBL_MIN);

    printf("FLT_MAX  = %e\n", FLT_MAX);
    printf("DBL_MAX  = %e\n", DBL_MAX);
    printf("LDBL_MAX  = %Le\n", LDBL_MAX);

    printf("FLT_TRUE_MIN  = %e\n", FLT_TRUE_MIN);
    printf("DBL_TRUE_MIN  = %e\n", DBL_TRUE_MIN);
    printf("LDBL_TRUE_MIN  = %Le\n", LDBL_TRUE_MIN);

    printf("FLT_EPSILON  = %e\n", FLT_EPSILON);
    printf("DBL_EPSILON  = %e\n", DBL_EPSILON);
    printf("LDBL_EPSILON  = %Le\n", LDBL_EPSILON);

    puts("");

    // 一些浮点数的幂指数限定
    printf("FLT_MAX_EXP  = %d\n", FLT_MAX_EXP);
    printf("DBL_MAX_EXP  = %d\n", DBL_MAX_EXP);
    printf("LDBL_MAX_EXP  = %d\n", LDBL_MAX_EXP);

    printf("FLT_MIN_EXP  = %d\n", FLT_MIN_EXP);
    printf("DBL_MIN_EXP  = %d\n", DBL_MIN_EXP);
    printf("LDBL_MIN_EXP  = %d\n", LDBL_MIN_EXP);

    printf("FLT_MAX_10_EXP  = %d\n", FLT_MAX_10_EXP);
    printf("DBL_MAX_10_EXP  = %d\n", DBL_MAX_10_EXP);
    printf("LDBL_MAX_10_EXP  = %d\n", LDBL_MAX_10_EXP);

    printf("FLT_MIN_10_EXP  = %d\n", FLT_MIN_10_EXP);
    printf("DBL_MIN_10_EXP  = %d\n", DBL_MIN_10_EXP);
    printf("LDBL_MIN_10_EXP  = %d\n", LDBL_MIN_10_EXP);

    // 其他宏表示
    printf("FLT_ROUNDS  = %d\n", FLT_ROUNDS);

    printf("FLT_EVAL_METHOD  = %d\n", FLT_EVAL_METHOD);

    printf("FLT_HAS_SUBNORM  = %d\n", FLT_HAS_SUBNORM);
    printf("DBL_HAS_SUBNORM  = %d\n", DBL_HAS_SUBNORM);
    printf("LDBL_HAS_SUBNORM  = %d\n", LDBL_HAS_SUBNORM);

    return 0;
}
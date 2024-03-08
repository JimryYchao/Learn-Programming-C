## C 复数运算（Complex arithmetic）：complex.h

```c
#define __STDC_VERSION_COMPLEX_H__          202311L
```

`complex.h` 声明并支持复数类型的基本运算。定义 `__STDC_NO_COMPLEX__` 则可以不提供这个头文件和它的任何功能。

除 `CMPLX` 宏外，每个复数类型都指定了一系列函数，该函数由具有一个或多个 `double complex` 参数的函数主体和 `double complex` 或 `double` 返回值组成；以及其他同名但带有 `f` 和 `l` 后缀的函数，这些函数是具有 `float` 和 `long double` 参数和返回值的对应函数。

值被解释为弧度，而不是度数。

为未来加入 `<complex.h>` 而潜在 (C23 起) 保留下列函数名，并且在包含该头文件的程序中不可使用：`cerf`、`cerfc`、`cexp2`、`cexpm1`、`clog10`、`clog1p`、`clog2`、`clgamma`、`ctgamma`、`csinpi`、`ccospi`、`ctanpi`、`casinpi`、`cacospi`、`catanpi`、`ccompoundn`、`cpown`、`cpowr`、`crootn`、`crsqrt`、`cexp10m1`、`cexp10`、`cexp2m1`、`clog10p1`、`clog2p1`、`clogp1` (C23 起)，还有它们带 `-f` 及 `-l` 后缀的变体。

---
### Macros

#### 复数定义

```c
#define complex         _Complex
#define _Complex_I      float _Complex      // 虚数单位 i^2 = -1
#define imaginary       _Imaginary
#define _Imaginary_I    float _Imaginary    // 虚数单位
#define I               _Complex_I or _Imaginary_I  // 若未定义 _Imaginary_I, 扩展为 _Complex_I
```

从 C99 开始支持三种内置类型 `double _Complex`、`float _Complex`、`long double _Complex` 的复杂数学运算，还支持三种虚数类型 `double _Imaginary`、`float _Imaginary`、`long double _Imaginary`。

- 复数函数中定义一个主函数对应 `double` 精度的复数运算，具有相同名称但后缀为 `f` 和 `l` 的函数，分别对应 `float`、`long double` 精度的复数运算。

>---
#### 复数构造 

```c
double complex CMPLX(double x, double y);
float complex CMPLXF(float x, float y);
long double complex CMPLXL(long double x, long double y);

#define CMPLX(x, y) ((double complex)((double)(x) + \
_Imaginary_I * (double)(y)))
#define CMPLXF(x, y) ((float complex)((float)(x) + \
_Imaginary_I * (float)(y)))
#define CMPLXL(x, y) ((long double complex)((long double)(x) + \
_Imaginary_I * (long double)(y)))
```

 
---
#### MSVC：复数定义

Microsoft C 运行库 CRT 提供复数数学库运算，也包括 ISO-C99 所需的所有函数。但是编译器不直接支持 `complex` 或 `_Complex` 关键字，因此 Microsoft 使用结构来表示复数。

```c
typedef struct _C_double_complex
{
    double _Val[2];
} _C_double_complex;

typedef struct _C_float_complex
{
    float _Val[2];
} _C_float_complex;

typedef struct _C_ldouble_complex
{
    long double _Val[2];
} _C_ldouble_complex;

typedef _C_double_complex  _Dcomplex;
typedef _C_float_complex   _Fcomplex;
typedef _C_ldouble_complex _Lcomplex;
```

Microsoft C 提供了相应的复数类型的构造器：

```c
#define _DCOMPLEX_(re, im)  _Cbuild(re, im)
#define _FCOMPLEX_(re, im)  _FCbuild(re, im)
#define _LCOMPLEX_(re, im)  _LCbuild(re, im)
```

---
### Pragma：CX_LIMITED_RANGE

```c
#pragma CX_LIMITED_RANGE  no-off-switch
```

通常用于复乘法、除法和绝对值的数学公式是有问题的，因为它们对无穷大的处理以及不适当的上溢和下溢。`CX_LIMITED_RANGE` 编译指示可用于通知实现（当状态为 “ON” 时）通常的数学公式是可以接受的。编译指示的默认状态是 “OFF”。

---
### Functions：三角函数（Trigonometric functions）

#### ccos、csin、ctan （三角函数）

```c
// 复数余弦函数
double complex ccos(double complex z);
float complex ccosf(float complex z);
long double complex ccosl(long double complex z);

// 复数正弦函数
double complex csin(double complex z);
float complex csinf(float complex z);
long double complex csinl(long double complex z);

// 复数正切函数
double complex ctan(double complex z);
float complex ctanf(float complex z);
long double complex ctanl(long double complex z);
```

>---

#### cacos、casin、catan （反三角函数）

```c
// 复数反余弦函数
double complex cacos(double complex z);
float complex cacosf(float complex z);
long double complex cacosl(long double complex z);

// 复数反正弦函数
double complex casin(double complex z);
float complex casinf(float complex z);
long double complex casinl(long double complex z);

// 复数反正切函数
double complex catan(double complex z);
float complex catanf(float complex z);
long double complex catanl(long double complex z);
```

---
### Functions：双曲函数（Hyperbolic functions）

#### ccosh、csinh、ctanh （双曲函数）

```c
// 复数双曲余弦函数
double complex ccosh(double complex z);
float complex ccoshf(float complex z);
long double complex ccoshl(long double complex z);

// 复数双曲正弦函数
double complex csinh(double complex z);
float complex csinhf(float complex z);
long double complex csinhl(long double complex z);

// 复数双曲正切函数
double complex ctanh(double complex z);
float complex ctanhf(float complex z);
long double complex ctanhl(long double complex z);
```

>---

#### cacosh、casinh、catanh （反双曲函数）

```c
// 复数反双曲余弦函数
double complex cacosh(double complex z);
float complex cacoshf(float complex z);
long double complex cacoshl(long double complex z);

// 复数反双曲正弦函数
double complex casinh(double complex z);
float complex casinhf(float complex z);
long double complex casinhl(long double complex z);

// 复数反双曲正切函数  
double complex catanh(double complex z);
float complex catanhf(float complex z);
long double complex catanhl(long double complex z); 
```

---
### Functions：指数和对数函数（Exponential and logarithmic functions）

#### cexp （指数函数）

```c
// 复数的以 e 为底的复数指数
double complex cexp(double complex z);
float complex cexpf(float complex z);
long double complex cexpl(long double complex z);
```

>---

#### clog、clog10 （对数函数）

```c
// 复数的以 e 为底的复数自然对数
double complex clog(double complex z);
float complex clogf(float complex z);
long double complex clogl(long double complex z);
```

---
### Functions：幂和绝对值函数（Power and absolute-value functions）

#### csqrt （平方根）

```c
// 复数的复数平方根
double complex csqrt(double complex z);
float complex csqrtf(float complex z);
long double complex csqrtl(long double complex z);
```

>---

#### cpow （数的给定次幂）

```c
// 复数的给定复数次幂 _X ^ _Y 
double complex cpow(double complex x, double complex y);
float complex cpowf(float complex x, float complex y);
long double complex cpowl(long double complex x, long double complex y);
```

>---

#### cabs （绝对值）

```c
// 复数的复数绝对值（也叫范数或模数、量值）
double cabs(double complex z);
float cabsf(float complex z);
long double cabsl(long double complex z);
```

---
### Functions：复数操作函数（Manipulation functions）

#### carg （复数的相角）

```c
// 复数的相位（角度）
double carg(double complex z);
float cargf(float complex z);
long double cargl(long double complex z);
```

>---

#### creal、cimag （实部和虚部）

```c
// 复数的虚部
double cimag(double complex z);
float cimagf(float complex z);
long double cimagl(long double complex z);

// 复数的实部
double creal(double complex z);
float crealf(float complex z);
long double creall(long double complex z);
```

>---

#### conj （复数共轭）

```c
// 复数的复数共轭
double complex conj(double complex z);
float complex conjf(float complex z);
long double complex conjl(long double complex z);
```

>---

#### cproj （Riemann 球体的复数投影）

```c
// 计算黎曼球体上某个复数的投影
double complex cproj(double complex z);
float complex cprojf(float complex z);
long double complex cprojl(long double complex z);
```

---
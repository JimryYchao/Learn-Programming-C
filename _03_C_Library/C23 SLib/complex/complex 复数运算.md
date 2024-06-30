## C 复数运算：complex.h

`complex.h` 声明并支持复数类型的基本运算。定义 `__STDC_NO_COMPLEX__` 则可以不提供这个头文件和它的任何功能。

除 `CMPLX` 宏外，每个复数类型都指定了一系列函数，该函数由具有一个或多个 `double complex` 参数的函数主体和 `double complex` 或 `double` 返回值组成；以及其他同名但带有 `f` 和 `l` 后缀的函数，这些函数是具有 `float` 和 `long double` 参数和返回值的对应函数。

值被解释为弧度，而不是度数。

为未来可能加入 `<complex.h>` 而潜在 (C23 起) 保留下列函数名，并且在包含该头文件的程序中不可使用：`cerf`、`cerfc`、`cexp2`、`cexpm1`、`clog10`、`clog1p`、`clog2`、`clgamma`、`ctgamma`、`csinpi`、`ccospi`、`ctanpi`、`casinpi`、`cacospi`、`catanpi`、`ccompoundn`、`cpown`、`cpowr`、`crootn`、`crsqrt`、`cexp10m1`、`cexp10`、`cexp2m1`、`clog10p1`、`clog2p1`、`clogp1` (C23 起)，还有它们带 `-f` 及 `-l` 后缀的变体。

>---
### 复数定义

| Specifier                        | Description                |
| :------------------------------- | :------------------------- |
| `complex`, `_Complex_I`          | 复数宏定义                 |
| `imaginary`, `_Imaginary_I`, `I` | 虚数宏定义和虚数单元。     |
| `CMPLX`                          | 构造 `double complex`      |
| `CMPLXF`                         | 构造 `float complex`       |
| `CMPLXL`                         | 构造 `long double complex` |

从 C99 开始支持三种内置类型 `double _Complex`、`float _Complex`、`long double _Complex` 的复杂数学运算，还支持三种虚数类型 `double _Imaginary`、`float _Imaginary`、`long double _Imaginary`。

> MSVC：复数定义

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

>---
### CX_LIMITED_RANGE

```c
#pragma CX_LIMITED_RANGE  no-off-switch
```

通常用于复乘法、除法和绝对值的数学公式是有问题的，因为它们对无穷大的处理以及不适当的上溢和下溢。`CX_LIMITED_RANGE` 编译指示可用于通知实现（当状态为 “ON” 时）通常的数学公式是可以接受的。编译指示的默认状态是 “OFF”。

>---
### 复数函数

复数函数中定义一个主函数对应 `double` 精度的复数运算，具有相同名称但后缀为 `f` 和 `l` 的函数，分别对应 `float`、`long double` 精度的复数运算。

| Specifier                    | Description             |
| :--------------------------- | :---------------------- |
| `ccos`、`csin`、`ctan`       | 三角函数                |
| `cacos`、`casin`、`catan`    | 反三角函数              |
| `ccosh`、`csinh`、`ctanh`    | 双曲函数                |
| `cacosh`、`casinh`、`catanh` | 反双曲函数              |
| `cexp`                       | 以 e 为底的复数指数     |
| `clog`、`clog10`             | 以 e 为底的复数自然对数 |
| `csqrt`                      | 复平方根                |
| `cpow`                       | 复数的给定次幂          |
| `cabs`                       | 复绝对值                |
| `carg`                       | 复数的相角              |
| `creal`、`cimag`             | 实部和虚部              |
| `conj`                       | 复数共轭                |
| `cproj`                      | 黎曼球体的复数投影      |

---
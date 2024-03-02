## C 复数运算（Complex arithmetic）：complex.h

`complex.h` 声明并支持复数的类型和基本运算。定义 `__STDC_NO_COMPLEX__` 可以不提供这个头文件和它的任何功能。

- 从 C99 开始支持三种内置类型 `double _Complex`、`float _Complex`、`long double _Complex` 的复杂数学运算，还支持三种虚数类型 `double _Imaginary`、`float _Imaginary`、`long double _Imaginary`。

- 复数函数中定义一个主函数对应 `double` 精度的复数运算，具有相同名称但后缀为 `f` 和 `l` 的函数，分别对应 `float`、`long double` 精度的复数运算。

> Microsoft 专用

- Microsoft C 运行库 CRT 提供复数数学库运算，也包括 ISO-C99 所需的所有函数。但是编译器不直接支持 `complex` 或 `_Complex` 关键字，因此 Microsoft 使用结构来表示复数。
 
---
### Microsoft Types
#### 复数类型定义

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

---
### Microsoft Macros

#### 复数构造器 

- Microsoft C 提供了相应的复数类型的构造器：

```c
#define _DCOMPLEX_(re, im)  _Cbuild(re, im)
#define _FCOMPLEX_(re, im)  _FCbuild(re, im)
#define _LCOMPLEX_(re, im)  _LCbuild(re, im)
```

<br>

#### 虚数单位

```c
#define _Complex_I   _FCbuild(0.0F, 1.0F)
#define I            _Complex_I
```

---
### 复数类的标准 C 定义

- 以下定义在 Microsoft C 编译器中不可用

```c
#pragma STDC CX_LIMITED_RANGE on-off-default     // 表示是否支持常用数学公式的编译提示

#define complex     _Complex
#define _Complex_I	(__extension__ 1.0iF)
// 可能定义
#define imaginary   _Imaginary
#define _Imaginary_I  (__extension__ 1.0iF)
// 虚数单位
#define I  _Complex_I

// 虚数构造器
#define CMPLX(re,ie)        // double complex
#define CMPLXF(re,ie)       // float complex
#define CMPLXL(re,ie)       // long double complex
```

---
### Functions：三角函数（Trigonometric functions）

#### ccos、csin、ctan （三角函数）

```c
_Dcomplex ccos(_Dcomplex _Z);           // 复数的余弦值
_Dcomplex csin(_Dcomplex _Z);           // 复数的正弦值   
_Dcomplex ctan(_Dcomplex _Z);           // 复数的正切值

_Fcomplex ccosf(_Fcomplex _Z);
_Fcomplex csinf(_Fcomplex _Z);
_Fcomplex ctanf(_Fcomplex _Z);

_Lcomplex ccosl(_Lcomplex _Z);
_Lcomplex csinl(_Lcomplex _Z);
_Lcomplex ctanl(_Lcomplex _Z);
```

<br>

#### cacos、casin、catan （反三角函数）

```c
_Dcomplex cacos(_Dcomplex _Z);           // 复数的反余弦值
_Dcomplex casin(_Dcomplex _Z);           // 复数的反正弦值   
_Dcomplex catan(_Dcomplex _Z);           // 复数的反正切值

_Fcomplex cacosf(_Fcomplex _Z);
_Fcomplex casinf(_Fcomplex _Z);
_Fcomplex catanf(_Fcomplex _Z);

_Lcomplex cacosl(_Lcomplex _Z);
_Lcomplex casinl(_Lcomplex _Z);
_Lcomplex catanl(_Lcomplex _Z);
```

---
### Functions：双曲函数（Hyperbolic functions）

#### ccosh、csinh、ctanh （双曲函数）

```c
_Dcomplex ccosh(_Dcomplex _Z);           // 复数的双曲余弦值
_Dcomplex csinh(_Dcomplex _Z);           // 复数的双曲正弦值   
_Dcomplex ctanh(_Dcomplex _Z);           // 复数的双曲正切值

_Fcomplex ccoshf(_Fcomplex _Z);
_Fcomplex csinhf(_Fcomplex _Z);
_Fcomplex ctanhf(_Fcomplex _Z);

_Lcomplex ccoshl(_Lcomplex _Z);
_Lcomplex csinhl(_Lcomplex _Z);
_Lcomplex ctanhl(_Lcomplex _Z);
```

<br>

#### cacosh、casinh、catanh （反双曲函数）

```c
_Dcomplex cacosh(_Dcomplex _Z);           // 复数的反双曲余弦值
_Dcomplex casinh(_Dcomplex _Z);           // 复数的反双曲正弦值   
_Dcomplex catanh(_Dcomplex _Z);           // 复数的反双曲正切值

_Fcomplex cacoshf(_Fcomplex _Z);
_Fcomplex casinhf(_Fcomplex _Z);
_Fcomplex catanhf(_Fcomplex _Z);

_Lcomplex cacoshl(_Lcomplex _Z);
_Lcomplex casinhl(_Lcomplex _Z);
_Lcomplex catanhl(_Lcomplex _Z);
```

---
### Functions：指数和对数函数（Exponential and logarithmic functions）

#### cexp （指数函数）

```c
_Dcomplex cexp(_Dcomplex _Z);           // 复数的以 e 为底的复数指数
_Fcomplex cexpf(_Fcomplex _Z);   
_Lcomplex cexpl(_Lcomplex _Z);   
```

<br>

#### clog、clog10 （对数函数）

```c
_Dcomplex clog(_Dcomplex _Z);           // 复数的以 e 为底的复数自然对数
_Dcomplex clog10(_Dcomplex _Z);         // 复数的以 10 为底的复数对数

_Fcomplex clogf(_Fcomplex _Z);   
_Fcomplex clog10f(_Fcomplex _Z);   

_Lcomplex clogl(_Lcomplex _Z);   
_Lcomplex clog10l(_Lcomplex _Z);   
```

---
### Functions：幂和绝对值函数（Power and absolute-value functions）

#### csqrt （平方根）

```c
_Dcomplex csqrt(_Dcomplex _Z);           // 复数的复数平方根
_Fcomplex csqrtf(_Fcomplex _Z);   
_Lcomplex csqrtl(_Lcomplex _Z); 
```

<br>

#### cpow （数的给定次幂）

```c
_Dcomplex cpow(_Dcomplex _X, _Dcomplex _Y);  // 复数的给定复数次幂 _X ^ _Y 
_Fcomplex cpow(_Fcomplex _X, _Fcomplex _Y);
_Lcomplex cpow(_Lcomplex _X, _Lcomplex _Y);
```

<br>

#### cabs （绝对值）

```c
double cabs(_Dcomplex _Z);           // 复数的复数绝对值（也叫范数或模数、量值）
float cabsf(_Fcomplex _Z);   
long double cabsl(_Lcomplex _Z); 
```

---
### Functions：复数操作函数（Manipulation functions）

#### carg （复数的相角）

```c
double carg(_Dcomplex _Z);           // 复数的自变量（相角）
float cargf(_Fcomplex _Z);   
long double cargl(_Lcomplex _Z); 
```

<br>

#### creal、cimag （实部和虚部）

```c
double creal(_Dcomplex _Z);           // 复数的实部
double cimag(_Dcomplex _Z);           // 复数的虚部

float crealf(_Fcomplex _Z);   
float cimagf(_Fcomplex _Z);   

long double creall(_Lcomplex _Z); 
long double cimagl(_Lcomplex _Z); 
```

<br>

#### conj （复数共轭）

```c
_Dcomplex conj(_Dcomplex _Z);         // 复数的复数共轭
_Fcomplex conjf(_Fcomplex _Z);   
_Lcomplex conjl(_Lcomplex _Z); 
```

<br>

#### cproj （Riemann 球体的复数投影）

```c
_Dcomplex cproj(_Dcomplex _Z);        // 计算 Riemann 球体上某个复数的投影
_Fcomplex cprojf(_Fcomplex _Z);   
_Lcomplex cprojl(_Lcomplex _Z); 
```

<br>

#### norm （复数的平方量值）

```c
double norm(_Dcomplex _Z);            // 复数的平方量值 _Z^2
float normf(_Fcomplex _Z);   
long double norml(_Lcomplex _Z); 
```

---
### Microsoft-Functions：运算函数

- 由于复数不是 Microsoft 编译器中的本机类型，复数类型上未定义标准的算术运算符，因此定义下列有关复数的有限处理。

#### 复数相加

```c
_Dcomplex _Cmulcc(_Dcomplex _X, _Dcomplex _Y);
_Fcomplex _FCmulcc(_Fcomplex _X, _Fcomplex _Y);
_Lcomplex _LCmulcc(_Lcomplex _X, _Lcomplex _Y);
```

#### 复数和浮点数相乘

```c
_Dcomplex _Cmulcr(_Dcomplex _X, double _Y);
_Fcomplex _FCmulcr(_Fcomplex _X, float _Y);
_Lcomplex _LCmulcr(_Lcomplex _X, long double _Y);
```

---
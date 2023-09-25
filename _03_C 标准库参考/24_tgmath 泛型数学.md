## C 泛型数学（Type-generic math）：tgmath.h

`tgmath.h` 包含了 `math.h` 和 `complex.h`，并定义了一些便利宏，这些宏会根据参数的类型决定要调用哪些数学函数。若参数的类型与所选函数的参数类型不兼容，则行为未定义。

---
### Macro-Functions：复数/实数泛型宏

- 对于所有拥有实数及复数对应的函数，存在泛型宏：
  - 实数函数：`XXXf` 对应 `float`，`XXX` 对应 `double`，`XXXl` 对应 `long double`；
  - 复数函数：`cXXXf` 对应 `float _complex`，`cXXX` 对应 `double _complex`，`cXXXl` 对应 `long double _complex`。

* 以 `sin` 为例进行定义，根据泛型参数的类型，自动选择相应的函数调用。

```c
#include <stdio.h>
#include <tgmath.h>

#define __CPLX(z,R,C) _Generic((z),\
	float:        R##f,		\
	long double:  R##l,     \
	_Fcomplex:    C##f,	    \
	_Dcomplex:    C,		\
    _Lcomplex:    C##l,     \
    default:      R		    \
)(z)

#define sin(x)  __CPLX(x, sin, csin)

int main(void)
{
	double rt = sin(1);
	printf("sin(1) = %.6f", rt);
}
```

> *复数/实数泛型宏如下所示*

```c
// 三角函数
#define cos(x)
#define sin(x)
#define tan(x)
#define acos(x)
#define asin(x)
#define atan(x)
// 双曲函数
#define cosh(x)
#define sinh(x)
#define tanh(x)
#define acosh(x)
#define asinh(x)
#define atanh(x)
// 基本函数
#define exp(x)
#define log(x)
#define pow(x,y)
#define sqrt(x)
#define fabs(x)
```

---
### Macro-Functions：实数限定函数

- 对于所有无复数对应的函数，除 `modf` 外都存在泛型宏 `XXX` ，它会调用实数函数变体的中的一种：
  - `float` 变体 `XXXf`；
  - `double` 变体 `XXX`；
  - `long double` 变体 `XXXl`。

> *实数限定泛型宏*

```c
// 四象限反正切函数
#define atan2(x,y)       // 点的象限
// 指数、对数函数
#define exp2(x)          // 指数相关
#define expm1(x) 
#define frexp(x,y)       // X * 2^exp
#define ldexp(x,y)       
#define log10(x)         // 对数相关
#define log2(x)         
#define log1p(x)        
#define logb(x)          // X = 2^exp
#define ilogb(x)         
#define scalbn(x,y)      // num * FLT_RADIX ^ N
#define scalbln(x,y)  
// 幂函数
#define cbrt(x)          // 立方根
#define hypot(x,y)       // 平方和的平方根
// 误差与伽马函数
#define erf(x)           // 误差函数
#define erfc(x)          // 互补误差函数
#define tgamma(x)        // 伽马函数
#define lgamma(x)        // 伽马函数的对数
// 近似整数函数
#define ceil(x)          // 向上取整
#define floor(x)         // 向下取整
#define nearbyint(x)     // 依据舍入方向取整
#define rint(x)          
#define lrint(x)        
#define llrint(x)       
#define round(x)         // 四舍五入取整 
#define lround(x)       
#define llround(x)      
#define trunc(x)         // 向零取整
// 余项函数
#define fmod(x,y)        // 求余
#define remainder(x,y)   
#define remquo(x,y,z)    // 求商求余
// 浮点操作函数
#define copysign(x,y)    // 符号复制
#define nextafter(x,y)   // 下一个有限浮点数
#define nexttoward(x,y) 
// 比较和正差函数
#define fmax(x,y)        // 最大
#define fmin(x,y)        // 最小
#define fdim(x,y)        // 正差
// 浮点乘加函数   
#define fma(x,y,z)       // 浮点乘加
```

---
### Macro-Functions：复数限定函数

- 对于所有没有实数对应的复数函数，存在泛型宏 `cXXX`，它会调用复数函数的变体：
  - `float complex` 变体 `cXXXf`；
  - `double complex` 变体 `cXXX`；
  - `long double complex` 变体 `cXXXl`。

> *复数限定泛型宏*

```c
#define creal(z)         // 复数的实部
#define cimag(z)         // 复数的虚部
#define carg(z)          // 复数的相角
#define conj(z)          // 复数的复数共轭
#define cproj(z)         // 黎曼球面上的投影
```

---
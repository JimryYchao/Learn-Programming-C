# complex.h 复数数学运算

---
- [complex.h 复数数学运算](#complexh-复数数学运算)
- [1. complex.h 复数数学运算库](#1-complexh-复数数学运算库)
- [2. 宏指令：创建复数类型](#2-宏指令创建复数类型)
- [3. 复数数学函数（以 double complex 为例）](#3-复数数学函数以-double-complex-为例)
	- [3.1 属性操作](#31-属性操作)
	- [3.2 指数函数](#32-指数函数)
	- [3.3 三角函数](#33-三角函数)
	- [3.4 幂函数](#34-幂函数)
	- [3.5 双曲函数](#35-双曲函数)
	- [3.6 特定于 Microsoft 函数](#36-特定于-microsoft-函数)
- [4. 自定义拓展复数数学运算](#4-自定义拓展复数数学运算)
	- [4.1 加法](#41-加法)
	- [4.2 减法](#42-减法)
	- [4.3](#43)

---
# 1. complex.h 复数数学运算库

> Microsoft 实现 ```complex.h``` 将这些类型定义为 C99 标准的等效项

```c
// ISO C99 标准形式 			 MSVC 类型等效项
float _Complex			   			_Fcomplex
double _Complex			   			_Dcomplex
long double _Complex	   			_Lcomplex
```

> 以 double _Complex 为例

```c
typedef struct{
	double _val[2];
} _C_double_complex;

typedef _C_double_complex _Dcomplex;

typedef _C_float_complex _Fcomplex;
typedef _C_ldouble_complex _Lcomplex;
```

---
# 2. 宏指令：创建复数类型

- MSVC 编译器专用

```c
#define _DCOMPLEX_(re, im)  _Cbuild(re, im)
#define _FCOMPLEX_(re, im)  _FCbuild(re, im)
#define _LCOMPLEX_(re, im)  _LCbuild(re, im)

#define _Complex_I 	_FCbuild(0.0F, 1.0F)
#define I          	_Complex_I
```

> 声明一个复数

```c
_Dcomplex dc = _DCOMPLEX_(re, im);
_Fcomplex fc = _FCOMPLEX_(re, im);
_Lcomplex lc = _LCOMPLEX_(re, im);
/* re 表示复数的实部，im 表示复数的虚部 */

/* 等效声明方式 */
_Dcomplex dc = _Cbuild(re, im);
_Fcomplex fc = _FCbuild(re, im);
_Lcomplex lc = _LCbuild(re, im);

/* 声明一个纯虚数 */
_Dcomplex dcI = _Complex_I;
```

---
# 3. 复数数学函数（以 double complex 为例）

- ```c-``` 前缀表示复数的数学库方法，无后缀表示 ```_Dcomplex``` 的相关操作；```-f``` 后缀表示 ```_Fcomplex``` 的相关操作；```-l``` 后缀表示 ```_Lcomplex``` 的相关操作
- 后缀区分适用于 C 函数，C++ 允许函数重载，```_Fcomplex（C++）``` 和 ```_Lcomplex（C++）``` 可以使用 ```_Dcomplex``` 的 C 方法形式的 C++ 重载

---
## 3.1 属性操作

```c
#include <complex.h>
typedef _Dcomplex DC;

double cabs(DC _Z);		/* 复数的模长 */
double carg(DC _Z);		/* 复数的辐角主值 */
double creal(DC _Z);	/* 复数的实部 */
double cimag(DC _Z);	/* 复数的虚部 */
DC conj(DC _Z);			/* 复数的共轭复数 */
DC cproj(DC _Z);		/* 复数在黎曼球上的投影 */
```

---
## 3.2 指数函数

```c
#include <complex.h>
typedef _Dcomplex DC;

DC cexp(DC _Z);			/* 复数的 e 底指数 */
DC clog(DC _Z);			/* 复数的自然对数 */
DC clog10(DC _Z);		/* 复数以 10 为底的对数 */
```

---
## 3.3 三角函数

```c
#include <complex.h>
typedef _Dcomplex DC;

DC cacos(DC _Z);		/* 复数反余弦 */
DC casin(DC _Z);		/* 复数反正弦 */
DC catan(DC _Z);		/* 复数反正切 */

DC ccos(DC _Z);			/* 复数余弦 */
DC csin(DC _Z);			/* 复数正弦 */
DC ctan(DC _Z);	 		/* 复数正切 */
```

---
## 3.4 幂函数

```c
#include <complex.h>
typedef _Dcomplex DC;

DC cpow(DC _X, DC _Y);	/* 复数的幂函数，X 为底，Y 为指数  */
DC csqrt(DC _Z);		/* 复数平方根 */
```

---
## 3.5 双曲函数

```c
#include <complex.h>
typedef _Dcomplex DC;

DC cacosh(DC _Z);		/* 复数反双曲余弦 */
DC casinh(DC _Z);		/* 复数反双曲正弦 */
DC catanh(DC _Z);		/* 复数反双曲正切 */

DC ccosh(DC _Z);		/* 复数双曲余弦 */
DC csinh(DC _Z);		/* 复数双曲正弦 */
DC ctanh(DC _Z);		/* 复数双曲正切 */
```

---
## 3.6 特定于 Microsoft 函数

```c
#include <complex.h>
typedef _Dcomplex DC;
typedef _Fcomplex FC;
typedef _Lcomplex LC;

double norm(DC _Z);		/* 复数平方的模 */
/* 复数相乘 */
DC _Cmulcc(DC _d1, DC _d2);		
FC _FCmulcc(FC _f1, FC _f2);	
LC _LCmulcc(LC _l1, LC _l2);               

/* 复数与浮点数相乘 */
DC _Cmulcr(DC _Z, double d);
FC _FCmulcr(FC _Z, float f);
LC _LCmulcr(LC _Z, long double ld);
```

---
# 4. 自定义拓展复数数学运算

---
## 4.1 加法

```c
/* 复数与复数加法 */
_Dcomplex __cdecl _Caddcc(_In_ _Dcomplex _X, _In_ _Dcomplex _Y) {
	return _DCOMPLEX_(_X._Val[0] + _Y._Val[0], _X._Val[1] + _Y._Val[1]);
}
_Fcomplex __cdecl _FCaddcc(_In_ _Fcomplex _X, _In_ _Fcomplex _Y) {
	return _FCOMPLEX_(_X._Val[0] + _Y._Val[0], _X._Val[1] + _Y._Val[1]);
}
_Lcomplex __cdecl _LCaddcc(_In_ _Lcomplex _X, _In_ _Lcomplex _Y) {
	return _LCOMPLEX_(_X._Val[0] + _Y._Val[0], _X._Val[1] + _Y._Val[1]);
}

/* 复数与浮点数加法 */
_Dcomplex __cdecl _Caddcr(_In_ _Dcomplex _X, _In_ double _Y) {
	return _DCOMPLEX_(_X._Val[0] + _Y, _X._Val[1]);
}
_Fcomplex __cdecl _FCaddcr(_In_ _Fcomplex _X, _In_ float _Y) {
	return _FCOMPLEX_(_X._Val[0] + _Y, _X._Val[1]);
}
_Lcomplex __cdecl _LCaddcr(_In_ _Lcomplex _X, _In_ long double _Y) {
	return _LCOMPLEX_(_X._Val[0] + _Y, _X._Val[1]);
}
```

---
## 4.2 减法

```c
/* 复数与复数减法 */
_Dcomplex __cdecl _Csubcc(_In_ _Dcomplex _X, _In_ _Dcomplex _Y) {
	return _DCOMPLEX_(_X._Val[0] - _Y._Val[0], _X._Val[1] - _Y._Val[1]);
}

/* 复数与浮点数减法 */
_Dcomplex __cdecl _Csubcr(_In_ _Dcomplex _X, _In_ double _Y) {

	return _DCOMPLEX_(_X._Val[0] - _Y, _X._Val[1]);
}
```

---
## 4.3 
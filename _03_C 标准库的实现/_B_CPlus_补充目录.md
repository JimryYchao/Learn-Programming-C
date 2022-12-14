# 补充目录清单

---
- [补充目录清单](#补充目录清单)
	- [1. 新增的 C99 和 C11 的 ANSI C 库](#1-新增的-c99-和-c11-的-ansi-c-库)
		- [1.1 断言 assert.h](#11-断言-asserth)
		- [1.2 C11 静态断言 _Static_assert](#12-c11-静态断言-_static_assert)
		- [1.3 复数 complex.h](#13-复数-complexh)
		- [1.4 错误报告 errno.h](#14-错误报告-errnoh)
		- [1.5 浮点环境 fenv.h (C99)](#15-浮点环境-fenvh-c99)
		- [1.6 浮点特性 float.h](#16-浮点特性-floath)
		- [1.7 整数类型的格式转换 inttype.h](#17-整数类型的格式转换-inttypeh)
		- [1.8 可选拼写 iso646.h](#18-可选拼写-iso646h)
		- [1.9 本地化 locale.h](#19-本地化-localeh)
		- [1.10 数学库 math.h](#110-数学库-mathh)
		- [1.11 非本地跳转 setjmp.h](#111-非本地跳转-setjmph)
		- [1.12 信号处理 signal.h](#112-信号处理-signalh)
		- [1.13 对齐 stdalign.h (C11)](#113-对齐-stdalignh-c11)
		- [1.14 可变参数 stdarg.h](#114-可变参数-stdargh)
		- [1.15 原子支持 stdatomic](#115-原子支持-stdatomic)
		- [1.16 布尔支持 stdbool.h](#116-布尔支持-stdboolh)
		- [1.17 通用定义 stddef.h](#117-通用定义-stddefh)
		- [1.18 整数类型 stdint.h](#118-整数类型-stdinth)
		- [1.19 通用工具 stdlib.h](#119-通用工具-stdlibh)
		- [1.20 _Noreturn stdnoreturn.h](#120-_noreturn-stdnoreturnh)
		- [1.21 处理字符串 string.h](#121-处理字符串-stringh)
		- [1.22 通用类型数学 tgmath.h (C99)](#122-通用类型数学-tgmathh-c99)
		- [1.23 线程 threads.h](#123-线程-threadsh)
		- [1.24 日期和时间 time.h](#124-日期和时间-timeh)
		- [1.25 统一码工具 uchar.h](#125-统一码工具-ucharh)
		- [1.26 扩展的多字节字符和宽字符工具 wchar.h (C99)](#126-扩展的多字节字符和宽字符工具-wcharh-c99)
		- [1.27 宽字符分类和映射工具 wctype.h (C99)](#127-宽字符分类和映射工具-wctypeh-c99)
	- [2. 扩展字符支持](#2-扩展字符支持)
		- [2.1 三字符序列](#21-三字符序列)
		- [2.2 双字符](#22-双字符)
		- [2.3 多字节字符](#23-多字节字符)
	- [3. C 与 C++ 的区别](#3-c-与-c-的区别)
		- [3.1 函数原型](#31-函数原型)
		- [3.2 char 常量](#32-char-常量)
		- [3.3 const 限定符](#33-const-限定符)
		- [3.4 结构与联合](#34-结构与联合)
		- [3.5 枚举](#35-枚举)
		- [3.6 指向 void 的指针](#36-指向-void-的指针)
		- [3.7 布尔类型](#37-布尔类型)
		- [3.8 可选拼写](#38-可选拼写)
		- [3.9 宽字符支持](#39-宽字符支持)
		- [3.10 复数类型](#310-复数类型)
		- [3.11 内联函数](#311-内联函数)
		- [3.12 C++11 中没有的 C99/C11 特性](#312-c11-中没有的-c99c11-特性)

---
## 1. 新增的 C99 和 C11 的 ANSI C 库

---
### 1.1 断言 assert.h

- assert.h 头文件中把 assert() 定义为一个宏。在包含 assert.h 头文件之前定义宏标识符 NDEBUG，可以禁用 assert() 宏。

- 通常用一个关系表达式或逻辑表达式作为 assert() 的参数，如果运行正常，那么程序在执行到该点时，作为参数的表达式应该为真

```c
	void assert(int exprs);
	// 如果 expts 为非 0(真), 宏无效,
	// 如果为 0(假), 则会显示该表达式所在的行号与文件名, 然后调用 abort()
```

---
### 1.2 C11 静态断言 _Static_assert

- 关键字声明: _Static_assert(常量表达式,字符串字面量), 提供一个编译时检查

- 如果对常量表达式求值为0，编译器会给出一条包含字符串字面量的错误消息；否则，没有任何效果。

---
### 1.3 复数 complex.h

- C99 提供支持复数计算, C11 进一步支持了这个功能

- _Imaginary 类型为可选类型, C99 的实现必须提供 _Complex 类型, C11 提供可选

> complex.h 提供的宏

```c
	complex 	展开为类型 _Complex
	_Complex_I  展开为 const float _Complex 类型的表达式, 其值的平方为 -1
	//如果支持虚数类型
	imaginary 		展开为 _Imaginary
	_Imaginary_I	展开为 const float _Imaginary 类型, 平方为 -1

	I 	展开为 _Complex_I 或 _Imaginary_I
```

> C 与 C++ 实现复数方面

- C 通过 complex.h 头文件支持，而 C++ 通过 complex 头文件支持。
  
- 而且，C++ 使用类来定义复数类型。

> 使用数学公式

- 可以使用 STDC CX_LIMITED_RANGE 编译指令来表明是使用普通的数学公式（设置为 on 时）, 还是要特别注意极值（设置为 off 时）

```c
	#include <complex.h>
	#pragma STDC CX_LIMITED_RANGE on
```

> 复数数学公式 

- 库函数分为 3 种：double、float、long double, float 和 long double 版本只需要在函数名后面分别加上 f 和 l。

```c
	// PS 角度的单位是弧度

	// 1. 反三角函数 (返回角度: 弧度)
	double complex cacos(double complex z);		// 返回 z 的复数反余弦
	double complex casin(double complex z);		// 返回 z 的复数反正弦
	double complex catan(double complex z);		// 返回 z 的复数反正切
	
	// 2. 三角函数
	double complex ccos(double complex z);		// 返回 z 的复数余弦
	double complex csin(double complex z);		// 返回 z 的复数正弦
	double complex ctan(double complex z);		// 返回 z 的复数正切

	// 3. 反双曲线
	double complex cacosh(double complex z);	// 返回 z 的复数反双曲余弦
	double complex casinh(double complex z);	// 返回 z 的复数反双曲正弦
	double complex catanh(double complex z);	// 返回 z 的复数反双曲正切

	// 4. 双曲线
	double complex ccosh(double complex z);		// 返回 z 的复数双曲余弦
	double complex csinh(double complex z);		// 返回 z 的复数双曲正弦
	double complex ctanh(double complex z);		// 返回 z 的复数双曲正切
	
	// 5. 指数与对数
	double complex cexp(double complex z);		// 返回 e 的 z 次幂复数值
	double complex clog(double complex z);		// 返回 z 的自然对数的复数值
	double cabs(double complex z);				// 返回 z 的绝对值或大小
	
	// 6. z 的 y 次幂
	double complex cpows(double complex z, double complex y);	

	// 7. 复数平方根
	double complex csqrt(double complex z);	

	// 8. 以弧度为单位返回 z 的相位角 (或幅角)
	double carg(double complex z);	

	// 9. 以实数返回 z 的虚部
	double cimag(double complex z);

	// 10. 返回 z 的共轭复数
	double complex conj(double complex z);
	
	// 11. 返回 z 在黎曼球面上的投影
	double complex cponj(double complex z);	
	
	// 12. 返回实部为 x, 虚部为 y 的复数
	double complex CMPLX(double x, double y);

	// 13. 以实数形式返回 z 的实部
	double creal(double complex z);	
```

---
### 1.4 错误报告 errno.h

- errno.h 头文件支持较老式的错误报告机制。该机制提供一个标识符（或有时称为宏） ERRNO 可访问的外部静态内存位置

> 标准提供了 3 个宏值表示特殊的错误

```c
	EDOM 	函数调用中的域错误 (参数越界)
	ERANGE	函数返回值的范围错误 (返回值越界)
	EILSEQ  宽字符转换错误
```

---
### 1.5 浮点环境 fenv.h (C99)

- C99 标准通过 fenv.h 头文件提供访问和控制浮点环境。

- 浮点环境（ floating-point environment ） 由一组状态标志（status flag）和控制模式（control mode）组成。

- 在浮点计算中发生异常情况时（如，被零除），可以 “抛出一个异常”。这意味着该异常情况设置了一个浮点环境标志

> 开启浮点环境

```c
	#pragma STDC FENV_ACCESS on
```

> 类型

```c
	fenv_t 		整个浮点环境
	fexcept_t	浮点状态标志集合
```

> 标准异常宏

```c
	FE_DIVBYZERO	抛出被零除异常
	FE_INEXACT		抛出不精确值异常
	FE_INVALID		抛出无效值异常
	FE_OVERFLOW		抛出上溢异常
	FE_UNDERFLOW	抛出下溢异常
	FE_ALL_EXCEPT	实现支持的所有浮点异常的按位或
	FE_DOWNWARD		向下舍入
	FE_TONEAREST	向最近的舍入
	FE_TOWARDZERO	趋零舍入
	FE_UPWARD		向上舍入
	FE_DFL_ENV		表示默认环境, 类型是 const fenv_t *
```

> 标准函数原型

```c
	// 清理 excepts 表示的异常
	void feclearexcept(int excepts);	
	
	// 把 excepts 指明的浮点状态标志储存在 flagp 指向的对象中
	void fegetexceptflag(fexcept_t * flagp, int excepts);

	// 抛出 excepts 指定的异常
	void feraiseexcept(int excepts);

	/* 把 excepts 指明的浮点状态标志设置为 flagp 的值; 在此之前, 
	  fegetexceptflag() 调用应该设置 flagp 的值           */
	void fesetexceptflag(const fexcept_t * flagp, int excepts);

	// 测试 excepts 指定的状态标志; 该函数返回指定状态标志的按位或
	int fetestexcept(int excepts);

	// 返回当前的舍入方向
	int fegetround(void);

	// 把舍入方向设置为 round 的值; 仅当设置成功时返回 0
	int fesetround(int round);

	// 把当前环境储存在 envp 指向的位置中
	void fegetenv(fenv_t * envp);

	/* 把当前浮点环境储存值 envp 指向的位置, 清除浮点状态标志, 发生
	  异常也继续执行, 成功时返回 0							*/
	int feholdexcept(fenv_t envp);

	/* 建立 envp 表示的浮点环境; envp 指向 fegetenv, feholdexcept 
	  设置的数据对象									   */
	void fesetenv(const fenv_t * envp);

	/* 函数在自动存储区中储存当前抛出的异常, 建立 envp 执行的对象表示
	  的浮点环境, 然后抛出已储存的浮点异常; 
	void feupdateenv(const fenv_t * envp);
```

---
### 1.6 浮点特性 float.h

- float.h 头文件中定义了一些表示各种限制和形参的宏

- 浮点表示模型:  【 $x=sb^e\sum\limits_{k=1}^{p}f_k^{b^-k}$ 】

- 若 $f_1$ 是非 0 且 $x$ 是非 0 , 该数字被称为标准化浮点数

---
### 1.7 整数类型的格式转换 inttype.h

- 该头文件定义了一些宏可用作转换说明来扩展整数类型

- 该头文件还声明了这个类型：imaxdiv_t。这是一个结构类型，表示 idivmax() 函数的返回值

```c
	// 返回 num 的绝对值
	intmax_t imaxabs(intmax_t num);	

	// 单独计算 numer/denom 的商和余数, 并把两个计算结果储存在返回的结构中
	imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom);

	// 相当于 strtol 函数, 将字符串转换成 intmax_t 类型
	uintmax_t strtoimax(const char * restrict nptr, 
						char ** restrict endptr, int base);

	// 相当于 strtoul 函数, 将字符串转换成 intmax_t 类型
	uintmax_t strtoumax(const char * restrict nptr, 
						char ** restrict endptr, int base);

	// strtoimax 函数的 wchar_t 类型的版本
	intmax_t wcstoimax(const wchar_t * restrict nptr, 
				wchar_t ** restrict endptr, int base);

	// strtoumax 函数的 wchar_t 类型的版本
	intmax_t wcstoumax(const wchar_t * restrict nptr, 
				wchar_t ** restrict endptr, int base);
```

---
### 1.8 可选拼写 iso646.h

- 该头文件提供了 11 个宏，扩展了指定的运算符

```c
	and	 		>>  	&&
	and_eq		>>  	&=
	bitand		>>  	&
	bitor		>>  	|
	compl		>>  	~
	not			>>  	!
	not			>>  	!=
	or			>>  	||
	or_eq		>>  	|=
	xor			>>  	^
	xor_eq		>>  	^=
```

---
### 1.9 本地化 locale.h

- 本地化是一组设置，用于控制一些特定的设置项，如表示小数点的符号

- 本地值储存在 struct lconv 类型的结构中，定义在 locale.h 头文件中

- 可以用一个字符串来指定本地化，该字符串指定了一组结构成员的特殊值。默认的本地化由字符串 "C" 指定。

---
### 1.10 数学库 math.h

- C99 为 math.h 头文件定义了两种类型：float_t 和 double_t。这两种类型分别与 float 和 double 类型至少等宽，是计算 float 和 double 时效率最高的类型

- 数学函数通常使用 double 类型的值。C99 新增了这些函数的 float 和 long double 版本，其函数名为分别在原函数名后添加 f 后缀和 l 后缀

---
### 1.11 非本地跳转 setjmp.h

- setjmp.h 头文件可以让你不遵循通常的函数调用、函数返回顺序。
  
- setjmp()函数把当前执行环境的信息（例如，指向当前指令的指针）储存在 jmp_buf 类型（定义在 setjmp.h 头文件中的数组类型）的变量中，然后 longjmp() 函数把执行转至这个环境中。
  
- 这些函数主要是用来处理错误条件，并不是通常程序流控制的一部分。

```c
	// 把调用环境储存在数组 env 中, 如果是直接调用, 返回 0;
	//  如果是通过 longjmp 调用, 返回非 0
	int setjmp(jmp_buf env);

	// 恢复最近的 setjmp() 调用 (设置 env 数组) 储存的环境, 完成后, 程序
	// 继续像调用 set_jmp 那样执行该函数, 返回 val (会转换成 1, 不允许返回 0) 
	void longjmp(jmp_buf env, int val);
```

---
### 1.12 信号处理 signal.h

- 信号（signal）是在程序执行期间可以报告的一种情况，可以用正整数表示。
  
- raise() 函数发送（或抛出）一个信号，signal() 函数设置特定信号的响应。

- 标准定义了一个整数类型：sig_atomic_t，专门用于在处理信号时指定原子对象(更新原子类型是不可分割的过程)

> 宏: 可作用于 raise 和 signal 的参数

```c
	SIGABRT		异常终止, 如 abort 调用发出的信号
	SIGFPE		错误的算数运算
	SIGILL		检测到无效功能(非法指令等)
	SIGINT		接收到交互信号(DOS中断等)
	SIGSEGV		非法访问内存
	SIGTERM		向程序发送终止请求
```

- signal() 函数的第 2 个参数接受一个指向 void 函数的指针，该函数有一个 int 类型的参数, 返回相同类型的指针 (这样为响应一个信号而被调用的函数称为信号处理器, signal handler)

- 标准定义了 3 个满足下面原型的宏：void (*funct)(int);

```c
	SIG_DFL		当该宏与一个信号值一起作为 signal 的参数时, 表示默认处理信号
	SIG_ERR		如果 signal 不能返回它的第 2 个参数, 就用该宏作为它的返回值
	SIG_IGN		当该宏与一个信号值一起作为 signal 的参数时, 表示忽略信号
```

- 如果产生了信号 sig，而且 func 指向一个函数（signal() 原型）
  
- 那么大多数情况下先调用 signal(sig, SIG_DFL) 把信号重置为默认设置
  
- 然后调用 (*func)(sig)。可以执行返回语句或调用 abort()、exit() 或 longjmp() 来结束 func 指向的信号处理函数。

```c
	>>> 信号函数
	// 如果产生信号 sig, 则执行 func 指向的函数; 
	// 如果能执行则返回 func, 否则返回 SIG_ERR
	void ( *signal(int sig, void ( *func)(int)))(int);

	// 向执行程序发送信号 sig; 成功返回 0
	int raise(int sig);
```

---
### 1.13 对齐 stdalign.h (C11)

- stdalign.h 头文件定义了 4 个宏，用于确定和指定数据对象的对齐属性

```c
	alignas 		展开为关键字 _Alignas
	alignof			展开为关键字 _Alignof
	__alignas_is_defined	展开为 1 , 适用于 #if
	__alignof_is_defined	展开为 1 , 适用于 #if
```

---
### 1.14 可变参数 stdarg.h

- stdarg.h 头文件提供一种方法定义参数数量可变的函数。这种函数的原型有一个形参列表，列表中至少有一个形参后面跟有省略号：

```c
	void f1(int n, ...); 				/* 有效 */
	int f2(int n, float x, int k, ...);	/* 有效 */
	double f3(...); 					/* 无效 */
```

- 头文件中声明了 va_list 类型表示储存形参列表中省略号部分的形参数据对象

- 列出了几个带可变参数列表的函数中用到的宏。在使用这些宏之前要声明一个 va_list 类型的对象

```c
	// 在 va_arg() 和 va_end() 使用 ap 之前初始化 ap, 
	// parmN 表示是形参列表中最后一个形参名的标识符
	void va_start(va_list ap, parmN);

	// 展开一个表达式, 其值和类型斗鱼 ap 表示的形参列表的下一项相同
	// type 为类型, 每次调用该宏都前进到 ap 的下一项
	type va_arg(va_list ap, type);

	// 关闭以上的过程, 可能导致 ap 在再次调用 va_start 之前不可用
	void va_end(va_list ap);
	
	// 把 dest 初始化为 src 当前状态的备份
	void va_copy(va_list dest, va_list src);
```

---
### 1.15 原子支持 stdatomic

- stdatomic.h 和 threads.h 头文件支持并发编程, stdatomic.h 头文件提供了创建原子操作的宏 (强调不可分割的特性)

- 一个操作（如，把一个结构赋给另一个结构）从编程层面上看是原子操作，但是从机器语言层面上看是由多个步骤组成, 当程序被分为多个线程, 其中的线程可能读或者修改另一线程正在使用的数据

- 给一个结构的多个成员赋值, 不同的线程给不同的成员赋值, 使用原子操作, 可以把这些创建当成不可分隔的操作, 这样就能保证线程之间互不干扰

---
### 1.16 布尔支持 stdbool.h

```c
	bool		展开为 _Bool
	false		展开为整型 0
	true		展开为整型 1
	_bool_true_false_are_defined	展开为整型常量 1
```

---
### 1.17 通用定义 stddef.h

- 定义了一些类型和宏

```c
	// 类型
	prtdiff_t	有符号整数类型, 表示两个指针之差
	size_t		无符号整数类型, 表示 sizeof 运算符的结果
	wchar_t		整数类型, 表示支持的本地化所指定的最大扩展字符集

	// 宏
	NULL		定义为空指针
	offsetof(type, member-designator)
	/* 展开为 size_t 类型的值, 表示 type 类型结构的指定成员在该结构中的偏移量,
	  以字节为单位. 成员不可以是位字段*/
```

> 偏移量

```c
#include <stddef.h>
struct car
{
	char brand[30];
	char model[30];
	double hp;
	double price;
};
int main(void)
{
	size_t into = offsetof(struct car, hp); /* hp成员的偏移量
}
```

---
### 1.18 整数类型 stdint.h

- stdint.h 头文件中使用 typedef 工具创建整数类型名，指定整数的属性。
  
- stdint.h 头文件包含在 inttypes.h 中，后者提供输入/输出函数调用的宏。

---
### 1.19 通用工具 stdlib.h

- ANSI C 标准库在 stdlib.h 头文件中定义了一些实用函数

---
### 1.20 _Noreturn stdnoreturn.h

- stdnoreturn.h 定义了 noreturn 宏，该宏展开为 _Noreturn。

---
### 1.21 处理字符串 string.h

- string.h 库定义了size_t 类型和空指针要使用的 NULL 宏。

---
### 1.22 通用类型数学 tgmath.h (C99)

- math.h 和 complex.h 库中有许多类型不同但功能相似的函数, tgmath.h 头文件定义了展开为通用调用的宏，即根据指定的参数类型调用合适的函数

> 通用数学函数

```c
	acos   asin   atanb  atan2
	acosh  asinh  atanh
	cos    sin    tan
	cosh   sinh   tanh
	exp    log    pow   sqrt   fabs
	cbrt   ceil   copysign  erf  erfc  exp2
	expm1  fdim   floor   
	fma    fmax   fmin   fmod   frexp
	hypot  ilogb  ldexp  lgamma  llrint  llround
	log10  log1p  log2   logb
	lrint  lround  nearbyint  nextafter
	nexttoward  remainder  remquo  rint  round
	scalbn  scalbln  tgamma  trunc
	carg   cimag   conj   cproj   creal   
```

- 在 C11 以前，编写实现必须依赖扩展标准才能实现通用宏。但是使用 C11 新增的 _Generic 表达式可以直接实现

---
### 1.23 线程 threads.h

- threads.h 和 stdatomic.h 头文件支持并发编程, 支持程序执行多线程，原则上可以把多个线程分配给多个处理器处理。

---
### 1.24 日期和时间 time.h

- time.h 定义了 3 个宏。
  
- 第 1 个宏是表示空指针的 NULL，许多其他头文件中也定义了这个宏。
  
- 第 2 个宏是 CLOCKS_PER_SEC，该宏除以 clock() 的返回值得以秒为单位的时间值。
  
- 第 3 个宏（C11）是 TIME_UTC，这是一个正整型常量，用于指定协调世界时（即 UTC）。该宏是 timespec_get() 函数的一个可选参数。

- UTC 是目前主要世界时间标准，作为互联网和万维网的普通标准，广泛应用于航空、天气预报、同步计算机时钟等各领域。

> 类型

```c
	size_t		sizeof 返回的整数类型
	clock_t		适用于表示时间的算数类型
	time_t		适用于表示时间的算数类型
	struct timespec		以秒和纳秒为单位储存指定时间间隔的结构 (C11)
	struct tm			储存日历时间的各部分
```

> timespec 中的成员

```c
	struct timespec{
		time_t tv_sec; // 秒; > 0
		long tv_nsec;  // 纳秒; 0 ~ 999999999
	};
```

> tm 中的成员

- 日历类型的各组成部分被称为分解时间（ broken-down time）

```c
	struct tm{
		int tm_sec;			// 秒 0 ~ 61
		int tm_min;			// 分 0 ~ 59
		int tm_hour;		// 时 0 ~ 23
		int tm_mday;		// 月 0 ~ 31
		int tm_mon;			// 一月后的月数 0 ~ 11
		int tm_year;		// 1900 后的年数
		int tm_wday;		// 星期日开始的天数 (0 ~ 6)
		int tm_yday;		// 从 1.1 开始的天数
		int tm_isdst;		// 夏令时标志(>0 有效, =0 无效, <0 信息不可以)
	};
```

---
### 1.25 统一码工具 uchar.h

- C99 的 wchar.h 头文件提供两种途径支持大型字符集。
  
- C11 专门针对统一码（Unicode）新增了适用于 UTF-16 和 UTF-32 编码的类型

> 类型

```c
	char16_t	16位字符的无符号整数类型
	char32_t	32位字符的无符号整数类型
	mbstate_t	非数组类型, 可储存多字节字符序列和宽字符相互转换的转换状态信息
```

---
### 1.26 扩展的多字节字符和宽字符工具 wchar.h (C99)

- wchar.h 头文件提供了一些工具用于处理扩展字符的两种表示法

> 类型

```c
	wchar_t		整数, 表示本地化支持的最大扩展字符集
	wint_t		整数, 可储存扩展字符集的任何值和至少一个不是扩展字符集成员的值
	struct tm	储存日历时间的组成部分
```

> 宏定义

```c
	WCHAR_MAX	最大值
	WCHAR_MIN	最小值
	WEOF		wint_t 类型的常量表达式, 不与扩展字符集的任何成员配对, 相当于
				EOF 的宽字符表示, 用于指定宽字符输入的文件末尾
```

---
### 1.27 宽字符分类和映射工具 wctype.h (C99)

- wctype.h 库提供了一些与 ctype.h 中的字符函数类似的宽字符函数，以及其他函数

---
## 2. 扩展字符支持

### 2.1 三字符序列

- C 可以替换双引号或外部的这些三字符序列, 要在编译器中设置相关选项才能激活这个特性

```c
	??=     #
	??(		[
	??)     ]
	??!     |
	??'		^
	??<		{
	??>     }
	??/		\
	??-		~
```

---
### 2.2 双字符

- 双字符在双引号内不会被替换

```c
	<:  	[
	:>		]
	<%		{
	%>		}
	%:		#
	%:%:	##
```

---
### 2.3 多字节字符

- C 标准把多字节字符描述为一个或多个字节的序列，表示源环境或执行环境中的扩展字符集成员

- 源环境指的是编写源代码的环境，执行环境指的是用户运行已编译程序的环境

---
## 3. C 与 C++ 的区别

- C++ 是 C 的超集，这意味着一个有效的 C 程序也是一个有效的 C++ 程序。
  
- C 和 C++ 的主要区别是，C++ 支持许多附加特性，C++ 中也有许多规则与 C 稍有不同。

---
### 3.1 函数原型

- C++ 中, 函数原型必不可少, 在 C 是可选的

- C++ 中可以声明重载函数, 但 C 要求不能重名

---
### 3.2 char 常量

- C 把 char 常量视为 int 类型，而 C++ 将其视为 char 类型, 在 C 中，常量 'A' 被储存在 int 大小的内存块, 在 C++ 中，'A' 和 ch 都占用 1 字节

```c
	// C 允许  >> 对于 int 是 4 字节的系统
	int x = 'ABCD';
	int x = 'ABCD';
	char c = 'ABCD';
	printf("%d %d %c %c\n", x, 'ABCD', c, 'ABCD');	
	// 得到的输出如下：
	1094861636 1094861636 D D

	// C++ 不允许这样的做
	char c = 'A';
```

---
### 3.3 const 限定符

- 在 C 中，全局的 const 具有外部链接，但是在 C++ 中，具有内部链接

```c++
	// C++
	const double PI = 3.14159;
	//相当于 C 的
	static const double PI = 3.14159;
```

- C++ 可以使用关键字 extern 使一个 const 值具有外部链接

- 在 C++ 中，可以使用 const 值来初始化其他 const 变量，但是在 C 中不能这样做

```c
	const double RATE = 0.06; 			// C++和C都可以
	const double STEP = 24.5; 			// C++和C都可以
	const double LEVEL = RATE * STEP; 	// C++可以，C不可以	
```

---
### 3.4 结构与联合

- C++ 中可以直接使用标识声明变量

```c++
	struct duo{
		int a;
		int b;
	};
	struct duo x;   // C 与 C++
	duo x;          // C++
```

> 结果是结构名会与变量名冲突

- 程序可作为 C 程序编译，但是作为 C++ 程序编译时会失败。因为 C++ 把 printf() 语句中的 duo 解释成结构类型而不是外部变量

```c
#include <stdio.h>
float duo = 100.3;
int main(void)
{
	struct duo { int a; int b;};
	struct duo y = { 2, 4};
	printf ("%f\n", duo); 	/* 在 C 中没问题，但是在 C++ 不行 */
	return 0;
}
```

> 结构嵌套

- 在 C 和 C++ 中，都可以在一个结构的内部声明另一个结构

```c++
struct box
{
	struct point {int x; int y; } upperleft;
	struct point lowerright;
};

// 调用时
	struct box ad; 		/* C和 C++都可以 */
	struct point dot; 	/* C可以，C++不行 */
	box::point dot; 	/* C不行，C++可以 */
```

---
### 3.5 枚举

- C++ 使用枚举比 C 严格
  * 只能把 enum 常量赋给 enum 变量，然后把变量与其他值作比较。
  * 不经过显式强制类型转换，不能把 int 类型值赋给 enum 变量
  * 而且也不能递增一个 enum 变量 

```c++
	enum sample {sage, thyme, salt, pepper};
	enum sample season;
	season = sage; 		/* C 和 C++ 都可以 */
	season = 2; 		/* 在 C 中会发出警告，在 C++ 中是一个错误 */

	season = (enum sample) 3; 	/* C 和 C++ 都可以*/
	season++; 		/* C 可以，在 C++ 中是一个错误 */
	
	//另外，在 C++ 中，不使用关键字 enum 也可以声明枚举变量：
	enum sample {sage, thyme, salt, pepper};
	sample season; 		/* C++ 可以，在 C 中不可以 */
```

---
### 3.6 指向 void 的指针

- C++ 可以把任意类型的指针赋给指向 void 的指针，这点与 C 相同

- 但是不同的是，只有使用显式强制类型转换才能把指向 void 的指针赋给其他类型的指针

- C++ 可以把派生类对象的地址赋给基类指针(类)

---
### 3.7 布尔类型

- 在 C++ 中，布尔类型是 bool，而且 ture 和 false 都是关键字。
  
- 在 C 中，布尔类型是 _Bool，但是要包含 stdbool.h 头文件才可以使用 bool、true 和 false。

---
### 3.8 可选拼写

- 在 C++ 中，可以用 or 来代替 ||，还有一些其他的可选拼写，它们都是关键字。在 C99 和 C11 中，这些可选拼写都被定义为宏，要包含 iso646.h 才能使用它们。

---
### 3.9 宽字符支持

> C++

- 在 C++ 中，wchar_t 是内置类型，而且 wchar_t 是关键字

- char16_t 和 char32_t 都是 C++11 的关键字

- C++ 通过 iostream 头文件提供宽字符 I/O 支持（wchar_t、char16_t 和 char32_t）

> C

- 在 C99 和 C11 中，wchar_t 类型被定义在多个头文件中（stddef.h、stdlib.h、wchar.h、wctype.h）

- 在 C11 中 char16_t 和 char32_t 都定义在 uchar.h 头文件中

- C99 通过 wchar.h 头文件提供一种完全不同于 C++ 的 I/O 支持包。

---
### 3.10 复数类型

- C++ 在 complex 头文件中提供一个复数类来支持复数类型。C 有内置的复数类型，并通过 complex.h 头文件来支持(两者很大程度上不兼容)

---
### 3.11 内联函数

- C99 支持了 C++ 的内联函数特性。但是，C99 的实现更加灵活。

- 在 C++ 中，内联函数默认是内部链接。在 C++ 中，如果一个内联函数多次出现在多个文件中，该函数的定义必须相同，而且要使用相同的语言记号。

- C 允许混合使用内联定义和外部定义，而 C++ 不允许。

---
### 3.12 C++11 中没有的 C99/C11 特性

- 指定初始化器；
- 复合初始化器（Compound initializer）；
- 受限指针（Restricted pointer）（即，restric指针）；
- 变长数组；
- 伸缩型数组成员；
- 带可变数量参数的宏。

---
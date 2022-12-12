

---
## 9. C 库 

* 访问 C 库取决于实现, 根据系统的不同, 可以在多个不同的位置找到库函数
  - 自动访问: 使用函数前必须先声明函数的类型, 通过包含合适的头文件即可
  - 文件包含: 函数被定义成宏, 可以通过 include 指令包含该定义的文件
  - 库包含: 一些编译的某些阶段, 可能需要指定库选项, 必须通过编译时选项显式指定这些库

---
### 9.1 数学库 (math.h)

```c
double acos(double x);			  	// 余弦值为 x 的角度(0 ~ PI 弧度)  
double asin(double x);			  	// 正弦值为 x 的角度(-PI/2 ~ PI/2, 弧度)
double atan(double x);			  	// 正切值为 x 的角度(-PI/2 ~ PI/2, 弧度)
double atan2(double x, double y); 	// 正弦值为 y/x 的角度 (-PI ~ PI, 弧度)
double cos(double x);			  	// x 的余弦值
double sin(double x);			  	// x 的正弦值
double tan(double x);			  	// x 的正切值
double exp(double x);			  	// x 的指数函数的值(e^x)
double log(double x);			  	// x 的自然对数值
double log10(double x);			  	// x 的以 10 为底的对数值
double pow(double x, double y);	  	// x 的 y 次幂
double sqrt(double x);			  	// x 的平方值
double cbrt(double x);			  	// x 的立方值
double ceil(double x);			  	// 不小于 x 的最小整数值
double fabs(double x);			  	// x 的绝对值
double floor(double x);			  	// 不大于 x 的最大整数值
```

> 把直角坐标转换为极坐标

```c
#include <stdio.h>
#include <math.h>
#define RAD_TO_DEG (180 / (4 * atan(1))) // 弧度转角度
typedef struct polar_v					 // 极坐标结构
{
	double magnitude;
	double angle;
} Polar_V;
typedef struct rect_v // 直角系结构
{
	double x;
	double y;
} Rect_V;

Polar_V rect_to_polar(Rect_V); // 转换函数原型

int main(void)
{
	Rect_V input;
	Polar_V result;
	puts("Enter x and y coordinates; enter q to quit:");
	while (scanf("%lf %lf", &input.x, &input.y) == 2)
	{
		result = rect_to_polar(input);
		printf("magnitude = %0.2f, angle = %0.2f\n",
			   result.magnitude, result.angle);
	}
	puts("Bye.");
	return 0;
}

// 转换函数 rect -> polar
Polar_V rect_to_polar(Rect_V rv)
{
	Polar_V pv;
	pv.magnitude = sqrt(rv.x * rv.x + rv.y * rv.y);
	if (pv.magnitude == 0)
		pv.angle = 0.0;
	else
		pv.angle = RAD_TO_DEG * atan2(rv.y, rv.x);
	return pv;
}
```

- 若编译器出现【 Undefined: _sqrt 】或【'sqrt': unresolved external】，表明编译器链接器没有找到数学库

```powershell
  $ gcc rect_pol.c -lm
```

> 数学库类型变体

- 基本的浮点型数学函数接受 double 类型的参数，并返回 double 类型的值

- 传入其他类型可能出现精度丢失的问题，C 标准专门为 float 类型和 long double 类型提供了标准函数，即在原函数名前加上 f 或 l 前缀

- 可以利用 C11 泛型选择表达式定义一个泛型宏

```c
// 泛型平方根
#define RAD_TO_DEG (180/(4 * atanl(1)))

#define SQRT(X) _Generic((X), long double: sqrtl, default: sqrt, float: sqrtf)(X)
// 泛型正弦函数
#define SIN(X) _Generic((X),long double: sinl((X)/RAD_TO_DEG),\
							default: sin((X)/RAD_TO_DEG),\
							float: sinf((X)/RAD_TO_DEG))

```

- _Generic 表达式的值是一个特定的函数调用， 如 sinf((X)/RAD_TO_DEG)，用传入 SIN() 的参数替换 X。

---
### 9.2 tgmath.h 泛型类型宏数学库

- tgmath.h 文件创建一个泛型类型宏，与原来 double 版本的函数名同名, 定义 sqrt()宏展开为 sqrtf()、sqrt()或 sqrtl() 函数。

- 若编译器支持复数运算, 也会支持 complex.h 头文件, 其中声明了与复数相关的函数

- 声明有 csqrtf()、csqrt() 和 csqrtl()，这些函数分别返回 float complex、double complex和
long double complex 类型的复数平方根, 同时 tgmath.h 也能展开为相应的复数平方根函数

> 调用 math 函数而非宏函数时

- 若调用 sqrt 函数而非 sqrt 宏, 可以将函数标识符括起来

```c
	#include <tgmath.h>
	float x = 44.0f;
	double y = sqrt(x);	// 调用宏, 泛型选择为 sqrtf(x)
	y = (sqrt)(x); 		// 调用函数 sqrt()
```

---
## 10. 通用工具库 (stdlib.h)

- 通用工具库包含各种函数，包括随机数生成器、查找和排序函数、转换函数和内存管理函数

---
### 10.1 exit 与 atexit 函数

- exit 调用时不返回主调函数, 在 main 返回系统时会自动(隐式)调用 exit(int) 函数

- atexit(void*) 传递函数地址, 并注册函数列表中的函数, 在 exit(int) 调用时执行这些函数, 这个函数列表至少可以放 32 个函数, 执行顺序与注册顺序相反, 最后添加的函数最先执行

- atexit() 注册的函数应该是不带任何参数且返回 void, 该函数一般会执行一些清理任务, 更新监视程序的文件或重置环境变量

- 未主动调用 exit 时, 也会在 main 结束时隐式调用 exit

- 一般清理工作包括：刷新所有输出流、关闭所有打开的流和关闭由标准 I/O 函数 tmpfile() 创建的临时文件, 然后将控制权返回主机环境 (可能报告终止状态), UNIX 程序使用 0 (EXIT_SUCCESS) 表示成功终止, 非 0 (EXIT_FAILURE,1) 值表示终止失败

---
### 10.2 qsort 快速排序函数

- 快速排序算法在 C 实现中的名称是 qsort()。qsort() 函数排序数组的数据对象

```c
void qsort(void *base, size_t nmemb, size_t size, 
		int (*compar)(const void *, const void *));
/*>>> base    指向待排序数组的首元素, 可以引用任何类型的数组
	  nmemb   待排序项的数量, 
	  size    显式指明待排序数组中每个元素的大小
	  compar  指针指向的比较函数用于确定排序的顺序
  >>> 比较函数: 如果第 1 项的值大于第 2 项，比较函数则返回正数；
  			   如果两项相同，则返回 0；
			   如果第 1 项的值小于第 2 项，则返回负数	  
*/


> 排序浮点值数组

```c
#include <stdio.h>
#include <stdlib.h>
#define NUM 40
void fillarray(double ar[], int n);
void showarray(const double ar[], int n);
int mycomp(const void *p1, const void *p2); // 比较函数原型
int main(void)
{
	double vals[NUM];
	fillarray(vals, NUM);
	puts("Random list:");
	showarray(vals, NUM);
	qsort(vals, NUM, sizeof(double), mycomp); // qsort 排序
	puts("\nSorted list:");
	showarray(vals, NUM);
	return 0;
}
// 随机数填充数组
void fillarray(double ar[], int n)
{
	int index;
	for (index = 0; index < n; index++)
		ar[index] = (double)rand() / ((double)rand() + 0.1);
}
void showarray(const double ar[], int n)
{
	int index;
	for (index = 0; index < n; index++)
	{
		printf("%9.4f ", ar[index]);
		if (index % 6 == 5)
			putchar('\n');
	}
	if (index % 6 != 0)
		putchar('\n');
}
/* 按从小到大的顺序排序 */ // 可自定义排序规则, 对复合结构
int mycomp(const void *p1, const void *p2)
{
	/* 要使用指向 double 的指针来访问这两个值 */
	const double *a1 = (const double *)p1;
	const double *a2 = (const double *)p2;
	if (*a1 < *a2)
		return -1;
	else if (*a1 == *a2)
		return 0;
	else
		return 1;
}
```

> C 与 C++ void* 通用型指针

- C++ 要求在把 void* 指针赋给任何类型的指针时必须进行强制类型转换

- C 没有这样的要求

---
## 11. 断言库

- assert.h 头文件支持的断言库是一个用于辅助调试程序的小型库

- assert.h 由 assert() 宏组成，接受一个整型表达式作为参数。如果表达式求值为假（非零），assert() 宏就在标准错误流（stderr）中写入一条错误信息，并调用 abort() 函数终止程序（abort()函数的原型在stdlib.h头文件中）

- assert() 宏是为了标识出程序中某些条件为真的关键位置，如果其中的一个具体条件为假，就用 assert()语句终止程序

- assert() 的参数是一个条件表达式或逻辑表达式。如果 assert() 中止了程序，它首先会显示失败的测试、包含测试的文件名和行号。

---
### 11.1 assert 

- assert 能够自动标识文件和问题的行号

- 还有一种无需更改代码就能开启或关闭 assert() 的机制。如果认为已经排除了程序的 bug，在包含 assert.h 的位置前面：【 #define NDEBUG 】, 编译器就会禁用文件中的所有 assert() 语句。

```c
#include <stdio.h>
#include <math.h>
#include <assert.h>
int main()
{
	double x, y, z;
	puts("Enter a pair of numbers (0 0 to quit): ");
	while (scanf("%lf%lf", &x, &y) == 2 && (x != 0 || y != 0))
	{
		z = x * x - y * y; /* 应该用 + */
		assert(z >= 0);
		printf("answer is %f\n", sqrt(z));
		puts("Next pair of numbers: ");
	}
	puts("Done");
	return 0;
}
/*
	Enter a pair of numbers (0 0 to quit):
	1 2
	Assertion failed: z >= 0, file .\test.c, line 11
*/
```

---
### 11.2 _Static_assert (C11) 静态断言

- assert() 表达式是在运行时进行检查

- C11 新增了一个特性：_Static_assert 声明，可以在编译时检查 assert() 表达式

- assert() 可以导致正在运行的程序中止，而 _Static_assert() 可以导致程序无法通过编译。

```c
	_Static_assert(exp, const char*);
	/*>>>>>>>
		exp   整型常量表达式
	*/
```

---
## 12. memcpy 与 memmove (string.h)

- 一般时不能将数组赋给另一个数组, 可以通过循环把数组中的每个元素赋给另一个数组相应的元素, 或使用 strcpy 与 strncpy 处理字符串

- memcpy 与 memmove 函数提供类似的方法处理任意类型的数组

```c
	void *memcpy(void * restrict s1, const void * restrict s2,size_t n);
	void *memmove(void *s1, const void *s2, size_t n);

	/*
		都是 s2 指向拷贝 n 字节到 s1 指向的位置, 并返回 s1 的值
		>>> memcpy 若两个参数的内存区域之间没有重叠, 拷贝可能会成功, 
				但假设重叠, 则可能出现数据被修改的风险
		>>> memmove 的拷贝过程会将所有字节拷贝到临时缓冲区, 然后再拷贝到目的地, 整个过程相对内存安全

		size n 要指明待拷贝的字节数
	*/
```

---
## 13. 可变参数 stdarg.h

> 使用步骤

1. 提供一个使用省略号的函数原型；
2. 在函数定义中创建一个 va_list 类型的变量；
3. 用宏把该变量初始化为一个参数列表；
4. 用宏访问参数列表；
5. 用宏完成清理工作。

```c
	// 有效	
	void f1(int n, ...);
	int f2(const char * s, int k, ...); 	
	// 无效
	char f3(char c1, ..., char c2);	// 省略号不在最后
	double f3(...); 				// 没有形参

	// 宏使用可变参数列表
	double sum(int lim,...)
	{
		// 设 lim 表明变参列表中参数的数量

		// 1. 声明一个储存参数的对象 
		va_list ap; 		
		// 2. 把 ap 初始化为参数列表, lim 为参数数目
		va_start(ap, lim);  

		// 3. 访问参数列表的内容 
		va_arg(ap, 类型名)
		/*
			double tic = va_arg(ap, double); // 检索第 1 个参数
			int toc = va_arg(ap, int); 		 // 检索第 2 个参数
		*//* 传入的参数类型必须与宏参数的类型相匹配 */
		
		// 4. 宏完成清理工作
		va_end(ap); 	// 清理工作
		/* 释放动态分配用于储存参数的内存 */
	}
```

- 调用 va_end(ap) 后，只有用 va_start 重新初始化 ap 后，才能使用变量 ap。

- va_arg() 并不提供退回之前参数的方法，所以有必要保存 va_list 类型变量的副本。

- 可以使用 (C99) va_copy(va_list1, va_list2),  把 list2 传递给第一个参数

> 示例

```c
#include <stdio.h>
#include <stdarg.h>
double sum(int, ...);
int main(void)
{
	double s, t;
	s = sum(3, 1.1, 2.5, 13.3);
	t = sum(6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1);
	printf("return value for "
		   "sum(3, 1.1, 2.5, 13.3): %g\n",
		   s);
	printf("return value for "
		   "sum(6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1): %g\n",
		   t);
	return 0;
}
double sum(int lim, ...)
{
	va_list ap; // 声明一个对象储存参数
	double tot = 0;
	int i;
	va_start(ap, lim); // 把ap初始化为参数列表
	for (i = 0; i < lim; i++)
		tot += va_arg(ap, double); // 访问参数列表中的每一项
	va_end(ap);					   // 清理工作
	return tot;
}
/*
	return value for sum(3, 1.1, 2.5, 13.3): 16.9
	return value for sum(6, 1.1, 2.1, 13.1, 4.1, 5.1, 6.1): 31.6
*/
```

---
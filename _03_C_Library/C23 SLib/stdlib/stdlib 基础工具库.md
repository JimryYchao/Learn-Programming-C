## C 基础工具库：stdlib.h


`stdlib.h` 定义了一些类型、宏和一些功能函数等：内存管理、程序工具、字符串转换、随机数、算法等。

`EXIT_FAILURE`，`EXIT_SCCESS` 展开为整数常量表达式，可用作 `exit` 函数的参数，分别向主机环境返回不成功或成功的终止状态。

>---
### 数值转换

| Specifier                                                    | Description              |
| :----------------------------------------------------------- | :----------------------- |
| `atof`, `atoi`, `atol`, `atoll`                              | 字符串转换为数值类型。   |
| `strfromd`, `strfromf`, `strfroml`, <code>strfromd*N*</code> | 浮点值转换为字节字符串。 |
| `strtod`, `strtof`, `strtold`, <code>strtod*N*</code>        | 字节字符串转浮点数。     |
| `strtol`, `strtoll`, `strtoul`, `strtoull`                   | 字节字符串转整数。       |


除了错误时的行为，它们等同于：

```c
// atoi(nptr); 
(int)strtol(nptr, nullptr, 10);

// atol(nptr);
strtol(nptr, nullptr, 10);

// atoll(nptr); 
strtoll(nptr, nullptr, 10);
```

> atoXX: 字符串转换为数值类型

```c
#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
    printf("%g\n", atof("  -0.0000000123junk"));
    printf("%g\n", atof("0.012"));
    printf("%g\n", atof("15e16"));
    printf("%g\n", atof("-0x1afp-2"));
    printf("%g\n", atof("inF"));
    printf("%g\n", atof("Nan"));
    printf("%g\n", atof("1.0e+309"));   // UB ：超出 double 范围
    printf("%g\n", atof("0.0"));
    printf("%g\n", atof("junk"));       // 无可进行的转换
    printf("%i\n", atoi(" -123junk"));
    printf("%i\n", atoi("0"));
    printf("%i\n", atoi("2147483648"));   // UB ：在 int 范围外
}
```

> strfromXX: 浮点值转换为字节字符串

这些函数将相应标准浮点类型或十进制浮点类型的值转换为字节字符串。它们等价于 `snprintf(s, n, format, fp)`，但格式字符串应当仅包含字符 `%`，可选的不包含星号 `*` 的精度，和以下转换指示符之一：`a`、`A`、`e`、`E`、`f`、`F`、`g` 和 `G`，分别使其适用于函数 `strformXX` 后缀 `XX` 所指定的类型。

```c
#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    char buffer[32];
    int written;
    const char* format[] = {"%a", "%A", "%e", "%E", "%f", "%F", "%g", "%G"};
 
    for (size_t fmt = 0; fmt != sizeof format / sizeof format[0]; ++fmt)
    {
        written = strfromf(buffer, sizeof buffer, format[fmt], 3.1415f);
        printf("strfromf(... %s ...) = %2i, buffer: \"%s\"\n",
               format[fmt], written, buffer);
    }
    puts("");
}
/*
strfromf(... %a ...) = 13, buffer: "0x1.921cacp+1"
strfromf(... %A ...) = 13, buffer: "0X1.921CACP+1"
strfromf(... %e ...) = 12, buffer: "3.141500e+00"
strfromf(... %E ...) = 12, buffer: "3.141500E+00"
strfromf(... %f ...) =  8, buffer: "3.141500"
strfromf(... %F ...) =  8, buffer: "3.141500"
strfromf(... %g ...) =  6, buffer: "3.1415"
strfromf(... %G ...) =  6, buffer: "3.1415"
*/
```

> strtoXX: 字节字符串转浮点数

合法的浮点值可以是以下之一：
- 十进制浮点数表达式。它由下列部分组成：
  - (可选) 正或负号。
  - 非空的十进制数字序列，可选地包含一个小数点字符（由当前的 C 本地环境确定）（定义有效数字）。
  - (可选) `e` 或 `E`，并跟随可选的正或负号，以及非空十进制数字序列（以 10 为底定义指数）。

+ 十六进制浮点数表达式。它由下列部分组成：
  + (可选) 正或负号。
  + `0x` 或 `0X`。
  + 非空的十六进制数字序列，选地包含一个小数点字符（由当前的 C 本地环境确定）（定义有效数字）。
  + (可选) `p` 或 `P`，并跟随可选的正或负号，以及非空十进制数字序列（以 2 为底定义指数）。

- 无穷大表达式。它由下列部分组成：
  - (可选) 正或负号。
  - `INF` 或 `INFINITY`，忽略大小写。

+ 非数（NaN）表达式。它由下列部分组成：
  + (可选) 正或负号。
  + `NAN` 或 `NAN(char_sequence)` ，忽略 `NAN` 部分的大小写。*char_sequence* 只能由数字、拉丁字母和下划线构成。结果是一个 *quiet* *NaN* 浮点值。

- 任何其他可由当前 C 本地环境接受的表达式

转换结束后函数会设置 `endptr` 所指向的指针指向最后被转译字符的后一字符的位置。如果 `endptr` 是空指针则忽略它。函数返回转换后的值（如果有）。如果无法执行转换，则返回正零或无符号零。

如果正确的值溢出并且默认舍入有效，则加上或减去 `HUGE_VAL`，返回 `HUGE_VALF` 或 `HUGE_VALL`（根据返回类型和值的符号）；如果整数表达式 `math_errhandling & MATH_ERRNO` 非零，则整数表达式 `errno` 获取 `ERANGE` 的值；如果整数表达式 `math_errhandling & MATH_ERREXCEPT` 非零，则引发 *overflow* 浮点异常。

如果结果下溢，函数返回一个大小不大于返回类型中的最小规范化正数；如果整数表达式 `math_errhandling & MATH_ERRNO` 为非零，则 `errno` 是否获取值 `ERANGE` 由实现定义；如果整数表达式 `math_errhandling & MATH_ERREXCEPT` 为非零，则是否引发 *underflow* 浮点异常由实现定义。

```c
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(void)
{
    // 带错误处理的剖析
    const char* p = "111.11 -2.22 Nan nan(2) inF 0X1.BC70A3D70A3D7P+6  1.18973e+4932zzz";
    printf("Parsing '%s':\n", p);
    char* end;
    for (double f = strtod(p, &end); p != end; f = strtod(p, &end))
    {
        printf("'%.*s' -> ", (int)(end - p), p);
        p = end;  
        if (errno == ERANGE) {
            printf("range error, got ");
            errno = 0;
        }
        printf("%f\n", f);
    }

    // 无错误处理的剖析
    printf("\n\"  -0.0000000123junk\"  -->  %g\n", strtod("  -0.0000000123junk", NULL));
    printf("\"junk\"                 -->  %g\n", strtod("junk", NULL));
}
/*
Parsing '111.11 -2.22 Nan nan(2) inF 0X1.BC70A3D70A3D7P+6  1.18973e+4932zzz':
'111.11' -> 111.110000
' -2.22' -> -2.220000
' Nan' -> nan
' nan(2)' -> nan
' inF' -> inf
' 0X1.BC70A3D70A3D7P+6' -> 111.110000
'  1.18973e+4932' -> range error, got inf

"  -0.0000000123junk"  -->  -1.23e-08
"junk"                 -->  0
*/
```

> strtoXX：字节字符串转整数

`base` 底的合法集是 `{0,2,3,...,36}`。对于大于 `2` 的底表示函数将收集相应进制数的合法字符串表示并转换为整数。对于 `base = 0`，函数将自动检测数值进制：字符串前缀为 `0`，那么底是八进制；前缀为 `0x` 或 `0X` 则底为十六进制；否则底默认为十进制。

成功时返回对应的数值，无可用转换时返回 0。若转换值出现在范围外的情况（超出范围时发生域错误（`errno = ERANGE`）：
  - 对于 `strtol` 和 `strtoll` 根据溢出情况会返回 `LONG_MAX`、`LONG_MIN`、`LLONG_MAX` 或 `LLONG_MIN`。
  - 对于 `strtoul` 和 `strtoull` 根据溢出情况会会返回 `ULONG_MAX` 或 `ULLONG_MAX`。

```c
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
 
int main(void)
{
    const char *p = "10 200000000000000000000000000000 30 -40";
    printf("Parsing '%s':\n", p);
    char *end;
    for (unsigned long i = strtoul(p, &end, 10); p != end; i = strtoul(p, &end, 10))
    {
        printf("'%.*s' -> ", (int)(end-p), p);
        p = end;
        if (errno == ERANGE){
            printf("range error, got ");
            errno = 0;
        }
        printf("%lu\n", i);
    }
}
/*
Parsing '10 200000000000000000000000000000 30 -40':
'10' -> 10
' 200000000000000000000000000000' -> range error, got 18446744073709551615
' 30' -> 30
' -40' -> 18446744073709551576
*/ 
```

>---
### 伪随机

| Specifier  | Description                             |
| :--------- | :-------------------------------------- |
| `rand`     | 产生一个伪随机数                        |
| `srand`    | 为 `rand` 伪随机数生成器提供种子        |
| `RAND_MAX` | `rand` 函数返回的最大值。至少为 32767。 |

```c
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	printf("first rand before srand(): %d\n", rand());
	printf("second rand : %d\n", rand());
	printf("reset seed, srand(1)\n");
	srand((unsigned)1);
	printf("3rd rand : %d\n", rand());
	printf("reset seed, srand(time(NULL))\n");
	srand(time(NULL));
	printf("4th rand : %d\n", rand());
}
/*
first rand before srand(): 41
second rand : 18467
reset seed, srand(1)
3rd rand : 41
reset seed, srand(time(NULL))
4th rand : 2775         // Different from 18467
*/
```

> *下面的函数定义了 `rand` 和 `srand` 的可移植实现。*

```c
static unsigned long int next = 1;
#define RAND_MAX  32767   // RAND_MAX 假定为 32767
int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}
void srand(unsigned int seed)
{
    next = seed;
}
```

>---
### 内存管理

| Specifier            | Description                                                                                                       |
| :------------------- | :---------------------------------------------------------------------------------------------------------------- |
| `free`               | 解分配之前由 `malloc`、`calloc`、`aligned_alloc` 或 `realloc` 分配的空间。                                        |
| `free_sized`         | 解分配从调用 `malloc`、`realloc` 或 `calloc` 获得的结果，其中 `size` 等于请求的分配大小。                         |
| `free_aligned_sized` | 解分配从调用 `aligned_alloc` 获得的结果，其中 `alignment` 等于请求的分配 `alignment`，`size` 等于请求的分配大小。 |
| `malloc`             | 分配 `size` 大小未初始化的内存。                                                                                  |
| `calloc`             | 分配并清零内存。                                                                                                  |
| `realloc`            | 扩充内存。                                                                                                        |
| `aligned_alloc`      | 分配对齐内存。                                                                                                    |



> malloc

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int* pmem = malloc(sizeof(int[10]));
	printf("The point is : %p\n", pmem);
	printf("pmem[0] value = %d\n", pmem[0]);  // 初始化的内存并不会清除
	int index = 0;
	do
		pmem[index] = index;
	while ((++index) < 10);
	printf("pmem[5] value = %d\n", pmem[5]);
	free(pmem);
}
```

> calloc

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int *pmem = calloc(5, sizeof(int));
	printf("The pointer is : %p\n", pmem);
	int index = 0;
	do
		printf("pmem[%d] value = %d\n", index, pmem[index]);
	while ((++index) < 5);
	free(pmem);
}
```

> realloc

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int* pmem = calloc(5, sizeof(int));
	printf("The pointer is : %p\n", pmem);
	int index = 0;
	do
		printf("pmem[%d] value = %d\n", index, pmem[index]);
	while ((++index) < 5);
	int* npmem = realloc(pmem, 10 * sizeof(int));
	if (npmem != 0) {
		printf("The new pointer is : %p\n", npmem);
		index = 0;
		do
			printf("pmem[%d] value = %d\n", index, pmem[index]);
		while ((++index) < 10);
	}
	free(npmem);
}
```

>---
### 程序环境支持

| Specifier            | Description                                                                                                       |
| :------------------- | :---------------------------------------------------------------------------------------------------------------- |
| `abort`              | 非正常终止但不清理程序。程序终止时不会调用 `atexit` 注册的函数。                                                  |
| `_Exit`              | 正常终止但不清理。终止时不调用 `atexit`、`at_quick_exit` 注册的函数，也不会触发 `signal` 函数注册的信号处理程序。 |
| `exit`               | 正常程序终止并完全清理资源。逆序调用 `atexit` 注册的函数。                                                        |
| `atexit`             | 注册 `func` 所指向的函数，使它在程序正常终止（通过 `exit` 或从 `main` 返回）时得到调用。                          |
| `quick_exit`         | 正常程序终止而不完全清理资源。逆序调用 `at_quick_exit` 注册的函数。                                               |
| `at_quick_exit`      | 注册 `func` 所指向的函数，通过调用 `quick_exit` 终止程序时得到调用。                                              |
| `getenv`, `getenv_s` | 访问环境变量列表。                                                                                                |
| `system`             | 以参数 `string` 调用主机环境的命令处理器。                                                                        |


> 程序清理步骤

- 首先，所有由 `atexit` 函数注册的函数以注册时的相反顺序被调用。若在调用由 `atexit` 注册的函数期间，对 `longjmp` 函数的调用将终止对注册函数的调用，则行为是未定义。
+ 其次，刷新所有具有未写入缓冲数据的打开流，并关闭所有打开的流。删除所有 `tmpfile` 创建的所有文件。
- 最后，控制权返回主机环境，若 `status` 值为 `EXIT_SUCCESS`，则返回指示成功终止的实现定义状态。若 `status` 的值为 `EXIT_FAILURE`，则返回指示不成功的实现定义状态。否则，返回的状态是实现定义的。

```c
#include <stdio.h>
#include <stdlib.h>

void fun1() { puts("pushed first"); }
static void fun2() { puts("pushed second"); }
int main(void)
{
	atexit(fun1);
	atexit(fun2);
	// exit(EXIT_SUCCESS); // or return 0;
}
/*
pushed second
pushed first
*/
```

> quick_exit、at_quick_exit 


```c
#include <stdio.h>
#include <stdlib.h>

void fun1() { puts("pushed first"); }
static void fun2() { puts("pushed second"); }
int main(void)
{
	at_quick_exit(fun1);
	at_quick_exit(fun2);
	quick_exit(EXIT_SUCCESS);  // 注册的函数只能通过主动调用 quick_exit 函数被调用
}
/*
pushed second
pushed first
*/
```

> getenv_s


```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	errno_t err;
	size_t len;
	char* pVal;
	if (!getenv_s(&len, NULL, 0, "path"))   // 获取保存 path 环境变量所需的最小长度。
	{
		pVal = calloc(len, sizeof(char));  // 用于保存环境变量
		err = getenv_s(&len, pVal, len, "path");
		if (err)
			puts(strerror(err));
		else
			printf("Path value = %s\n", pVal);
		free(pVal);
	}
}
```

> system

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("rt = %d\n", system("cmd"));
	printf("rt = %d\n", system(NULL));
}
```

>---
### 搜索和排序

| Specifier              | Description                                 |
| :--------------------- | :------------------------------------------ |
| `qsort`, `qsort_s`     | 以 `compar` 设定的比较规则进行排序。        |
| `bsearch`, `bsearch_s` | 二分查找升序序列中与 `key` 匹配的元素位置。 |


> qsort_s

对于函数 `compar` 用于设定比较规则：
  - 若需要升序排序，则要求函数在首参数大于第二个参数时返回正数，小于时返回负数，等价时返回零（或小于等于时返回负数，则相等的元素会排在后面）。
  - 若需要降序排序，则要求函数在受参数大于第二个参数时返回负数，小于时返回正数，等价时返回零（或小于等于时返回正数，则相等的元素会排在前面）。
  - 如果两个元素比较为相等，则它们在结果排序数组中的顺序未指定。

```c
#include <stdio.h>
#include <stdlib.h>

struct Score {
	const char* name;
	int chinese;
	int math;
	int english;
} student[] = {
	{"Tom", 45,85,75},
	{"Mary", 88,52,66},
	{"Mark", 98,89,100},
	{"Jimry", 78,65,89},
	{"Ychao", 77,89,60}
};
void compare_s(const char* flag, const struct Score* lhs, const struct Score* rhs) {

	if (flag == "math")
		return (lhs->math > rhs->math) - (lhs->math < rhs->math);
	else if (flag == "english")
		return (lhs->english > rhs->english) - (lhs->english < rhs->english);
	else
		return (lhs->chinese > rhs->chinese) - (lhs->chinese < rhs->chinese);

}
int main(void)
{
	qsort_s(student, sizeof(student) / sizeof(student[0]), sizeof student[0], compare_s, "english");
	int index = 0;
	struct Score* s;
	do {
		s = &student[index];
		printf("Student: %5s, Math = %3d, Chinese = %3d, English = %3d\n", s->name, s->math, s->chinese, s->english);
	} while ((++index) < sizeof(student) / sizeof(student[0]));
}
```

> bsearch、bsearch_s

```c
void * bsearch(const void *key, void *base, size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));
```

`bsearch` 函数在一个 `nmemb` 个对象组成的数组中搜索与 `key` 指向的对象匹配的元素，该数组的初始元素由 `base` 指向。数组中每个元素的大小由 `size` 指定。如果 `base` 数组不采用升序排序顺序或包含具有相同键的重复记录，则结果不可预知。

由 `compar` 所指向的比较函数被调用时带有两个参数，它们依次指向 `key` 对象和数组元素。如果 `key` 对象分别被认为小于、匹配或大于数组元素，则该函数应返回小于、等于或大于零的整数。该数组应包含：所有比较小于的元素、所有比较等于的元素，以及所有比较大于 `key` 对象的元素。

对于 `bsearch`，同一对象必须始终以相同的方式与 `key` 进行比较。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdlib.h>

void compare(const void* key,const void* val) {

	int const* const l = key;
	int const* const r = val;
	return (*l > *r) - (*l < *r);  // 升序函数，若要逆序只需 (*l < *r) - (*l > *r)
}
int main(void)
{
	int arr[] = { 1,4,5,8,9,7,2,85,78,4,5,8,4 };
	int key = 85;
	int context[sizeof arr] = { 0 };
	qsort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), compare);  // 重新排序为升序
	int* pint = bsearch_s(&key, arr, sizeof(arr)/ sizeof(arr[0]), sizeof(arr[0]), compare, context);
	if (pint) 
		printf("The index = %td, value = %d\n", pint - arr, *pint);     // 查找元素
}
```

>---
### 整数算数

| Specifier                    | Description                 |
| :--------------------------- | :-------------------------- |
| `abs`、`labs`、`llabs`       | 整数绝对值                  |
| `div`、`ldiv`、`lldiv`       | 整数余商计算                |
| `div_t`, `ldiv_t`, `lldiv_t` | 为相应 `div` 函数的返回类型 |


>---
### 多字节 / 宽字符转换

| Specifier            | Description                                                                                                                    |
| :------------------- | :----------------------------------------------------------------------------------------------------------------------------- |
| `mbtowc`             | 多字节字符转换成宽字符，`n` 表示 `s` 中能被检验的字节数的限制。返回的值不能大于 `n` 或 `MB_CUR_MAX` 宏的值。                   |
| `wctomb`、`wctomb_s` | 转换宽字符为多字节编码，并存储（含迁移状态）于 `s` 指向其首元素的字符数组                                                      |
| `mblen`              | `s` 指向其首字符的多字节字符的字节大小。它等效于调用 `mbtowc((wchar_t*)0, s, n)` 或 `mbtowc((wchar_t*)0, (const char*)0, 0)`。 |


多字节字符函数的行为受当前区域设置的 `LC_CTYPE` 类别的影响。更改 `LC_CTYPE` 类别会导致描述 `mbtowc` 和 `wctomb` 函数转换状态的内部对象具有不确定的表示。

> mbtowc

```c
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>

// 打印多字节字符串到宽面向的 stdout, 等价于 wprintf(L"%s\n", ptr);
void print_mb(const char* ptr)
{
    mbtowc(NULL, 0, 0); // 重置初始转换状态
    const char* end = ptr + strlen(ptr);  // 指向字符串尾
    int ret;
    for (wchar_t wc; (ret = mbtowc(&wc, ptr, end - ptr)) > 0; ptr += ret)
        wprintf(L"%lc", wc);
    wprintf(L"\n");
}

int main(void)
{
    setlocale(LC_ALL, "en_US.utf8");
    // UTF-8 窄多字节编码
    print_mb(u8"z\u00df\u6c34\U0001F34C"); // 或 u8"zß水🍌"
}
```

> wctomb


```c
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void demo(wchar_t wc)
{
	printf("State-dependent encoding?   %d\n", wctomb(NULL, wc));
	char mb[512];
	int len = wctomb(mb, wc);
	if (len > 0)
	{
		wprintf(L"wide char '%lc' -> multibyte char '", wc);
		for (int idx = 0; idx < len; ++idx)
			printf("%#2x ", (unsigned char)mb[idx]);
		printf("'\n");
	}
	else printf("paramter is too large for this type\n");
}

int main(void)
{
	setlocale(LC_ALL, "en_US.utf8");
	printf("MB_CUR_MAX = %zu\n", MB_CUR_MAX);
	demo(L'A');
	demo(L'\u00df');
	demo(L'\U0001d10b'); // 过大
}
```

> mblen

```c
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
// 多字节字符串的字符数是 mblen() 的和
size_t strlen_mb(const char* ptr)
{
    size_t result = 0;
    const char* end = ptr + strlen(ptr);
    mblen(NULL, 0); // 重置转换状态
    while (ptr < end) {
        int next = mblen(ptr, end - ptr); // 确定每一个多字节字符的长度
        if (next == -1) {
            perror("strlen_mb");
            break;
        }
        ptr += next;
        ++result;
    }
    return result;
}
void dump_bytes(const char* str)
{
    const char* end = str + strlen(str);
    for (; str != end; ++str)
        printf("%02X ", (unsigned char)str[0]);
    printf("\n");
}
int main(void)
{
    setlocale(LC_ALL, "en_US.utf8");
    const char* str = "z水\u00df";
    printf("The string \"%s\" consists of %zu characters, but %zu bytes: ",
        str, strlen_mb(str), strlen(str));
    dump_bytes(str);
}
```

>---
### 多字节 / 宽字符串转换

| Specifier                | Description                                                                                             |
| :----------------------- | :------------------------------------------------------------------------------------------------------ |
| `mbstowcs`, `mbstowcs_s` | 转换来自从首元素为 `src` 所指的数组的多字节字符串为其宽字符表示。返回转换成功的字符数（不包含空终止符） |
| `wcstombs`、`wcstombs_s` | 转换来自首元素为 `pwcs` 所指向的数组到其始于初始迁移状态的多字节表示。                                  |

`wctomb`、`wctomb_s` |  转换宽字符为多字节编码，并存储（含迁移状态）于 `s` 指向其首元素的字符数组
`mblen` |  `s` 指向其首字符的多字节字符的字节大小。它等效于调用 `mbtowc((wchar_t*)0, s, n)` 或 `mbtowc((wchar_t*)0, (const char*)0, 0)`。


> mbstowcs、mbstowcs_s

```c
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>
int main(void)
{
    setlocale(LC_ALL, "en_US.utf8");
    const char* mbstr = u8"zß水🍌"; // or u8"zß水🍌"
    wchar_t wstr[5];
    mbstowcs(wstr, mbstr, 5);
    wprintf(L"MB string: %s\n", mbstr);
    wprintf(L"Wide string: %ls\n", wstr);
}
```

> wcstombs、wcstombs_s 

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(void)
{
    const wchar_t src[] = L"z\u00df\u6c34";
    char dst[7];

    setlocale(LC_ALL, "en_US.utf8");
    printf("wide-character string: '%ls'\n", src);
    for (size_t ndx = 0; ndx < sizeof src / sizeof src[0]; ++ndx)
        printf("   src[%2zu] = %#8x\n", ndx, src[ndx]);

    int rtn_val = wcstombs(dst, src, sizeof dst);
    printf("rtn_val = %d\n", rtn_val);
    if (rtn_val > 0)
        printf("multibyte string:  '%s'\n", dst);
    for (size_t ndx = 0; ndx < sizeof dst; ++ndx)
        printf("   dst[%2zu] = %#2x\n", ndx, (unsigned char)dst[ndx]);
}
```

>---
### 内存对齐

`memalignment` 函数接受指向任何对象的指针，并返回其地址值所满足的最大对齐。这个对齐可以是扩展对齐，也可以超出显式使用 `alignas` 的实现所支持的范围。如果是这样，它将满足实现可用的所有对齐。可以将返回的值与 `alignof` 的结果进行比较，如果它大于或等于，则满足类型操作数的对齐要求。

函数指针 `p` 的对齐方式，它是 2 的幂。如果 `p` 是空指针，则返回零对齐。零对齐表示被测试的指针不能用于访问任何类型的对象。

---
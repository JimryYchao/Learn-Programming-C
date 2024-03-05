## C 基础工具库（General utilities）：stdlib.h

```c
#define __STDC_VERSION_STDLIB_H__		202311L
```

`stdlib.h` 定义了一些类型、宏和一些功能函数等：内存管理、程序工具、字符串转换、随机数、算法等。

---
### Types

`size_t` 和 `wchar_t` 在 `stddef.h` 声明；`once_flag` 在 `threads.h` 声明。

>---

#### div_t、ldiv_t、lldiv_t

```c
typedef struct{
    int quot;
    int rem;
} div_t;        // 函数 div 的返回类型

typedef struct{
    long quot;
    long rem;
} ldiv_t;       // 函数 ldiv 的返回类型

typedef struct{
    long long quot;
    long long rem;
} lldiv_t;      // 函数 lldiv 的返回类型
```

---
### Macros

`NULL` 在 `stddef.h` 声明；`ONCE_FLAG_INIT` 在 `threads.h` 声明。

>---
#### EXIT_FAILURE、EXIT_SCCESS （程序退出状态）

```c
// Argument values for exit()
#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1
```

这些宏展开为整数常量表达式，可用作 `exit` 函数的参数，分别向主机环境返回不成功或成功的终止状态。

>---

#### RAND_MAX （最大随机数限定）

```c
#define RAND_MAX 	
```

`RAND_MAX` 展开为一个整数常量表达式，它是 `rand` 函数返回的最大值。`RAND_MAX` 的值至少为 32767。

>---

#### MB_CUR_MAX （当前多字节字符中的最大字节数）

```c
#define MB_CUR_MAX  ___mb_cur_max_func()
```

`MB_CUR_MAX` 展开为一个类型为 `size_t` 的正整数表达式。该值表示为当前区域设置（`LC_CTYPE` 类别）指定的扩展字符集的多字节字符中的最大字节数，它永远不会大于 `MB_LEN_MAX`（`limits.h`）。

```c
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(void)
{
	puts("The maximum number of bytes in a multibyte character in an extended character set : ");
	setlocale(LC_CTYPE, "C");
	printf("default C: %d\n", MB_CUR_MAX);
	setlocale(LC_CTYPE, "zh_cn.utf8");
	printf("zh_cn: %d\n", MB_CUR_MAX);
}
/*
default C: 1
zh_cn: 4
*/
```

---
### Functions：数值转换（Numeric conversion functions）

函数 `atof`、`atoi`、`atol` 和 `atoll` 不需要影响整数表达式 `errno` 的值。如果结果的值无法表示，则行为未定义。

>---
#### atof （字节字符串转浮点值）

```c
double atof(const char *nptr);
```

`atof` 函数将 `nptr` 所指向的字节字符串中的初始部分转换为 `double` 浮点值。函数会舍弃开头的任何空白符，直至找到首个空白符。成功转化时返回对应的转化结果，无可进行的转化返回 `0.0`。不在返回类型表示范围内的，返回值是未定义，并设置相应的 `errno`。

合法的浮点值字符串可以是：
  - 可选的正或负号。
  - 非空的数字序列：十进制（可包括 E 计数法），`0x` 或 `0X` 表示的十六进制（可包括 P 计数法），忽略大小写的无穷大 `inf` 或 `infinity`，忽略大小写的非数字 `nan`。可以包含一个小数点符号。
  - 任何其他可由当前 C 本地环境接受的表达式。

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
}
```

>---

#### atoi、atol、atoll （字节字符串转整数）

```c
int atoi(const char *nptr);             // to int
long int atol(const char *nptr);        // to long
long long int atoll(const char *nptr);  // to long long
```

函数转译 `nptr` 所指的字节字符串中的整数值。转换过程中舍弃任何的前置空白符，并收集尽可能多的字符以组成。不在返回类型表示范围内的，返回值是未定义，并设置相应的 `errno`。

合法的整数表示：
  - 可选的正或负号。
  - 十进制数字字符序列。

```c
#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    printf("%i\n", atoi(" -123junk"));
    printf("%i\n", atoi("0"));
    printf("%i\n", atoi("junk"));         // 无可进行的转换
    printf("%i\n", atoi("2147483648"));   // UB ：在 int 范围外
}
```


除了错误时的行为，它们等同于：

```c
// atoi(nptr); 
(int)strtol(nptr, nullptr, 10);

// atol(nptr);
strtol(nptr, nullptr, 10);

// atoll(nptr); 
strtoll(nptr, nullptr, 10);
```

>---
#### strfromd、strfromf、strfroml、strfromd*N* （浮点值转换为字节字符串）

```c
int strfromd(char * restrict s, size_t n, const char * restrict format, double fp);
int strfromf(char * restrict s, size_t n, const char * restrict format, float fp);
int strfroml(char * restrict s, size_t n, const char * restrict format, long double fp);

#ifdef __STDC_IEC_60559_DFP__
int strfromd32(char * restrict s, size_t n, const char * restrict format, _Decimal32 fp);
int strfromd64(char * restrict s, size_t n, const char * restrict format, _Decimal64 fp);
int strfromd128(char * restrict s, size_t n, const char * restrict format, _Decimal128 fp);
#endif
```

这些函数将相应标准浮点类型或十进制浮点类型的值转换为字节字符串。它们等价于 `snprintf(s, n, format, fp)`，但格式字符串应当仅包含字符 `%`，可选的不包含星号 `*` 的精度，和以下转换指示符之一：`a`、`A`、`e`、`E`、`f`、`F`、`g` 和 `G`，分别使其适用于函数 `strformXX` 后缀 `XX` 所指定的类型。以其他任何格式字符串调用这些函数将导致未定义行为。

`s`	表示指向将写入的字符串；`n`	表示最多写入 `n-1` 个字符和空终结符；`format` 表示指向空终结字节字符串的指针，指定如何判读数据；`fp`	表示欲转换的浮点值。

假设 `n` 足够大时将会写入的字符数量，不计入终结的空字符。因而，当且仅当返回值非负且小于 `n` 时，才会完整写入带空终结的输出。

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

>---
#### strtod、strtof、strtold、strtod*N* （字节字符串转浮点数）

```c
double strtod(const char * restrict nptr, char ** restrict endptr);
float strtof(const char * restrict nptr, char ** restrict endptr);
long double strtold(const char * restrict nptr, char ** restrict endptr);

#ifdef __STDC_IEC_60559_DFP__
_Decimal32 strtod32(const char * restrict nptr, char ** restrict endptr);
_Decimal64 strtod64(const char * restrict nptr, char ** restrict endptr);
_Decimal128 strtod128(const char * restrict nptr, char ** restrict endptr);
#endif
```

函数转译 `nptr` 所指的字节字符串中的浮点值。转化过程中舍弃任何的前置空白符，并收集尽可能多的字符，以后成合法的浮点数表示，并将其转换为浮点值。

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

转换结束后函数会设置 `endptr` 所指向的指针指向最后被转译字符的后一字符的位置。如果 `endptr` 是空指针则忽略它。

函数返回转换后的值（如果有）。如果无法执行转换，则返回正零或无符号零。

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

>---

#### strtol、strtoll、strtoul、strtoull （字节字符串转整数）

```c
// 转译为有符号整数
long int strtol(const char * restrict nptr, char ** restrict endptr, int base);
long long int strtoll(const char * restrict nptr, char ** restrict endptr, int base);
// 转译为无符号整数
unsigned long int strtoul(const char * restrict nptr, char ** restrict endptr, int base);
unsigned long long int strtoull(const char * restrict nptr, char ** restrict endptr, int base);
```

函数用于转译 `nptr` 所指的字节字符串中的整数值。函数会舍弃掉任何前置空白符，并收集尽可能多的字符组成底为 `base` 的合法整数表示。函数设置 `endptr` 所指向的指针指向最后一个被转译字符的后一字符。若 `endptr` 为空指针，则忽略它。

`base` 底的合法集是 `{0,2,3,...,36}`。对于大于 `2` 的底表示函数将收集相应进制数的合法字符串表示并转换为整数。对于 `base = 0`，函数将自动检测数值进制：字符串前缀为 `0`，那么底是八进制；前缀为 `0x` 或 `0X` 则底为十六进制；否则底默认为十进制。

若负符号是输入序列的一部分，那么对从数字序列计算得来的数字值取反，如同用结果类型的一元减，**它对无符号整数应用回卷规则**。

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

---
### Functions：伪随机函数（Pseudo-random sequence generation functions）
#### rand、srand

```c
int rand(void);    // 产生一个伪随机数
void srand(unsigned int seed);  // 
```

`rand` 函数计算 0 到 `RAND_MAX` 范围内的伪随机整数序列。`rand` 函数不需要避免与其他伪随机序列生成函数调用的数据竞争。

`srand` 函数为 `rand` 伪随机数生成器提供种子，每次以 `srand` 播种 `rand` 时，一定会产生相同的整数序列。若在任何对 `srand` 的调用前使用 `rand`，默认是以 `srand(1)` 向 `rand` 传播种子。`srand` 函数不需要避免与其他对伪随机序列生成函数的调用的数据竞争。

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

---
### Functions：内存管理（Memory management functions）

连续调用 `aligned_alloc`、`calloc`、`malloc` 和 `realloc` 函数所分配的存储的顺序和连续度是未指定的。

如果分配成功，返回的指针被适当地对齐，这样它就可以被分配给指向任何类型对象的指针，这些对象具有基本对齐要求且大小小于或等于请求的大小。然后可以使用它来访问分配的空间中的这样的对象或这样的对象数组（直到显式地释放空间）。

已分配对象的生存期从分配开始一直延伸到解除分配。每个这样的分配都应该产生一个指向与任何其他对象不相交的对象的指针。返回的指针指向已分配空间的起始(最低字节地址)。

如果不能分配空间，则返回空指针。如果请求的空间大小为零，则行为是由实现定义的:要么返回空指针以指示错误，要么行为就像大小是非零值一样，只是返回的指针不能用于访问对象。

为了确定是否存在数据竞争，内存分配函数的行为就好像它们只访问可通过其参数访问的内存位置，而不访问其他静态持续时间存储。然而，这些函数可以明显地修改它们分配或释放的存储。

对这些分配或释放特定内存区域的函数的调用应该以单一的总顺序发生，并且每个这样的释放调用都应该按照这个顺序与下一个分配（如果有的话）同步。

>---
#### free、free_sized、free_aligned_sized （释放内存）

```c
void free(void *ptr);  
void free_sized(void *ptr, size_t size);
void free_aligned_sized(void *ptr, size_t alignment, size_t size);
```

`free` 函数用于解分配之前由 `malloc`、`calloc`、`aligned_alloc` 或 `realloc` 分配的空间。若 `ptr` 为空指针则不作为；若 `ptr` 与之前上述的内存管理函数返回的指针不匹配，或 `ptr` 所指代的区域已经被解分配（被 `free` 或 `realloc` 释放），则行为未定义。

`free_sized` 的参数 `ptr` 如果是一个空指针，或者是从调用 `malloc`、`realloc` 或 `calloc` 获得的结果，其中 `size` 等于请求的分配大小，则此函数等效于 `free(ptr)`。否则，行为是未定义的。`aligned_alloc` 的调用结果不能传递给 `free_sized`。

`free_aligned_sized` 的参数 `ptr` 如果是一个空指针，或者是从调用 `aligned_alloc` 获得的结果，其中 `alignment` 等于请求的分配 `alignment`，`size` 等于请求的分配大小，则此函数等效于 `free（ptr)`。否则，行为是未定义的。其他内存分配的函数的结果不能传递给该函数。

```c
#include <stdlib.h>
int main(void)
{
    int *p1 = malloc(10*sizeof *p1);
    free(p1); // 每一个分配的指针都要释放
    int *p2 = calloc(10, sizeof *p2);
    int *p3 = realloc(p2, 1000*sizeof *p3);
    if(p3) // p3 非空表示 p2 被 realloc 释放
       free(p3);
    else // p3 为空表示 p2 未被释放
       free(p2);
}
```

>---

#### malloc （分配内存）

```c
void * malloc(size_t size);
```

`malloc` 函数为大小由 `size` 指定且值不确定的对象分配空间。若分配成功，则返回为任何拥有基础对齐的对象类型对齐的指针，否则返回空指针。

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

>---

#### calloc （分配并清零内存）

```c
void * calloc(size_t nmemb, size_t size);
```

`calloc` 函数为 `nmemb` 个对象的数组分配空间，每个对象的大小为 `size`。分配的空间中所有位被初始化为零。若分配成功，会返回指向分配内存块最低位（首位）字节的指针，它为任何类型适当地对齐，否则返回空指针。

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

>---

#### realloc (扩充内存)

```c
void * realloc(void *ptr, size_t size);
```

`realloc` 函数释放 `ptr` 所指向的旧对象，并返回一个指向新对象的指针（它可能与指向旧对象的指针具有相同的值），该指针的大小由 `size` 指定。`ptr` 必须是之前为 `malloc`、`calloc`、`realloc` 所分配的，且未被 `free` 或 `realloc` 释放。

重新分配规则：
  - 尽可能的扩张或收缩 `ptr` 所指的已存在内存。内容在新旧大小中的较小者范围内保持不变。若扩张，新增的内存中的内容是不确定的。
  - 分配一个大小为 `size` 字节的新内存块，并复制旧内存块中的内容到新内存（收缩时多余的旧内存内容被舍弃），然后释放旧内存。

若 `ptr` 为 `NULL`，则函数等价于 `malloc(size)`。若 `size` 为 0，则行为是未定义的（C23）。如果没有为新对象分配内存，则旧对象不会被释放，其值也不会改变。

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

####  aligned_alloc (分配对齐内存)

```c
void * aligned_alloc(size_t alignment, size_t size);
```

`aligned_alloc` 分配 `size` 字节未初始化的存储空间，并按照 `alignment` 指定对齐方式。如果对齐值不是实现所支持的有效对齐，则该函数将返回空指针而失败。

> Macrosoft C 专用

MS CRT 不支持 `aligned_alloc` 函数，因为其 `std::free` 的实现无法处理任意种类的对齐分配。MS CRT 提供了 `_aligned_malloc` 作为替代，其结果使用 `_aligned_free` 函数释放。

```c
void * _aligned_malloc(size_t _Size, size_t _Alignment);
void _aligned_free(void* _Block);
```

---
### Functions：程序环境支持（Communication with the environment）

#### abort （非正常终止但不清理）

```c
[[noreturn]] void abort(void);
```

调用 `abort` 函数导致程序异常终止，除非传递给 `signal` 的信号处理函数捕获 `SIGANRT` 信号且该处理函数不返回。是否刷新具有未写入缓冲数据的打开流、关闭打开流或删除临时文件是实现定义的。状态不成功终止的实现定义的形式通过调用函数 `raise(SIGABRT)` 返回到主机环境。`abort` 函数不会返回到它的调用方。

`abort` 程序终止时不会调用 `atexit` 注册的函数。

>---

#### _Exit （正常终止但不清理）

```c
[[noreturn]] void _Exit(int status);
```

`_Exit` 函数导致正常的程序终止而不完全清理资源，并将控制返回给主机环境。返回到主机环境的状态的确定方法与 `exit` 函数相同。具有未写入缓冲数据的打开流是否被刷新、关闭打开流或删除临时文件是由实现定义的。

`_Exit` 程序终止时不调用 `atexit`、`at_quick_exit` 注册的函数，也不会触发 `signal` 函数注册的信号处理程序。

>---

#### exit、atexit （正常终止并清理）

```c
[[noreturn]] void exit(int status);
int atexit(void (*func)(void));
```

`exit` 函数导致正常的程序终止并完全清理资源。程序终止时不调用 `at_quick_exit` 函数注册的函数。如果一个程序不止一次调用 `exit`，或者除了 `exit` 函数之外还调用了 `quick_exit`，则该行为是未定义的。

从 `main` 函数返回时，无论是通过 `return` 语句还是抵达函数尾，都会将 `return` 语句的参数（或若使用隐式返回，则为 ​0​）作为 `status` 传递，并执行 `exit(status)`。

`atexit` 注册 `func` 所指向的函数，使它在程序正常终止（通过 `exit` 或从 `main` 返回）时得到调用，在调用 `exit` 函数之前未发生的对 `atexit` 函数的调用是否成功是未指定的。这些函数将以注册顺序的逆序被调用。可以注册同一函数多次，`atexit` 函数是线程安全的，C 标准保证至少支持注册 32 个函数。注册成功时返回 0，失败时返回非 0。


> 程序清理步骤：

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

>---

#### quick_exit、at_quick_exit （正常终止但不完全清理）

```c
[[noreturn]] void quick_exit(int status);
int at_quick_exit(void (*func)(void));
```

`quick_exit` 函数正常的程序终止而不完全清理资源。程序终止时不调用 `atexit` 函数注册的函数或 `signal` 函数注册的信号处理程序。如果一个程序不止一次调用 `quick_exit` 函数，或者除了调用 `quick_exit` 函数之外还调用了 `exit` 函数，那么该行为是未定义的。如果在 `quick_exit` 函数执行时引发了一个信号，那么该行为是未定义的。

`at_quick_exit` 注册 `func` 所指向的函数，通过调用 `quick_exit` 终止程序时得到调用，在调用 `quick_exit` 函数之前未发生的对 `at_quick_exit` 函数的调用是否成功是未指定的。这些函数将以注册顺序的逆序被调用。可以注册同一函数多次，`at_quick_exit` 函数是线程安全的，C 标准保证至少支持注册 32 个函数。注册成功时返回 0，失败时返回非 0。

`quick_exit` 函数首先调用由 `at_quick_exit` 函数注册的所有函数，按照它们注册的相反顺序依次调用。如果在调用任何这样的函数期间，对 `longjmp` 函数的调用将终止对注册函数的调用，则行为是未定义的。然后通过调用 `_Exit(status)` 函数将控制权返回给主机环境。

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

>---

#### getenv、getenv_s （访问环境变量列表）

> `getenv`

```c
char * getenv(const char *name);
```

`getenv` 在当前主机环境指定的环境列表中，查找名为 `name` 的环境变量，并返回关联到匹配环境变量的字符串。环境变量的集合及修改它的方法是实现定义的。此函数不保证是线程安全的，对 `getenv` 的调用和对 POSIX 函数 `setenv`、`unsetenv`、`putenv` 的调用，可能会使先前调用返回的指针非法或修改先前调用得到的字符串结果。

`getenv` 函数不需要用来避免与修改环境列表的其他执行线程的数据竞争。

`getenv` 函数的作用是：返回一个指向与匹配 `name` 的环境变量字符串的指针。所指向的字符串不能被程序修改，但可以被后续对 `getenv` 函数的调用覆盖。如果找不到指定的名称，则返回空指针。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("%s\n", getenv("tmp"));  // 返回主机环境的 TEMP 环境变量的值 value
}
```

> `getenv_s`

```c
errno_t getenv_s(size_t* len, char* buf, rsize_t bufSize, char const* name);
```

- 同 `getenv`，函数将匹配成功的环境变量的值写入到缓冲区 `buf`，写入的字节数存储于 `*len` 中（除非是 `NULL`）。若 `name` 无法匹配成功则 `*len = 0`，`value[0] = '\0'`。
- 函数 `getenv_s` 在运行时检测下列错误并调用当前安装的制约处理函数：
  - `name` 是空指针；
  - `bufSize` 大于 `RSIZE_MAX`；
  - `buf` 是空指针且 `bufSize` 非零。

- 若匹配的结果字符串超过 `buf` 缓冲区的容量，则匹配将失败，返回非零值。可以空指针 `buf` 和零值的 `bufSize` 为参数传递给函数 `getenv_s` 用于确定 `name` 匹配成功时可保有结果所需的缓冲区大小，并把该值保存到 `*len` 中。 

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
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

>---

#### system （宿主环境的命令处理器）

```c
int system(const char *string);
```

`system` 函数以参数 `string` 调用主机环境的命令处理器。如果 `string` 是空指针，则 `system` 检查主机环境是否有命令处理器。如果 `string` 不是空指针，`system` 函数将 `string` 传递给命令处理器，以一种实现应记录的方式执行。这可能会导致程序调用系统以不一致的方式运行或终止。

`system` 函数仅在命令处理器可用时返回非零值，不可用则返回 0。如果 `string` 不是空指针，并且 `system` 函数确实返回，则返回实现定义的值（通常是被调用程序所返回的值）。

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("rt = %d\n", system("cmd"));
	printf("rt = %d\n", system(NULL));
}
```

---
### Functions：搜索和排序（Searching and sorting utilities）
#### qsort、qsort_s （排序）

> qsort

```c
void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
```

`qsort` 函数用于对一个由 `nmemb` 个大小为 `size` 的对象组成的数组 `base` （指向初始元素）以 `compar` 设定的比较规则进行排序。

对于函数 `compar` 用于设定比较规则：
  - 若需要升序排序，则要求函数在首参数大于第二个参数时返回正数，小于时返回负数，等价时返回零（或小于等于时返回负数，则相等的元素会排在后面）。
  - 若需要降序排序，则要求函数在受参数大于第二个参数时返回负数，小于时返回正数，等价时返回零（或小于等于时返回正数，则相等的元素会排在前面）。
  - 如果两个元素比较为相等，则它们在结果排序数组中的顺序未指定。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdlib.h>

void compare_ascending(const void* key, const void* val) {

	int const* const l = key;
	int const* const r = val;
	/*if (*l > *r)	return 1;
	else if (*l < *r) return -1;
	else return 0;*/
	return (*l > *r) - (*l < *r);  // 升序
}
void compare_descending(const void* key, const void* val) {
	int const* const l = key;
	int const* const r = val;
	return (*l < *r) - (*l > *r);  // 降序
}
int main(void)
{
	int arr[] = { 1,4,5,8,9,7,2,85,78,4,5,8,4 };
	qsort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), compare_ascending);  // 升序排序
	int index = 0;
	puts("ascending order...");
	do
		printf("The index = %td, value = %d\n", index, arr[index]);
	while (sizeof arr / sizeof arr[0] > (++index));

	puts("descending order...");
	index = 0;
	qsort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), compare_descending); // 降序排序
	do
		printf("The index = %td, value = %d\n", index, arr[index]);
	while (sizeof arr / sizeof arr[0] > (++index));
}
```

> `qsort_s`

```c
errno_t qsort_s( void *base, rsize_t elemCount, rsize_t elemSize,
                 int (*compar)(void *, const void *, const void *),
                 void *context );
```

`qsort_s` 功能上与 `qsort` 相同，该函数额外提供了一个 `context` 参数，用于传递给 `compar` 的首元素，它指向可在比较函数中访问的对象的指针，表示一个附加的对照信息。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
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


>---

#### bsearch、bsearch_s （二分查找）

> `bsearch`

```c
void *bsearch(const void *key, void *base, size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));
// 泛型宏
/*QVoid*/ *bsearch(const void *key, /*QVoid*/ *base, size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));
```

`bsearch` 泛型函数在一个 `nmemb` 个对象组成的数组中搜索与 `key` 指向的对象匹配的元素，该数组的初始元素由 `base` 指向。数组中每个元素的大小由 `size` 指定。**如果 `base` 数组不采用升序排序顺序或包含具有相同键的重复记录，则结果不可预知。**

由 `compar` 所指向的比较函数被调用时带有两个参数，它们依次指向 `key` 对象和数组元素。如果 `key` 对象分别被认为小于、匹配或大于数组元素，则该函数应返回小于、等于或大于零的整数。该数组应包含：所有比较小于的元素、所有比较等于的元素，以及所有比较大于 `key` 对象的元素。

对于 `bsearch`，同一对象必须始终以相同的方式与 `key` 进行比较。

对于 `bsearch` 泛型函数的宏定义被禁止访问实际函数（`void * bsearch()` 或函数指针），则实际函数 `void * bsearch()` 变为可见。`bsearch` 泛型函数返回一个指向数组中匹配元素的指针，如果没有找到匹配，则返回一个空指针。如果两个元素比较为相等，则未指定哪个元素匹配。令 T 为一个无限定的对象类型（包括 `void`）：
- 若 `ptr` 类型为 `const T*`，则返回类型为 `const void*`。
- 否则，若 `ptr` 类型为 `T*` ，则返回类型为 `void*`。
- 否则行为未定义。


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

> `bsearch_s`

```c
void *bsearch_s(const void *key, const void *base, rsize_t elemCount, rsize_t elemSize,
                 int (*compar)(void *, const void *, const void *),
                 void *context );
// 泛型宏
/*QVoid*/ *bsearch_s( const void *key, /*QVoid*/ *ptr, rsize_t count, rsize_t size,
                      int (*comp)(const void *, const void *, void *),
                      void *context );
```

`bsearch_s` 功能上与 `bsearch` 相同，该函数额外提供了一个 `context` 参数，用于传递给 `compar` 的首元素，它指向可在比较函数中访问的对象的指针，表示一个附加的对照信息。

使用 `bsearch_s` 之前可以先对数组使用 `qsort_s` 进行升序排序。

对于 `bsearch_s` 泛型函数的宏定义被禁止访问实际函数（`void * bsearch_s` 或函数指针），则实际函数 `void * bsearch_s` 变为可见。

---
### Functions：整数算数（Integer arithmetic functions）

#### abs、labs、llabs （整数绝对值）

```c
int abs(int j);
long int labs(long int j);
long long int llabs(long long int j);
```

这些函数计算整数 `j` 的绝对值。如果结果无法表示，则行为未定义。

>---

#### div、ldiv、lldiv （整数余商计算）

```c
div_t div(int numer, int denom);
ldiv_t ldiv(long int numer, long int denom);
lldiv_t lldiv(long long int numer, long long int denom);
```

`div` 一次操作分别计算商 `quot = numer/denom` 和余数 `rem = numer%denom`，并将结果返回。 

---
### Functions：多字节 / 宽字符转换（Multibyte/wide character conversion functions）

多字节字符函数的行为受当前区域设置的 `LC_CTYPE` 类别的影响。对于依赖于状态的编码，`mbtowc` 或 `wctomb` 函数在第一次调用该函数之前被置于其初始转换状态，并且可以通过其字符指针参数 `s` 为空指针的调用返回到该状态。如果后续调用的 `s` 不是空指针，则会根据需要更改函数的内部转换状态。内部转换状态是否具有线程存储持续时间，以及新创建的线程是否具有与当前线程在创建时相同的状态或初始转换状态，都是由实现定义的。如果编码具有状态依赖性，则以 `s` 作为空指针的调用会导致这些函数返回非零值，否则返回零值。这些函数是否避免与对同一函数的其他调用的数据竞争由实现定义。

更改 `LC_CTYPE` 类别会导致描述 `mbtowc` 和 `wctomb` 函数转换状态的内部对象具有不确定的表示。

>---
#### mbtowc （多字节到宽）

```c
int mbtowc(wchar_t * restrict pwc, const char * restrict s, size_t n);
```

`mbtowc` 将 `s` 指向其首字节的多字节字符转换成宽字符，若 `pwc` 非空则写入 `*pwc`。若 `s` 为空指针，则重置全局转换状态并确定是否使用迁移序列。`n` 表 `s` 中能被检验的字节数的限制。

每次对 `mbtowc` 的调用更新内部全局转换状态（`mbstate_t` 类型的静态对象，只为此函数所知）。若多字节编码使用迁移状态，则必须留意以避免回撤或多次扫描。任何情况下，多线程不应调用 `mbtowc` 而不同步：可用 `mbrtowc` 代替。

若 `s` 不是空指针，则返回多字节字符所含的字节数，或若 `s` 所指的首字节不组成合法多字节字符则返回 `-1`，或若 `s` 指向空字符 `'\0'` 则函数保持初始转换状态并返回零；若 `s` 是空指针，则重置内部转换状态为初始迁移状态，并若当前多字节编码非状态依赖（不使用迁移序列）则返回零，否则返回非零值。

在任何情况下，返回的值都不能大于 `n` 或 `MB_CUR_MAX` 宏的值。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
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

>---

#### wctomb、wctomb_s （宽到多字节）

> `wctomb`

```c
int wctomb(char *s, wchar_t wc);
```

`wctomb` 转换宽字符 `wc` 为多字节编码，并存储（含迁移状态）于 `s` 指向其首元素的字符数组。存储字节数不多于 `MB_CUR_MAX`。

若 `wc` 是空字符，则将空字符写入 `s`，之前可以有需要恢复初始迁移状态的任何迁移状态；若 `s` 是空指针，则此函数重设全局转换状态并确定是否使用迁移序列。

若 `s` 非空指针，则返回 `wc` 的多字节表示所含的字节数，或者若 `wc` 非合法字符则为 `-1`；若 s 是空指针，则重设内部转换状态以表示初始迁移状态，并若当前多字节编码非状态依赖（不使用迁移序列）则返回 ​0​ ，否则返回非零值。

在任何情况下，返回的值都不能大于 `MB_CUR_MAX` 宏的值。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
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

> `wctomb_s`

```c
errno_t wctomb_s(int *restrict status, char *restrict s, rsize_t ssz, wchar_t wc);
```

`wctomb_s` 同 `wctomb`，除了结果被返回到输出参数 `status`。同时在运行时检测下列错误，并调用当前安装的约束处理函数： 
  - `ssz` 小于会被写入的字节数（除非 `s` 为空）
  - `ssz` 大于 `RSIZE_MAX` （除非 `s` 为空）
  - `s` 为空指针但 `ssz` 非零

转换成功时返回为零，此情况下存储 `wc` 的多字节表示于 `s`，并存储其长度于 `*status`；或若 `s` 为空，则存储迁移序列状态于 `*status`。编码错误或运行时制约错误发生时为非零，此情况下存储 `-1` 于 `*status`。存储于 `*status` 的值决不超过 `MB_CUR_MAX`。 

>---

#### mblen （多字节长度）

```c
int mblen(const char *s, size_t n);
```

`mblen` 确定 `s` 指向其首字符的多字节字符的字节大小。除了 `mbtowc` 函数的转换状态不受影响外，它等效于调用 `mbtowc((wchar_t*)0, s, n)` 或 `mbtowc((wchar_t*)0, (const char*)0, 0)`。

若 `s` 是空指针，则 `mblen` 函数分别返回非零值或零值（如果多字节字符编码具有或不具有依赖于状态的编码）。如果 `s` 不是空指针，则 `mblen` 函数返回 0（如果 `s` 指向空字符），或者返回多字节字符中包含的字节数（如果接下来的 `n` 个或更少的字节构成有效的多字节字符），或者返回 -1（如果它们不构成有效的多字节字符）。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
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

---
### Functions：多字节 / 宽字符串转换（Multibyte/wide string conversion functions）

#### mbstowcs、mbstowcs_s （多字节到宽）

```c
size_t mbstowcs(wchar_t * restrict pwcs, const char * restrict src, size_t n);
errno_t mbstowcs_s(size_t *restrict convertedcount, 
                wchar_t *restrict pwcs, rsize_t pwcsSize, 
                const char *restrict src, rsize_t n);
```

`mbstowcs` 和 `mbstowcs_s` 转换来自从首元素为 `src` 所指的数组的多字节字符串为其宽字符表示。被转换的字符存储于 `pwcs` 所指向数组的相继元素。写入目标数组的宽字符数不多于 `n`。`mbtowc` 转换状态不受影响。

`mbstowcs` 函数返回转换成功的字符数（不包含空终止符），发生错误时返回 `(size_t)-1`。

`mbstowcs_s` 保存转换成功的字符数到 `convertedcount`，发生错误时设置 `convertedcount = (size_t)-1` 并设置 `pwcs[0] = L'\0'`，同时返回实现定义的错误码。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
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

>---


#### wcstombs、wcstombs_s （宽到多字节）

```c
size_t wcstombs(char * restrict pmbs, const wchar_t * restrict pwcs, size_t n);
errno_t wcstombs_s( size_t *restrict convertedcount, 
                    char *restrict pmbs, rsize_t pmbsSize,
                    const wchar_t *restrict pwcs, rsize_t n);
```

`wcstombs` 和 `wcstombs_s` 转换来自首元素为 `pwcs` 所指向的数组到其始于初始迁移状态的多字节表示。转换出的字符被存储于 `pmbs` 所指向的数组的相继元素。写入目标数组的字节数不多于 `n`。`wctomb` 的转换状态不受影响。

`wcstombs` 成功时，返回写入首元素为 `pmbs` 所指向的字符数组的字节数（包含任何迁移序列，但不含终止的 `'\0'`）。转换错误时（若遇到非法宽字符），返回 `(size_t)-1`。

`wcstombs_s` 成功时返回零（该情况下，写入转换成功的字节数到 `convertedcount`，排除终止零），错误时返回非零。运行时制约违规的情况下，存储 `(size_t)-1` 于 `*convertedcount` （除非 `convertedcount` 为空）并设置 `pmbs[0] = '\0'`（除非 `pmbs` 为空或 `pmbsSize` 为零或大于 `RSIZE_MAX`）。

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

### Functions：内存对齐（Alignment of memory）

#### memalignment

```c
size_t memalignment(const void *p);
```

`memalignment` 函数接受指向任何对象的指针，并返回其地址值所满足的最大对齐。这个对齐可以是扩展对齐，也可以超出显式使用 `alignas` 的实现所支持的范围。如果是这样，它将满足实现可用的所有对齐。可以将返回的值与 `alignof` 的结果进行比较，如果它大于或等于，则满足类型操作数的对齐要求。

函数指针 `p` 的对齐方式，它是 2 的幂。如果 `p` 是空指针，则返回零对齐。零对齐表示被测试的指针不能用于访问任何类型的对象。

---
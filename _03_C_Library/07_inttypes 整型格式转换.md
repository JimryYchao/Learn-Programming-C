## C 整型类型转换（Format conversion of integer types）：inttypes.h

`inttypes.h` 包含 `stdint.h` 并使用托管实现提供的附加功能对其进行扩展。它声明了用于操作最大宽度整数（`intmax_t`）和将数字字符串转换为最大宽度整数的函数，并声明了类型 `imaxdiv_t`

---
### Type

#### imaxdiv_t

- 是 `imaxdiv` 函数返回值的类型。

```c
typedef struct
{
    intmax_t quot;  // 商
    intmax_t rem;   // 余数
} imaxdiv_t;
```

---
### Macros：格式化输出

每个类对象宏都可以展开为对应类型的转换说明符的字符串字面量，适用于在转换相应的整数类型时，在格式化输入和输出函数的 format 参数中使用。

#### 用于格式化输出有符号整数的转换说明符

> *PS：N 表示整型的类型，8、16、32、64... （`PRIdN` N = 8，表示为 `PRIdN`，对应类型 `int8_t`）。* 

- `%d` 格式化输出转换说明符。

```c
// 映射 intN_t
#define PRId8        "hhd"
#define PRId16       "hd"
#define PRId32       "d"
#define PRId64       "lld"

// 映射 int_leastN_t
#define PRIdLEAST8   PRId8
#define PRIdLEAST16  PRId16
#define PRIdLEAST32  PRId32
#define PRIdLEAST64  PRId64

// 映射 int_fastN_t
#define PRIdFAST8    PRId8
#define PRIdFAST16   PRId32
#define PRIdFAST32   PRId32
#define PRIdFAST64   PRId64

// other macros
#define PRIdMAX      PRId64
#ifdef _WIN64
    #define PRIdPTR  PRId64
#else
    #define PRIdPTR  PRId32
#endif
```

- `%i` 格式化输出转化说明符。

```c
#define PRIi8        "hhi"
#define PRIi16       "hi"
#define PRIi32       "i"
#define PRIi64       "lli"

#define PRIiLEASTN   PRIiN
#define PRIiFASTN    PRIiN

#define PRIiMAX      PRIi64

#ifdef _WIN64
    #define PRIiPTR  PRIi64
#else
    #define PRIiPTR  PRIi32
#endif
```

<br>

#### 用于格式化输出无符号整数的转换说明符

- 无符号八进制整数转换说明符（`%o`）。

```c
#define PRIo8        "hho"
#define PRIo16       "ho"
#define PRIo32       "o"
#define PRIo64       "llo"

#define PRIoLEASTN   PRIoN
#define PRIoFASTN    PRIoN

#define PRIoMAX      PRIo64
#define PRIoPTR 
```

- 无符号十进制整数转换说明符（`%u`）。

```c
#define PRIu8        "hhu"
#define PRIu16       "hu"
#define PRIu32       "u"
#define PRIu64       "llu"

#define PRIuLEASTN   PRIuN
#define PRIuFASTN    PRIuN

#define PRIuMAX      PRIu64
#define PRIuPTR      
```

- 无符号十六进制整数转换说明符（`%x` / `%X`）。

```c
// 小写格式化
#define PRIx8        "hhx"
#define PRIx16       "hx"
#define PRIx32       "x"
#define PRIx64       "llx"

#define PRIxLEASTN   PRIxN
#define PRIxFASTN    PRIxN

#define PRIxMAX      PRIx64
#define PRIxPTR

// 大写格式化
#define PRIX8        "hhX"
#define PRIX16       "hX"
#define PRIX32       "X"
#define PRIX64       "llX"

#define PRIXLEASTN   PRIXN
#define PRIXFASTN    PRIXN

#define PRIXMAX      PRIX64
#define PRIXPTR
```

<br>

#### 格式化输出案例

```c
#include <stdio.h>
#include <inttypes.h>

#define printf(format, number) printf(#number "[" #format "] = %" format "\n", number)

int main()
{
	// 有符号整数输出
	puts("Signed Integers >>> ");
	printf(PRId8, 12345);
	printf(PRId16, -12345);
	printf(PRId32, 12345);
	printf(PRId64, -12345678987654321LL);

	printf(PRIi8, 12345);
	printf(PRIi32, -12345);
	
	printf(PRIdLEAST32, 12345);
	printf(PRIdFAST32, -12345);

	// 无符号整数输出
	puts("\nUnsigned Integers >>> ");
	printf(PRIo32, 98765);
	printf(PRIu32, 98765);
	printf(PRIx32, 98765);
	printf(PRIX32, 98765);

	printf(PRIoLEAST32, 98765);
	printf(PRIoFAST32, 98765);

	return 0;
}
/*
Signed Integers >>>
12345[PRId8] = 57
-12345[PRId16] = -12345
12345[PRId32] = 12345
-12345678987654321LL[PRId64] = -12345678987654321
12345[PRIi8] = 57
-12345[PRIi32] = -12345
12345[PRIdLEAST32] = 12345
-12345[PRIdFAST32] = -12345

Unsigned Integers >>>
98765[PRIo32] = 300715
98765[PRIu32] = 98765
98765[PRIx32] = 181cd
98765[PRIX32] = 181CD
98765[PRIoLEAST32] = 300715
98765[PRIoFAST32] = 300715
*/
```

---
### Macros：格式化输入

#### 用于格式化输入有符号整数的转换说明符

> *PS：N 表示整型的类型，8、16、32、64... （`intN_t` N = 8，表示为 `int8_t` 类型）。* 

- `%d` 格式化输入转换说明符。

```c
#define SCNd8        "hhd"
#define SCNd16       "hd"
#define SCNd32       "d"
#define SCNd64       "lld"

#define SCNdLEASTN   SCNdN
#define SCNdFASTN    SCNdN

#define SCNdMAX      SCNd64
#define SCNdPTR
```

- `%i` 格式输入转换说明符。

```c
#define SCNi8        "hhi"
#define SCNi16       "hi"
#define SCNi32       "i"
#define SCNi64       "lli"

#define SCNiLEASTN   SCNiN
#define SCNiFASTN    SCNiN

#define SCNiMAX      SCNi64
#define SCNiPTR
```

<br>

#### 用于格式化输入无符号整数的转换说明符

- 无符号八进制整数（`%o`）。

```c
#define SCNo8        "hho"
#define SCNo16       "ho"
#define SCNo32       "o"
#define SCNo64       "llo"

#define SCNoLEASTN   SCNoN
#define SCNoFASTN    SCNoN

#define SCNoMAX      SCNo64
#define SCNoPTR
```

- 无符号十进制整数（`%u`）。

```c
#define SCNu8        "hhu"
#define SCNu16       "hu"
#define SCNu32       "u"
#define SCNu64       "llu"

#define SCNuLEASTN   SCNuN
#define SCNuFASTN    SCNuN

#define SCNuMAX      SCNu64
#define SCNuPTR
```

- 无符号十六进制整数（`%x`）。

```c
#define SCNx8        "hhx"
#define SCNx16       "hx"
#define SCNx32       "x"
#define SCNx64       "llx"

#define SCNxLEASTN   SCNxN
#define SCNxFASTN    SCNxN

#define SCNxMAX      SCNu64
#define SCNxPTR
```

---
### Functions：最大宽度整数数学拓展

#### imaxabs （求绝对值）

```c
intmax_t imaxabs(intmax_t j); 
```

- 计算整数 `j` 的绝对值。


<br>

#### imaxdiv （计算商余）

```c
imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom);
```

- `imaxdiv` 在一次操作中计算 `numer / denom` 和 `numer % denom`。

```c
#include <stdio.h>
#include <inttypes.h>


int main()
{
	intmax_t numer = 9876543210;
	intmax_t denom = 1234567890;
	imaxdiv_t rt = imaxdiv(numer, denom);

	printf("%" PRIiMAX " / " "%" PRIiMAX " = "
		"%" PRIiMAX " ... "
		"%" PRIiMAX,
		numer, denom, rt.quot, rt.rem);

	return 0;
}
/*
9876543210 / 1234567890 = 8 ... 90
*/
```

---
### Functions：数字字符转换函数拓展

#### strtoimax、wcstoimax （将字符串转换为最大有符号整数）

- 函数转换字符串为数值的过程中，如果不能执行转换，返回零。如果正确值在可表示的值范围之外，则返回该函数返回类型的极值（`INTMAX_MAX` or `INTMAX_MIN`），且设置 `errno` 为 `ERANGE`。

```c
intmax_t strtoimax(
    const char * restrict nptr, 
    char ** restrict endptr, 
    int base
    );

intmax_t wcstoimax(
    const wchar_t * restrict nptr,
    wchar_t ** restrict endptr,
    int base
    );
```

- `strtoimax` 等价于 `strtol`、`strtoll` 函数。
- `wcstoimax` 等价于 `wcstol`、`wcstoll` 函数。

```c
#include <stdio.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>

#define STRTOIMAX(str, endptr, base) printf("[" #str "] to Int_max = %lld\n", \
        strtoimax(str, endptr, base))

int main()
{

    char *endptr;

    STRTOIMAX(" -123junk", &endptr, 10); /* base 10                    */
    STRTOIMAX("11111111", &endptr, 2);   /* base 2                     */
    STRTOIMAX("XyZ", &endptr, 36);       /* base 36                    */
    STRTOIMAX("010", &endptr, 0);        /* octal auto-detection       */
    STRTOIMAX("10", &endptr, 0);         /* decimal auto-detection     */
    STRTOIMAX("0x10", &endptr, 0);       /* hexadecimal auto-detection */

    /* range error                */
    /* INT64_MAX + 1 --> LONG_MAX */
    // INT64_MAX = 9223372036854775807LL6
    errno = 0;
    puts("\nOut-of-Range test:");
    STRTOIMAX("9223372036854775808", &endptr, 10);
    printf("errno = %s\n", strerror(errno));
    return 0;
}
/*
[" -123junk"] to Int_max = -123
["11111111"] to Int_max = 255
["XyZ"] to Int_max = 44027
["010"] to Int_max = 8
["10"] to Int_max = 10
["0x10"] to Int_max = 16

Out-of-Range test:
["9223372036854775808"] to Int_max = 9223372036854775807
errno = Result too large
*/
```

<br> 

#### strtoumax、wcstoumax （将字符串转换为最大无符号整数）

- 函数转换字符串为数值的过程中，如果不能执行转换，返回零。如果正确值在可表示的值范围之外，则返回 `UINTMAX_MAX`，且设置 `errno` 为 `ERANGE`。

```c
uintmax_t strtoumax(
    const char * restrict nptr,
    char ** restrict endptr,
    int base
    );

uintmax_t wcstoumax(
    const wchar_t * restrict nptr,
    wchar_t ** restrict endptr,
    int base
    );
```

- `strtoumax` 等价于 `strtoul`、`strtoull` 函数。
- `wcstoumax` 等价于 `wcstoul`、`wcstoull` 函数。

---
## C 整型类型转换（Format conversion of integer types）：inttypes.h

```c
#define __STDC_VERSION_INTTYPES_H__     202311L
```

`inttypes.h` 包含头文件 `stdint.h` 并使用托管实现提供的附加功能对其进行扩展。它声明了用于操作最大宽度整数（`intmax_t`）和将数字字符串转换为最大宽度整数的函数，并声明了类型 `imaxdiv_t`

---
### Type

#### imaxdiv_t

结构类型 `imaxdiv_t` 是 `imaxdiv` 函数返回值的类型。对于中声明的每种类型 `stdint.h`，它都为转换说明符定义了相应的宏，以便与格式化的输入/输出函数一起使用。

```c
typedef struct
{
    intmax_t quot;  // 商
    intmax_t rem;   // 余数
} imaxdiv_t;
```

---
### Macros：格式说明宏

以下每个类对象宏都可以展开为对应类型的转换说明符的字符串字面量，适用于在转换相应的整数类型时，在格式化输入和输出函数的 `format` 格式参数中使用。这些宏名的一般形式为 `PRI`（`fprintf` 和 `fwprintf` 家族的字符串字面值）或 `SCN`（`fscanf` 和 `fwscanf` 家族的字符串字面值），后跟转换说明符，后跟相应类型的名称。这些名称中，*`N`* 描述对应类型的宽度，*`N`* 可以是 8，16，32，64。例如 `PRIdFAST32` 可以在格式字符串中用于打印 `int_fast32_t` 类型的整数值。

>---
#### 格式化输出

| Format                     | Conversion | Macros                                                                                                               |
| :------------------------- | :--------- | :------------------------------------------------------------------------------------------------------------------- |
| 有符号整数                 | `%d`       | <code>PRId<em>N</em></code>、<code>PRIdLEAST<em>N</em></code>、<code>PRIdFAST<em>N</em></code>、`PRIdMAX`、`PRIdPTR` |
| 有符号整数                 | `%i`       | <code>PRIi<em>N</em></code>、<code>PRIiLEAST<em>N</em></code>、<code>PRIiFAST<em>N</em></code>、`PRIiMAX`、`PRIiPTR` |
| 无符号二进制整数           | `%b`       | <code>PRIb<em>N</em></code>、<code>PRIbLEAST<em>N</em></code>、<code>PRIbFAST<em>N</em></code>、`PRIbMAX`、`PRIbPTR` |
| 无符号八进制整数           | `%o`       | <code>PRIo<em>N</em></code>、<code>PRIoLEAST<em>N</em></code>、<code>PRIoFAST<em>N</em></code>、`PRIoMAX`、`PRIoPTR` |
| 无符号十进制整数           | `%u`       | <code>PRIu<em>N</em></code>、<code>PRIuLEAST<em>N</em></code>、<code>PRIuFAST<em>N</em></code>、`PRIuMAX`、`PRIuPTR` |
| 无符号十六进制整数（小写） | `%x`       | <code>PRIx<em>N</em></code>、<code>PRIxLEAST<em>N</em></code>、<code>PRIxFAST<em>N</em></code>、`PRIxMAX`、`PRIxPTR` |
| 无符号十六进制整数（大写） | `%X`       | <code>PRIX<em>N</em></code>、<code>PRIXLEAST<em>N</em></code>、<code>PRIXFAST<em>N</em></code>、`PRIXMAX`、`PRIXPTR` |
| 无符号二进制整数（可选）           | `%B`       | <code>PRIB<em>N</em></code>、<code>PRIBLEAST<em>N</em></code>、<code>PRIBFAST<em>N</em></code>、`PRIBMAX`、`PRIBPTR` |

```c
// 映射 intN_t, %d
#define PRId8        "hhd"
#define PRId16       "hd"
#define PRId32       "d"
#define PRId64       "lld"
```

> *格式化输出案例*

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

>---
#### 格式化输入

| Format | Conversion | Macros |
| :----- | :--------- | :----- |
|有符号整数|`%d`|<code>SCNd<em>N</em></code>、<code>SCNdLEAST<em>N</em></code>、<code>SCNdFAST<em>N</em></code>、`SCNdMAX`、`SCNdPTR`|
|有符号整数|`%i`|<code>SCNi<em>N</em></code>、<code>SCNiLEAST<em>N</em></code>、<code>SCNiFAST<em>N</em></code>、`SCNiMAX`、`SCNiPTR`|
|无符号二进制整数|`%b`|<code>SCNb<em>N</em></code>、<code>SCNbLEAST<em>N</em></code>、<code>SCNbFAST<em>N</em></code>、`SCNbMAX`、`SCNbPTR`|
|无符号八进制整数|`%o`|<code>SCNo<em>N</em></code>、<code>SCNoLEAST<em>N</em></code>、<code>SCNoFAST<em>N</em></code>、`SCNoMAX`、`SCNoPTR`|
|无符号十进制整数|`%u`|<code>SCNu<em>N</em></code>、<code>SCNuLEAST<em>N</em></code>、<code>SCNuFAST<em>N</em></code>、`SCNuMAX`、`SCNuPTR`|
|无符号十六进制整数|`%x`|<code>SCNx<em>N</em></code>、<code>SCNxLEAST<em>N</em></code>、<code>SCNxFAST<em>N</em></code>、`SCNxMAX`、`SCNxPTR`|

```c
// 映射 intN_t, %d
#define SCNd8        "hhd"
#define SCNd16       "hd"
#define SCNd32       "d"
#define SCNd64       "lld"
```

---
### Functions：最大宽度整数数学拓展

#### imaxabs （求绝对值）

```c
intmax_t imaxabs(intmax_t j); 
```

`imaxabs` 函数计算整数 `j` 的绝对值。如果结果无法表示，则行为未定义。

>---

#### imaxdiv （计算商余）

```c
imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom);
```

`imaxdiv` 函数在一次操作中计算 `numer / denom` 和 `numer % denom`。函数返回一个 `imaxdiv_t` 类型的结构体，结构体包含商和余数，它们的类型都是 `intmax_t`。

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

>---
#### strtoimax、wcstoimax （将字符串转换为最大有符号整数）

```c
intmax_t strtoimax(const char * restrict nptr, char ** restrict endptr, int base);
intmax_t wcstoimax(const wchar_t * restrict nptr, wchar_t ** restrict endptr, int base);
```

`strtoimax` 函数等效于 `strtol`、`strtoll` 函数。`wcstoimax` 函数等效于 `wcstol`、`wcstoll` 函数。

函数转换字符串为数值的过程中，如果不能执行转换，返回零。如果正确值在可表示的值范围之外，则返回该函数返回类型的极值（`INTMAX_MAX` or `INTMAX_MIN`），并且设置 `errno` 为 `ERANGE`。

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

>--- 

#### strtoumax、wcstoumax （将字符串转换为最大无符号整数）


```c
uintmax_t strtoumax(const char * restrict nptr, char ** restrict endptr, int base);
uintmax_t wcstoumax(const wchar_t * restrict nptr, wchar_t ** restrict endptr, int base);
```

`strtoumax` 函数等效于 `strtoul`、`strtoull` 函数。`wcstoumax` 等效于 `wcstoul`、`wcstoull` 函数。

函数转换字符串为数值的过程中，如果不能执行转换，返回零。如果正确值在可表示的值范围之外，则返回 `UINTMAX_MAX`，并且设置 `errno` 为 `ERANGE`。

---
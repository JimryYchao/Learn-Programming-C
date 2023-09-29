## C 扩展多字节和宽字符工具（Extended multibyte and wide character utilities）：wchar.h

`wchar.h` 提供一些宽字符整型的数据类型和对应的字符工具函数。

---
### Types

```c
typedef short    wchar_t                // 保有任何合法宽字符的整数类型
typedef unsigned long long    size_t    // 无符号整数类型，表示类型大小
```

#### mbstate_t

```c
typedef struct
{ 
    unsigned long _Wchar;
    unsigned short _Byte;
    unsigned short _State;
} mbstate_t;
```

-  `mbstate_t` 可以保存在多字节字符序列和宽字符序列之间转换所需的转换状态信息。

<br>

#### wint_t

```c
typedef unsigned short   wint_t;
```

- `wint_t` 可以保存与扩展字符集成员相对应的任何值，以及至少一个不与扩展字符集成员相对应的值。

---
### Macros

```c
#define NULL  ((void *)0)
#define WCHAR_MIN  0x0000
#define WCHAR_MAX  0xffff
```

<br>

#### WEOF

```c
#define WEOF  ((wint_t)(0xFFFF))
```

- `WEOF` 扩展为 `wint_t` 类型的常量表达式，其值不对应于扩展字符集的任何成员。它被 `wchar.h` 中的几个函数接受（并返回）来表示文件结束，即不再有来自流的输入。它还用作不对应于扩展字符集的任何成员的宽字符值。

---
### Functions：格式化宽字符输入与输出（Formatted wide character input/output functions）

- 参考 `stdio.h` 中的标准输入和输出函数，以下提供对应的宽字符版本。

#### 格式化宽字符输出函数

> 打印格式化宽字符输出到 `stdout`、文件流或缓冲区

```c
// printf
int wprintf(const wchar_t *restrict format, ...);
int wprintf_s(const wchar_t *restrict format, ...);
// fprintf
int fwprintf(FILE * restrict stream, const wchar_t * restrict format, ...);
int fwprintf_s(FILE *restrict stream, const wchar_t *restrict format, ...);
// sprintf
int swprintf(wchar_t *restrict buffer, size_t bufsz, const wchar_t *restrict format, ...);
int swprintf_s(wchar_t *restrict buffer, rsize_t bufsz, const wchar_t* restrict format, ...);
// snprintf
int _snwprintf_s(wchar_t * restrict s, rsize_t n, const wchar_t * restrict format, ...)
```

> 打印格式化宽字符输出到 `stdout`、文件流或缓冲区（使用可变参数列表）

```c
// vprintf
int vwprintf(const wchar_t *restrict format, va_list vlist);
int vwprintf_s(const wchar_t *restrict format, va_list vlist);
// vfwprintf
int vfwprintf(FILE *restrict stream, const wchar_t *restrict format, va_list vlist);
int vfwprintf_s(FILE * restrict stream, const wchar_t *restrict format, va_list vlist);
// vswprintf
int vswprintf(wchar_t *restrict buffer, size_t bufsz, const wchar_t *restrict format, va_list vlist );
int vswprintf_s(wchar_t *restrict buffer, rsize_t bufsz, const wchar_t * restrict format, va_list vlist);
// vsnwprintf
int _vsnwprintf_s(wchar_t *restrict buffer, rsize_t bufsz, const wchar_t *restrict format, va_list vlist);
```

<br>

#### 格式化宽字符输入函数

> 从 `stdin`、文件流或缓冲区读取格式化宽字符输入

```c
// scanf
int wscanf(const wchar_t *restrict format, ...);
int wscanf_s(const wchar_t *restrict format, ...);
// fscanf
int fwscanf(FILE *restrict stream, const wchar_t *restrict format, ...);
int fwscanf_s(FILE *restrict stream, const wchar_t *restrict format, ...);
// sscanf
int swscanf(const wchar_t *buffer, const wchar_t *format, ...);
int swscanf_s(const wchar_t *restrict s, const wchar_t *restrict format, ...);
```

> 从 `stdin`、文件流或缓冲区读取格式化宽字符输入（使用可变参数列表）

```c
// vscanf
int vwscanf(const wchar_t *restrict format, va_list vlist);
int vwscanf_s(const wchar_t *restrict format, va_list vlist);
// vfscanf
int vfwscanf(FILE *restrict stream, const wchar_t *restrict format, va_list vlist);
int vfwscanf_s(FILE *restrict stream, const wchar_t *restrict format, va_list vlist);
// vsscanf
int vswscanf(const wchar_t *restrict buffer, const wchar_t *restrict format, va_list vlist);
int vswscanf_s(const wchar_t *restrict buffer, const wchar_t *restrict format, va_list vlist);
```

---
### Functions：宽字符输入与输出（Wide character input/output functions）

- 参考 `stdio.h` 中的标准输入和输出函数，以下提供对应的宽字符版本。

#### 宽字符输出函数

> 字符输出

```c
wint_t putwc(wchar_t ch, FILE *stream);       // putc
wint_t fputwc(wchar_t ch, FILE *stream);      // fputc
wint_t putwchar(wchar_t ch);                  // putchar
```

> 字符串输出

```c
int fputws(const wchar_t * restrict str, FILE * restrict stream);   // fputs
```



#### 宽字符输入函数

> 字符输入

```c
wint_t getwc(FILE *stream);         // getc
wint_t fgetwc(FILE *stream);        // fgetc
wint_t getwchar(void);              // getchar
```

> 字符串输入

```c
wchar_t *fgetws(wchar_t * restrict str, int count, FILE * restrict stream);  // fgets
```

<br>

#### ungetwc

```c
wint_t ungetwc(wint_t ch, FILE *stream);   // ungetc
```

<br>

#### fwide （流方向）

```c
int fwide(FILE* stream, int mode);
```

- `fwide` 函数的作用是确定 `stream` 所指向的流的方向：
  - 如果 `mode` 大于 0，则该函数首先尝试使流面向宽。
  - 如果 `mode` 小于 0，则函数首先尝试使流面向字节。
  - 如果 `mode` 为 0，函数不改变流的方向，只查询流的当前面向。

- 如果调用后流具有宽方向，则 `fwide` 函数返回一个大于 0 的值，如果流具有字节方向则返回一个小于 0 的值，如果流没有方向则返回 0。
- 此函数的当前版本不符合 C 标准。此函数当前仅返回 `mode`。

---
### Functions：通用宽字符串工具（General wide string utilities）

#### 宽字符串数字转换函数

> 转换为浮点数

```c
double wcstod(const wchar_t * restrict nptr, wchar_t ** restrict endptr);       // strtod
float wcstof(const wchar_t * restrict nptr, wchar_t ** restrict endptr);        // strtof
long double wcstold(const wchar_t * restrict nptr, wchar_t ** restrict endptr); // strtold
```

> 转换为整数

```c
// 转换为有符号整数值
long wcstol(const wchar_t * str, wchar_t ** restrict str_end, int base);                      // strtol
long long wcstoll(const wchar_t * restrict str, wchar_t ** restrict str_end, int base);       // strtoll
// 转换为无符号整数值
unsigned long wcstoul(const wchar_t * restrict str, wchar_t ** restrict str_end, int base);   // strtoul
unsigned long long wcstoull(const wchar_t * restrict str, wchar_t ** restrict str_end, int base); // strtoull
```

<br>

#### 宽字符串复制函数

> 字符数组复制

```c
// 复制一定数量的字符数组（不可重叠）
wchar_t *wmemcpy(wchar_t *restrict dest, const wchar_t *restrict src, size_t count);   // memcpy
errno_t wmemcpy_s(wchar_t *restrict dest, rsize_t destsz, const wchar_t *restrict src, rsize_t count);  // wmemcpy_s
// 移动一定数目的字符数组（可重叠）
wchar_t* wmemmove(wchar_t* dest, const wchar_t* src, size_t count);                    // memmove
errno_t wmemmove_s(wchar_t *dest, rsize_t destsz, const wchar_t *src, rsize_t count);  // memmove_s
```

> 字符串复制（追加宽空字符串）

```c
// 复制宽字符串
wchar_t *wcscpy(wchar_t *restrict dest, const wchar_t *restrict src);                   // strcpy
errno_t wcscpy_s(wchar_t *restrict dest, rsize_t destsz, const wchar_t *restrict src);  // strcpy_s
// 复制一定长的宽字符串
wchar_t *wcsncpy(wchar_t *restrict dest, const wchar_t *restrict src, size_t n);        // strncpy
errno_t wcsncpy_s(wchar_t *restrict dest, rsize_t destsz, const wchar_t *restrict src, rsize_t n);  // strncpy_s
```

<br>

#### 宽字符串拼接函数

```c
// 尾部拼接宽字符串
wchar_t *wcscat(wchar_t *restrict dest, const wchar_t *restrict src);                   // strcat
errno_t wcscat_s(wchar_t *restrict dest, rsize_t destsz, const wchar_t *restrict src);  // strcat_s
// 尾部拼接一定长度的宽字符串
wchar_t *wcsncat(wchar_t *restrict dest, const wchar_t *restrict src, size_t count);    // strncat
errno_t wcsncat_s(wchar_t *restrict dest, rsize_t destsz, const wchar_t *restrict src, rsize_t count);  // strncat_s
```

<br>

#### 宽字符串比较函数

```c
// 比较数组中一定数目的宽字符
int wmemcmp(const wchar_t *lhs, const wchar_t *rhs, size_t count);  // memcmp
// 比较字符串
int wcscmp(const wchar_t *lhs, const wchar_t *rhs);                 // strcmp
int wcsncmp(const wchar_t* lhs, const wchar_t* rhs, size_t count);  // strncmp
// 根据本地环境比较字符串
int wcscoll(const wchar_t *lhs, const wchar_t *rhs);                // strcoll
// 根据本地环境变换字符串
size_t wcsxfrm(wchar_t* restrict dest, const wchar_t* restrict src, size_t count);  // strxfrm
```

<br>

#### 宽字符检索函数

```c
// 数组中字符首次出现 
wchar_t *wmemchr(const wchar_t *ptr, wchar_t ch, size_t count);     // memchr
// 字符串中字符首次出现
wchar_t* wcschr(const wchar_t* str, wchar_t ch);                    // strchr
// 字符串中字符最后出现
wchar_t* wcsrchr(const wchar_t* str, wchar_t ch);                   // strrchr
// 字符串中出现另一个字符串的位置
wchar_t* wcsstr(const wchar_t* dest, const wchar_t* src);           // strstr
// 字符集中内字符在字符串中首次出现的位置
wchar_t* wcspbrk(const wchar_t* dest, const wchar_t* str);          // strpbrk
// 包含在字符集中字符的起始连续长度
size_t wcsspn(const wchar_t* dest, const wchar_t* src);             // strspn
// 不包含在字符集内的字符的起始连续长度
size_t wcscspn(const wchar_t* dest, const wchar_t* src);            // strcspn
// 字符串分割，查找分割字符的位置并分割字符串
wchar_t *wcstok(wchar_t * restrict str, const wchar_t * restrict delim, wchar_t **restrict ptr);   // strtok
wchar_t *wcstok_s(wchar_t *restrict str, rsize_t *restrict strmax,          // strtok_s
                  const wchar_t *restrict delim, wchar_t **restrict ptr);
```

<br>

#### 宽字符工具函数

```c
// 字符串长度
size_t wcslen(const wchar_t *str);                             // strlen
size_t wcsnlen_s(const wchar_t *str, size_t strsz);            // strlen_s
// 复制一定数目的宽字符到数组中
wchar_t *wmemset(wchar_t *dest, wchar_t ch, size_t count);     // memset
```

---
### Function：格式化时间宽字符（Wide character time conversion functions）

#### wcsftime

```c
size_t wcsftime(wchar_t *strDst, size_t maxsize, const wchar_t *format, const struct tm *timeptr);  // strftime
```

- `wcsftime` 函数将来自给定的日历时间 `timeptr` 的日期和时间信息，按照格式字符串 `format`，转换成空终止宽字符串 `strDst`。最多写入 `maxsize` 个宽字符。

```c
#include <stdio.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

int main(void)
{
	wchar_t buff[40];
	struct tm my_time = { 0 };
	time_t curtime = time(NULL);
	errno_t err = gmtime_s(&my_time, &curtime);
	if (err)
		perror("Time");
	else
	{
		if (wcsftime(buff, sizeof buff, L"%A %c", &my_time)) 
			printf("UTC: %ls\n", buff);
		else puts("wcsftime failed");

		setlocale(LC_ALL, "ja_JP.utf8");

		if (wcsftime(buff, sizeof buff, L"%A %c", &my_time))
			printf("UTC: %ls\n", buff);
		else puts("wcsftime failed");
	}
}
/*
UTC: Thursday Thu Sep 28 17:11:08 2023
UTC: 木曜日 2023/09/28 17:11:08
*/
```

---
### Functions：扩展多字节/宽字符转换（Extended multibyte/wide character conversion utilities）

#### btowc、wctob （单字节/宽字符转换）

```c
wint_t btowc(int ch);      // 加宽单字节到宽字符
int wctob(wint_t ch);      // 窄化宽字符到单字节
```

- `btowc` 加宽单字节字符 `ch`（转译为 `unsigned char`）为宽字符。若 `ch` 为 `EOF` 则返回 `WEOF`。成功时返回对应的宽字符表示，否则返回 `WEOF`。
* 若宽字符 `ch` 的多字节字符等价在初始迁移状态为单字节，函数 `wctob` 将其转换为单字节并返回。失败时返回 `EOF`。

```c
#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#include <assert.h>

void try_narrowing(wchar_t c)
{
    int cn = wctob(c);
    if (cn != EOF)
        printf("%#x narrowed to %#x\n", c, cn);
    else
        printf("%#x could not be narrowed\n", c);
}

int main(void)
{
    char* utf_locale_present = setlocale(LC_ALL, "th_TH.utf8");
    assert(utf_locale_present);
    puts("In Thai UTF-8 locale:");
    try_narrowing(L'a');
    try_narrowing(L'๛');

    char* tis_locale_present = setlocale(LC_ALL, "th_TH");
    printf("%s\n", tis_locale_present);
    assert(tis_locale_present);
    puts("In Thai default locale:");
    try_narrowing(L'a');
    try_narrowing(L'๛');
}
/*
In Thai UTF-8 locale:
0x61 narrowed to 0x61
0xe5b could not be narrowed
th_TH
In Thai default locale:
0x61 narrowed to 0x61
0xe5b narrowed to 0xfffffffb
*/
```

<br>

#### mbsinit （检查 mbstate_t）

```c
int mbsinit(const mbstate_t* ps);
```

- `mbsinit` 函数检查的 `mbstate_t` 对象是否描述了初始转换状态。如果 `ps` 是空指针，或者引用的对象描述了初始转换状态，则 `mbsinit` 函数返回非零，否则返回 0。
* `mbstate_t` 表示任何能出现于实现定义的受支持多字节编码规则集合的转换状态。`mbstate_t` 的零初始化值表示初始转换状态。`mbstate_t` 的可行实现是一个结构体类型，保有表示不完整多字节字符的数组、指示数组中已处理字节数和当前迁移状态的表示。由于可能的数据竞争，不从多个线程以空指针为 `mbstate_t*` 参数调用下列函数而不同步：`mbrlen`、`mbrtowc`、`mbsrtowcs`、`mbtowc`、`wcrtomb`、`wcsrtombs`、`wctomb`。

```c
#include <locale.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>

int main(void)
{
    // 允许mbrlen()作用于UTF-8多字节字符串
    setlocale(LC_ALL, "en_US.utf8");
    // UTF-8 narrow multibyte encoding
    const char* str = u8"水";   // 或 u8"\u6c34" 或 "\xe6\xb0\xb4"
    static mbstate_t mb;        // 零初始化
    (void)mbrlen(&str[0], 1, &mb);
    if (!mbsinit(&mb)) {
        printf("After processing the first 1 byte of %s,\n"
            "the conversion state is not initial\n\n", str);
    }
    (void)mbrlen(&str[1], strlen(str), &mb);
    if (mbsinit(&mb)) {
        printf("After processing the remaining 2 bytes of %s,\n"
            "the conversion state is initial conversion state\n", str);
    }
}
/*
After processing the first 1 byte of 水,
the conversion state is not initial

After processing the remaining 2 bytes of 水,
the conversion state is initial conversion state
*/
```

<br>

#### mbrtowc、wcrtomb （定状态多字节/宽字节字符转换）

> `mbrtowc` 多字节到宽字符

```c
size_t mbrtowc(wchar_t * restrict pwc, const char * restrict s, 
               size_t n, mbstate_t * restrict ps);
```

- `mbrtowc` 函数转换窄多字节字符为宽字符：
  - 当 `s` 不为空时，则从 `s` 所指的字节起，最多检查只 `n` 个字符，以确定完成下个多字节字符（包含任何迁移序列）的字节数。转换成功时存储于 `*pwc`。
  - 当 `s` 是空指针，则忽略 `n` 和 `pwc` 的值，等价于 `mbrtowc(NULL,"",1,ps)`。
  - 若产生的宽字符是空字符，则存储与 `*ps` 的转换状态为初始迁移状态。

* `mbrtowc` 返回值解析：
  - `0`：转换的字符为空字符。
  - `[1...n]`：成功转换的多字节字符的字节数。
  - `(size_t)(-2)`：如果接下来的 `n` 个字节构成一个不完整（但可能有效）的多字节字符，并且所有 `n` 个字节都已被处理。不写入 `pwc`。
  - `(size_t)(-1)`：如果发生编码错误，在这种情况下，下一个 `n` 或更少的字节不会构成完整有效的多字节字符（不存储任何值）。宏 `EILSEQ` 的值存储在 `errno` 中，置转换状态 `*ps` 的值为未指定。

```c
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>

// 打印窄字符串为宽字符串
void print_mb(const char* ptr)
{
    mbstate_t state;
    memset(&state, 0, sizeof state);
    const char* end = ptr + strlen(ptr);
    int len;
    wchar_t wc;
    while ((len = mbrtowc(&wc, ptr, end - ptr, &state)) > 0) {
        wprintf(L"Next %d bytes are the character %lc \n", len, wc);
        ptr += len;
    }
}
int main(void)
{
    setlocale(LC_ALL, "en_US.utf8");
    // UTF-8 窄多字符编码
    print_mb(u8"z\u00df\u6c34\U0001F34C"); // 或 u8"zß水🍌"
}
```

> `wcrtomb`、`wcrtomb_s` 宽字符到多字节

```c
size_t wcrtomb(char *restrict s, wchar_t wc, mbstate_t *restrict ps);
errno_t wcrtomb_s(size_t *restrict retval, char *restrict s, rsize_t ssz,
                  wchar_t wc, mbstate_t *restrict ps);
```

- `wcrtomb` 函数转换宽字符为其窄多字节表示：
  - 若 `s` 不是空指针，则函数检测存储 `wc` 的多字节字符表示所需的字节数（包含任何迁移序列，并考虑当前多字节转换状态 `*ps`，并存储多字节字符表示于 `s` 所指向的字符数组，按需更新 `*ps` 。此函数至多能写入 `MB_CUR_MAX` 字节。
  - 若 `s` 为空指针，则调用等价于对某内部缓冲区 `buf` 的 `wcrtomb(buf, L'\0', ps)`。
  - 若 `wc` 是空宽字符 `L'\0'`，则存储空字节，前接任何恢复到初始迁移状态所需的迁移序列，并更新转换状态参数 `*ps` 以表示其初始迁移状态。
  - 若定义环境宏 `__STDC_ISO_10646__`，则 `wchar_t` 类型的值与 `Unicode` 要求集（典型地为 `UTF-32` 编码）中字符的短标识符相同；否则它是实现定义的。任何情况下，此函数所用的多字节字符编码为当前活跃的 C 本地环境所指定。
- `wcrtomb` 转换成功时，返回写入首元素为 `s` 所指向的字符数组的字节数（包含任何迁移序列）。失败时（若 `wc` 不是合法宽字符），返回 `(size_t)-1`，存储 `EILSEQ` 于 `errno`，并使 `*ps` 留在未指定状态。


* `wcrtomb_s` 同 `wcrtomb`。若 `s` 为空指针，则调用等价于用内部变量 `retval` 和 `buf`（其大小大于 `MB_CUR_MAX`）的 `wcrtomb_s(&retval, buf, sizeof buf, L'\0', ps)`。返回结果（转换成功字符数）于输出参数 `retval`。
* `wcrtomb_s` 成功时返回零。失败时返回非零，该情况下，设置 `s[0]` 为 `'\0'` 并设置 `*retval` 为 `(size_t)-1`（除非 `retval` 为空）。

```c
#define _CRT_SECURE_NO_WARNINGS 0 // 0
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>

int main(void)
{
	setlocale(LC_ALL, "en_US.utf8");
	mbstate_t state;
	memset(&state, 0, sizeof state);
	wchar_t in[] = L"zß水"; // 或 "z\u00df\u6c34"
	size_t in_sz = sizeof in / sizeof * in;

	printf("Processing %zu wchar_t units: [ ", in_sz);
	for (size_t n = 0; n < in_sz; ++n) printf("%#x ", in[n]);
	puts("]");

	char* out = calloc(MB_CUR_MAX * in_sz, sizeof(char));
	char* p = out;
	for (size_t n = 0; n < in_sz; ++n) {
		size_t rc = wcrtomb(p, in[n], &state);
		if (rc == (size_t)-1) break;
		p += rc;
	}
	size_t out_sz = p - out;
	printf("into %zu UTF-8 code units: [ ", out_sz);
	for (size_t x = 0; x < out_sz; ++x) 
		printf("%#x ", +(unsigned char)out[x]);
	puts("]");
	free(out);
}
/*
Processing 4 wchar_t units: [ 0x7a 0xdf 0x6c34 0 ]
into 7 UTF-8 code units: [ 0x7a 0xc3 0x9f 0xe6 0xb0 0xb4 0 ]
*/
```

<br>

#### mbrlen（剩余多字节字符长度）

```c
size_t mbrlen(const char *restrict s, size_t n, mbstate_t *restrict ps);
```

- `mbrlen` 凭借当前转换状态 `ps`，确定 `s` 所指向的剩余多字节字符的字节大小。此函数等价于对于某个隐藏的 `mbstate_t` 类型对象 `internal` 调用 `mbrtowc(NULL, s, n, ps != NULL ? ps : &internal)` ，但是 `ps` 指定的表达式只求值一次。
 `mbrlen` 函数返回一个介于 `0` 和 `n` 之间的值，包括 `(size_t)(-2)` 或 `(size_t)(-1)`：
  - `0`：若接下来 `n` 个或更少字节组成空字符，或 `s` 为空指针。两种情况下都重置转换状态。
  - `[1...n]`：合法的多字节字符的字节数。
  - `(size_t)(-2)`：若接下来 `n` 个字节是可能合法的多字节字符的一部分，但在检验所有 `n` 个字节后仍不完整。
  - `(size_t)(-1)`：如果发生编码错误。宏 `EILSEQ` 的值存储在 `errno` 中，置转换状态 `*ps` 的值为未指定。

```c
#define _CRT_SECURE_NO_WARNINGS 0 // 0
#include <locale.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>
 
int main(void)
{   
    // 允许 mbrlen() 以 UTF-8 多字节编码工作
    setlocale(LC_ALL, "en_US.utf8");
    char str[] = u8"\u6c340";  // u8"水"
    size_t sz = strlen(str);
    
    mbstate_t mb;
    memset(&mb, 0, sizeof mb);
    int len1 = mbrlen(str, 1, &mb);  // mb 保存当前的多字节信息
    if(len1 == -2) 
        printf("The first 1 byte of %s is an incomplete multibyte char"
               " (mbrlen returns -2)\n", str);
 
    int len2 = mbrlen(str+1, sz-1, &mb);  // mb 只求值一次，恢复初始状态
    printf("The remaining %zu  bytes of %s hold %d bytes of the multibyte"
           " character\n", sz-1, str, len2);
 
    // 不完整字符使用初始 mb 将抛出编码错误
    printf("Attempting to call mbrlen() in the middle of %s while in initial"
           " shift state returns %zd\n", str, mbrlen(str+1, sz-1, &mb)); 
    perror("UTF-8");
}
/*
The first 1 byte of 水0 is an incomplete multibyte char (mbrlen returns -2)
The remaining 3  bytes of 水0 hold 2 bytes of the multibyte character
Attempting to call mbrlen() in the middle of 水0 while in initial shift state returns -1
UTF-8: Illegal byte sequence
*/
```

<br>

#### mbstowcs、mbstowcs_s （多字节转换宽字符串）

```c
size_t mbsrtowcs(wchar_t *restrict dst, const char **restrict src, size_t len, mbstate_t *restrict ps);
errno_t mbsrtowcs_s(size_t *restrict retval, wchar_t *restrict dst, rsize_t dstsz,
                     const char **restrict src, rsize_t len, mbstate_t *restrict ps);
```

-  `mbsrtowcs` 依据当前 `*ps` 的多字节状态转换来自 `src` 的空终止多字节字符序列为其宽字符表示，并存储于 `dst` 所指向数组。写入目标数组的宽字符数不多于 `len`。函数如同以对 `mbrtowc` 的调用转换每个多字节字符，当出现以下任一情况则转换停止：
  - 转换并存储了多字节空字符。设置 `*src` 为空指针值并令 `*ps` 表示初始迁移状态。
  - 遇到当前 C 本地环境中的非法多字节字符。设置 `*src` 指向首个未转换的多字节字符的起始。
  - 已转换了 `len` 个宽字符。设置 `*src` 指向首个未转换的多字节字符的起始（若 `dst` 为空则不检查此条件）。

* `mbsrtowcs_s` 同 `mbsrtowcs`。函数将转换成功的宽字符数保存到 `*retval`，写入 `len` 个字符后未到达宽空字符则自动存储 `L'\0'` 于 `dst[len]`（常规要求 `dst` 的大小为 `len+1`）。


```c
#define _CRT_SECURE_NO_WARNINGS 0 // 0
#include <locale.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

int main(void)
{
	const char* str = u8"你好，世界";
	size_t len = strlen(str);
	mbstate_t mb;
	memset(&mb, 0, sizeof mb);
	size_t wcslen = mbstowcs(NULL, &str, 0);  // 获取需要存储宽字符的数组最短长度
	wchar_t* wcsStr = calloc(wcslen, sizeof(wchar_t));
	setlocale(LC_ALL, "zh_cn.utf8");
	size_t c = 0;
	if (!mbsrtowcs_s(&c, wcsStr, wcslen, &str, wcslen-1, &mb))
		printf("convert successfully [count = %zd]: %ls\n", c, wcsStr);
	free(wcsStr);
}
/*
convert successfully [count = 5]: 你好，世界
*/
```

<br>

#### wcstombs、wcstombs_s （宽字符串转多字节）

```c
size_t wcsrtombs(char *restrict dst, const wchar_t **restrict src, size_t len, mbstate_t *restrict ps);
errno_t wcsrtombs_s(size_t *restrict retval, char *restrict dst, rsize_t dstsz,
                    const wchar_t **restrict src, rsize_t len, mbstate_t *restrict ps);
```

- `wcsrtombs` 依据当前 `*ps` 的宽字符状态转换 `*src` 所指向的宽字符序列为其窄多字节表示。若 `dst` 非空，则存储转换后的字符于 `dst` 字符数组。不写入多于 `len` 个字节到目标数组。如同以调用 `wcrtomb` 转换每个字符。若遇到下列条件则停止转换：
  - 转换并存储了空字符 `L'\0'`。此情况下存储的字节是反迁移序列（若需要）后随 `'\0'`，设置 `*src` 为空指针值并令 `*ps` 表示初始迁移状态。
  - 找到当前 C 本地环境中不对应合法字符的 `wchar_t`。设置 `*src` 指向首个未转换的宽字符。
  - 下个多字节字符将超出 `len`。设置 `*src` 指向首个未转换的宽字符。若 `dst` 为空指针则不检查此条件。

* `wcsrtombs_s` 同 `wcsrtombs`。函数将转换的字节数存储于 `*retval`。转换停止而未写入空字符则在 `dst` 末尾自动附加空字符。函数最多写入 `len+1 / dstsz+1` 个字节。

```c
#define _CRT_SECURE_NO_WARNINGS 0 // 0
#include <locale.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>

int main(void)
{
	setlocale(LC_ALL, "zh_cn.utf8");
	wchar_t* wcstr = L"你好，世界";
	size_t len = wcslen(wcstr);
	mbstate_t mb;
	size_t mbslen;
	size_t c = 0;
	errno_t err;
	memset(&mb, 0, sizeof mb);

	err = wcstombs_s(&mbslen, NULL, 0, wcstr, 0);  // 获取需要存储多字节字符的数组最短长度
	if (!err) {
		char* mbsStr = calloc(mbslen, sizeof(char));
		if (!wcsrtombs_s(&c, mbsStr, mbslen, &wcstr, mbslen-1, &mb))
			printf("convert successfully [count = %zd]: %s\n", c, mbsStr);
		free(mbsStr);
	}
	else
		perror("");
}
/*
convert successfully [count = 16]: 你好，世界
*/
```

---
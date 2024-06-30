## C 扩展多字节和宽字符工具：wchar.h

`wchar.h` 提供一些宽字符和扩展的多字节实用程序。

---
### Types

#### mbstate_t

```c
typedef struct
{ 
    unsigned long _Wchar;
    unsigned short _Byte;
    unsigned short _State;
} mbstate_t;
```

`mbstate_t` 是一个非数组类型的完整对象类型，可以保存在多字节字符序列和宽字符序列之间转换所需的转换状态信息。

>---

#### wint_t

```c
typedef unsigned short   wint_t;
```

`wint_t` 是一个不被默认参数提升所改变的整数类型，可以保存与扩展字符集成员相对应的任何值，以及至少一个不与扩展字符集成员相对应的值。

---
### Macros

宏引用定义：

```c
#define NULL  ((void *)0)
#define WCHAR_MIN 
#define WCHAR_MAX 
#define WCHAR_WIDTH
```

>---

#### WEOF

```c
#define WEOF  ((wint_t)(0xFFFF))
```

`WEOF` 扩展为 `wint_t` 类型的常量表达式，其值不对应于扩展字符集的任何成员。它被 `wchar.h` 中的几个函数接受（并返回）来表示文件结束，即不再有来自流的输入。它还用作与扩展字符集的任何成员都不对应的宽字符值。

>---
### 宽字符输入与输出

| Specifier                           | Description                        |
| :---------------------------------- | :--------------------------------- |
| `fwprintf`、`swprintf`、`wprintf`   | 宽字符格式化输出                   |
| `vfwprintf`、`vswprinf`、`vwprintf` | 使用可变参数列表的宽字符格式化输出 |
| `fwscanf`、`swscanf`、`wscanf`      | 宽字符格式化输入                   |
| `vfwscanf`、`vswscanf`、`vwscanf`   | 使用可变参数列表的宽字符格式化输入 |
| `putwc`、`fputwc`、`putwchar`       | 宽字符输出                         |
| `getwc`、`fgetwc`、`getwchar`       | 宽字符输入                         |
| `fputws`、`fgetws`                  | 宽字符串输出与输入                 |
| `ungetwc`                           | 宽字符回推                         |
| `fwide`                             | 确定 `stream` 所指向的流的方向     |


>---
### 宽字符转换和复制函数

| Specifier                                  | Description              |
| :----------------------------------------- | :----------------------- |
| `wcstod`、`wcstof`、`wcstold`              | 宽字符串转换标准浮点数   |
| <code>wcstod*N*</code>                     | 宽字符串转换十进制浮点数 |
| `wcstol`、`wcstoll`、`wcstoul`、`wcstoull` | 宽字符串转换为整数       |
| `wcscpy`、`wcsncpy`                        | 宽字符串复制             |
| `wmemcpy`、`wmemmove`                      | 宽字符复制               |

>---
### 宽字符串工具类函数

| Specifier                                                                          | Description                  |
| :--------------------------------------------------------------------------------- | :--------------------------- |
| `wcscat`、`wcsncat`                                                                | 宽字符串拼接函数             |
| `wmemcmp`、`wcscmp`、`wcsncmp`、`wcscoll`、`wcsxfrm`                               | 宽字符串比较函数             |
| `wmemchr`、`wcschr`、`wcsrchr`、`wcsstr`、`wcspbrk`、`wcsspn`、`wcscspn`、`wcstok` | 宽字符检索函数               |
| `wcslen`                                                                           | 字符串长度                   |
| `wmemset`                                                                          | 复制一定数目的宽字符到数组中 |
| `wcsftime`                                                                         | 宽字符时间格式化转换         |

> wcsftime

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

>---
### 扩展多字节 / 宽字符转换

| Specifier                                                                          | Description                  |
| :--------------------------------------------------------------------------------- | :--------------------------- |
`btowc`、`wctob`| 单字节 / 宽字符转换
`mbsinit`  | 状态转换函数
`mbrtowc`、`wcrtomb`| 定状态多字节 / 宽字符转换
`mbrlen` | 剩余多字节字符长度
`mbstowcs`、`mbstowcs_s` | 多字节转换宽字符串
`wcstombs`、`wcstombs_s` | 宽字符串转换多字节

> 单字节 / 宽字符转换

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

> mbsinit

`mbsinit` 函数检查的 `mbstate_t` 对象是否描述了初始转换状态。如果 `ps` 是空指针，或者引用的对象描述了初始转换状态，则 `mbsinit` 函数返回非零，否则返回 0。

`mbstate_t` 表示任何能出现于实现定义的受支持多字节编码规则集合的转换状态。`mbstate_t` 的零初始化值表示初始转换状态。`mbstate_t` 的可行实现是一个结构体类型，保有表示不完整多字节字符的数组、指示数组中已处理字节数和当前迁移状态的表示。由于可能的数据竞争，不从多个线程以空指针为 `mbstate_t*` 参数调用下列函数而不同步：`mbrlen`、`mbrtowc`、`mbsrtowcs`、`mbtowc`、`wcrtomb`、`wcsrtombs`、`wctomb`。

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

> mbrtowc、wcrtomb

`mbrtowc` 函数转换窄多字节字符为宽字符：
  - 当 `s` 不为空时，则从 `s` 所指的字节起，最多检查只 `n` 个字符，以确定完成下个多字节字符（包含任何迁移序列）的字节数。转换成功时存储于 `*pwc`。
  - 当 `s` 是空指针，则忽略 `n` 和 `pwc` 的值，等价于 `mbrtowc(NULL,"",1,ps)`。
  - 若产生的宽字符是空字符，则存储与 `*ps` 的转换状态为初始迁移状态。

`mbrtowc` 返回值解析：
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

`wcrtomb` 函数转换宽字符为其窄多字节表示：
  - 若 `s` 不是空指针，则函数检测存储 `wc` 的多字节字符表示所需的字节数（包含任何迁移序列，并考虑当前多字节转换状态 `*ps`，并存储多字节字符表示于 `s` 所指向的字符数组，按需更新 `*ps` 。此函数至多能写入 `MB_CUR_MAX` 字节。
  - 若 `s` 为空指针，则调用等价于对某内部缓冲区 `buf` 的 `wcrtomb(buf, L'\0', ps)`。
  - 若 `wc` 是空宽字符 `L'\0'`，则存储空字节，前接任何恢复到初始迁移状态所需的迁移序列，并更新转换状态参数 `*ps` 以表示其初始迁移状态。
  - 若定义环境宏 `__STDC_ISO_10646__`，则 `wchar_t` 类型的值与 `Unicode` 要求集（典型地为 `UTF-32` 编码）中字符的短标识符相同；否则它是实现定义的。任何情况下，此函数所用的多字节字符编码为当前活跃的 C 本地环境所指定。

`wcrtomb` 转换成功时，返回写入首元素为 `s` 所指向的字符数组的字节数（包含任何迁移序列）。失败时（若 `wc` 不是合法宽字符），返回 `(size_t)-1`，存储 `EILSEQ` 于 `errno`，并使 `*ps` 留在未指定状态。

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

> mbrlen

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

> mbsrtowcs


`mbsrtowcs` 依据当前 `*ps` 的多字节状态转换来自 `src` 的空终止多字节字符序列为其宽字符表示，并存储于 `dst` 所指向数组。写入目标数组的宽字符数不多于 `len`。函数如同以对 `mbrtowc` 的调用转换每个多字节字符，当出现以下任一情况则转换停止：
  - 转换并存储了多字节空字符。设置 `*src` 为空指针值并令 `*ps` 表示初始迁移状态。
  - 遇到当前 C 本地环境中的非法多字节字符。设置 `*src` 指向首个未转换的多字节字符的起始。
  - 已转换了 `len` 个宽字符。设置 `*src` 指向首个未转换的多字节字符的起始（若 `dst` 为空则不检查此条件）。

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

> wcsrtombs

`wcsrtombs` 依据当前 `*ps` 的宽字符状态转换 `*src` 所指向的宽字符序列为其窄多字节表示。若 `dst` 非空，则存储转换后的字符于 `dst` 字符数组。不写入多于 `len` 个字节到目标数组。如同以调用 `wcrtomb` 转换每个字符。若遇到下列条件则停止转换：
  - 转换并存储了空字符 `L'\0'`。此情况下存储的字节是反迁移序列（若需要）后随 `'\0'`，设置 `*src` 为空指针值并令 `*ps` 表示初始迁移状态。
  - 找到当前 C 本地环境中不对应合法字符的 `wchar_t`。设置 `*src` 指向首个未转换的宽字符。
  - 下个多字节字符将超出 `len`。设置 `*src` 指向首个未转换的宽字符。若 `dst` 为空指针则不检查此条件。

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
## C Unicode 字符工具（Unicode utilities）：uchar.h

`uchar.h` 提供了多字节字符和 UTF-16、UTF-32 之间的转换函数。

---
### Types

```c
typedef struct
{ 
    unsigned long _Wchar;
    unsigned short _Byte;
    unsigned short _State;
} mbstate_t;            // 保存在多字节字符序列和宽字符序列之间转换所需的转换状态信息

typedef unsigned long long    size_t    // 无符号整数类型，表示类型大小
typedef unsigned short   char16_t;      // 用于表示 16 位的无符号整数
typedef unsigned int     char32_t;      // 用于表示 32 位的无符号整数
```

---
### Functions：多字节 / 宽字符转换（Restartable multibyte/wide character conversion functions）

#### mbrtoc16、c16rtomb （UTF-16 宽字符 / 多字节转换）

> `mbrtoc16`

```c
size_t mbrtoc16(char16_t * restrict pc16, const char * restrict s, size_t n, mbstate_t * restrict ps);
```

- `mbrtoc16` 函数将单个编码点的多字节字符表示转换为其 UTF-16 位的宽字符表示：
  - 当 `s` 不是空指针时，函数从 `s` 开始最多审查 `n` 个字节，以确定下个多字节字符所需的字节数。若 `s` 中的下个多字节字符完整且合法，则转换它为对应的 UTF-16 宽字符并保存在 `*pc16`。随后的调用将存储连续的宽字符，而不消耗任何额外的输入，直到所有的字符都存储完毕。若当遇到空宽字符时，则置 `*ps` 为初始转换状态。
  - 若 `s` 是空指针，则忽略 `n` 与 `pc16` 的值，等价于调用 `mbrtoc16(NULL, "", 1, ps)`。

* 若定义 `__STDC_UTF_16__` 宏，则此函数使用的 16 位编码是 UTF-16；否则它是实现定义的。任何情况下，此函数所用的多字节字符编码为当前活跃的 C 本地环境所指定。

- 函数返回值解析：
  - `0`：如果下一个n或更少的字节完成了与空宽字符对应的多字节字符（存储到 `*pc16`）。
  - `[0...n]`：如果下一个 `n` 或更少字节完成一个有效的多字节字符（存储到 `*pc16`）；返回的值是完成多字节字符的字节数。
  - `(size_t)(-3)`：如果先前调用产生的下一个字符已被存储（此调用没有消耗输入的字节）。
  - `(size_t)(-2)`：如果接下来的 `n` 个字节构成了一个不完整（但可能有效）的多字节字符，并且所有 `n` 个字节都已处理（不存储任何值）。
  - `(size_t)(-1)`：如果发生编码错误，在这种情况下，下一个 `n` 或更少的字节不会构成完整有效的多字节字符（不存储任何值）；宏 `EILSEQ` 的值存储在 `errno` 中，转换状态未指定。

```c
#define _CRT_SECURE_NO_WARNINGS 0 // 0
#include <stdio.h>
#include <locale.h>
#include <uchar.h>
#include <stdint.h>
#include <stdlib.h>

mbstate_t state;
int main(void)
{
    setlocale(LC_ALL, "en_US.utf8");
    char in[] = u8"zß水🍌"; // 或 "z\u00df\u6c34\U0001F34C"
    size_t in_sz = sizeof in / sizeof * in;

    printf("Processing %zu UTF-8 code units: [ ", in_sz);
    for (size_t n = 0; n < in_sz; ++n) printf("%#x ", (unsigned char)in[n]);
    puts("]");

    char16_t * out = calloc(in_sz, sizeof(char16_t));
    char* p_in = in, * end = in + in_sz;
    char16_t* p_out = out;
    size_t rc;
    while ((rc = mbrtoc16(p_out, p_in, end - p_in, &state)))
    {
        if (rc == (size_t)-3) // UTF-16 中的代理对
            p_out += 1;
        else if (rc <= SIZE_MAX / 2) {
            p_in += rc;
            p_out += 1;
        }
        else break;
    }

    size_t out_sz = p_out - out + 1;
    printf("into %zu UTF-16 code units: [ ", out_sz);
    for (size_t x = 0; x < out_sz; ++x) printf("%#x ", out[x]);
    puts("]");

    free(out);
}
/*
Processing 11 UTF-8 code units: [ 0x7a 0xc3 0x9f 0xe6 0xb0 0xb4 0xf0 0x9f 0x8d 0x8c 0 ]
into 6 UTF-16 code units: [ 0x7a 0xdf 0x6c34 0xd83c 0xdf4c 0 ]
*/
```

> `c16rtomb`

```c
size_t c16rtomb(char * restrict s, char16_t c16, mbstate_t * restrict ps);
```

- `c16rtomb` 函数将 UTF-16 位宽字符表示转换到其单个编码点的多字节窄字符表示：
  - 若 `s` 不是空指针且 `c16` 是合法的 16 位编码点，则函数确定存储该编码点所需的字节数（包含任何迁移序列，并考虑当前多字节转换状态 *ps），并存储多字节表示于 `s` 所指向的字符数组，若必要则更新 `*ps`。此函数最能写入 `MB_CUR_MAX` 个字节。
  - 若 `s` 是空指针，则调用等价于对于某内部缓冲区 `buf` 的 `c16rtomb(buf, u'\0', ps)`。
  - 若 `c16` 是空宽字符 `u'\0'` ，则存储空字节，前附恢复到初始迁移状态所需的任何迁移序列，并更新 `*ps` 以表示初始迁移状态。
  - 若 `c16` 不是 UTF-16 编码的宽字符，则不写入 `s` 所指向的数组，只更新 `*ps`。

* 若定义宏 `__STDC_UTF_16__`，则此函数所用的 16 位编码是 UTF-16；否则，它是实现定义的。任何情况下，此函数所用的宽字符编码为当前活跃的 C 本地环境所指定。

- `c16rtomb` 函数返回存储在数组对象中的字节数（包括任何移位序列）。当 `c16` 不是有效的宽字符时，会发生编码错误：函数将宏 `EILSEQ` 的值存储在 `errno` 中并返回 `(size_t)(-1)`，且转换状态未指定。

```c
#define _CRT_SECURE_NO_WARNINGS 0 // 0
#include <stdio.h>
#include <locale.h>
#include <uchar.h>
#include <stdlib.h>

mbstate_t state;
int main(void)
{
	setlocale(LC_ALL, "en_US.utf8");
	char16_t in[] = u"zß水🍌"; // 或 "z\u00df\u6c34\U0001F34C"
	size_t in_sz = sizeof in / sizeof * in;

	printf("Processing %zu UTF-16 code units: [ ", in_sz);
	for (size_t n = 0; n < in_sz; ++n) printf("%#x ", in[n]);
	puts("]");

	char* out = calloc(MB_CUR_MAX * in_sz, sizeof(char));
	char* p = out;
	for (size_t n = 0; n < in_sz; ++n) {
		size_t rc = c16rtomb(p, in[n], &state);
		if (rc == (size_t)-1) break;
		p += rc;
	}

	size_t out_sz = p - out;
	printf("into %zu UTF-8 code units: [ ", out_sz);
	for (size_t x = 0; x < out_sz; ++x) printf("%#x ", +(unsigned char)out[x]);
	puts("]");
	free(out);
}
/*
Processing 6 UTF-16 code units: [ 0x7a 0xdf 0x6c34 0xd83c 0xdf4c 0 ]
into 11 UTF-8 code units: [ 0x7a 0xc3 0x9f 0xe6 0xb0 0xb4 0xf0 0x9f 0x8d 0x8c 0 ]
*/
```

<br>

#### mbrtoc32、c32rtomb （UTF-32 宽字符 / 多字节转换）

> `mbrtoc32`

```c
size_t mbrtoc32(char32_t restrict * pc32, const char * restrict s, size_t n, mbstate_t * restrict ps);
```

- `mbrtoc32` 是 `mbrtoc16` 的多字节转换宽字节的 UTF-32 位版本。参考 `mbrtoc16` 的函数描述。

```c
#define _CRT_SECURE_NO_WARNINGS 0 // 0
#include <stdio.h>
#include <locale.h>
#include <uchar.h>
#include <stdlib.h>
#include <assert.h>

mbstate_t state;
int main(void)
{
    setlocale(LC_ALL, "en_US.utf8");
    char in[] = u8"zß水🍌"; // 或 "z\u00df\u6c34\U0001F34C"
    size_t in_sz = sizeof in / sizeof * in;

    printf("Processing %zu UTF-8 code units: [ ", in_sz);
    for (size_t n = 0; n < in_sz; ++n) printf("%#x ", (unsigned char)in[n]);
    puts("]");

    char32_t * out = calloc(in_sz, sizeof(char32_t));
    char* p_in = in, * end = in + in_sz;
    char32_t* p_out = out;
    size_t rc;
    while ((rc = mbrtoc32(p_out, p_in, end - p_in, &state)))
    {
        assert(rc != (size_t)-3); // UTF-32 中无代理对
        if (rc > ((size_t)-1) / 2) break;
        p_in += rc;
        p_out += 1;
    }

    size_t out_sz = p_out - out + 1;
    printf("into %zu UTF-32 code units: [ ", out_sz);
    for (size_t x = 0; x < out_sz; ++x) 
        printf("%#x ", out[x]);
    puts("]");
    free(out);
}
/*
Processing 11 UTF-8 code units: [ 0x7a 0xc3 0x9f 0xe6 0xb0 0xb4 0xf0 0x9f 0x8d 0x8c 0 ]
into 5 UTF-32 code units: [ 0x7a 0xdf 0x6c34 0x1f34c 0 ]
*/
```

> `c32rtomb` 

```c
size_t c32rtomb(char * restrict s, char32_t c32, mbstate_t * restrict ps);
```

- `c32rtomb` 是 `c16rtomb` 的多字节转换宽字节的 UTF-32 位版本。参考 `c16rtomb` 的函数描述。

```c
#define _CRT_SECURE_NO_WARNINGS 0 // 0
#include <stdio.h>
#include <locale.h>
#include <uchar.h>
#include <stdlib.h>

mbstate_t state;
int main(void)
{
    setlocale(LC_ALL, "en_US.utf8");
    char32_t in[] = U"zß水🍌"; // 或 "z\u00df\u6c34\U0001F34C"
    size_t in_sz = sizeof in / sizeof * in;

    printf("Processing %zu UTF-32 code units: [ ", in_sz);
    for (size_t n = 0; n < in_sz; ++n) printf("%#x ", in[n]);
    puts("]");

    char *out = calloc(MB_CUR_MAX * in_sz, sizeof(char));
    char* p = out;
    for (size_t n = 0; n < in_sz; ++n) {
        size_t rc = c32rtomb(p, in[n], &state);
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
Processing 5 UTF-32 code units: [ 0x7a 0xdf 0x6c34 0x1f34c 0 ]
into 11 UTF-8 code units: [ 0x7a 0xc3 0x9f 0xe6 0xb0 0xb4 0xf0 0x9f 0x8d 0x8c 0 ]
*/
```

---
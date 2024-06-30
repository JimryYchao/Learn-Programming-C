## C Unicode 字符工具：uchar.h

`uchar.h` 提供了多字节字符和 UTF-16、UTF-32 之间的转换函数。

>---
### 多字节 / 宽字符转换

| Specifier            | Description                |
| :------------------- | :------------------------- |
| `char8_t`            | 用于表示 8 位的无符号整数  |
| `char16_t`           | 用于表示 16 位的无符号整数 |
| `char32_t`           | 用于表示 32 位的无符号整数 |
`mbstate_t` | 保存在多字节字符序列和宽字符序列之间转换所需的转换状态信息
| `mbrtoc16、c16rtomb` | 多字节与 UTF-16 相互转换   |
| `mbrtoc32、c32rtomb` | 多字节与 UTF-32 相互转换   |
| `mbrtoc8、c8rtomb`   | 多字节与 UTF-8 相互转换    |


这些函数有一个参数 `ps`，类型为 `mbstate_t` 的指针，指向一个对象，该对象可以完全描述相关多字节字符序列的当前转换状态，函数会根据需要对其进行更改。如果 `ps` 是空指针，则每个函数都使用自己的内部指针。

`char8_t`、`char16_t` 和 `char32_t` 对象以及这些对象的序列的编码分别为 UTF-8、UTF-16 和 UTF-32。

> mbrtoc16、c16rtomb

`mbrtoc16` 函数将单个编码点的多字节字符表示转换为其 UTF-16 位的宽字符表示：
  - 当 `s` 不是空指针时，函数从 `s` 开始最多审查 `n` 个字节，以确定下个多字节字符所需的字节数。若 `s` 中的下个多字节字符完整且合法，则转换它为对应的 UTF-16 宽字符并保存在 `*pc16`。随后的调用将存储连续的宽字符，而不消耗任何额外的输入，直到所有的字符都存储完毕。若当遇到空宽字符时，则置 `*ps` 为初始转换状态。
  - 若 `s` 是空指针，则忽略 `n` 与 `pc16` 的值，等价于调用 `mbrtoc16(NULL, "", 1, ps)`。

函数返回值解析：
  - `0`：如果下一个n或更少的字节完成了与空宽字符对应的多字节字符（存储到 `*pc16`）。
  - `[1...n]`：如果下一个 `n` 或更少字节完成一个有效的多字节字符（存储到 `*pc16`）；返回的值是完成多字节字符的字节数。
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
    const char in[] = u8"zß水🍌"; // 或 "z\u00df\u6c34\U0001F34C"
    const size_t in_sz = sizeof in / sizeof *in;
 
    printf("Processing %zu UTF-8 code units: [ ", in_sz);
    for (size_t n = 0; n < in_sz; ++n)
        printf("%#x ", (unsigned char)in[n]);
    puts("]");
 
    char16_t out[in_sz];
    const char *p_in = in, *end = in + in_sz;
    char16_t *p_out = out;
    for (size_t rc; (rc = mbrtoc16(p_out, p_in, end - p_in, &state));)
    {
        if (rc == (size_t)-1)     // 无效输入
            break;
        else if(rc == (size_t)-2) // 被截断的输入
            break;
        else if(rc == (size_t)-3) // UTF-16 高位代理
            p_out += 1;
        else
        {
            p_in += rc;
            p_out += 1;
        };
    }
 
    const size_t out_sz = p_out - out + 1;
    printf("into %zu UTF-16 code units: [ ", out_sz);
    for (size_t x = 0; x < out_sz; ++x)
        printf("%#x ", out[x]);
    puts("]");
}
/*
Processing 11 UTF-8 code units: [ 0x7a 0xc3 0x9f 0xe6 0xb0 0xb4 0xf0 0x9f 0x8d 0x8c 0 ]
into 6 UTF-16 code units: [ 0x7a 0xdf 0x6c34 0xd83c 0xdf4c 0 ]
*/
```

`c16rtomb` 函数将 UTF-16 位宽字符表示转换到其单个编码点的多字节窄字符表示：
  - 若 `s` 不是空指针且 `c16` 是合法的 16 位编码点，则函数确定存储该编码点所需的字节数（包含任何迁移序列，并考虑当前多字节转换状态 *ps），并存储多字节表示于 `s` 所指向的字符数组，若必要则更新 `*ps`。此函数最能写入 `MB_CUR_MAX` 个字节。
  - 若 `s` 是空指针，则调用等价于对于某内部缓冲区 `buf` 的 `c16rtomb(buf, u'\0', ps)`。
  - 若 `c16` 是空宽字符 `u'\0'` ，则存储空字节，前附恢复到初始迁移状态所需的任何迁移序列，并更新 `*ps` 以表示初始迁移状态。
  - 若 `c16` 不是 UTF-16 编码的宽字符，则不写入 `s` 所指向的数组，只更新 `*ps`。

`c16rtomb` 函数返回存储在数组对象中的字节数（包括任何移位序列）。当 `c16` 不是有效的宽字符时，会发生编码错误：函数将宏 `EILSEQ` 的值存储在 `errno` 中并返回 `(size_t)(-1)`，且转换状态未指定。

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

> mbrtoc32、c32rtomb

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

`c32rtomb` 是类似于 `c16rtomb` 的多字节转换宽字节的 UTF-32 位版本。参考 `c16rtomb` 的函数描述。

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
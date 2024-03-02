## C 字符串处理（String handling）：string.h

`string.h` 提供一些操作字符类型数组和其他被视为字符类型数组对象的函数等。

---
### Functions：复制（Copying functions）

#### memcpy、memcpy_s （缓冲区复制）

```c
void * memcpy(void * restrict dst, const void * restrict src, size_t size);

errno_t memcpy_s( void *restrict dst, rsize_t dstSize,
                  const void *restrict src, rsize_t srcSize);
```

- `memcpy` 函数将 `src` 所指向的对象中的 `size` 个字符复制到 `dst` 所指向的对象中。如果复制发生在重叠的对象之间，则行为未定义。复制成功时返回 `dst` 的副本，本质为更底层操作的临时内存地址（不建议直接使用）。
* `memcpy_s` 同 `memcpy`，失败时将清除 `dst` 整个目标范围。它在运行时检测下列错误，并调用当前安装的约束处理函数：
  - `dst` 或 `src` 为空指针；
  - `dstSize` 或 `srcSize` 大于 `RSIZE_MAX`；
  - `srcSize` 大于 `dstSize` （会发生缓冲区溢出）；
  - 源和目标对象重叠。
  
```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
	char str1[] = "Hello world";
	char* str2 = calloc(sizeof(str1) / sizeof str1[0], sizeof(str1[0]));
	errno_t err = memcpy_s(str2, sizeof str1, str1, sizeof str1);
	if (err) puts(strerror(err));
	else printf("&str1 = %p\n""&str2 = %p, str2 = %s\n", str1, str2, str2);
	free(str2);
}
/*
&str1 = 000000C4434FF558
&str2 = 0000022F4156E5E0, str2 = Hello world
*/
```

<br>

#### memmove、memmove_s （缓冲区移动）

```c
void *memmove(void *dst, const void *src, size_t size);

errno_t memmove_s(void *dst, rsize_t dstSize, const void *src, rsize_t srcSize);
```

- `memmove` 函数从 `src` 所指向的对象复制 `size` 个字节到 `dst` 所指向的对象，若 `dst` 或 `src` 为非法或空指针则行为未定义。两个对象都被转译成 `unsigned char` 的数组。`dst` 和 `stc` 对象可以重叠：如同复制字符到临时数组，再从该数组复制到 `dst` 数组。
* `memmove_s` 同 `memmove`，失败时将清除 `dst` 整个目标范围。它在运行时检测下列错误，并调用当前安装的约束处理函数：
  - `dst` 或 `src` 为空指针；
  - `dstSize` 或 `srcSize` 大于 `RSIZE_MAX`；
  - `srcSize` 大于 `dstSize` （会出现溢出）。

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
	// 创建一个 4x4 的矩阵
	int arr[4][4] = {
		{1,2,3,4},
		{2,2,2,2},
		{4,3,2,1},
		{4,4,4,4}
	};
	// 调换其中 2,3 行。
	int tmpRow[4];
	memcpy_s(tmpRow, sizeof(tmpRow), arr[1], sizeof(tmpRow));  // 复制第 2 行
	memmove_s(arr[1], sizeof(tmpRow), arr[2], sizeof(tmpRow)); // 移动第 3 行到第 2 行
	memcpy_s(arr[2], sizeof(tmpRow), tmpRow, sizeof(tmpRow));  // 复制临时数组到第 3 行

	for (size_t i = 0; i < 4; i++)
		printf("the line(%d): %2d,%2d,%2d,%2d\n", i + 1, arr[i][0], arr[i][1], arr[i][2], arr[i][3]);
}
```

<br>

#### strcpy、strcpy_s （字符串复制）

```c
char *strcpy(char * restrict dst, const char * restrict src);

errno_t strcpy_s(char *restrict dst, rsize_t dstSize, const char *restrict src);
```

- `strcpy` 复制 `src` 所指向的空终止字节字符串，包含空终止符，到首元素为 `dst` 所指的字符数组。`dst` 的长度不足则行为未定义。若 `src` 不是指向空终止字节字符串的指针则行为未定义。若字符串重叠则行为未定义。成功时返回 `dst` 的副本
* `strcpy_s` 同 `src`。`dst` 缓冲区的大小 `dstSize` 不可小于 `src` 的长度。转换失败时会将 `dst[0] = '\0'`。

```c
#include <stdio.h>
#include <string.h>
int main(void)
{
	char* str = "Hello world";
	char dst[12];
	if (!strcpy_s(dst, 12, str))
		printf("%s\n", dst);
}
```

<br>

#### strncpy、strncpy_s （字符串截取复制）

```c
char *strncpy(char * restrict dst, const char * restrict src, size_t count);

errno_t strncpy_s(char *restrict dst, rsize_t dstSize,
                  const char *restrict src, rsize_t count);
```

- `strncpy` 函数从 `src` 指向的数组复制不超过 `count` 个字符（不复制空字符后面的字符）到 `dst` 指向的数组：
  - 若 `src` 数组是一个小于 `count` 个字符的字符串，则会追加空字符到 `dst` 所指向的数组中，直到写入共 `count` 个字符。
  - 若在完全复制整个 `src` 数组前抵达 `count`，则结果的字符数组不是空终止的（不会自动附加 null）。
  - 如果复制发生在重叠的对象之间，则行为未定义。若 `dst` 的长度小于 `count` 或 `src` 字符数组中不包含空终止，则行为未定义。

* `strncpy_s` 同 `strncpy`。发生错误时写入零到 `dst[0]`。若在完全复制整个 `src` 数组前抵达 `count`，则附加一个空终止符到 `dst[count]`。

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[] = "Hello world";
	char str2[20];

	strncpy_s(str2, sizeof(str2), str+6, 5);
	printf("str2 = %s\n", str2);  // world
}
```

---
### Functions：字符串拼接（Concatenation functions）
#### strcat、strcat_s （字符串拼接）

```c
char * strcat(char * restrict dst, const char * restrict src);
 
errno_t strcat_s(char *restrict dst, rsize_t dstSize, const char *restrict src);
```

- `strcat`、`strncat` 函数将 `src` 所指向的字符串的副本（包括空终止符）附加到 `dst` 所指向的字符串的末尾。`src` 的初始字符将覆盖 `dst` 末尾的空终止符。如果复制发生在重叠的对象之间，则行为未定义。 若 `dst` 数组长度不足以容纳 `src` 附加后的长度则行为未定义。拼接成功时返回 `dst` 的副本。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str1[] = "hello";
	char str2[] = "world";
	char newStr[sizeof str1 + sizeof str2];
	strcpy(newStr, str1);
	strcat(newStr, " ");
	strcat(newStr, str2);
	printf("%s\n", newStr); 
} // hello world
```

<br>

#### strncat、strncat_s （字符串片段拼接）

```c
char * strncat(char * restrict dst, const char * restrict src, size_t count);

errno_t strncat_s(char * restrict dst, rsize_t dstSize, const char * restrict src, rsize_t count);
```

- `strncat`、`srtncat_s` 用于后附 `src` 字符串中的 `count` 个数目的字符，到 `dst` 字符串的末尾处。若源与目标对象重叠，则行为未定义。`dst` 长度要足够容纳即将要附加的字符数，否则行为是未定义的。函数依次读取 `src` 的字符并插入到 `dst` 的末尾（空终止符的位置），直到遇到 `src` 的终止符或读取到 `count` 个字符才停止。成功拼接后将在末尾附加终止符。
- 函数发生错误时会将 `dst` 原始空终止的位置重新置为 0。

```c
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str1[] = "hello ";
	char str2[] = "world.....abcd";
	char newStr[sizeof str1 + sizeof str2];
	strcpy(newStr, str1);
	strncat_s(newStr, sizeof(newStr), str2, 5);
	printf("%s\n", newStr);
}
```

---
### Functions：比较（Comparison functions）
#### memcmp （比较缓冲区）

```c
int memcmp(const void* lhs, const void* rhs, size_t count);
```

- `memcmp` 函数用于比较 `lhs` 和 `rhs` 所指对象的前 `count` 个字节。按照字典序进行比较（每一对字节转译成 `unsigned char`），返回的结果的字符由被比较对象中不同的第一对字节（都解释为 `unsigned char`）的值之间的差的符号决定。比较相等时返回零。

```c
#include <stdio.h>
#include <string.h>
int main(void)
{
	char str1[] = "hello ";
	char str2[] = "hello world";
	printf("memcmp(str1,str2,5) = %d", memcmp(str1, str2, 5));  // 0
}
```

<br>

#### strcmp、strncmp （比较字符串）

```c
int strcmp(const char *lhs, const char *rhs);       // 比较字符串

int strncmp(const char *lhs, const char *rhs, size_t count);  // 比较字符串前 count 个字符
```

- `strcmp` 用于比较两个字符串之间的字典序。此函数不考虑本地环境。
* `strncmp` 用于比较两个字符串最多 count 个字符序列的字典序。超过字符串结尾的访问比较，行为未定义。此函数不考虑本地环境。

```c
#include <stdio.h>
#include <string.h>
int main(void)
{
	char str1[] = "hello ";
	char str2[] = "hello world";
	printf("strcmp(str1,str2) = %d\n", strcmp(str1, str2)); // -1
	printf("strncmp(str1,str2,5) = %d", strncmp(str1, str2, 5));  // 0
}
```

<br>

#### strcoll （以本地比较字符串）

```c
int strcoll(const char *lhs, const char *rhs);
```

- `strcoll` 函数将 `lhs` 指向的字符串与 `rhs` 指向的字符串进行比较，两者都被解释为适合当前语言环境的 `LC_COLLATE` 类别。

```c
#include <stdio.h>
#include <string.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_COLLATE, "cs_CZ");
	const char* s1 = "hrnec";
	const char* s2 = "chrt";

	printf("In the Czech locale: ");    // 本地环境限定的顺序
	if (strcoll(s1, s2) < 0)
		printf("%s before %s\n", s1, s2);
	else
		printf("%s before %s\n", s2, s1);

	printf("In lexicographical comparison: ");  // 国际字典序
	if (strcmp(s1, s2) < 0)
		printf("%s before %s\n", s1, s2);
	else
		printf("%s before %s\n", s2, s1);
}
/*
In the Czech locale: hrnec before chrt
In lexicographical comparison: chrt before hrnec
*/
```

<br>

#### strxfrm （变换字符串）

```c
size_t strxfrm(char *restrict dst, const char *restrict src, size_t count);
```

- `strxfrm` 变换 `src` 字符串为 `strcoll` 函数解释原始字符串为符合当前语言环境的 `LC_COLLATE` 类别的变换字符串，此时用 `strcmp` 比较两个变换字符串的结果和 `strcoll` 直接比较原始字符串的结果相等。
- `strxfrm` 函数将变换后的字符串的首 `count` 个字符写入 `dst` 对象，包括空终止符，并返回排除空字符串的完整转换后字符串的长度（该长度为 `strxfrm(NULL, src, 0)` 的返回结果）。

```c
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

int main(void)
{
    setlocale(LC_COLLATE, "cs_CZ");
    
    const char* in1 = "hrnec";
    int len1 = 1 + strxfrm(NULL, in1, 0);
    char* out1 = calloc(len1, sizeof(char));
    strxfrm(out1, in1, len1);

    const char* in2 = "chrt";
    int len2 = 1 + strxfrm(NULL, in2, 0);
    char* out2 = calloc(len2, sizeof(char));
    strxfrm(out2, in2, len2);

    printf("In the Czech locale: ");
    if (strcmp(out1, out2) < 0)
        printf("%s before %s\n", in1, in2);
    else
        printf("%s before %s\n", in2, in1);

    printf("In lexicographical comparison: ");
    if (strcmp(in1, in2) < 0)
        printf("%s before %s\n", in1, in2);
    else
        printf("%s before %s\n", in2, in1);

    free(out1);
    free(out2);
}
/*
In the Czech locale: hrnec before chrt
In lexicographical comparison: chrt before hrnec
*/
```

---
### Functions：检索（Search functions）

#### memchr （数组中检索字符）

```c
void* memchr(const void* ptr, int ch, size_t count);
```

- `memchr` 函数在字节数组 `ptr` 中查找 (`unsigned char)ch`，最多检索 `count` 个字节（转译为 `unsigned char`），首次出现时返回该字节位置的指针，否则返回空指针。`count` 大于 `ptr` 指向字节数组的长度，则行为未定义。

```c
#include <stdio.h>
#include <string.h>
int main(void)
{
	char str[] = "hello world";
	char* pos;
	if (pos = memchr(str, 'l', strlen(str)))
		printf("the char('l') is at %p, and indexof(str) = %td\n", pos, pos - str);
}
// the char('l') is at 00000051A1CFF5BA, and indexof(str) = 2
```

<br>

#### strchr、strrcar （字符串中检索字符）

```c
char *strchr(const char *str, int ch);      // 检索字符 ch 在字符串中首次出现的位置
char *strrchr(const char *str, int ch);     // 检索字符 ch 在字符串中最后出现的位置       
```

- `strchr` 函数定位 `str` 所指向的字符串中首次出现的 `ch`（转换为 `char`）。结束的 `null` 字符被认为是字符串的一部分。
- `strrchr` 函数定位 `str` 所指向的字符串中最后出现的 `ch`（转换为 `char`）。结束的 `null` 字符被认为是字符串的一部分。

```c
#include <stdio.h>
#include <string.h>
int main(void)
{
	char str[] = "hello world";
	char* pos;
	if (pos = strchr(str, 'l'))
		printf("First found 'l' at %p, and indexof(str) = %td\n", pos, pos - str);
	if (pos = strrchr(str, 'l'))
		printf(" Last found 'l' at %p, and indexof(str) = %td\n", pos, pos - str);
}
/*
First found 'l' at 000000334652FB5A, and indexof(str) = 2
 Last found 'l' at 000000334652FB61, and indexof(str) = 9
*/
```

<br>

#### strstr （检索子字符串）

```c
char *strstr(const char* str, const char* substr);
```

- `strstr` 函数定位序列 `substr` 字符串片段在 `str` 字符串中首次出现的位置（不包括结束的空字符），返回子字符串 `substr` 首元在 `str` 中的定位指针。

```c
#include <stdio.h>
#include <string.h>
int main(void)
{
	char str[] = "hello world";
	char* pos;
	if (pos = strstr(str, "wor"))
		printf("Found \"wor\" at %p, and indexof(str) = %td\n", pos, pos - str);
}
/*
Found "wor" at 000000314E2FF86E, and indexof(str) = 6
*/
```

<br>

#### strspn （从起始检索字符集连续包含数量）

```c
size_t strspn(const char *dst, const char *set)
```

- `strspn` 函数计算 `dst` 字节串的最大起始段长度，该段仅由 `set` 字符串中 **包含的字符** 组成。

```c
#include <string.h>
#include <stdio.h>
int main(void)
{
    const char* string = "abcde312$#@";
    const char* low_alpha = "qwertyuiopasdfghjklzxcvbnm";
    // 获取从起始开始连续包含字母的字符数目
    size_t spnsz = strspn(string, low_alpha);  
    printf("After skipping initial lowercase letters from '%s'\n"
        "The remainder is '%s'\n", string, string + spnsz);
}
/*
After skipping initial lowercase letters from 'abcde312$#@'
The remainder is '312$#@'
*/
```

<br>

#### strcspn （从起始检索字符集连续不包含数量）

```c
size_t strcspn(const char *dst, const char *set);
```

- `strcspn` 函数计算 `dst` 字符串的最大起始段长度，该段仅由 `set` 字符串中 **以外的字符** 组成

```c
#include <string.h>
#include <stdio.h>
int main(void)
{
    const char *string = "abcde312$#@";
    const char *invalid = "*$#";
    size_t valid_len = strcspn(string, invalid);
    if(valid_len != strlen(string))
       printf("'%s' contains invalid chars starting at position %zu\n", string, valid_len);
}
// 'abcde312$#@' contains invalid chars starting at position 8
```


<br>

#### strpbrk （检索字符集）

```c
char* strpbrk(const char* dst, const char* breakset);
```

- `strpbrk` 在 `dst` 所指向的字节串中，扫描来自 `breakset` 字节串的任何字符，并返回指向该字符的指针。不能检索 `\0`。

```c
#include <stdio.h>
#include <string.h>
int main(void)
{
	char str[] = "hello world, friend of mine!";
	const char breakSet[] = " ,!";
	char* tmpstr = str;
	do {
		tmpstr = strpbrk(tmpstr, breakSet);  // 寻找 ' ', ',' '!'
		if (tmpstr) {
			printf("Found %c at str[%d]\n", *tmpstr, tmpstr - str);
			tmpstr += strspn(tmpstr, breakSet); // 跳过 breakSet 中的任意字符
		}
	} while (tmpstr && *tmpstr); // 检查是否到 \0
}
/*
Found   at str[5]
Found , at str[11]
Found   at str[19]
Found   at str[22]
Found ! at str[27]
*/
```

<br>

#### strtok、strtok_s （分割字符串）

```c
char *strtok(char *str, const char *delim);

char *strtok_s(char *restrict str, const char *restrict delim, char **restrict context);
```

- 对 `strtok` 函数的一系列调用将 `str` 字符串分解为一系列标记，每个标记由 `delim` 字符组指定的标记分隔符进行分隔。首次调用将静态绑定字符串 `str` 用于后续调用 `strtok` 继续分离标记。
- `strtok` 分析时使用静态缓冲区，单线程时交替使用可能会导致数据破坏和结果不准确。解析不同字符串时，只能是解析完一个字符串后再开始解析下一个字符串。因此 `strtok` 函数是线程不安全的。
- 每次调用 `strtok` 都会修改 `str`：忽略前面的分隔符，直到遇到非分隔字符时认为是找到了标记的首元，然后继续向后查找分隔字符并使用 `\0` 替换找到的标记分隔符，并返回指向该标记的指针。若继续查找 `str` 的下一个标记，则继续调用 `strtok(NULL, delim)`，返回每次找到的标记，直至某次调用时遇到空终止符而未找到任何标记，此时返回空指针，表示无法继续分离更多标记。

* `strtok_s` 同 `strtok`。`context` 是指向有效上下文指针的指针，使用 `context` 取代了 `strtok` 使用的静态缓冲区，因此可以在同一个线程同时分析多个字符串。`strtok_s` 是线程安全的。

```c
#define _CRT_SECURE_NO_WARNINGS 0 // 0
#include <string.h>
#include <stdio.h>

int main(void)
{
    char input[] = "A bird came down the walk";
    const char* delim = " ";
    char* token;
    printf("Parsing the input string '%s'\n", input);
#if _CRT_SECURE_NO_WARNINGS
    token = strtok(input, delim);
    while (token) {
        puts(token);
        token = strtok(NULL, delim);
    }
#else
    char* next_token;
    token = strtok_s(input, delim, &next_token);
    while (token) {
        puts(token);
        token = strtok_s(NULL, delim, &next_token);
    }
#endif
    printf("Contents of the input string now: '");
    for (size_t n = 0; n < sizeof input; ++n)
        input[n] ? putchar(input[n]) : fputs("\\0", stdout);
    puts("'");
}
/*
Parsing the input string 'A bird came down the walk'
A
bird
came
down
the
walk
Contents of the input string now: 'A\0bird\0came\0down\0the\0walk\0'
*/
```

---
### Functions：功能函数（Miscellaneous functions）
#### memset （初始化字符）

```c
void * memset(void *dst, int ch, size_t count);
```

- `memset` 函数将 `ch` 的值（转换为 `unsigned char`）复制到 `dst` 所指向对象的前 `count` 个字符中。替换成功则返回 `dst` 的副本，否则返回空指针。
- `memset` 可用于清除固定大小的缓冲区，即 `memset(buf,0,bufSize)`。

```c
#include <string.h>
#include <stdio.h>
int main(void)
{
	char str[] = "aaaaBBBBCCCC";
	if (memset(str, 'A', 4))
		printf("Str = %s\n", str);
} // Str = AAAABBBBCCCC
```

<br>

#### strlen （字符串长度）

```c
size_t strlen(const char *str);
```

- `strlen` 函数计算 `str` 指向字符串的长度。即返回空终止符之前的字符数。

<br>

#### strerror、strerror_s

```c
char * strerror(int errnum);

errno_t strerror_s(char *buf, rsize_t bufSize, errno_t errnum);
```

- `strerror` 函数返回指向系统错误码 `errnum` （一般来自于 `errno`）的文本表示的指针，其内容是特定于语言环境的，等同于 `perror`。所指向的数组不能被程序修改，但可以被随后调用 `strerror` 函数覆盖。

* `strerror` 将对应错误码的文本表示存储到 `buf` 中，不写于多于 `bufSize-1` 个字符，并在末尾添加空终止符。 

```c
#define _CRT_SECURE_NO_WARNINGS 0 // 0
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int len = strlen(strerror(1));
	char* strerr = calloc(len + 1, sizeof(char));
	errno_t err;
	if (!(err = strerror_s(strerr, len + 1, 1))) {
		printf("ERROR : %s\n",strerr);
	}
	free(strerr);
} // ER
```

---
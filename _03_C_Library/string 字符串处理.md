## C 字符串处理（String handling）：string.h

```c
#define __STDC_VERSION_STRING_H__		202311L
```

`string.h` 提供一些操作字符类型的数组和其他被视为字符类型数组的对象的函数等。确定数组长度的方法有很多，但在所有的情况下，`char *` 或 `void *` 参数都指向数组的初始（最低寻址）字符。如果在对象的末尾之外访问数组，则行为未定义。

当一个参数声明为 `size_t n` 时，它指定了一个函数的数组长度，在调用该函数时，`n` 的值可以为零。除非对一些特定函数的描述中另有明确说明，否则此类调用的指针参数仍应具有有效值。在这样的调用中，定位字符的函数没有找到匹配项，比较两个字符序列的函数返回零，复制字符的函数复制零个字符。

以下的所有函数，每个字符都被解释为 `unsigned char` 类型，因此每种可能的对象表示都是有效的，并且具有不同的值。

---
### Functions：复制（Copying functions）

#### memcpy、memcpy_s （缓冲区复制）

```c
void * memcpy(void * restrict dst, const void * restrict src, size_t size);
errno_t memcpy_s( void *restrict dst, rsize_t dstSize,
                  const void *restrict src, rsize_t srcSize);
```

`memcpy` 函数将 `src` 所指向的对象中的 `size` 个字符复制到 `dst` 所指向的对象中。如果复制发生在重叠的对象之间，则行为未定义。复制成功时返回 `dst` 的副本，本质为更底层操作的临时内存地址（不建议直接使用）。

`memcpy_s` 同 `memcpy`，失败时将清除 `dst` 整个目标范围。它在运行时检测下列错误，并调用当前安装的约束处理函数：
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

>---

#### memccpy

```c
void *memccpy(void * restrict dest, const void * restrict src, int c, size_t n);
```

`memccpy` 函数将字符从 `src` 指向的对象复制到 `dest` 指向的对象，在第一次复制字符 `c`（转换为 `unsigned char`）后停止，或者在复制 `n` 个字符后停止，以先发生者为准。如果复制发生在重叠的对象之间，则行为未定义。

`memccpy` 函数返回一个指针，指向 `dest` 中复制的 `c` 之后的字符，或者如果在 `src` 的前 `n` 个字符中没有找到 `c`，则返回一个空指针。

```c
#include <string.h>
#include <stdio.h>

int main(void)
{
    char bigString[1000];
    char *end = bigString + sizeof bigString;

    char *p = memccpy(bigString, "John, ", '\0', sizeof bigString - 1);
    if (p) p = memccpy(p - 1, "Paul, ", '\0', end - p);
    if (p) p = memccpy(p - 1, "George, ", '\0', end - p);
    if (p) p = memccpy(p - 1, "Joel ", '\0', end - p);
    if (!p) end[-1] = '\0';

    puts(bigString); // John, Paul, George, Joel
}
```

>---

#### memmove、memmove_s （缓冲区移动）

```c
void *memmove(void *dst, const void *src, size_t size);
errno_t memmove_s(void *dst, rsize_t dstSize, const void *src, rsize_t srcSize);
```

`memmove` 函数从 `src` 所指向的对象复制 `size` 个字节到 `dst` 所指向的对象，若 `dst` 或 `src` 为非法或空指针则行为未定义。两个对象都被转译成 `unsigned char` 的数组。复制的发生就好像 `src` 指向的对象中的 `size` 个字符首先被复制到一个 `size` 个字符的临时数组中，该数组不与 `dst` 和 `src` 指向的对象重叠，然后临时数组中的 `size` 个字符被复制到 `dst` 指向的对象中。函数返回 `dst` 的值。

`memmove_s` 同 `memmove`，失败时将清除 `dst` 整个目标范围。它在运行时检测下列错误，并调用当前安装的约束处理函数：
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

>---

#### strcpy、strcpy_s （字符串复制）

```c
char *strcpy(char * restrict dst, const char * restrict src);
errno_t strcpy_s(char *restrict dst, rsize_t dstSize, const char *restrict src);
```

`strcpy` 复制 `src` 所指向的空终止字节字符串，包含空终止符，到首元素为 `dst` 所指的字符数组。`dst` 的长度不足则行为未定义。若 `src` 不是指向空终止字节字符串的指针则行为未定义。如果复制发生在重叠的对象之间，则行为未定义。成功时返回 `dst` 的副本。

`strcpy_s` 同 `src`。`dst` 缓冲区的大小 `dstSize` 不可小于 `src` 的长度。转换失败时会将 `dst[0] = '\0'`。

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

>---

#### strncpy、strncpy_s （字符串截取复制）

```c
char *strncpy(char * restrict dst, const char * restrict src, size_t count);
errno_t strncpy_s(char *restrict dst, rsize_t dstSize,
                  const char *restrict src, rsize_t count);
```

`strncpy` 函数从 `src` 指向的数组复制不超过 `count` 个字符（不复制空字符后面的字符）到 `dst` 指向的数组：
  - 若 `src` 数组是一个小于 `count` 个字符的字符串，则会追加空字符到 `dst` 所指向的数组中，直到写入共 `count` 个字符。
  - 若在完全复制整个 `src` 数组前抵达 `count`，则结果的字符数组不是空终止的（不会自动附加空终止符）。
  - 如果复制发生在重叠的对象之间，则行为未定义。若 `dst` 的长度小于 `count` 或 `src` 字符数组中不包含空终止，则行为未定义。
  - 函数返回 `dst` 的副本。

`strncpy_s` 同 `strncpy`。成功时返回零，错误时返回非零。发生错误时写入零到 `dst[0]`。若在完全复制整个 `src` 数组前抵达 `count`，则附加一个空终止符到 `dst[count]`。

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

>---
#### strdup （分配字符串的副本）

```c
char *strdup(const char *s);
```

`strdup` 返回指向作为 `s` 所指向的字符串的副本的空终止字节字符串的指针。如同通过调用 `malloc` 获得新字符串的空间。必须将返回的指针传递给 `free` 以避免内存泄漏。若出现错误，则返回空指针值并可能设置 `errno`。

函数返回指向新分配的字符串的指针，或若出现错误则返回空指针。

```c
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    const char *s1 = "Duplicate me!";
    char *s2 = strdup(s1);
    printf("s2 = \"%s\"\n", s2);
    free(s2);  // s2 = "Duplicate me!"
}
```

>---
#### strndup （分配指定大小的字符串副本）

```c
char *strndup(const char *s, size_t n);
```

`strndup` 返回指向含有来自 `s` 所指向的字符串的至多 `n` 个字节的副本的空终止字节字符串的指针。如同通过调用 `malloc` 获得新字符串的空间。若在首 `n` 个字节中未遇到空终止符，则在该数组副本上追加一个 null。必须将返回的指针传递给 `free` 以避免内存泄漏。

`strndup` 函数返回一个指向创建的字符串的首字符的指针；若无法分配，则返回空指针值。

```c
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    const size_t n = 3;
 
    const char *src = "Replica";
    char *dup = strndup(src, n);
    printf("strndup(\"%s\", %lu) == \"%s\"\n", src, n, dup);
    free(dup);
 
    src = "Hi";
    dup = strndup(src, n);
    printf("strndup(\"%s\", %lu) == \"%s\"\n", src, n, dup);
    free(dup);
 
    const char arr[] = {'A','B','C','D'}; // NB ：无尾随 '\0'
    dup = strndup(arr, n);
    printf("strndup({'A','B','C','D'}, %lu) == \"%s\"\n", n, dup);
    free(dup);
}
/*
strndup("Replica", 3) == "Rep"
strndup("Hi", 3) == "Hi"
strndup({'A','B','C','D'}, 3) == "ABC"
*/
```

---
### Functions：字符串拼接（Concatenation functions）
#### strcat、strcat_s （字符串拼接）

```c
char * strcat(char * restrict dst, const char * restrict src);
errno_t strcat_s(char *restrict dst, rsize_t dstSize, const char *restrict src);
```

`strcat`、`strncat` 函数将 `src` 所指向的字符串的副本（包括空终止符）附加到 `dst` 所指向的字符串的末尾。`src` 的初始字符将覆盖 `dst` 末尾的空终止符。如果复制发生在重叠的对象之间，则行为未定义。

若 `dst` 数组长度不足以容纳 `src` 附加后的长度则行为未定义。拼接成功时返回 `dst` 副本的值。

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

>---

#### strncat、strncat_s （字符串片段拼接）

```c
char * strncat(char * restrict dst, const char * restrict src, size_t count);

errno_t strncat_s(char * restrict dst, rsize_t dstSize, const char * restrict src, rsize_t count);
```

`strncat`、`srtncat_s` 用于后附 `src` 字符串中的 `count` 个数目的字符（空字符及其后面的字符不追加）追加到 `dst` 字符串的末尾处。`src` 的起始字符覆盖 `dst` 末尾的空字符。若源与目标对象重叠，则行为未定义。

`dst` 长度要足够容纳即将要附加的字符数，否则行为是未定义的。函数依次读取 `src` 的字符并插入到 `dst` 的末尾（空终止符的位置），直到遇到 `src` 的终止符或读取到 `count` 个字符才停止。一个终止空字符总是附加到结果。

函数发生错误时会将 `dst` 原始空终止的位置重新置为 0。

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

由比较函数 `memcmp`、`strcmp` 和 `strncmp` 返回的非零值的符号由第一对字符（均解释为 `unsigned char`）的值之间的差的符号确定，这两个字符在被比较的对象中不同。

#### memcmp （比较缓冲区）

```c
int memcmp(const void* lhs, const void* rhs, size_t count);
```

`memcmp` 函数用于比较 `lhs` 和 `rhs` 所指对象的前 `count` 个字节。按照字典序进行比较（每一对字节转译成 `unsigned char`），返回一个大于、等于或小于零的整数，对应于，`lhs` 所指向的对象大于、等于或小于 `rhs` 所指向的对象。

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

>---

#### strcmp、strncmp （比较字符串）

```c
int strcmp(const char *lhs, const char *rhs);       // 比较字符串
int strncmp(const char *lhs, const char *rhs, size_t count);  // 比较字符串前 count 个字符
```

`strcmp` 用于比较两个字符串之间的字典序。此函数不考虑本地环境。

`strncmp` 用于比较两个字符串最多 `count` 个字符序列的字典序（不比较空字符后面的字符）。超过字符串结尾的访问比较，行为未定义。此函数不考虑本地环境。

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

>---

#### strcoll （以本地比较字符串）

```c
int strcoll(const char *lhs, const char *rhs);
```

`strcoll` 函数将 `lhs` 指向的字符串与 `rhs` 指向的字符串进行比较，两者都被解释为适合当前区域设置的 `LC_COLLATE` 类别。

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

>---

#### strxfrm （变换字符串）

```c
size_t strxfrm(char *restrict dst, const char *restrict src, size_t count);
```

`strxfrm` 变换 `src` 字符串为 `strcoll` 函数解释原始字符串为符合当前区域设置的 `LC_COLLATE` 类别的变换字符串，此时用 `strcmp` 比较两个变换字符串的结果和 `strcoll` 直接比较原始字符串的结果相等。

`strxfrm` 函数将变换后的字符串的首 `count` 个字符写入 `dst` 对象，包括空终止符，并返回完整转换后字符串（不包括终止空字符）的长度（该长度为 `strxfrm(NULL, src, 0)` 的返回结果）。

`1 + strxfrm(nullptr, s, 0)` 表达式的值表示为保存 `s` 指向的字符串的转换所需的数组大小。

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

以下定义的无状态搜索函数（`memchr`、`strchr`、`strpbrk`、`strrchr`、`strstr`）是泛型函数。这些函数在要搜索的数组的限定条件上是泛型的，并且会返回一个指向与传递的数组具有相同限定条件的元素的结果指针。如果要搜索的数组是 `const` 限定的，则结果指针将指向 `const` 限定的元素；否则结果指针指向非限定元素。

这些泛型函数的外部声明有一个具体的函数类型，它返回一个指向非限定元素的指针（指定为 *`QChar`* 时为 `char` 类型，指定为 *`QVoid`* 时为 `void` 类型），并接受一个指向相同类型的 `const` 限定数组的指针进行搜索。此签名支持所有正确的用法。如果这些泛型函数中的任何一个的宏定义被禁止访问实际函数，则具有相应具体类型的外部声明是可见的。

#### memchr （数组中检索字符）

```c
/*QVoid*/ *memchr( /*QVoid*/ *ptr, int ch, size_t count );
void* memchr(const void* ptr, int ch, size_t count);
```

`memchr` 泛型函数在 `ptr` 指向的对象的前 `count` 个字符（每个字符都被解释为 `unsigned char`）中定位第一个出现的 `ch`（转换为 `unsigned char`）。实现的行为应该像它顺序读取字符一样，并在找到匹配字符后立即停止。

`memchr` 泛型函数返回一个指向已定位字符的指针，如果字符不在对象中，则返回一个空指针。若在所搜索的数组结尾后发生访问，则行为未定义。若 `ptr` 为空指针则行为未定义。

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

>---

#### strchr、strrcar （字符串中检索字符）

```c
/*QChar*/ *strchr( /*QChar*/ *str, int ch );
char *strchr(const char *str, int ch);      // 检索字符 ch 在字符串中首次出现的位置

/*QChar*/ *strrchr( /*QChar*/ *str, int ch );
char *strrchr(const char *str, int ch);     // 检索字符 ch 在字符串中最后出现的位置       
```

`strchr` 泛型函数定位 `str` 所指向的字符串中首次出现的 `ch`（转换为 `char`）。结束的 `null` 字符被认为是字符串的一部分。函数返回一个指向所定位字符的指针，如果字符串中没有出现该字符，则返回一个空指针。

`strrchr` 泛型函数定位 `str` 所指向的字符串中最后出现的 `ch`（转换为 `char`）。结束的 `null` 字符被认为是字符串的一部分。函数返回一个指向所定位字符的指针，如果字符串中没有出现该字符，则返回一个空指针。

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

>---

#### strstr （检索子字符串）

```c
/*QChar*/ *strstr( /*QChar*/ *str, const char *substr );
char *strstr(const char* str, const char* substr);
```

`strstr` 泛型函数定位 `substr` 字符串中的字符序列（不包括终止空字符）在 `str` 字符串中首次出现的位置。函数返回一个指向已定位字符串的指针，如果未找到字符串，则返回空指针。如果 `substr` 指向长度为零的字符串，则返回 `str`。

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

>---

#### strspn （从起始检索字符集连续包含数量）

```c
size_t strspn(const char *dst, const char *set)
```

`strspn` 函数计算 `dst` 字节串的最大起始段长度，该段仅由 `set` 字符串中 **包含的字符** 组成。

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

>---

#### strcspn （从起始检索字符集连续不包含数量）

```c
size_t strcspn(const char *dst, const char *set);
```

`strcspn` 函数计算 `dst` 字符串的最大起始段的长度，该字符串完全由 `set` 字符串中 **以外的字符** 组成。函数返回起始段的长度。

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

>---

#### strpbrk （检索字符集）

```c
/*QChar*/ *strpbrk( /*QChar*/ *dst, const char *breakset );
char* strpbrk(const char* dst, const char* breakset);
```

`strpbrk` 泛型函数定位 `breakset` 字符串中任何字符在 `dst` 字节串中的第一个匹配项，并返回指向该字符的指针；如果 `breakset` 中没有字符出现在 `dst` 中，则返回一个空指针。不能检索 `\0`。

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

>---

#### strtok、strtok_s （分割字符串）

```c
char *strtok(char * restrict str, const char * restrict delim);
char *strtok_s(char *restrict str, const char *restrict delim, char **restrict context);
```

对 `strtok` 函数的一系列调用将 `str` 字符串分解为一系列标记，每个标记由 `delim` 字符组指定的标记分隔符进行分隔。首次调用将静态绑定字符串 `str` 用于后续调用 `strtok` 继续分离标记。

若 `str` 不是空指针，则调用被当做 `strtok` 对此特定字符串的首次调用。函数搜索首个不含于 `delim` 的字符。
- 若找不到这种字符，则 `str` 中完全没有记号，而函数返回空指针。
- 若找到这种字符，则它是记号的起始。然后函数从该点搜索首个含于 `delim` 的字符。
  - 若找不到这种字符，则 `str` 只有一个记号，而将来对 `strtok` 的调用将返回空指针；
  - 若找到这种字符，则用空字符 `'\0'` 替换它，并将指向下个字符的指针存储于静态位置，以为后继调用所用。
- 然后函数返回指向记号起始的指针。

若 `str` 为空指针，则将调用当做对 `strtok` 的后继调用，函数从先前调用中它剩下的位置开始。行为如同将先前存储的指针作为 `str` 传递。

若 `str` 或 `delim` 不是指向空终止字节字符串的指针，则行为未定义。

`strtok_s` 同 `strtok`。`context` 是指向有效上下文指针的指针，使用 `context` 取代了 `strtok` 使用的静态缓冲区，因此可以在同一个线程同时分析多个字符串。`strtok_s` 是线程安全的。

```c
#include <string.h>

int main()
{
	static char str[] = "?a???b,,,#c";
	char *t;

	t = strtok(str, "?"); 		// t points to the token "a"
	t = strtok(nullptr, ","); 	// t points to the token "??b"
	t = strtok(nullptr, "#,"); 	// t points to the token "c"
	t = strtok(nullptr, "?"); 	// t is a null pointer
}
```

---
### Functions：功能函数（Miscellaneous functions）
#### memset、memset_explicit （以字符填充缓冲区）

```c
void * memset(void *dst, int ch, size_t count);
void * memset_explicit( void *dst, int ch, size_t count );
```

`memset` 函数将 `ch` 的值（转换为 `unsigned char`）复制到 `dst` 所指向对象的前 `count` 个字符中。替换成功则返回 `dst` 的副本，否则返回空指针。

`memset_explicit` 同 `memset`，但对敏感信息是安全的。此函数的目的是使存储在对象中的敏感信息不可访问。
  
`memset` 可用于清除固定大小的缓冲区，即 `memset(buf, 0, bufSize)`。

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

>---

#### strlen （字符串长度）

```c
size_t strlen(const char *str);
```

`strlen` 函数计算 `str` 指向字符串的长度。即返回空终止符之前的字符数。

```c

#include <string.h>

int main(void)
{
    return strlen("Hello World!");   // 12
}
```

>---

#### strerror、strerror_s

```c
char * strerror(int errnum);
errno_t strerror_s(char *buf, rsize_t bufSize, errno_t errnum);
```

`strerror` 函数返回指向系统错误码 `errnum` （`errnum` 通常从 `errno` 变量获得）的文本表示的指针，等同于 `perror()` 打印的描述。所指向的数组不能被程序修改，但对 `strerror` 函数的后继调用可能重写该字符串。字符串的内容是特定于本地环境的。

如果返回值是在对 `strerror` 函数的后续调用之后使用的，或者在调用该函数以获取返回值的线程退出之后使用的，则该行为是未定义的。

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
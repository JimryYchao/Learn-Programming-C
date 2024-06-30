## C 字符串处理：string.h

`string.h` 提供一些操作字符类型的数组和其他被视为字符类型数组的对象的函数等。确定数组长度的方法有很多，但在所有的情况下，`char *` 或 `void *` 参数都指向数组的初始（最低寻址）字符。如果在对象的末尾之外访问数组，则行为未定义。

当一个参数声明为 `size_t n` 时，它指定了一个函数的数组长度，在调用该函数时，`n` 的值可以为零。除非对一些特定函数的描述中另有明确说明，否则此类调用的指针参数仍应具有有效值。在这样的调用中，定位字符的函数没有找到匹配项，比较两个字符序列的函数返回零，复制字符的函数复制零个字符。

以下的所有函数，每个字符都被解释为 `unsigned char` 类型，因此每种可能的对象表示都是有效的，并且具有不同的值。

>---
### 复制

| Specifier              | Description                                                                                      |
| :--------------------- | :----------------------------------------------------------------------------------------------- |
| `memcpy`, `memcpy_s`   | 缓冲区复制。如果复制发生在重叠的对象之间，则行为未定义。                                         |
| `memccpy`              | 连续复制字符，直至遇到 `c` 或已复制 `n` 个字符停止。如果复制发生在重叠的对象之间，则行为未定义。 |
| `memmove`, `memmove_s` | 缓冲区移动。                                                                                     |
| `strcpy`, `strcpy_s`   | 字符串复制，包含空终止符。                                                                       |
| `strncpy`, `strncpy_s` | 字符串截取复制。                                                                                 |
| `strdup`, `strndup`    | 分配字符串的副本。返回的指针需要显式 `free` 防止内存泄露。                                       |

> memcpy, memcpy_s

```c
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

> memccpy

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

> memmove、memmove_s

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

> strcpy、strcpy_s （字符串复制）


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

> strncpy、strncpy_s （字符串截取复制）


`strncpy` 函数从 `src` 指向的数组复制不超过 `count` 个字符（不复制空字符后面的字符）到 `dst` 指向的数组：
  - 若 `src` 数组是一个小于 `count` 个字符的字符串，则会追加空字符到 `dst` 所指向的数组中，直到写入共 `count` 个字符。
  - 若在完全复制整个 `src` 数组前抵达 `count`，则结果的字符数组不是空终止的（不会自动附加空终止符）。
  - 如果复制发生在重叠的对象之间，则行为未定义。若 `dst` 的长度小于 `count` 或 `src` 字符数组中不包含空终止，则行为未定义。
  - 函数返回 `dst` 的副本。

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

> strdup, strndup 

`strdup` 返回指向作为 `s` 所指向的字符串的副本的空终止字节字符串的指针。如同通过调用 `malloc` 获得新字符串的空间。必须将返回的指针传递给 `free` 以避免内存泄漏。若出现错误，则返回空指针值并可能设置 `errno`。

`strndup` 返回指向含有来自 `s` 所指向的字符串的至多 `n` 个字节的副本的空终止字节字符串的指针。

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

>---
### 字符串拼接

| Specifier              | Description      |
| :--------------------- | :--------------- |
| `strcat`, `strcat_s`   | 字符串拼接。     |
| `strncat`、`strncat_s` | 字符串片段拼接。 |
| `strxfrm`              | 变换字符串       |


> strcat、strcat_s

```c
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
### 比较

| Specifier           | Description                                                        |
| :------------------ | :----------------------------------------------------------------- |
| `memcmp`            | 比较缓冲区                                                         |
| `strcmp`, `strncmp` | 比较字符串。                                                       |
| `strcoll`           | 以本地区域设置比较字符串。                                         |
| `strxfrm`           | 解释原始字符串为符合当前区域设置的 `LC_COLLATE` 类别的变换字符串。 |


> strcoll


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

> strxfrm

`strxfrm` 变换 `src` 字符串为 `strcoll` 函数解释原始字符串为符合当前区域设置的 `LC_COLLATE` 类别的变换字符串，此时用 `strcmp` 比较两个变换字符串的结果和 `strcoll` 直接比较原始字符串的结果相等。

`strxfrm` 函数将变换后的字符串的首 `count` 个字符写入 `dst` 对象，包括空终止符，并返回完整转换后字符串（不包括终止空字符）的长度（该长度为 `strxfrm(NULL, src, 0)` 的返回结果）。`1 + strxfrm(nullptr, s, 0)` 表达式的值表示为保存 `s` 指向的字符串的转换所需的数组大小。

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

>---
### 检索

| Specifier            | Description                                                          |
| :------------------- | :------------------------------------------------------------------- |
| `memchr`             | 数组中检索字符。返回一个指向已定位字符的指针或空指针。               |
| `strchr`, `strrcar`  | 字符串中检索字符。`strchr` 检索首次出现，`strrchr` 检索最后出现。    |
| `strstr`             | 检索子字符串。                                                       |
| `strspn`             | 从起始检索字符集连续包含数量。                                       |
| `strcspn`            | 从起始检索字符集连续不包含数量。                                     |
| `strpbrk`            | 定位字符集中任何字符在 `dst` 字节串中的第一个匹配项。不能检索 `\0`。 |
| `strtok`, `strtok_s` | 分割字符串                                                           |


> strchr、strrcar


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

> strspn


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

> strcspn

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

> strpbrk

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

> strtok、strtok_s


对 `strtok` 函数的一系列调用将 `str` 字符串分解为一系列标记，每个标记由 `delim` 字符组指定的标记分隔符进行分隔。首次调用将静态绑定字符串 `str` 用于后续调用 `strtok` 继续分离标记。

若 `str` 不是空指针，则调用被当做 `strtok` 对此特定字符串的首次调用。函数搜索首个不含于 `delim` 的字符。
- 若找不到这种字符，则 `str` 中完全没有记号，而函数返回空指针。
- 若找到这种字符，则它是记号的起始。然后函数从该点搜索首个含于 `delim` 的字符。
  - 若找不到这种字符，则 `str` 只有一个记号，而将来对 `strtok` 的调用将返回空指针；
  - 若找到这种字符，则用空字符 `'\0'` 替换它，并将指向下个字符的指针存储于静态位置，以为后继调用所用。
- 然后函数返回指向记号起始的指针。

若 `str` 为空指针，则将调用当做对 `strtok` 的后继调用，函数从先前调用中它剩下的位置开始。行为如同将先前存储的指针作为 `str` 传递。若 `str` 或 `delim` 不是指向空终止字节字符串的指针，则行为未定义。

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

>---
### 功能函数

| Specifier | Description |
| :-------- | :---------- |
`memset`, `memset_explicit` | 以字符填充缓冲区。
`strlen` | 字符串长度。
`strerror`, `strerror_s` | 返回指向系统错误码 `errnum` （`errnum` 通常从 `errno` 变量获得）的文本表示的指针。

> memset、memset_explicit

`memset_explicit` 同 `memset`，但对敏感信息是安全的。此函数的目的是使存储在对象中的敏感信息不可访问。`memset` 可用于清除固定大小的缓冲区，即 `memset(buf, 0, bufSize)`。

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

> strerror_s

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
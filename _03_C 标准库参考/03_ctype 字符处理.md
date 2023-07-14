## [C 字符处理：ctype.h](./clib-test/s_ctype.c)

字符处理库，声明了一些用于对字符进行分类和映射的函数。这些函数的行为受当前语言环境的影响。

---
### 字符分类函数（Character classification functions）

#### isalnum

```c
int isalnum(int c);
```

`isalnum` 函数测试字符是否为数字或字母（`isalpha` 和 `isdigit` 为真的任何字符，[A-Za-z0-9]）。

<br>

#### isalpha

```c
int isalpha(int c)
```

`isalpha` 函数测试 `isupper` 或 `islower` 为真的任何字符，或者是特定于语言环境的一组字母字符中的任何字符，其中 `iscntrl`、`isdigit`、`ispunct` 或 `isspace`都不为真。

在 “C” 语言环境中，`isalpha`仅对 `isupper` 或 `islower` 为真的字符返回真，[A-Za-z]）。

<br>

#### isblank

```c
int isblank(int c);
```

`isblank` 函数测试标准空白字符（`' '`）或 `isspace`为 `true` 的特定于本地的一组字符中的任何字符，该字符用于分隔文本行的单词。

标准的空白字符：空格（`' '`）、水平制表符（`'\t'`）、换行符（`'\n'`）、垂直制表符（`'\v'`）、换页符（`'\f'`）、回车符（`'\r'`）。在 "C" 语言环境中，`isblank` 仅对标准空白字符返回 `true`。

<br>

#### iscntrl

```c
int iscntrl(int c);
```

`iscntrl` 测试任何控制字符。

<br>

#### isdigit

```c
int isdigit(int c);
```

`isdigit` 测试任何十进制数字字符。

<br>

#### isgraph

```c
int isgraph(int c);
```

`isgraph` 函数测试除空格以外的任何打印字符。

<br>

#### islower

```c
int islower(int c);
```

`islower` 函数测试小写字母或特定于语言环境的一组字符中的任何字符，其中 `iscntrl`、`isdigit`、`ispunct` 或 `isspace` 都不为真。在 "C" 语言环境中，`islower`` 仅对小写字母返回 `true`。

<br>

#### isprint

```c
int isprint(int c);
```

`isprint` 函数测试除空格以外的任何打印字符。

<br>

#### ispunct

```c
int ispunct(int c);
```

`ispunct` 函数测试任何打印字符，该字符是特定于语言环境的一组标点字符之一，且 `isspace`和 `isalnum` 都不为真。

在 "C" 语言环境中，`ispunct` 对每个 `isspace` 和 `isalnum` 都不为真的打印字符返回真。

<br>

#### isspace

```c
int isspace(int c);
```

`isspace` 函数测试标准空白字符或 `isalnum` 为 `false` 的特定于语言环境的一组字符中的任何字符。

标准的空白字符：空格（`' '`）、水平制表符（`'\t'`）、换行符（`'\n'`）、垂直制表符（`'\v'`）、换页符（`'\f'`）、回车符（`'\r'`）。在 "C" 语言环境中，`isblank` 仅对标准空白字符返回 `true`。

<br>

#### isupper

```c
int isupper(int c);
```

`isupper` 函数测试大写字母的任何字符，或者特定于语言环境的一组字符中的任何字符，其中 `iscntrl`、`isdigit`、`ispunct` 或 `isspace` 都不为真。

在 "C" 语言环境中，`isupper` 仅对大写字母返回 `true`。

<br>

#### isxdigit

```c
int isxdigit(int c);
```

`isxdigit` 函数测试任何十六进制数字字符。


---
### 字符映射函数（Character case mapping functions） 

#### tolower

```c
int tolower(int c);
```

`tolower` 函数将大写字母转换为相应的小写字母。

<br>

#### toupper

```c
int toupper(int c);
```

`toupper` 函数将小写字母转换为相应的大写字母。
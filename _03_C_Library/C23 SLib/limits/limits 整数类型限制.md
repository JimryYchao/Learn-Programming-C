## C 整数类型限制：limits.h

`limits.h` 定义了一些宏，可以扩展为标准整数类型的各种限制和参数。这些宏适用于条件表达式包含预处理指令的常量表达式。

>---
### 整数类型的宽度

| Specifier         | Description                                        |
| :---------------- | :------------------------------------------------- |
| `CHAR_BIT`        | 非位域的最小对象的位数（字节）。                   |
| `BOOL_WIDTH`      | `bool` 的宽度。                                    |
| `UCHAR_WIDTH`     | `unsigned char` 的宽度。                           |
| `SCHAR_WIDTH`     | `signed char` 的宽度。                             |
| `CHAR_WIDTH`      | `char` 的宽度。                                    |
| `USHRT_WIDTH`     | `unsigned short` 的宽度。                          |
| `SHRT_WIDTH`      | `short` 的宽度。                                   |
| `UINT_WIDTH`      | `unsigned int` 的宽度。                            |
| `INT_WIDTH`       | `int` 的宽度。                                     |
| `ULONG_WIDTH`     | `unsigned long` 的宽度。                           |
| `LONG_WIDTH`      | `long` 的宽度。                                    |
| `ULLONG_WIDTH`    | `unsigned long long` 的宽度。                      |
| `LLONG_WIDTH`     | `long long` 的宽度。                               |
| `BITINT_MAXWIDTH` | `_BitInt(N)`, 至少为 `ULLONG_WIDTH`。              |
| `MB_LEN_MAX`      | 对于任何支持的区域设置，多字节字符中的最大字节数。 |

>---
### 整数类型的范围限制

| Specifier    | Value                  | Description               |
| :----------- | :--------------------- | :------------------------ |
| `BOOL_MAX`   | 1                      | 2 <sup>`BOOL_WIDTH`</sup> − 1      |
| `UCHAR_MAX`  | 255                    | 2 <sup>`UCHAR_WIDTH`</sup> − 1     |
| `SCHAR_MAX`  | +127                   | 2 <sup> `SCHAR_WIDTH`−1</sup> − 1 |
| `SCHAR_MIN`  | -128                   | −2 <sup>`SCHAR_WIDTH`−1</sup>    |
| `CHAR_MAX`   | UCHAR_MAX or SCHAR_MAX |
| `CHAR_MIN`   | 0 or SCHAR_MIN         |
| `USHRT_MAX`  | 65535                  | 2 <sup>`USHRT_WIDTH`</sup> − 1     |
| `SHRT_MAX`   | +32767                 | 2 <sup>`SHRT_WIDTH`−1</sup> − 1  |
| `SHRT_MIN`   | -32768                 | −2 <sup>`SHRT_WIDTH`−1</sup>     |
| `UINT_MAX`   | 65535                  | 2 <sup>`UINT_WIDTH`</sup> − 1      |
| `INT_MAX`    | +32767                 | 2 <sup>`INT_WIDTH`−1</sup> − 1   |
| `INT_MIN`    | -32768                 | −2 <sup>`INT_WIDTH`−1</sup>      |
| `ULONG_MAX`  | 4294967295             | 2 <sup>`ULONG_WIDTH`</sup> − 1     |
| `LONG_MAX`   | +2147483647            | 2 <sup>`LONG_WIDTH`−1</sup> − 1  |
| `LONG_MIN`   | -2147483648            | −2 <sup>`LONG_WIDTH`−1</sup>     |
| `ULLONG_MAX` | 18446744073709551615   | 2 <sup>`ULLONG_WIDTH`</sup> − 1    |
| `LLONG_MAX`  | +9223372036854775807   | 2 <sup>`LLONG_WIDTH`−1</sup> − 1 |
| `LLONG_MIN`  | -9223372036854775808   | −2 <sup>`LLONG_WIDTH`−1</sup>    |

---
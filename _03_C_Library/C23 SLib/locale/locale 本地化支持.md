## C 本地化支持：locale.h

`locale.h` 提供查询和设置区域支持的方法。

>---
### lconv：区域约定结构

`lconv` 包含本地环境定义的数值和货币格式化规则。其中除了 `decimal_point`，每个 `char *` 成员都可以指向 `""`，指示该值在当前语言环境不可用或长度为零；`char` 类型成员均为非负数，任何一个都可以是 `CHAR_MAX`，以表示该值在当前区域环境不可用。在 `"C"` 区域设置中，各成员应具有注释中指定的值。 

```c 
struct lconv
{
    // 非货币数值格式化参数
    char* decimal_point;        // "." // 用于格式化非货币量的小数点字符
    char* thousands_sep;        // ""  // 在格式化的非货币量中，用于分隔小数点字符前的数字组的字符
    char* grouping;             // ""  // 一个字符串，其元素指示格式化的非货币量中每组数字的大小

    // 货币数值格式化参数
    char* mon_decimal_point;    // ""  // 用于格式化货币数量的小数点
    char* mon_thousands_sep;    // ""  // 格式化货币量中小数点前的数字组的分隔符
    char* mon_grouping;		    // ""  // 一个字符串，其元素指示格式化货币量中每组数字的大小
    char* positive_sign;        // ""  // 用于指示非负值格式货币量的字符串
    char* negative_sign;        // ""  // 用于指示负值格式货币量的字符串

    // 本地货币数值格式化参数
    char* currency_symbol;      // ""  		 // 适用于当前区域设置的本地货币符号
    char  frac_digits;          // CHAR_MAX  // 要在本地格式化货币量中显示的小数位数（小数点后的数字）
    char  p_cs_precedes;        // CHAR_MAX  // 若 currency_symbol 置于非负本地格式货币量的值之前则为 1，于其后则为 ​0​
    char  n_cs_precedes;        // CHAR_MAX  // 若 currency_symbol 置于负本地格式货币量的值之前则为 1，于其后则为 ​0​
    char  p_sep_by_space;       // CHAR_MAX  // 设置为一个值，指示 currency_symbol、positive_sign 及非负货币量的分隔
    char  n_sep_by_space;       // CHAR_MAX  // 设置为一个值，指示 currency_symbol、positive_sign 及负货币量的分隔
    char  p_sign_posn;          // CHAR_MAX  // 设置为一个值，指示非负货币量中 positive_sign 的位置
    char  n_sign_posn;          // CHAR_MAX  // 设置为一个值，指示负货币量中 negative_sign 的位置

    // 国际货币数值格式化参数
    char* int_curr_symbol;      // ""  		 // 适用于当前区域设置的国际货币符号
    char  int_frac_digits;      // CHAR_MAX  // 在国际格式的货币量中显示的小数位数（小数点后的数字）

	char  int_p_cs_precedes;    // CHAR_MAX	 // 如果 int_curr_symbol 置于非负国际格式货币量值的前面或后面，则设置为 1 或 0
	char  int_n_cs_precedes;    // CHAR_MAX  // 如果 int_curr_symbol 置于负国际格式货币量值的前面或后面，则设置为 1 或 0
	char  int_p_sep_by_space;   // CHAR_MAX  // 设置为一个值，该值指示 int_curr_symbol、符号字符串和非负国际格式货币数量的值的分隔
	char  int_n_sep_by_space;   // CHAR_MAX  // 设置为一个值，该值指示 int_curr_symbol、符号字符串和负国际格式货币数量的值的分隔
	char  int_p_sign_posn;      // CHAR_MAX  // 设置为一个值，该值指示非负国际格式货币量的 positive_sign 的位置
	char  int_n_sign_posn;      // CHAR_MAX  // 设置为一个值，该值指示负数国际格式货币量的 negative_sign 的位置
}
```

- `mon_grouping` 和 `grouping` 的值解释为：
  - `CHAR_MAX`：不执行任何分组。
  - 0：前一元素将重复英语剩余的数字。
  - n：构成当前组的位数，检查下一个元素以确定当前组前下一组数字的大小。（例如，一般常为 `\003` 三位数字分组）

+ `currency_symbol` 和 `int_curr_symbol` 的值解释为：
  - 前三个字符指定字母本地（国际）货币符号，表现形式参考货币或资金表示形式 `ISO 4217`。
  - 第四个字符（`\0`）将货币符号与货币数量分隔开来。
 
- `p_cs_precedes` 和 `n_cs_precedes` 的值解释为：
  - 0：货币符号位于非负（负）货币量之后。
  - 1：货币符号位于非负（负）货币量之前。

+ `p_sep_by_space`、`n_sep_by_space`、`int_p_sep_by_space`、`int_n_sep_by_space` 的值解释为：
  - 0：没有空格分隔货币符号和数值。
  - 1：如果货币符号和符号字符串相邻，则用空格将它们与值分隔开；否则，用空格将货币符号与数值分隔开。
  - 2：如果货币符号和符号字符串相邻，则用空格分隔它们；否则，用空格分隔符号字符串和值。

- `p_sign_posn`、`n_sign_posn`、`int_p_sign_posn`、`int_n_sign_posn` 的值解释为：
  - 0：数量和货币符号用括号括起来。
  - 1：符号字符串位于数量和货币符号之前。
  - 2：符号字符串接在数量和货币符号之后。
  - 3：符号字符串紧接在货币符号之前。
  - 4：符号字符串紧跟在货币符号之后。

>---
### 区域类别

| Specifier     | Description                                                                                                                | Value |
| :------------ | :------------------------------------------------------------------------------------------------------------------------- | :---- |
| `LC_ALL`      | 表示选择整个本地区域环境                                                                                                   | 0     |
| `LC_COLLATE`  | 本地区域中的对照类别，影响 `strcoll`、`strxfrm` 等函数的行为。                                                             | 1     |
| `LC_CTYPE`    | 本地区域中的字符分类类别，影响字符处理函数以及多字节或宽字符函数的行为。                                                   | 2     |
| `LC_MONETARY` | 本地区域中的货币格式化类别，影响 `localeconv` 函数返回的货币格式信息。                                                     | 3     |
| `LC_NUMERIC`  | 本地区域中的数值格式化类别，影响格式化输入或输出函数和字符串转换函数的小数点字符，以及 `localeconv` 返回的非货币格式信息。 | 4     |
| `LC_TIME`     | 本地区域中的时间格式化类别，影响 `strftime` 和 `wcsftime` 函数的行为。                                                     | 5     |
| `LC_MIN`      | 等于 `LC_ALL`                                                                                                              |
| `LC_MAX`      | 等于 `LC_TIME`                                                                                                             |
| `setlocale`   | 尝试设置由 `category` 和 `locale` 参数指定的区域设置。                                                                     |
| `localeconv`  | 根据当前区域设置返回当前线程的 `lconv` 区域约定。函数返回一个指向已填充对象的不可变指针，但可以由该函数的稍后调用修改。    |

> setlocale

函数 `setlocale` 参数 `locale` 的形式可以是：
  - `"locale-name"`：表示简易格式的 IETF 标准化字符串，参考 Windows 语言代码标识符（LCID）的 [语言标记](https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-lcid/a9eac961-e77d-41a6-90a5-ce1a8b0cdb9c)（例如，`"zh-cn"` 忽略大小写）。
  - `"language[_country-region[.code-page]]"` 表示使用语言（额外信息：国家 / 地区）字符串创建区域设置，其中 [语言字符串集 `language`](https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/language-strings?view=msvc-170) 和 [国家-地区字符串集 `country-region`](https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/country-region-strings?view=msvc-170) 未关联时，则指定国家-地区的默认语言将存储在区域设置中。
  - `".code-page"`：是与区域设置关联的 [ANSI / OEM 代码页](https://learn.microsoft.com/zh-cn/windows/win32/Intl/code-page-identifiers)，特殊值 `.ACP` 将指定国家 / 地区的 ANSI 代码页（ANSI 适用于英语和大多数欧洲语言）；特殊值 `.OCP` 将指定国家 / 地区的 OEM 代码页。一般性建议使用 Unicode，而不是特定的代码页。
  - `"C"`：指定程序语言转换的最小 ANSI 一致性环境。在程序启动时，相当于执行了 `setlocale(LC_ALL, "C")`。
  - `""`：表示区域设置是实现定义的本地环境。
  - `NULL`：`locale` 传入空指针，`setlocale` 函数将返回一个指向与程序当前 `category` 相关联的字符串的指针。程序的区域设置不会被改变。

`setlocale` 函数返回的指向字符串的指针：函数后续调用该字符串及其相关类别时，将恢复到该部分程序的区域设置。该指针指向的字符串不可更改，且该值在随后调用 `setlocale` 函数之后使用，或在调用 `setlocale` 函数获取返回值的线程已经退出后使用，则行为未定义。 

```c
#include <stdio.h>
#include <locale.h>

void Setlocale(const char* locale) {

	char* sl = setlocale(LC_ALL, locale);
	if (sl) {
		printf("[%s] set successful >> %s\n", locale, sl);
		printf("         curr_symbol = %s\n", localeconv()->currency_symbol);
		printf("     int_curr_symbol = %s\n\n", localeconv()->int_curr_symbol);
	}
	else
		printf("[%s] set failed >> %s\n\n", locale, sl);
}

int main()
{
	// locale-name
	puts("\n=====  TEST \"locale-name\" =====\n");
	Setlocale("zh-cn");
	Setlocale("zh-hk");

	// language[_country-region[.code-page]]
	puts("\n=====  TEST \"language\" =====\n");
	Setlocale("norwegian");   // language
	Setlocale("english-uk");  // language

	puts("\n=====  TEST \"language_country-region\" =====\n");
	Setlocale("chinese_china");  // language_country-region
	Setlocale("american_china"); // language_country-region (不匹配时应用 国家地区 country 设置)

	puts("\n=====  TEST \".code-page\" =====\n");
	Setlocale("us");		    // language
	Setlocale("us.OCP");        // language.code-page
	Setlocale("us_china.ACP");  // language_country.code-page (不匹配时应用 国家地区 country 设置)
	Setlocale(".OCP");          // .code-page （language 应用本地区域设置）
	Setlocale("Japanese.437");  // language.code-page

	puts("\n=====  TEST \"C\" =====\n");
	Setlocale("C");    // 最小环境设置，大写 C

	puts("\n=====  TEST \"\" =====\n");
	Setlocale("");	   // 应用本地区域设置

	puts("\n=====  TEST NULL =====\n");
	Setlocale("us");   // 预先 setlocale
	Setlocale(NULL);   // 不修改并返回当前区域设置
}
```

如果为区域设置字符串时可以执行选择，`setlocale` 将返回指向与新区域设置的指定类别相关联的字符串的指针；否则将返回一个空指针，且程序的语言环境不会被改变。

```c
#include <locale.h>
#include <stdio.h>

int main(void)
{
    setlocale(LC_ALL, "en-US.UTF-8");  
    struct lconv* lc = localeconv();
    printf("en-US currency symbol: %s(%s)\n", lc->currency_symbol, lc->int_curr_symbol);
}
// en-US currency symbol: $(USD)
```

使用 `category`，可以为 `setlocale` 函数同时指定所有区域设置类别。

```c
#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "de-DE");
	setlocale(LC_ALL, "LC_MONETARY=en-GB;LC_TIME=es-ES");

	char* sl = setlocale(LC_ALL, NULL);
	printf("%s\n", sl);
}
// LC_COLLATE=de-DE;LC_CTYPE=de-DE;LC_MONETARY=en-GB;LC_NUMERIC=de-DE;LC_TIME=es-ES
```

UCRT 支持使用 UTF-8 代码页，例如，`setlocale(LC_ALL, ".UTF8")` 将当前默认的 Windows ANSI 代码页 (ACP) 用于区域设置，对代码页使用 UTF-8。其中不区分大小写，连字符可省略，它必须位于 `.code-page` 位置。

```c
// 有效的 UTF8 代码页格式
".UTF8"
".UTF-8"
".utf8"
".utf-8"
"en_us.utf8"
"ja_JP.Utf-8"
```

> localeconv

`localeconv` 函数返回一个指向已填充对象的指针。返回值所指向的结构不能被程序修改，但可以被随后对 `localeconv` 函数的调用覆盖。此外，使用类别 `LC_ALL`、`LC_MONETARY` 或 `LC_NUMERIC` 调用 `setlocale` 函数可能会覆盖该结构的内容。

```c
#include <stdio.h>
#include <locale.h>

#define PR(Format, value) printf("["#value"] = " #Format "\n", value)

void print_locale() {
	struct lconv locale = *localeconv();

	PR("%s", locale.decimal_point);
	PR("%s", locale.thousands_sep);
	PR("%u", *locale.grouping);

	PR("%s", locale.mon_decimal_point);
	PR("%s", locale.mon_thousands_sep);
	PR("%u", *locale.mon_grouping);
	PR("%s", locale.positive_sign);
	PR("%s", locale.negative_sign);
	
	PR("%s", locale.currency_symbol);
	PR("%u", locale.frac_digits);
	PR("%u", locale.p_cs_precedes);
	PR("%u", locale.n_cs_precedes);
	PR("%u", locale.p_sep_by_space);
	PR("%u", locale.n_sep_by_space);
	PR("%u", locale.p_sign_posn);
	PR("%u", locale.n_sign_posn);
	
	PR("%s", locale.int_curr_symbol);
	PR("%u", locale.int_frac_digits);
}

int main()
{
	setlocale(LC_ALL, "zh-cn.UTF-8");
	print_locale();
}
/*
[locale.decimal_point] = "."
[locale.thousands_sep] = ","
[*locale.grouping] = "3"
[locale.mon_decimal_point] = "."
[locale.mon_thousands_sep] = ","
[*locale.mon_grouping] = "3"
[locale.positive_sign] = ""
[locale.negative_sign] = "-"
[locale.currency_symbol] = "￥"
[locale.frac_digits] = "2"
[locale.p_cs_precedes] = "1"
[locale.n_cs_precedes] = "1"
[locale.p_sep_by_space] = "0"
[locale.n_sep_by_space] = "0"
[locale.p_sign_posn] = "4"
[locale.n_sign_posn] = "4"
[locale.int_curr_symbol] = "CNY"
[locale.int_frac_digits] = "2"
*/
```

> 下表举例四个国家可能用来格式化货币量的规则

| Country  | 本地格式 (+)  | 本地格式 (-)   | 国际格式 (+) | 国际格式 (-)  |
| :------- | :------------ | :------------- | :----------- | :------------ |
| Country1 | 1.234,56 mk   | -1.234,56 mk   | FIM 1.234,56 | FIM -1.234,56 |
| Country2 | L.1.234       | -L.1.234       | ITL 1.234    | -ITL 1.234    |
| Country3 | ƒ 1.234,56    | ƒ -1.234,56    | NLG 1.234,56 | NLG -1.234,56 |
| Country4 | SFrs.1,234.56 | SFrs.1,234.56C | CHF 1,234.56 | CHF 1,234.56C |

对于这些地区，`localeconv` 可能返回：

|                      | Country1 | Country2 | Country3 | Country4 |
| :------------------- | :------- | :------- | :------- | :------- |
| `mon_decimal_point`  | ","      | ""       | ","      | "."      |
| `mon_thousands_sep`  | "."      | "."      | "."      | ","      |
| `mon_grouping`       | "\3"     | "\3"     | "\3"     | "\3"     |
| `positive_sign`      | ""       | ""       | ""       | ""       |
| `negative_sign`      | "-"      | "-"      | "-"      | "C"      |
| `currency_symbol`    | "mk"     | "L."     | "\u0192" | "SFrs."  |
| `frac_digits`        | 2        | 0        | 2        | 2        |
| `p_cs_precedes`      | 0        | 1        | 1        | 1        |
| `n_cs_precedes`      | 0        | 1        | 1        | 1        |
| `p_sep_by_space`     | 1        | 0        | 1        | 0        |
| `n_sep_by_space`     | 1        | 0        | 2        | 0        |
| `p_sign_posn`        | 1        | 1        | 1        | 1        |
| `n_sign_posn`        | 1        | 1        | 4        | 2        |
| `int_curr_symbol`    | "FIM "   | "ITL "   | "NLG "   | "CHF "   |
| `int_frac_digits`    | 2        | 0        | 2        | 2        |
| `int_p_cs_precedes`  | 1        | 1        | 1        | 1        |
| `int_n_cs_precedes`  | 1        | 1        | 1        | 1        |
| `int_p_sep_by_space` | 1        | 1        | 1        | 1        |
| `int_n_sep_by_space` | 2        | 1        | 2        | 1        |
| `int_p_sign_posn`    | 1        | 1        | 1        | 1        |
| `int_n_sign_posn`    | 4        | 1        | 4        | 2        |

> `cs_precedes`、`sep_by_space` 和 `sign_posn` 成员如何影响格式化值

| `p_cs_precedes` | `p_sign_posn` | `p_sep_by_space = 0` | `p_sep_by_space = 1` | `p_sep_by_space = 2` |
| :-------------- | :------------ | :------------------- | :------------------- | :------------------- |
| 0               | 0             | `(1.25$)`            | `(1.25 $)`           | `(1.25$)`            |
| 0               | 1             | `+1.25$`             | `+1.25 $`            | `+ 1.25$`            |
| 0               | 2             | `1.25$+`             | `1.25 $+`            | `1.25$ +`            |
| 0               | 3             | `1.25+$`             | `1.25 +$`            | `1.25+ $`            |
| 0               | 4             | `1.25$+`             | `1.25 $+`            | `1.25$ +`            |
| 1               | 0             | `($1.25)`            | `($ 1.25)`           | `($1.25)`            |
| 1               | 1             | `+$1.25`             | `+$ 1.25`            | `+ $1.25`            |
| 1               | 2             | `$1.25+`             | `$ 1.25+`            | `$1.25 +`            |
| 1               | 3             | `+$1.25`             | `+$ 1.25`            | `+ $1.25`            |
| 1               | 4             | `$+1.25`             | `$+ 1.25`            | `$ +1.25`            |


---

### Locale 附录

#### LCID

[https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-lcid/a9eac961-e77d-41a6-90a5-ce1a8b0cdb9c](https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-lcid/a9eac961-e77d-41a6-90a5-ce1a8b0cdb9c)

#### 语言（language）字符串

[https://learn.microsoft.com/en-us/cpp/c-runtime-library/language-strings?view=msvc-170](https://learn.microsoft.com/en-us/cpp/c-runtime-library/language-strings?view=msvc-170)

#### 国家-地区（country-region）字符串

[https://learn.microsoft.com/en-us/cpp/c-runtime-library/country-region-strings?view=msvc-170](https://learn.microsoft.com/en-us/cpp/c-runtime-library/country-region-strings?view=msvc-170)

#### 代码页（code-page）

[https://learn.microsoft.com/en-us/windows/win32/Intl/code-page-identifiers](https://learn.microsoft.com/zh-cn/windows/win32/Intl/code-page-identifiers)

---
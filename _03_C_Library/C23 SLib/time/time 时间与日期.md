## C 时间与日期：time.h

`time.h` 声明与操作时间相关的类型和函数，宏等。许多函数处理表示当前日期（根据公历）和时间的日历时间。一些函数处理本地时间，这是为某些特定时区表示的日历时间，以及夏令时，这是确定本地时间的算法中的临时更改。本地时区和夏令时是实现定义的。

>---
### 时间操作

| Specifier            | Description                                                                                                                       |
| :------------------- | :-------------------------------------------------------------------------------------------------------------------------------- |
| `clock_t`            | 足以表示处理器时间的实数类型。                                                                                                    |
| `time_t`             | 日历时间。                                                                                                                        |
| `tm`                 | 保有将日历时间拆分成其组分的日历日期和时间的结构体，称为分解时间。                                                                |
| `timespec`           | 保存以秒和纳秒指定的间隔，可以表示基于特定历元的日历时间。                                                                        |
| `CLOCKS_PER_SEC`     | `(clock_t)(1000)`                                                                                                                 |
| `TIME_UTC`           | 指定日历时基。                                                                                                                    |
| `TIME_MONOTONIC`     | 指定单调时基。                                                                                                                    |
| `TIME_ACTIVE`        | 指定总体执行的活动处理时基。                                                                                                      |
| `TIME_THREAD_ACTIVE` | 指定线程特定的活动处理时基。                                                                                                      |
| `clock`              | 进程运行时间。值除以 `CLOCKS_PER_SEC` 可转换为秒。不可用返回 `(clock_t)(-1)`。                                                    |
| `difftime`           | 计算两个日历时间差的秒数。                                                                                                        |
| `mktime`             | 转换分解时间结构 `tm` 为从纪元开始的日历时间。                                                                                    |
| `timegm`             | 转换分解时间结构 `tm` 为 UTC 日历时间。                                                                                           |
| `time`               | 返回当前日历时间的最佳近似值。                                                                                                    |
| `timespec_get`       | 函数修改 `timespec *ts` 对象，保存以时间基底 `base` 表示的当前日历时间。`base` 为 `TIME_UTC` 或其他任何指示时间基底的非零整数值。 |
| `timespec_getres`    | 函数返回由 `timespec_get` 函数在 `ts` 指向的 `timespec` 结构中为 `base` 提供的时间分辨率。                                        |

> tm

```c
struct tm           // 保有拆分成其组分的日历日期和时间的结构体，称为分解时间
{
    int tm_sec;     // 分后之秒数 - [0, 60]
    int tm_min;     // 时后之分钟数 - [0, 59]
    int tm_hour;    // 自午夜起的小时数 - [0, 23]
    int tm_mday;    // 月的第几天 - [1, 31]
    int tm_mon;     // 自一月起的月份数 - [0, 11]
    int tm_year;    // 自 1900 年起的年份
    int tm_wday;    // 自星期日起的天数 - [0, 6]
    int tm_yday;    // 自1月1日起的天数 - [0, 365]
    int tm_isdst;   // 夏令时标签（有效为正，无效为 0，无可用信息为负）
};
```

> mktime

```c
#include <stdio.h>
#include <time.h>

static const char* const wday[] = {
"Sunday", "Monday", "Tuesday", "Wednesday",
"Thursday", "Friday", "Saturday", "-unknown-"
};

int main() {
	// 2023/9/20/12:30:45
	struct tm time_str = {
		.tm_year = 2023 - 1900,
		.tm_mon = 9 - 1,
		.tm_mday = 20,
		.tm_hour = 12,
		.tm_min = 30,
		.tm_sec = 45,
		.tm_isdst = -1
	};

	if (mktime(&time_str) == (time_t)(-1))
		time_str.tm_wday = 7;
	printf("2023/9/20/12:30:45 is %s\n", wday[time_str.tm_wday]);
}
/*
2023/9/20/12:30:45 is Wednesday
*/
```

> time

`time` 函数返回编码成 `time_t` 对象的当前日历时间的最佳近似值。如果日历时间不可用，则返回 `(time_t)(-1)`。当 `timer` 不是空指针时，返回值也会被赋值给 `timer` 所指的对象。

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdint.h>

int main() {
	time_t timer = time(NULL);

	if (timer != (time_t)(-1)) {
		printf("The current time is %s(%jd seconds since the Epoch)\n", asctime(gmtime(&timer)),(intmax_t)(timer));
	}
}
/*
The current time is Wed Sep 20 08:35:29 2023
(1695198929 seconds since the Epoch)
*/
```

> timespec_get


`timespec_get` 函数修改 `ts` 对象，保存以时间基底 `base` 表示的当前日历时间。`base` 为 `TIME_UTC` 或其他任何指示时间基底的非零整数值。若 `base` 为 `TIME_UTC` 时，`ts->tv_sec` 被设置为实现定义的纪元以来的秒数并截断为整数值，`ts->tv_nsec` 设置为纳秒数的整数值，并按照系统时钟的分辨率舍入。

可选时间基 `TIME_MONOTONIC` 是与此相同，但参考点是实现定义的时间点；不同的程序调用可能会也可能不会引用相同的参考点。如果 `TIME_MONOTONIC` 说明了执行环境挂起的时间，则它是实现定义的。对于可选时间基 `TIME_ACTIVE` 和 `TIME_THREAD_ACTIVE` 的结果是相似的，但是调用分别度量与整个程序调用或调用线程相关的活动处理时间的总量。

函数在成功时返回非零值（`base`），否则返回 `0`。

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <locale.h>

int main() {
	struct timespec ts;
	if (timespec_get(&ts, TIME_UTC)) {
		printf("The current time is %s (%jd sec, %d nsec)\n", asctime(gmtime(&ts.tv_sec)), (intmax_t)(ts.tv_sec), ts.tv_nsec);
	}
}
/*
*The current time is Wed Sep 20 11:24:19 2023
 (1695209059 sec, 719197500 nsec)
*/
```

>---
### 时间转换

| Specifier                                 | Description                                                                                           |
| :---------------------------------------- | :---------------------------------------------------------------------------------------------------- |
| `asctime`, `asctime_s`                    | 转换分解时间结构 `tm` 为 `Www Mmm dd hh:mm:ss yyyy\n` 格式化字符串。                                  |
| `localtime`, `localtime_s`, `localtime_r` | 转换日历时间 `timer` 为本地区域的分解时间 `struct tm`。                                               |
| `ctime`, `ctime_s`                        | 将 `timer` 转换从纪元起的给定日历时间转换为 `Www Mmm dd hh:mm:ss yyyy\n` 格式化字符串的本地区域时间。 |
| `gmtime`, `gmtime_s`, `gmtime_r`          | 将 `timer` 指向的日历时间转换为世界协调时间 UTC 的分解时间。                                          |
| `strftime`                                | 按照 `format` 转换来自给定的日历时间 `timeptr` 的日期和时间信息。                                     |

> asctime_s

`asctime_s` 仅若实现定义 `__STDC_LIB_EXT1__` 且用户在包含 `time.h` 前定义 `__STDC_WANT_LIB_EXT1__` 为整数常量 `1` 才保证可用。

```c
#define __STDC_WANT_LIB_EXT1__ 1 
#include <time.h>
#include <stdio.h>
 
int main(void)
{
    struct tm tm = *localtime(&(time_t){time(NULL)});
    printf("%s", asctime(&tm));
 
#ifdef __STDC_LIB_EXT1__
    char str[26];
    asctime_s(str, sizeof str, &tm);
    printf("%s", str);
#endif
}
```

> localtime、localtime_s、localtime_r

```c
#define _CRT_SECURE_NO_WARNINGS 0 // 1
#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>
#include <stdio.h>

int main(void)
{
	time_t timer = time(NULL);
	struct tm local_time = { 0 };

#if _CRT_SECURE_NO_WARNINGS

	local_time = *localtime(&timer);
	printf("local time = %s", asctime(&local_time));

#else
	//#ifdef __STDC_LIB_EXT1__
	if (!localtime_s(&local_time, &timer)) {
		char str[26] = { 0 };
		asctime_s(str, sizeof str, &local_time);
		printf("local time = %s", str);
	}
	//#endif
#endif
}
/*
local time = Wed Sep 20 21:59:14 2023
*/
```

> ctime、ctime_s

```c
#define __STDC_WANT_LIB_EXT1__  1
#include <time.h>
#include <stdio.h>

int main(void)
{
	// 2023/9/20/12:30:45
	struct tm time_str = {
		.tm_year = 2023 - 1900,
		.tm_mon = 9 - 1,
		.tm_mday = 20,
		.tm_hour = 12,
		.tm_min = 30,
		.tm_sec = 45,
		.tm_isdst = -1
};

    time_t result = mktime(&time_str);
#ifdef _CRT_SECURE_NO_WARNINGS          // 在 MSVC 下取消不安全代码警告
    printf("%s", ctime(&result));
#endif
//#ifdef __STDC_LIB_EXT1__
    char str[26];
    ctime_s(str, sizeof str, &result);
    printf("%s", str);
//#endif
}
```

> gmtime、gmtime_s、gmtime_r

```c
#define _CRT_SECURE_NO_WARNINGS 0 // 1
#define __STDC_WANT_LIB_EXT1__  1
#include <time.h>
#include <stdio.h>

int main(void)
{
	time_t timer = time(NULL);
	time_t timer_utc = { 0 };
#if _CRT_SECURE_NO_WARNINGS
	timer_utc = mktime(gmtime(&timer));
	printf("UTC time   = %s", ctime(&timer_utc));
#else
// #ifdef __STDC_LIB_EXT1__
	struct tm _TM = { 0 };
	if (!gmtime_s(&_TM, &timer))
	{
		timer_utc = mktime(&_TM);
		char str[26];
		ctime_s(str, sizeof str, &timer_utc);
		printf("UTC time   = %s", str);
	}
// #endif
#endif
}
```

> strftime 

`format` 中每个转换符都应替换为以下描述的适当字符。适当的字符应该使用当前语言环境的 `LC_TIME` 类别以及 `timeptr` 指向的分解时间结构的零个或多个成员的值来确定。

```c
//=== 符号类
"%%"      // 符号 "%"
"%n"      // 换行符 "\n"
"%t"      // 水平制表符 "\t"

//===  year  年  (tm_year)
"%y"      // 写年的末两位数字 [00,99].
"%Y"      // 以四位十进制写年, 1997.
"%Ey"     // 将年写作本地环境的替用时期 %EC 的偏移 (本地环境依赖).
"%EY"     // 依据区域设置, 以完整替用方式写年, 例如在 ja_JP 环境中, 以 "平成23年" 取代 "2011年". 
"%Oy"     // 以替用数字系统写年的末 2 位数字, 例如在 ja_JP 环境中以 "十一" 取代 "11".
"%C"      // 写年的首两位数字 [00,99].
"%EC"     // 依据区域设置, 以替用表示写年份基底 (时期)，例如 ja_JP 中的 "平成".
"%g"      // 写基于 ISO 8601 的年后两位 [00,99]，包含指定星期.  (tm_year,tm_wday,tm_yday)
"%G"      // 写基于 ISO 8601 的年, 包含指定星期.  (tm_year,tm_wday,tm_yday)

//=== month  月  (tm_mon)
"%b"      // 写缩略月名, 例如 Oct.
"%Ob"     // 替换为区域设置的缩写替代月份名称
"%h"      // 相当于 b.
"%B"      // 写完整月名, 例如 October.
"%OB"     // 依据区域设置, 以替用表示写完整月名.
"%m"      // 将月写作十进制数, [01,12].
"%Om"     // 依据区域设置, 以替用数字系统写月, 例如 ja_JP 本地环境中 "十二" 取代 "12".

//=== weekday 星期  (tm_year,tm_wday,tm_yday)
"%U"      // 以十进制数写年的星期, 星期日是星期的首日, [00,53].
"%OU"     // 依据区域设置, 以替用数值系统写如同用 %U 的年的星期, 例如 "五十二" 在 ja_JP 中取代 "52".
"%W"      // 以十进制数写年的星期, 星期一是星期的首日, [00,53].
"%OW"     // 依据区域设置, 以替用数值系统写如同用 %W 的年的第星期, 例如 "五十二" 在 ja_JP 中取代 "52".
"%V"      // 写 ISO 8601 的年的星期, [00,53].
"%OV"     // 依据区域设置, 以替用数值系统写如同用 %V 的年的星期, 例如 "五十二" 在 ja_JP 中取代 "52".

//=== day of year/month 年/月之日  (tm_mday)
"%j"      // 以十进制数写年的第几日, [001,366].  (tm_yday) 
"%d"      // 以十进制数写月的第几日, [01,31].
"%Od"     // 依据区域设置, 以替用数字系统写零基的月的第几日, 例如 ja_JP 中 "二十七" 取代 "27", 单字符前加空格 (" 1").
"%e"      // 以十进制数写月的第几日, [01,31]. 单数字前加空格.
"%Oe"     // 依据区域设置, 以替用数字系统写一基的月的第几日, 例如 ja_JP 中 "二十七" 取代 "27", 单字符前加空格.

//=== day of week  星期之日  (tm_wday)
"%a"      // 写缩略的星期日期名, 例如 Fri.  
"%A"      // 写完整的星期日期名, 例如 Friday.
"%w"      // 以十进制数写星期日期, 其中星期日是 0, [0,6].
"%Ow"     // 依据区域设置, 用替用数字系统写星期日期, 其中星期日是 0. 例如 ja_JP 中 "二" 取代 "2".
"%u"      // 十进制数写星期日期, 其中星期一是 1, [1-7] (ISO 8601 格式).
"%Ou"     // 依据区域设置, 用替用数字系统写星期日期, 其中星期一是 1. 例如 ja_JP 中 "二' 取代 "2".

//=== hour/min/sec  时,分,秒  (tm_hour), (tm_min), (tm_sec)
"%H"      // 以十进制数写时, 24 小时制 [00-23].
"%OH"     // 依据区域设置, 以替用数字系统写 24 小时制的时, 例如 ja_JP 中 "十八" 取代 "18".
"%I"      // 以十进制数写时, 12 小时制 [01,12].
"%OI"     // 依据区域设置, 以替用数字系统写 12 小时制的时, 例如 ja_JP 中 "六" 取代 "6".
"%M"      // 以十进制数写分[00,59].
"%OM"     // 依据区域设置, 以替用数字系统写分, 例如 ja_JP 中 "二十五" 取代 "25".
"%S"      // 以十进制数写秒 [00,640]. 
"%OS"     // 依据区域设置, 以替用数字系统写秒, 例如 ja_JP 中 "二十四" 取代 "24".

//===== others
"%c"      // 写标准日期时间字符串, 例如 Sun Oct 17 04:41:13 2010.  (All)
"%Ec"     // 依据区域设置, 写替用日期时间字符串, 例如 ja_JP 中 "平成23年" 取代 "2011年".  (All)
"%x"      // 写本地化的日期表示.
"%Ex"     // 依据区域设置, 写替用日期表示, 例如 ja_JP 中 "平成23年" 取代 "2011年".  (All)
"%X"      // 写本地化的时间表示, 例如 18:40:20 或 6:40:20 PM.  (All)
"%EX"     // 依据区域设置, 写替用时间表示.  (All)
"%D"      // 等价于 "%m/%d/%y". (tm_mon, tm_mday, tm_year)
"%F"      // 等价于 "%Y-%m-%d", ISO 8601 日期格式.  (tm_mon, tm_mday, tm_year)
"%r"      // 写本地化的 12 小时制时间.  (tm_hour, tm_min, tm_sec)
"%R"      // 等价于 "%H:%M".  (tm_hour, tm_min)
"%T"      // 等价于 "%H:%M:%S", ISO 8601 时间格式.  (tm_hour, tm_min, tm_sec)
"%p"      // 写本地化的 a.m. 或 p.m.  (tm_hour)
"%z"      // 以 ISO 8601 格式（例如 -0430 ）写距 UTC 的偏移，或者倘若时区信息不可用则不写字符.  (tm_isdst)
"%Z"      // 写依赖本地环境的时区名或缩写，或者若时区信息不可用则不写字符.  (tm_isdst)
```

在 `"C"` 的区域设置中，`E` 和 `O` 被忽略，以下说明符的替换字符串为：

```c
"%a"      // %A 的前三个字符
"%A"      // "Sunday", "Monday", . . . , "Saturday" 之一
"%b"      // %B 的前三个字符
"%B"      // "January", "February", . . . , "December" 之一	
"%c"      // 相当于 "%a %b %e %T %Y"
"%p"      // "AM" 或 "PM" 之一
"%r"      // 相当于 "%I:%M:%S %p"
"%x"      // 相当于 "%m/%d/%y"
"%X"      // 相当于 "%T"
"%Z"      // 实现定义。
```

```c
#include <stdio.h>
#include <time.h>
#include <locale.h>

int main(void)
{
	char buff[70];
	struct tm timer;
	time_t time_l = time(NULL);
	localtime_s(&timer, &time_l);

	if (strftime(buff, sizeof buff, "[Native format]= %A %c", &timer))
		puts(buff);
	else
		puts("strftime failed");

	setlocale(LC_TIME, "en_us.utf8");

	if (strftime(buff, sizeof buff, "[USA format] = %A %c", &timer))
		puts(buff);
	else
		puts("strftime failed");
}
/*
[Native format]= Thursday Thu Sep 21 01:10:16 2023
[USA format] = Thursday 9/21/2023 1:10:16 AM
*/
```

---
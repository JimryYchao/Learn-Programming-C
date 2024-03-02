## C 时间与日期（Date and time）：time.h

`time.h` 声明与操作时间相关的类型和函数，宏等。

---
### Types

#### clock_t、time_t

```c
typedef long        clock_t;       // 自进程开始 CRT 初始化后的运行时间，即程序时间
typedef long long   time_t;        // 自 UTC-1970-1-1-00:00 开始的秒数，即日历时间
```

<br>

#### timespec

```c
struct timespec         // 表示基于特定历元的日历时间
{
    time_t tv_sec;      // 秒 Seconds - >= 0                
    long   tv_nsec;     // 纳秒 Nanoseconds - [0, 999999999]
};
```

<br>

#### tm

```c
struct tm           // 保有拆分成其组分的日历日期和时间的结构体
{
    int tm_sec;     // 分后之秒 - [0, 60] including leap second
    int tm_min;     // 时后之分 - [0, 59]
    int tm_hour;    // 自午夜起的小时 - [0, 23]
    int tm_mday;    // 月之日 - [1, 31]
    int tm_mon;     // 自一月起的月 - [0, 11]
    int tm_year;    // 自 1900 年起的年
    int tm_wday;    // 自星期日起的星期 - [0, 6]
    int tm_yday;    // 自 1 月 1 日 起的日 - [0, 365]
    int tm_isdst;   // 夏令时标签（有效为正，无效为 0，无可用信息为负）
};
```

---
### Macros

```c
#define CLOCKS_PER_SEC  ((clock_t)1000)
#define TIME_UTC 1
```

- `CLOCKS_PER_SEC` 展开表示时钟函数每秒返回的值的个数，即处理器每秒的时间计数。
- `TIME_UTC` 扩展为一个大于 0 的整数，用来指定 UTC 时基。

---
### Functions：时间操作（Time manipulation functions）

#### clock （进程运行时间）

```c
clock_t clock(void);
```

- `clock` 时钟函数返回从关联到进程开始执行的实现定义起，进程所用的近似处理器时间。该值除以 `CLOCKS_PER_SEC` 可转换为秒。
- 返回程序自运行到现在的处理器时间，若信息不可以，则返回 `(clock_t)(-1)`。

```c
#include <stdio.h>
#include <time.h>

volatile unsigned sink;

int main(void)
{
	clock_t start = clock();

	for (size_t i = 0; i < 10000000; ++i)
		sink++;

	clock_t end = clock();
	double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	printf("for loop took %f seconds to execute \n", cpu_time_used);
}
/*
for loop took 0.014000 seconds to execute
*/
```

<br>

#### difftime （时间差）

```c
double difftime(time_t time1, time_t time0);
```

- `difftime` 计算两个日历时间之间的差（`time1 - time0`），并返回以秒为单位的时间差值。

```c
#include <stdio.h>
#include <time.h>

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

	printf("2023/9/20/12:30:45 - 1970/1/1/00:00:00 = %.3f sec", difftime(mktime(&time_str), 0));
}
/*
2023/9/20/12:30:45 - 1970/1/1/00:00:00 = 1695184245.000 sec
*/
```

<br>

#### mktime （tm 转换为 time_t）

```c
time_t mktime(struct tm * timeptr);
```

- `mktime` 重整化 `timeptr` 指向的日历时间，并转换为从纪元开始的日历时间 `time_t` 格式。该结构的 `tm_wday` 和 `tm_yday` 值被忽略，转换过程中容许其他值不受原先的范围的限制。若转换 `time_t` 成功则修改更新 `timeptr` 的所有域为符合其正确范围的值，并最后用可用于其他域的信息重新计算 `tm_wday` 和 `tm_yday` 的值。
- 若无法返回转换后的日历时间，函数返回 `(time_t)(-1)`。

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

<br>

#### time （当前日历时间）

```c
time_t time(time_t *timer);
```

- `time` 函数返回编码成 `time_t` 对象的当前日历时间的最佳近似值。如果日历时间不可用，则返回 `(time_t)(-1)`。当 `timer` 不是空指针时，返回值也会被赋值给 `timer` 所指的对象。

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

<br>

#### timespec_get （指定 UTC 当前时间）

```c
int timespec_get(struct timespec *ts, int base);
```

- `timespec_get` 函数修改 `ts` 对象，保存以时间基底 `base` 表示的当前日历时间。`base` 为 `TIME_UTC` 或其他任何指示时间基底的非零整数值。
- `base` 为 `TIME_UTC` 时，`ts->tv_sec` 被设置为实现定义的纪元后的秒数，`ts->tv_nsec` 设置为纳秒数的整数值，并按照系统时钟的分辨率舍入。（Microsoft 专用：当前函数仅支持 `TIME_UTC` 作为 `base` 值。）
- 函数在成功时返回非零值（`base`），否则返回 `0`。

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

---
### Functions：时间转换（Time conversion functions）

#### asctime、asctime_s （tm 转换成文本）

```c
char* asctime(const struct tm* timeptr);
```

- `asctime` 函数将 `timeptr` 指向的结构中被分解的时间转换成 `Www Mmm dd hh:mm:ss yyyy\n` （例如，`Wed Sep 20 11:24:19 2023\n`）。函数不支持本地化，且不能移除换行符，且非线程安全。
- 对于 `timeptr`，其中任何成员在其正常范围外则行为未定义。`timeptr->tm_year` 小于 1000 或大于 9999 行为未定义。

```c
// 等价于
char* asctime(const struct tm* timeptr)
{
	static const char wday_name[7][3] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
	};
	static const char mon_name[12][3] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	static char result[26];
	sprintf(result, "%.3s %.3s%3d %.2d:%.2d:%.2d %d\n",
		wday_name[timeptr->tm_wday],
		mon_name[timeptr->tm_mon],
		timeptr->tm_mday, timeptr->tm_hour,
		timeptr->tm_min, timeptr->tm_sec,
		1900 + timeptr->tm_year);
	return result;
}
```

> C23：`asctime` 将会被弃用，转而使用线程安全的 `asctime_s`。

```c
errno_t asctime_s( char* buf, rsize_t bufsz, const struct tm* timeptr )
```

- `asctime_s` 函数写入消息到用户提供的存储 `buf` 中，且保证它是空终止的。其中 `buf` 指向用户提供至少有 26 字节的缓冲区的指针，`bufsz` 表示用户提供的缓冲区大小。函数转换成功时返回非零 `errno_t` 类型的对象。

- 在运行时检测下列错误并调用当前安装的制约处理函数：
  - `buf` 或 `timeptr` 为空指针；
  - `bufsz` 小于 26 或超过 `rsize_t` 的表示范围；
  - 不是所有 `timeptr` 成员都在其正常范围内；
  - `timeptr->tm_year` 不在 0 ~ 9999 范围内。

- `asctime_s` 仅若实现定义 `__STDC_LIB_EXT1__` 且用户在包含 `time.h` 前定义 `__STDC_WANT_LIB_EXT1__` 为整数常量 `1` 才保证可用。

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

<br>

#### localtime、localtime_s、localtime_r （time_t 转换为 struct tm 格式）

```c
struct tm *localtime(const time_t *timer);
```

- `localtime` 转换当前的日历时间 `timer` 为分解时间 `struct tm`，表示为本地时间。转换失败将返回一个空指针 `NULL`。

> C11：线程安全的 `localtime_s`

```c
error_t localtime_s(struct tm *_Tm, const time_t *_Time);
```

- `localtime_s` 将 `_Time` 的转换结果保存到 `_TM` 指向的对象中。转换成功时返回零，否则返回非零。
- 在运行时检测下列错误并调用当前安装的制约处理函数：
  - `_Tm` 或 `_Time` 是空指针；

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

> C23：`localtime_r`

```c
struct tm *localtime_r(struct tm *buf, const time_t *_Time);
```

- `localtime_r` 功能和 `localtime` 相同，除了函数使用的是用户提供的存储 `buf`。

<br>

#### ctime、ctime_s （time_t 转换成文本）

```c
char *ctime(const time_t *timer);
```

- `ctime` 函数将 `timer` 转换从纪元起的给定日历时间转换为字符串形式的本地时间，它相当于 `asctime(localtime(timer))` 。函数返回格式为 `Www Mmm dd hh:mm:ss yyyy\n` 的时间文本形式。

> C23：`ctime` 将在 C23 被弃用，转而使用线程安全的 `ctime_s`。

```c
errno_t ctime_s( char *buf, rsize_t bufsz, const time_t* timer);
```

- 函数等价于 `asctime_s(buf, bufsz, localtime_r(timer, &*(struct tm){0}))`。
- 下列错误并调用当前安装的制约处理函数：
  - `buf` 或 `timer` 为空指针；
  - `bufsz` 小于 26 或超出 `rsize_t` 的范围。

- 函数将结果 `Www Mmm dd hh:mm:ss yyyy\n` 保存在 `buf` 指向的缓冲区。转换成功时返回非零 `errno_t` 类型的对象。

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

<br>

#### gmtime、gmtime_s、gmtime_r （time_t 转换为世界协调时间 UTC 的 struct tm 格式）

```c
struct tm *gmtime(const time_t *timer);
```

- `gmtime` 函数转换 `timer` 为 `struct tm` 格式以表示世界协调时间 UTC。存储结果于静态存储，并返回指向静态存储的指针。转换失败返回 `NULL`。

> C11：使用线程安全的 `gmtime_s`

```c
errno_t gmtime_s(struct tm *_Tm, const time_t *_Time);
```

- 将 `_Time` 的转换结果保存到 `_TM` 指向的对象中。函数转换成功时返回非零 `errno_t` 类型的对象。
- 在运行时检测下列错误并调用当前安装的制约处理函数：
  - `_Tm` 或 `_Time` 是空指针；


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

> C23：`gmtime_r`

```c
struct tm *gmtime_r(struct tm *buf, const time_t *_Time);
``` 

- `gmtime_r` 功能和 `gmtime` 相同，除了函数使用的是用户提供的存储 `buf`。


<br>

#### strftime （格式化输出时间字符串）

```c
size_t strftime(
    char * restrict str,
    size_t maxsize,
    const char * restrict format,
    const struct tm * restrict timeptr
);
```

- `strftime` 按照格式字符串 `format`，转换来自给定的日历时间 `timeptr` 的日期和时间信息，并将转换后的空终止多字节字符串 `*format` 写入 `str`，最多写入 `maxsize` 字节。
- 格式字符串 `format` 由零个到多个转换说明负和普通多字节字符组成。
- `strtime` 在格式化转换成功时，返回写入 `str` 所指向的字符数组的字节数，不包括字节终止符 `\0`。若写入提前到达 `count`，则返回 0，此时 `str` 被写入的内容是不确定的。转换完成后自动在最后写入字符的位置后添加 `\0` 表示字符串终止。

> `format` *中的转换说明符列举*

- 每个转换符都应替换为以下描述的适当字符。适当的字符应该使用当前语言环境的 `LC_TIME` 类别以及 `timeptr` 指向的分解时间结构的零个或多个成员的值来确定。

```c
//=== 符号类
"%%"      // 符号 "%"
"%n"      // 换行符 "\n"
"%t"      // 水平制表符 "\t"

//===  year  年  (tm_year)
"%y"      // 写年的末两位数字 [00,99].
"%Y"      // 以四位十进制写年, 1997.
"%Ey"     // 将年写作本地环境的替用时期 %EC 的偏移 (本地环境依赖).
"%EY"     // 以替用方式写年, 例如在 ja_JP 环境中, 以 "平成23年" 取代 "2011年". 
"%Oy"     // 以替用数字系统写年的末 2 位数字, 例如在 ja_JP 环境中以 "十一" 取代 "11".
"%C"      // 写年的首两位数字 [00,99].
"%EC"     // 以本地环境的替用表示写年份基底 (时期)，例如 ja_JP 中的 "平成".
"%g"      // 写基于 ISO 8601 的年后两位 [00,99]，包含指定星期.  (tm_year,tm_wday,tm_yday)
"%G"      // 写基于 ISO 8601 的年, 包含指定星期.  (tm_year,tm_wday,tm_yday)

//=== month  月  (tm_mon)
"%b"      // 写缩略月名, 例如 Oct.
"%Ob"     // 以本地环境的替用表示写缩写月名.
"%h"      // 相当于 b.
"%B"      // 写完整月名, 例如 October.
"%OB"     // 以本地环境的替用表示写完整月名.
"%m"      // 将月写作十进制数, [01,12].
"%Om"     // 以替用数字系统写月, 例如 ja_JP 本地环境中 "十二" 取代 "12".

//=== weekday 星期  (tm_year,tm_wday,tm_yday)
"%U"      // 以十进制数写年的星期, 星期日是星期的首日, [00,53].
"%OU"     // 以替用数值系统写如同用 %U 的年的星期, 例如 "五十二" 在 ja_JP 中取代 "52".
"%W"      // 以十进制数写年的星期, 星期一是星期的首日, [00,53].
"%OW"     // 以替用数值系统写如同用 %W 的年的第星期, 例如 "五十二" 在 ja_JP 中取代 "52".
"%V"      // 写 ISO 8601 的年的星期, [00,53].
"%OV"     // 以替用数值系统写如同用 %V 的年的星期, 例如 "五十二" 在 ja_JP 中取代 "52".

//=== day of year/month 年/月之日  (tm_mday)
"%j"      // 以十进制数写年的第几日, [001,366].  (tm_yday) 
"%d"      // 以十进制数写月的第几日, [01,31].
"%Od"     // 以替用数字系统写零基的月的第几日, 例如 ja_JP 中 "二十七" 取代 "27", 单字符前加空格 (" 1").
"%e"      // 以十进制数写月的第几日, [01,31]. 单数字前加空格.
"%Oe"     // 以替用数字系统写一基的月的第几日, 例如 ja_JP 中 "二十七" 取代 "27", 单字符前加空格.

//=== day of week  星期之日  (tm_wday)
"%a"      // 写缩略的星期日期名, 例如 Fri.  
"%A"      // 写完整的星期日期名, 例如 Friday.
"%w"      // 以十进制数写星期日期, 其中星期日是 0, [0,6].
"%Ow"     // 用替用数字系统写星期日期, 其中星期日是 0. 例如 ja_JP 中 "二" 取代 "2".
"%u"      // 十进制数写星期日期, 其中星期一是 1, [1-7] (ISO 8601 格式).
"%Ou"     // 用替用数字系统写星期日期, 其中星期一是 1. 例如 ja_JP 中 "二' 取代 "2".

//=== hour/min/sec  时,分,秒  (tm_hour), (tm_min), (tm_sec)
"%H"      // 以十进制数写时, 24 小时制 [00-23].
"%OH"     // 以替用数字系统写 24 小时制的时, 例如 ja_JP 中 "十八" 取代 "18".
"%I"      // 以十进制数写时, 12 小时制 [01,12].
"%OI"     // 以替用数字系统写 12 小时制的时, 例如 ja_JP 中 "六" 取代 "6".
"%M"      // 以十进制数写分[00,59].
"%OM"     // 以替用数字系统写分, 例如 ja_JP 中 "二十五" 取代 "25".
"%S"      // 以十进制数写秒 [00,640]. 
"%OS"     // 以替用数字系统写秒, 例如 ja_JP 中 "二十四" 取代 "24".

//===== others
"%c"      // 写标准日期时间字符串, 例如 Sun Oct 17 04:41:13 2010.  (All)
"%Ec"     // 写替用日期时间字符串, 例如 ja_JP 中 "平成23年" 取代 "2011年".  (All)
"%x"      // 写本地化的日期表示.
"%Ex"     // 写替用日期表示, 例如 ja_JP 中 "平成23年" 取代 "2011年".  (All)
"%X"      // 写本地化的时间表示, 例如 18:40:20 或 6:40:20 PM.  (All)
"%EX"     // 写替用时间表示.  (All)
"%D"      // 等价于"%m/%d/%y". (tm_mon, tm_mday, tm_year)
"%F"      // 等价于"%Y-%m-%d", ISO 8601 日期格式.  (tm_mon, tm_mday, tm_year)
"%r"      // 写本地化的 12 小时制时间.  (tm_hour, tm_min, tm_sec)
"%R"      // 等价于"%H:%M".  (tm_hour, tm_min)
"%T"      // 等价于"%H:%M:%S", ISO 8601 时间格式.  (tm_hour, tm_min, tm_sec)
"%p"      // 写本地化的 a.m. 或 p.m.  (tm_hour)
"%z"      // 以 ISO 8601 格式（例如 -0430 ）写距 UTC 的偏移，或者倘若时区信息不可用则不写字符.  (tm_isdst)
"%Z"      // 写依赖本地环境的时区名或缩写，或者若时区信息不可用则不写字符.  (tm_isdst)
```

> `strftime` 案例

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
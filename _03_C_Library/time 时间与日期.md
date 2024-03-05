## C 时间与日期（Date and time）：time.h

```c
#define __STDC_VERSION_TIME_H__			202311L
```

`time.h` 声明与操作时间相关的类型和函数，宏等。许多函数处理表示当前日期（根据公历）和时间的日历时间。一些函数处理本地时间，这是为某些特定时区表示的日历时间，以及夏令时，这是确定本地时间的算法中的临时更改。本地时区和夏令时是实现定义的。

---
### Types

#### clock_t、time_t

```c
typedef /* unspecified */  clock_t;  // 足以表示进程所用的处理器时间的实数类型，它拥有实现定义的范围和精度
typedef /* unspecified */  time_t;   // 日历时间
```

`clock_t` 和 `time_t` 表示为能够表示时间的实数类型。其表示的时间范围和精度是由实现定义的。

>---

#### timespec

```c
struct timespec         // 表示基于特定历元的日历时间
{
    time_t tv_sec;      // 秒 Seconds - >= 0                
    /* 有符号整数 */   tv_nsec;     // 纳秒 Nanoseconds - [0, 999999999]
};
```

`timespec` 保存以秒和纳秒指定的间隔，可以表示基于特定历元的日历时间。`tv_nsec` 成员应该是实现定义的有符号整数类型，能够表示范围 $[ 0，99999999 ]$。

>---

#### tm

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

---
### Macros

```c
#define CLOCKS_PER_SEC  ((clock_t)1000)
```

`CLOCKS_PER_SEC` 扩展为一个 `clock_t` 类型的表达式，`clock_t` 是 `clock` 函数每秒返回的值的数量。

```c
#define TIME_UTC 
#define TIME_MONOTONIC
```

`TIME_UTC` 和 `TIME_MONOTONIC` 扩展大于 0 的整数常量，分别用来指定日历时基和单调时基。其他附加的时间基宏定义，以 `TIME_` 和一个大写字母开头，也可以由实现指定。

```c
#define TIME_ACTIVE
#define TIME_THREAD_ACTIVE
```

如果定义 `TIME_ACTIVE` 和 `TIME_THREAD_ACTIVE` 宏，则它们展开为整数值，分别指定总体执行和线程特定的活动处理时间基。

除了 `TIME_UTC` 之外的时间基的宏定义都是可选的。如果定义了，则对应的时间基由 `timespec_get` 和 `timespec_getres` 函数支持，并且它们的值为正。如果定义了可选 `TIME_ACTIVE` 宏，其值必须不同于常量 `TIME_UTC` 和 `TIME_MONOTONIC`，并且在同一个程序调用期间不可改变。如果实现不支持线程，则不能定义可选宏 `TIME_THREAD_ACTIVE`，它的值不能与 `TIME_UTC`、`TIME_MONOTONIC`、`TIME_ACTIVE` 相同，对于同一个线程的宏的所有扩展都是相同的，并且为一个线程提供的值不能被另一个线程用作是 `timespec_get` 和 `timespec_getres` 的 `base` 参数。

---
### Functions：时间操作（Time manipulation functions）

#### clock （进程运行时间）

```c
clock_t clock(void);
```

`clock` 函数返回从关联到进程开始执行的实现定义起，进程所用的近似处理器时间。该值除以 `CLOCKS_PER_SEC` 可转换为秒。函数返回程序自运行到现在的处理器时间。若使用的处理器时间不可用，则返回 `(clock_t)(-1)`。如果无法表示该值，则函数返回未指定的值。

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

>---

#### difftime （时间差）

```c
double difftime(time_t time1, time_t time0);
```

`difftime` 计算两个日历时间之间的差（`time1 - time0`），并返回以秒为单位的时间差值。

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

>---

#### mktime （tm 转换为本地 time_t）

```c
time_t mktime(struct tm * timeptr);
```

`mktime` 重整化 `timeptr` 结构中的分解时间（表示为本地时间）转换为日历时间值（即，将其转换为从纪元开始的日历时间 `time_t` 格式）。该结构的 `tm_wday` 和 `tm_yday` 值被忽略，转换过程中容许其他值不受原先的范围的限制。若转换 `time_t` 成功则修改更新 `timeptr` 的所有成员为符合其正确范围的值，并最后用可用于其他域的信息重新计算 `tm_wday` 和 `tm_yday` 的值。`timeptr->tm_isdst` 的负值会导致 `mktime` 尝试确定在指定时间夏时令是否有效。

函数在成功转换时返回表示从纪元开始时间的 `time_t` 对象；若无法返回转换后的日历时间，函数返回 `(time_t)(-1)`，并且不能改变结构 `tm_wday` 成员的值。

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

>---

#### timegm （tm 转换为 UTC time_t）

```c
time_t timegm(struct tm *timeptr);
```

`timegm` 函数将 `timeptr` 所指向的结构中的分解时间（表示为 UTC 时间）转换为日历时间值，其编码与 `time` 函数返回的值的编码相同。结构的 `tm_wday` 和 `tm_yday` 分量的原始值将被忽略，并且其他分量的原始值不限于先前指示的范围。成功完成后，结构的 `tm_wday` 和 `tm_yday` 组件的值将被适当设置，其他组件的值将被设置为表示指定的日历时间，但其值将强制设置为前面指定的范围；在确定 `tm_mon` 和 `tm_year` 之前，不会设置 `tm_mday` 的最终值。

`timegm` 函数返回指定的日历时间，该时间编码为 `time_t` 类型的值。如果日历时间不能用返回值所用的 `time_t` 编码表示，或者 `timeptr` 所指向的结构的 `tm_year` 组件中要返回的值不能表示为 `int`，则函数返回值 `(time_t)(-1)`，并且该值不可更改。

>---

#### time （当前日历时间）

```c
time_t time(time_t *timer);
```

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

>---

#### timespec_get （指定 UTC 当前时间）

```c
int timespec_get(struct timespec *ts, int base);
```

`timespec_get` 函数修改 `ts` 对象，保存以时间基底 `base` 表示的当前日历时间。`base` 为 `TIME_UTC` 或其他任何指示时间基底的非零整数值。

若 `base` 为 `TIME_UTC` 时，`ts->tv_sec` 被设置为实现定义的纪元以来的秒数并截断为整数值，`ts->tv_nsec` 设置为纳秒数的整数值，并按照系统时钟的分辨率舍入。

可选时间基 `TIME_MONOTONIC` 是与此相同，但参考点是实现定义的时间点；不同的程序调用可能会也可能不会引用相同的参考点。对于同一个程序调用，两次使用 `TIME_MONOTONIC` 调用`timespec_get` 的结果，使得第一次发生在第二次之前，其值不应减少。如果 `TIME_MONOTONIC` 说明了执行环境挂起的时间，则它是实现定义的。

对于可选时间基 `TIME_ACTIVE` 和 `TIME_THREAD_ACTIVE` 的结果是相似的，但是调用分别度量与整个程序调用或调用线程相关的活动处理时间的总量。

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
#### timespec_getres

```c
int timespec_getres(struct timespec *ts, int base);
```

如果 `ts` 为非空，并且 `timespec_get` 函数支持 `base`，则 `timespec_getres` 函数返回由 `timespec_get` 函数在 `ts` 指向的 `timespec` 结构中为 `base` 提供的时间分辨率。对于每个支持的 `base`，在同一程序执行期间多次调用 `timespec_getres` 函数将得到相同的结果。

如果 `timespec_get` 函数支持值 `base`，则 `timespec_getres` 函数返回非零值 `base`；否则返回零。

---
### Functions：时间转换（Time conversion functions）

带 `_r` 后缀的函数将转换结果放入 `buf` 引用的缓冲区，并返回该指针。这些函数和函数 `strftime` 不应受到数据竞争的影响，除非时间或日历状态在多线程执行中发生更改。

函数 `gmtime` 和 `localtime` 与后缀为 `_r` 的对应函数相同。它们使用指向一个或两个分解时间 `tm` 结构的指针代替参数 `buf`。类似地，`char` 数组通常由 `asctime` 和 `ctime` 使用。执行任何返回指向这些对象的指针的函数都可能覆盖先前调用使用相同对象的这些函数所返回的信息。这些函数不是可重入的，并且不需要避免彼此之间的数据竞争。在调用返回指针的函数的线程退出后，访问返回的指针会导致未定义的行为。

#### asctime、asctime_s （tm 转换成文本）

```c
[[deprecated]] char* asctime(const struct tm* timeptr);
```

此函数自 C23 起弃用。

`asctime` 函数将 `timeptr` 指向的结构中的分解时间转换成 `Www Mmm dd hh:mm:ss yyyy\n` （例如，`Wed Sep 20 11:24:19 2023\n`）。函数返回一个指向字符串的指针。此函数不支持本地化，且不能移除换行符，且非线程安全。

对于 `timeptr`，其中任何成员在其正常范围外，则函数的行为未定义。如果计算的年份 `timeptr->tm_year` 小于 1000 或超过四位数，则行为未定义。



```c
// 等价于
[[deprecated]] char* asctime(const struct tm* timeptr)
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

`asctime_s` 函数写入消息到用户提供的存储 `buf` 中，且保证它是空终止的。其中 `buf` 指向用户提供至少有 26 字节的缓冲区的指针，`bufsz` 表示用户提供的缓冲区大小。函数转换成功时返回非零 `errno_t` 类型的对象。

在运行时检测下列错误并调用当前安装的制约处理函数：
  - `buf` 或 `timeptr` 为空指针；
  - `bufsz` 小于 26 或超过 `rsize_t` 的表示范围；
  - 不是所有 `timeptr` 成员都在其正常范围内；
  - `timeptr->tm_year` 不在 0 ~ 9999 范围内。

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

>---

#### localtime、localtime_s、localtime_r （time_t 转换为 struct tm 格式）

```c
struct tm *localtime(const time_t *timer);
struct tm *localtime_r(const time_t *timer, struct tm *buf);
```

`localtime` 转换当前的日历时间 `timer` 为分解时间 `struct tm`，表示为本地时间。函数返回一个指向分解时间的指针，如果指定的时间不能转换为本地时间，则返回一个空指针。

`localtime_r` 功能和 `localtime` 相同，除了函数使用的是用户提供的存储 `buf`。

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

>---

#### ctime、ctime_s （time_t 转换成文本）

```c
[[deprecated]] char *ctime(const time_t *timer);
```

此函数自 C23 起弃用。

`ctime` 函数将 `timer` 转换从纪元起的给定日历时间转换为字符串形式的本地时间，它相当于 `asctime(localtime(timer))` 。`ctime` 函数返回由 `asctime` 函数返回的指针，并将分解的时间作为参数。返回格式为 `Www Mmm dd hh:mm:ss yyyy\n` 的时间文本形式。

> C23：`ctime` 将在 C23 被弃用，转而使用线程安全的 `ctime_s`。

```c
errno_t ctime_s( char *buf, rsize_t bufsz, const time_t* timer);
```

函数等价于 `asctime_s(buf, bufsz, localtime_r(timer, &*(struct tm){0}))`。

下列错误并调用当前安装的制约处理函数：
  - `buf` 或 `timer` 为空指针；
  - `bufsz` 小于 26 或超出 `rsize_t` 的范围。

函数将结果 `Www Mmm dd hh:mm:ss yyyy\n` 保存在 `buf` 指向的缓冲区。转换成功时返回非零 `errno_t` 类型的对象。

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

>---

#### gmtime、gmtime_s、gmtime_r （time_t 转换为世界协调时间 UTC 的 struct tm 格式）

```c
struct tm *gmtime(const time_t *timer);
struct tm *gmtime_r(const time_t *timer, struct tm *buf);
```

`gmtime` 函数将 `timer` 指向的日历时间转换为分解时间（`struct tm` 格式）以表示世界协调时间 UTC。函数返回一个指向分解时间的指针，如果指定的时间不能转换为 UTC，则返回一个空指针。

`gmtime_r` 功能和 `gmtime` 相同，除了函数使用的是用户提供的存储 `buf`。

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

>---

#### strftime （格式化输出时间字符串）

```c
size_t strftime(
    char * restrict str,
    size_t maxsize,
    const char * restrict format,
    const struct tm * restrict timeptr
);
```

`strftime` 按照格式字符串 `format`，转换来自给定的日历时间 `timeptr` 的日期和时间信息，并将转换后的空终止多字节字符串 `*format` 写入 `str`，最多写入 `maxsize` 字节。格式字符串 `format` 由零个到多个转换说明负和普通多字节字符组成。

`strftime` 在格式化转换成功时，返回写入 `str` 所指向的字符数组的字节数，不包括字节终止符 `\0`。否则返回零，此时 `str` 被写入的内容是不确定的。转换完成后自动在最后写入字符的位置后添加 `\0` 表示字符串终止。

> `format` *中的转换说明符列举*

每个转换符都应替换为以下描述的适当字符。适当的字符应该使用当前语言环境的 `LC_TIME` 类别以及 `timeptr` 指向的分解时间结构的零个或多个成员的值来确定。

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
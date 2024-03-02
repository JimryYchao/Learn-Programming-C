## C 错误报告（Errors）：errno.h

`errno.h` 定义了几个有关错误报告条件相关的宏。

---
### Macros

#### C 标准定义 macros

```c
#define ERANGE 22  // 计算结果过大
#define EDOM 33    // 数学参数在定义域之外 
#define EILSEQ 42  // 非法字节序列
```

每个定义于 `errno.h` 的宏都展开成 `int` 类型的整数常量表达式，并且拥有独立的正整数值。

```c
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>
 
int main(void)
{
    errno = 0;
    printf("log(-1.0) = %f\n", log(-1.0));
    printf("%s\n\n", strerror(errno));
 
    errno = 0;
    printf("log(0.0)  = %f\n", log(0.0));
    printf("%s\n", strerror(errno));
}
/*
    log(-1.0) = 1.#QNAN0
    Domain error

    log(0.0)  = -1.#INF00
    Result too large
*/
```

> POSIX 和 C++ 标准库定义了更多的额外错误常量

<br>

#### errno （错误码）

```c
extern int *_errno(void);
#define errno (*_errno())
```


`errno` 是一个预处理器宏，展开成线程本地 `int` 类型的可修改左值。一些标准库函数通过写入正整数到 `errno` 指定错误。

通常会将 `errno` 的值（程序启动时为 0）设置为错误码（一般以 E 开始的宏常量，定义于 `errno.h`）之一。库函数绝不会将 0 存储于 `errno` 中。

库函数 `perror` 和 `strerror` 能用于获得当前 `errno` 值的错误条件的文本描述。

```c
#include <stdio.h>
#include <math.h>
#include <errno.h>
 
void show_errno(void)
{
    const char *err_info = "unknown error";
    switch (errno) {
    case EDOM:
        err_info = "domain error";
        break;
    case EILSEQ:
        err_info = "illegal sequence";
        break;
    case ERANGE:
        err_info = "pole or range error";
        break;
    case 0:
        err_info = "no error";
    }
    fputs(err_info, stdout);
    puts(" occurred");
}
 
int main(void)
{
    errno = 0;
    1.0/0.0;
    show_errno();
 
    errno = 0;
    acos(+1.1);
    show_errno();
 
    errno = 0;
    log(0.0);
    show_errno();
 
    errno = 0;
    sin(0.0);
    show_errno();
}
/*
no error occurred
domain error occurred
pole or range error occurred
no error occurred
*/
```

---
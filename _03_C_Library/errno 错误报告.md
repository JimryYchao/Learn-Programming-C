## C 错误报告（Errors）：errno.h

`errno.h` 定义了几个有关错误条件的报告相关的宏。

---
### Macros

#### 错误条件宏

```c
#define ERANGE          // 计算结果过大
#define EDOM            // 数学参数在定义域之外 
#define EILSEQ          // 非法字节序列
```

这些宏定义分别扩展为 `int` 类型、不同正值的整数常量表达式，且适用于包含条件表达式的预处理指令中使用。其他的错误条件宏定义（一般由 `E` 加数字或 `E` 加大写字母开头）也可以由实现指定。

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

>---

#### errno （错误码）

```c
extern int *_errno(void);
#define errno (*_errno())  // 可能的实现
```

`errno` 扩展为一个可修改的左值，且具有 `int` 类型和线程存储时间。一些标准库函数通过写入正整数到 `errno` 指定错误。如果宏定义被禁止访问实际对象，或者程序定义了名为 `errno` 的标识符，则行为未定义。

在程序启动时，`errno` 在初始线程中的值为零（`errno` 在其他线程中指定的对象的初始表示形式是不确定的），任何的库函数都不会将其设置为零。无论是否存在错误，`errno` 的值都可以通过库函数调用设置为非零，前提是 C 标准中的函数描述中没有记录 `errno` 的使用。

库函数通常会将 `errno` 的值设置为错误码（一般以 E 开始的宏常量，定义于 `errno.h`）之一。库函数绝不会将 0 存储于 `errno` 中。

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
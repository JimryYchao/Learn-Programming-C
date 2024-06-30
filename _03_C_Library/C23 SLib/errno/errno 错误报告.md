## C 错误报告：errno.h

`errno.h` 定义了几个有关错误条件的报告相关的宏。

>---
### errno

`errno` 扩展为一个可修改的线程存储类型的 `int` 左值。一些标准库函数通过写入正整数到 `errno` 指定错误。线程初始化时值为零。库函数 `perror` 和 `strerror` 能用于获得当前 `errno` 值的错误条件的文本描述。

错误条件宏定义（一般由 `E` 加数字或 `E` 加大写字母开头）可以由实现指定，适用于包含条件表达式的预处理指令中使用。

```c
#define ERANGE          // 计算结果过大
#define EDOM            // 数学参数在定义域之外 
#define EILSEQ          // 非法字节序列
```

发生特定的错误时，相应的函数将设置 `errno`。例如浮点错误：

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
    1.0 / 0.0;
    show_errno(); // no error occurred

    acos(+1.1);
    show_errno(); // domain error occurred

    log(0.0);
    perror("log(0.0)"); // log(0.0): Result too large

    float a = sqrtf(-1);
    printf(strerror(errno)); // Domain error
}
```

---
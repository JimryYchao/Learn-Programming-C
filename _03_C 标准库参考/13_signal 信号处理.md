## C 信号处理（Signal handling）：signal.h

`signal.h` 用于处理各种信号（程序执行期间可能报告的条件）。

---
### Type

#### sig_atomic_t

```c
typedef int sig_atomic_t;
```

- `sig_atomic_t` 是整数类型，可以作为原子实体访问（即使存在异步中断）。

---
### Macros

#### 定义信号处理函数

```c
#define SIG_DFL         // 默认信号处理
#define SIG_IGN         // 忽略信号中断

#define SIG_ERR         // 指示以发生错误信号的返回类型
```

- 这些宏扩展为不同值的常量表达式，其类型与 `signal` 函数的第二个参数和返回值兼容。其返回值

#### 定义信号类型 sig

```c
#define SIGTERM	        // 发送给程序的终止请求
#define SIGINT	        // 外部中断，通常为用户所发动
#define SIGABRT	        // 异常终止条件，例如 abort() 所起始的

#define SIGFPE	        // 错误的算术运算，如除以零
#define SIGILL	        // 非法程序映像，例如非法指令
#define SIGSEGV	        // 非法内存访问（段错误）
```

- 这些宏展开成拥有相异值的整数常量表达式，表示发送给程序的不同信号。

---
### Function

#### signal （指定信号处理函数）

```c
void (*signal(int sig, void (*handler)(int)))(int);

// 等效写法
typedef void (*_fn_signal_t) (int) 
_fn_signal_t signal(int sig, _fn_signal_t handler);
```

- 设置信号 `sig` 的错误处理函数：
  - `sig` 信号类型，可以是 `SIGTERM`、`SIGSEGV`、`SIGINT`、`SIGILL`、`SIGABRT`、`SIGFPE` 等的一种；
  - `handler` 信号处理函数，可以是默认处理 `SIG_DFL`、忽略信号 `SIG_IGN` 或用户定义函数 `void func(int sig)` 类型的函数指针。

- 若 `signal` 设置成功，则返回之前设置的信号处理 `handler`，失败则返回 `SIG_ERR`。

- 从信号处理函数返回时，信号处理函数所修改的任何对象的值，除了 `volatile sig_atomic_t` 及免锁原子对象，均为未定义。

- 在多线程程序中使用 `signal` 会导致未定义行为。

> *信号处理函数*

 用户定义的信号处理函数必须满足：
  - 若用户定义函数在处理 `SIGFPE`、`SIGILL` 或 `SIGSEGV` 时返回，则行为未定义。
  - 若作为 `abort` 或 `raise` 的结果调用了信号处理函数 `handler`，若 `handler` 调用了 `raise`，则行为未定义。
  - 若信号处理函数不是作为 `abort` 或 `raise` 的结果调用（换言之，信号处理是异步的），则在下列场合行为未定义：
    - **信号处理在调用任何标准库内的函数**，除了 `abort`、`_Exit`、`quick_exit`、以当前处理信号的编号为第一参数调用 `signal`、`stdatomic.h` 的原子操作函数且原子参数是无锁的、`atomic_is_lock_free` （以任意类型的原子参数）。
    - **信号处理函数使用任何拥有静态或线程存储期，且非免锁原子的对象**，除了赋值给静态 `volatile sig_atomic_t` 对象。

进入信号处理函数时，浮点环境状态和所有对象的值是未指定的，除了
  - `volatile sig_atomic_t` 对象；
  - 免锁原子类型对象；
  - 通过 `atomic_signal_fence` 使之可见的副效应。

触发信号处理函数时，会将程序的退出代码设置为 `code = 3`

<br>

#### raise （触发特定信号处理函数）

```c
int raise(int sig);
```

- `raise` 函数对 `sig` 描述的信号类型执行对应的信号处理函数，在 `handler` 信号处理函数返回之前，`raise` 函数不会返回。信号处理成功时返回零，不成功时返回非零值。

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
 
void signal_handler(int signal)
{
    printf("Received signal %d\n", signal);
}
 
int main(void)
{
    /* 安装信号处理函数。 */
    if (signal(SIGTERM, signal_handler) == SIG_ERR)
    {
        printf("Error while installing a signal handler.\n");
        exit(EXIT_FAILURE);
    }
 
    printf("Sending signal %d\n", SIGTERM);
    if (raise(SIGTERM) != 0)
    {
        printf("Error while raising the SIGTERM signal.\n");
        exit(EXIT_FAILURE);
    }
 
    printf("Exit main()\n");
    return EXIT_SUCCESS;
}
```

---
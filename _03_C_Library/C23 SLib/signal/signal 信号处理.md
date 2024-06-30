## C 信号处理：signal.h

`signal.h` 用于处理各种信号（程序执行期间可能报告的条件）。

>---
### 信号处理

| Specifier | Description                                  |
| :-------- | :------------------------------------------- |
|`sig_atomic_t`|整数类型（可能是 `volatile` 限定）的对象，可以作为原子实体访问，即使存在异步中断。|
| `signal`  | 指定信号处理函数。                           |
| `SIGABRT` | 信号值，异常终止。例如由异常终止启动的 `abort` 函数。    |
| `SIGFPE`  | 信号值，一种错误的算术运算。如除零或导致溢出的运算 。  |
| `SIGILL`  | 信号值，检测无效函数图像。例如无效指令。               |
| `SIGINT`  | 信号值，收到交互式注意信号。                          |
| `SIGSEGV` | 信号值，对存储器的无效访问。                           |
| `SIGTERM` | 信号值，发送到程序的终止请求。                         |
| `SIG_DFL` | 信号处理函数，默认信号处理。                 |
| `SIG_IGN` | 信号处理函数，忽略信号中断。                 |
| `SIG_ERR` | 指示以发生错误信号的返回类型。 |
|`raise`|对 `sig` 描述的信号类型执行对应的信号处理函数，在 `func` 信号处理程序返回之前，`raise` 函数不会返回。成功时返回零。|


> signal

`signal` 函数从随后处理接收信号值的三种方式中选择一种：
- 如果 `func` 的值为 `SIG_DFL`，则将对该信号进行默认处理。
- 如果 `func` 的值为 `SIG_IGN`，则该信号将被忽略。
- 否则，`func` 将指向该信号发生时要调用的函数。

当一个信号发生并且 `func` 指向一个函数时，是否等效于执行 `signal(sig, SIG_DFL);` 是由实现定义的，或者实现阻止一些实现定义的信号集（至少包括 `sig`）发生，直到当前信号处理完成；在 `SIGILL` 信号的情况下，实现可以选择定义不采取任何操作。当函数返回时，如果 `sig` 的值是 `SIGFPE`、`SIGILL`、`SIGSEGV` 或任何其他与计算异常相对应的实现定义的值，则该行为未定义；否则程序将在被中断的点恢复执行。
 
如果信号是由于调用 `abort` 或 `raise` 函数发生的，则信号处理程序不应调用 `raise` 函数。

如果信号处理程序引用任何具有静态或线程存储持续时间的对象，该对象不是无锁原子对象，并且不是使用 `constexpr` 存储类说明符声明的对象，而是将值赋给声明为 `volatile sig_atomic_t` 的对象，或者信号处理程序调用除下面列出的标准库中的任何函数，而不是调用 `abort` 或 `raise` 函数，则该行为未定义：
- `abort`、`_Exit`、`quick_exit`；
- `stdatomic.h` 头文件中声明的函数（除非另有说明），且原子参数是无锁的；
- 带有任意原子参数的 `atomic_is_lock_free` 函数；
- 第一个参数等于导致调用处理程序的信号对应的信号数的 `signal` 函数。此外，如果对 `signal` 函数的这种调用导致 `SIG_ERR` 返回，则由 `errno` 指定的对象具有不确定的表示。

在程序启动时，`signal(sig, SIG_IGN);` 可以对以实现定义的方式选择的一些信号执行；`signal(sig, SIG_DFL)` 对实现定义的其他信号执行。

在多线程程序中使用 `signal` 会导致未定义行为。实现应表现得好像没有库函数调用 `signal` 函数。

如果请求可以被执行，`signal` 函数对指定的信号 `sig` 返回最近一次成功调用的 `func`。否则，返回 `SIG_ERR` 的值，并将有一个正值存储在 `errno` 中。

设置信号 `sig` 的错误处理函数：
  - `sig` 信号类型，可以是 `SIGTERM`、`SIGSEGV`、`SIGINT`、`SIGILL`、`SIGABRT`、`SIGFPE` 等的一种；
  - `func` 信号处理程序，可以是默认处理 `SIG_DFL`、忽略信号 `SIG_IGN` 或用户定义的信号处理程序 `void func(int sig)` 类型的函数指针。

进入信号处理程序时，浮点环境状态和所有对象的值是未指定的，除了
  - `volatile sig_atomic_t` 对象；
  - 免锁原子类型对象；
  - 通过 `atomic_signal_fence` 使之可见的副效应。

触发信号处理程序时，会将程序的退出代码设置为 `code = 3`

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
 
void signal_handler(int signal)
{
    printf("signal %d\n", signal);
}
 
int main(void)
{
    /* 安装信号处理函数。 */
    if (signal(SIGTERM, signal_handler) == SIG_ERR)
    {
        perror("Error while installing a signal handler: ");
        exit(EXIT_FAILURE);
    }
 
    if (raise(SIGTERM) != 0)   // signal 15
    {
        printf("Error while raising the SIGTERM signal.\n");
        exit(EXIT_FAILURE);
    }

    signal(SIGABRT, signal_handler);
    abort();  // signal 22
}
```

---
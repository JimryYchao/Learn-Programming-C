## C 线程库（Threads）：threads.h

`threads.h` 包含 `time.h`，并声明了支持多个执行线程的类型、枚举常量、宏定义和函数。若定义了 `__STDC_NO_THREADS__` 则不提供该头文件。

> types

|Specifier|Description|
|:--|:--
`cnd_t` | 保存条件变量的标识符。
`thrd_t` | 保存线程的标识符。
`tss_t` | 保存特定于线程的存储指针的标识符。
`mtx_t` | 保存互斥锁的标识符。
`tss_dtor_t` | 函数指针类型 `void(*)(void *)`，用于特定于线程的存储指针的析构函数。
`thrd_start_t` | 函数指针类型 `int(*)(void *)`，用以传递给 `thrd_create` 创建一个新的线程。
`once_flag` | 包含有供 `call_once` 使用的标志

> enums

```c
enum {
    mtx_plain,      // 传递给 `mtx_init` 创建不支持超时的互斥对象。
    mtx_recursive,  // 传递给 `mtx_init` 创建支持递给锁定的互斥对象。
    mtx_timed,      // 传递给 `mtx_init` 创建支持超时的互斥对象。
}

enum{
    thrd_success,   // 指示请求的操作成功。
    thrd_nomen,     // 指示请求的操作失败，因为它无法分配内存。
    thrd_timedout,  // 由定时等待函数返回，以指示在未获取请求的资源的情况下已达到调用中指定的时间。
    thrd_busy,      // 指示请求的操作失败，因为测试和返回函数请求的资源已在使用中。
    thrd_error,     // 指示请求的操作失败。
}
```

>---
### Functions
#### call_once （初始化函数）

```c
#define ONCE_FLAG_INIT
void call_once(once_flag *flag, void (*func)(void));
```

`call_once` 函数使用 `flag` 标志指向的 `once_flag` 来确保 `func` 只调用一次，即第一次使用该 `flag` 值调用 `call_once` 函数。完成对 `call_once` 函数的有效调用将与对具有相同 `flag` 值的 `call_once` 函数的所有后续调用同步。

`ONCE_FLAG_INIT` 扩展为可用于初始化类型为 `once_flag` 的对象的值。

>---
#### 条件变量函数：cnd_init、cnd_broadcast、cnd_signal、cnd_wait、cnd_timedwait、cnd_destroy

```c
int cnd_init(cnd_t *cond);
int cnd_broadcast(cnd_t *cond);
int cnd_signal(cnd_t *cond);
int cnd_wait(cnd_t *cond, mtx_t *mtx);
int cnd_timedwait(cnd_t * restrict cond, mtx_t * restrict mtx, const struct timespec * restrict ts);
void cnd_destroy(cnd_t *cond);
```

`cnd_init` 函数创建一个条件变量。如果成功，它会将 `cond` 指向的对象设置为唯一标识新创建的条件变量的值。对新创建的条件变量调用 `cnd_wait` 的线程将阻塞。`cnd_init` 函数在成功时返回 `thrd_success`，如果无法为新创建的条件分配内存，则返回 `thrd_nomem`，如果无法满足请求，则返回 `thrd_error`。

`cnd_broadcast` 函数取消阻止在调用时 `cond` 指向的条件变量上被阻塞的所有线程。如果在调用时 `cond` 指向的条件变量上没有线程被阻塞，则该函数不执行任何操作。`cnd_broadcast` 函数在成功时返回  `thrd_success`，如果无法满足请求，则返回 `thrd_error`。

`cnd_signal` 函数取消阻塞在调用时 `cond` 指向的条件变量上被阻塞的一个线程。如果在调用时条件变量上没有阻止线程，则函数不执行任何操作并返回成功。`cnd_signal` 函数在成功时返回 `thrd_success`，如果无法满足请求，则返回 `thrd_error`。

`cnd_wait` 函数以原子方式解锁 `mtx` 指向的互斥锁并阻塞，直到 `cond` 指向的条件变量通过调用 `cnd_signal` 或 `cnd_broadcast` 发出信号，或者直到由于未指定的原因而解除阻塞。当调用线程被解锁时，它会在返回之前锁定 `mtx` 指向的互斥锁。`cnd_wait` 函数要求调用线程锁定 `mtx` 指向的互斥锁。函数在成功时返回 `thrd_success`，如果无法满足请求，则返回 `thrd_error`。

`cnd_timedwait` 函数以原子方式解锁 `mtx` 指向的互斥锁并阻塞，直到 `cond` 指向的条件变量通过调用 `cnd_signal` 或 `cnd_broadcast` 发出信号，或者等待直到 `ts` 指向的基于 `TIME_UTC` 的日历时间之后，或者直到由于未指定的原因而解除阻塞。当调用线程被解锁时，它会在返回之前锁定 `mtx` 指向的对象。`cnd_timedwait` 函数要求调用线程锁定 `mtx` 指向的互斥锁。函数在成功时返回 `thrd_success`，如果达到调用中指定的时间而未获取请求的资源，则返回 `thrd_timedout`，如果无法满足请求，则返回 `thrd_error`。

`cnd_destroy` 函数释放 `cond` 指向的条件变量使用的所有资源。函数要求没有线程正在等待 `cond` 指向的条件变量时阻塞。

>---
#### 互斥函数：mtx_init、mtx_lock、mtx_timedlock、mtx_trylock、mtx_unlock、mtx_destroy

```c
int mtx_init(mtx_t *mtx, int type);
int mtx_lock(mtx_t *mtx);
int mtx_timedlock(mtx_t * restrict mtx, const struct timespec * restrict ts);
int mtx_trylock(mtx_t *mtx);
int mtx_unlock(mtx_t *mtx);
void mtx_destroy(mtx_t *mtx);
```

`mtx_init` 函数创建一个互斥对象，该对象具有由 `type` 指示的属性。如果 `mtx_init` 函数成功，它会将 `mtx` 指向的互斥锁设置为唯一标识新创建的互斥锁的值。函数在成功时返回 `thrd_success`，如果请求无法满足，则返回 `thrd_error`。该 `type` 应具有以下值之一：
- `mtx_plain` 对于简单的非递归互斥锁;
- `mtx_timed` 支持超时的非递归互斥锁；
- `mtx_plain | mtx_recursive` 对于简单的递归互斥锁，或者；
- `mtx_timed | mtx_recursive`，对于支持超时的递归互斥锁。

`mtx_lock` 函数会阻塞，直到它锁定 `mtx` 指向的互斥锁。如果互斥锁是非递归的，则不应被调用线程锁定。之前对同一互斥锁上 `mtx_unlock` 的调用将与此操作同步。函数在成功时返回 `thrd_success`，如果请求无法满足，则返回 `thrd_error`。

`mtx_timedlock` 函数会尝试阻塞，直到它锁定 `mtx` 指向的互斥锁，或者等待直到 `ts` 指向的基于 `TIME_UTC` 的日历时间之后。指定的互斥锁应支持超时。如果操作成功，则之前对同一互斥锁上的 `mtx_unlock` 的调用将与此操作同步。函数在成功时返回 `thrd_success`，如果达到指定的时间而未获取请求的资源，则返回 `thrd_timedout`，如果无法满足请求，则返回 `thrd_error`。

`mtx_trylock` 函数试图锁定 `mtx` 指向的互斥锁。如果互斥锁已锁定，则该函数返回而不阻塞。如果操作成功，则之前对同一互斥锁上的 `mtx_unlock` 的调用将与此操作同步。函数在成功时返回 `thrd_success`，如果请求的资源已在使用中，则返回 `thrd_busy`，如果请求无法满足，则返回 `thrd_error`。`mtx_trylock` 可能会错误地无法锁定未使用的资源，在这种情况下，它会返回 `thrd_busy`。

`mtx_unlock` 函数解锁 `mtx` 指向的互斥锁。`mtx` 指向的互斥锁应由调用线程锁定。函数在成功时返回 `thrd_success`，如果无法满足请求，则返回 `thrd_error`。

`mtx_destroy` 函数释放 `mtx` 指向的互斥锁使用的任何资源。等待 `mtx` 指向的互斥锁时，不能阻塞任何线程。

>---
#### 线程函数：thrd_create、thrd_current、thrd_detach、thrd_equal、thrd_exit、thrd_join、thrd_sleep、thrd_yield

```c
int thrd_create(thrd_t *thr, thrd_start_t func, void *arg);
thrd_t thrd_current(void);
int thrd_detach(thrd_t thr);
int thrd_equal(thrd_t thr0, thrd_t thr1);
[[noreturn]] void thrd_exit(int res);
int thrd_join(thrd_t thr, int *res);
int thrd_sleep(const struct timespec *duration, struct timespec *remaining);
void thrd_yield(void);
```

`TSS_DTOR_ITERATIONS` 扩展为一个整数常量表达式，表示线程终止时将调用析构函数的最大次数。

`thrd_create` 函数创建一个执行 `func(arg)` 的新线程。如果 `thrd_create` 函数成功，它会将 `thr` 指向的对象设置为新创建的线程的标识符。一旦原始线程退出并分离或加入到另一个线程，线程的标识符可以重新用于其他线程。`thrd_create` 函数的完成与新线程的开始执行同步。从 `func` 返回的行为与使用从 `func` 返回的值调用 `thrd_exit` 的行为相同。函数在成功时返回 `thrd_success`，如果无法为请求的线程分配内存，则返回 `thrd_nomem`，如果无法满足请求，则返回 `thrd_error`。

`thrd_current` 函数标识调用它的线程。函数返回调用它的线程的标识符。

`thrd_detach` 函数告诉操作系统在线程终止时释放分配给 `thr` 标识的线程的任何资源。由 `thr` 标识的线程之前不得已分离或与其他线程结合。函数在成功时返回 `thrd_success`，如果无法满足请求，则返回 `thrd_error`。

`thrd_equal` 函数将确定由 `thr0` 标识的线程是否引用由 `thr1` 标识的线程。如果线程 `thr0` 和线程 `thr1` 引用不同的线程，则 `thrd_equal` 函数返回零。否则返回非零值。

对于使用非 null 析构函数创建且值为非 null 的每个特定于线程的存储键，`thrd_exit` 将与该键关联的值设置为 `null` 指针值，然后使用其以前的值调用析构函数。调用析构函数的顺序未指定。如果在此过程之后仍保留具有非 null 析构函数和值的键，则实现将重复此过程最多 `TSS_DTOR_ITERATIONS` 次。在此之后，`thrd_exit` 函数终止调用线程的执行，并将其结果代码设置为 `res`。在最后一个线程终止后，程序正常终止。该行为就像程序在线程终止时调用状态为 `EXIT_SUCCESS` 的退出函数一样。

`thrd_join` 函数通过阻塞将 `thr` 标识的线程与当前线程连接起来，直到另一个线程终止。如果参数 `res` 不是 `null` 指针，则它将线程的结果代码存储在 `res` 指向的整数中。另一个线程的终止与 `thrd_join` 函数的完成同步。由 `thr` 标识的线程之前不得已分离或与其他线程连接。函数在成功时返回 `thrd_success`，如果无法满足请求，则返回 `thrd_error`。

`thrd_sleep` 函数暂停调用线程的执行，直到 `duration` 指定的时间间隔已过或接收到未被忽略的信号。如果被信号中断，并且 `remaining` 参数不为 `null`，则剩余时间量（请求的时间间隔减去实际休眠时间）将存储在它指向的间隔中。`duration` 和 `remaining` 参数可以指向同一对象。挂起时间可能比请求的要长，因为时间间隔四舍五入到休眠精度的整数倍，或者由于系统调度了其他活动。但是，除被信号中断的情况外，暂停时间不会少于由系统时钟 `TIME_UTC` 测量的指定时间。如果请求的时间已过，则 `thrd_sleep` 函数返回零，如果被信号中断，则返回 `−1`，如果失败，则返回负值（也可能是 `−1`）。

`thrd_yield` 函数尝试允许其他线程运行，即使当前线程通常会继续运行。

>---
#### 特定于线程的存储函数：tss_create、tss_delete、tss_get、tss_set

```c
#define TSS_DTOR_ITERATIONS     /* implementation */
int tss_create(tss_t *key, tss_dtor_t dtor);
void tss_delete(tss_t key);
void *tss_get(tss_t key);
int tss_set(tss_t key, void *val);
```

`tss_create` 函数使用析构函数 `dtor`（可能为 `null`）创建特定于线程的存储指针。空指针值与所有现有线程中新创建的键相关联。在后续线程创建时，与所有键关联的值将初始化为新线程中的空指针值。与特定于线程的存储关联的析构函数不会在程序终止时调用。`tss_create` 函数不能在析构函数内部调用。如果 `tss_create` 函数成功，它会将 `key` 指向的特定于线程的存储设置为一个值，该值唯一标识新创建的指针并返回 `thrd_success`；否则返回 `thrd_error`，并且按 `key` 指向的特定于线程的存储设置为不确定表示形式。

`tss_delete` 函数释放由 `key` 标识的特定于线程的存储使用的任何资源。`tss_delete` 函数必须在线程开始执行析构函数之前使用由调用 `tss_create` 返回的 `key` 值作为参数进行调用。如果在另一个线程执行析构函数时调用 `tss_delete`，则这是否会影响与该线程上的 `key` 关联的析构函数的调用次数未指定。调用 `tss_delete` 不会导致调用任何析构函数。

`tss_get` 函数返回由 `key` 标识的特定于线程的存储中保存的当前线程的值。`tss_get` 函数必须在线程开始执行析构函数之前使用由调用 `tss_create` 返回的 `key` 值作为参数进行调用。如果成功，函数返回当前线程的值，否则返回零。

`tss_set` 函数将按 `key` 标识的特定于线程的存储中保存的当前线程的值设置为 `val`。`tss_set` 函数必须在线程开始执行析构函数之前使用由调用 `tss_create` 返回的 `key` 值作为参数进行调用。此操作不会调用与要替换的值的键关联的析构函数。`tss_set` 函数在成功时返回 `thrd_success`，如果无法满足请求，则返回 `thrd_error`。

---
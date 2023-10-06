## C 原子操作（Atomics）：stdatomic.h (待定)

`stdatomic.h` 提供原子操作、互斥、条件变量的内建支持。

---
### Standard Define

#### 指示无锁原子类型宏常量 （atomic lock-free macros）

```c
#define ATOMIC_BOOL_LOCK_FREE      1
#define ATOMIC_CHAR_LOCK_FREE      1
#define ATOMIC_CHAR16_T_LOCK_FREE  1
#define ATOMIC_CHAR32_T_LOCK_FREE  1
#define ATOMIC_WCHAR_T_LOCK_FREE   1
#define ATOMIC_SHORT_LOCK_FREE     1
#define ATOMIC_INT_LOCK_FREE       1
#define ATOMIC_LONG_LOCK_FREE      1
#define ATOMIC_LLONG_LOCK_FREE     1
#define ATOMIC_POINTER_LOCK_FREE   1
```

- 这些宏展开成值为 `0` 或 `1` 或 `2` 的预处理器常量表达式，它指示对应的原子类型的免锁属性：
  - `0`：该原子类型绝不免锁
  - `1`：该原子类型有时免锁
  - `2`：该原子类型始终免锁

<br>

#### atomic_flag、ATOMIC_FLAG_INIT

```c
typedef struct atomic_flag {
    _Atomic(_Bool) _Val;
} atomic_flag;

#define ATOMIC_FLAG_INIT     { 0 }
```

- 宏 `ATOMIC_FLAG_INIT` 扩展为 `atomic_flag` 类型对象的初始化式。
- `atomic_flag` 是一种原子布尔类型，表示无锁的原始原子标志。`atomic_flag` 不提供加载或存储操作。

<br>

#### memory_order

```c
typedef enum{
    memory_order_relaxed = __ATOMIC_RELAXED,
    memory_order_consume = __ATOMIC_CONSUME,
    memory_order_acquire = __ATOMIC_ACQUIRE,
    memory_order_release = __ATOMIC_RELEASE,
    memory_order_acq_rel = __ATOMIC_ACQ_REL,
    memory_order_seq_cst = __ATOMIC_SEQ_CST
} memory_order;
```

- `memory_order` 枚举定义常规（非原子）内存同步操作，并提供可能的操作排序：
  - `memory_order_relaxed`	无需排序（宽松顺序）。
  - `memory_order_consume`	加载操作将充当内存位置上的消耗操作。
  - `memory_order_acquire`	加载操作将充当内存位置上的获取操作。
  - `memory_order_release`	存储操作将充当内存位置上的释放操作。
  - `memory_order_acq_rel`	将 `memory_order_acquire` 和 `memory_order_release` 结合。
  - `memory_order_seq_cst`	将 `memory_order_acquire` 和 `memory_order_release` 结合。标记为 `memory_order_seq_cst` 的内存访问必须顺序一致。

> 宽松顺序

- 带标签 `memory_order_relaxed` 的原子操作不是同步操作；它们不会为并发的内存访问行为添加顺序约束。它们只保证原子性和修改顺序的一致性。


```c

```
## C 原子操作：stdatomic.h

`stdatomic.h` 提供原子操作、互斥、条件变量的内建支持。

未指定在 `<stdatomic.h>` 中声明的任何泛型函数是宏还是使用外部链接声明的标识符。如果禁止宏定义以访问实际函数，或者程序使用泛型函数的名称定义外部标识符，则行为未定义。

以下约定：
- *A* 是指原子类型；
- *C* 是指其相应的非原子类型；
- *M* 是指算数运算的其他参数的类型。对于原子整数类型，*M* 是 *C*；对于原子指针类型，*M* 是 `ptrdiff_t`。
- 不以 `_explicit` 结尾的函数与相应的带有 `memory_order_seq_cst` 参数的 `_explicit` 函数具有相同语义的。

>---
### 原子无锁宏

```c
#define ATOMIC_BOOL_LOCK_FREE     
#define ATOMIC_CHAR_LOCK_FREE     
#define ATOMIC_CHAR8_T_LOCK_FREE 
#define ATOMIC_CHAR16_T_LOCK_FREE 
#define ATOMIC_CHAR32_T_LOCK_FREE 
#define ATOMIC_WCHAR_T_LOCK_FREE  
#define ATOMIC_SHORT_LOCK_FREE    
#define ATOMIC_INT_LOCK_FREE      
#define ATOMIC_LONG_LOCK_FREE     
#define ATOMIC_LLONG_LOCK_FREE    
#define ATOMIC_POINTER_LOCK_FREE  
```

这些宏展开成值为 `0` 或 `1` 或 `2` 的预处理器常量表达式，并指示相应原子类型（有符号和无符号）的无锁属性：
  - `0`：该原子类型绝不免锁
  - `1`：该原子类型有时免锁
  - `2`：该原子类型始终免锁

>---
### 原子初始化

具有未初始化的自动存储持续时间的原子对象或具有分配存储持续时间的此类对象最初具有不确定的表示形式；同样，对表示的任何字节的非原子存储（直接存储或例如，通过调用 `memcpy` 或 `memset`）使任何原子对象具有不确定的表示。对于具有静态或线程存储持续时间且不具有类型 `atomic_flag` 的原子对象的显式或默认初始化，可以保证生成有效状态。

在将原子对象设置为有效状态之前，即使通过原子操作，对原子对象的并发访问也构成数据争用。如果信号不是由于调用 `abort` 或 `raise` 函数的结果而发生的，则当信号处理程序读取或修改具有不确定表示形式的原子对象时，该行为是未定义的。

以下定义确保 `guide` 和 `head` 的有效状态，无论这些状态是在文件作用域还是块作用域中找到。因此，在满足初始化后对它们执行的任何原子操作都是明确定义的。

```c
_Atomic int guide = 42;
static _Atomic(void*) head;
```

>---
### 多线程执行和数据竞争

在没有定义 `__STDC_NO_THREADS__` 宏的宿主环境中，程序可以并发运行多个执行线程（或线程）。每个线程的执行按照以下所定义的方式进行。整个程序的执行包括其所有线程的执行。在独立实现中，程序是否可以有多个执行线程是由实现定义的。

线程 *T* 在特定点上可见的对象的值是该对象的初始值、*T* 存储在该对象中的值或另一个线程存储在该对象中的值。

如果其中一个表达式计算修改内存位置，而另一个表达式计算读取或修改相同的内存位置，则两个表达式计算会发生冲突。

`stdatomic.h` 库定义了原子操作，`threads.h` 定义了对互斥锁的操作，这些操作被特别标识为同步操作。这些操作在使一个线程中的分配对另一个线程可见方面发挥着特殊作用。对一个或多个内存位置的同步操作是 *获取操作*、*释放操作*、*获取和释放操作* 或 *使用操作* 之一。没有关联内存位置的同步操作是一个屏障（*fence*），可以是 *获取屏障*、*释放屏障*，也可以同时是 *获取和释放屏障*。此外，还有不属于同步操作的 *宽松原子操作*，以及具有特殊特征的 *原子读-修改-写操作*。

例如，获取互斥锁的调用将对组成互斥锁的位置执行获取操作。相应地，释放相同互斥锁的调用将在这些相同的位置执行释放操作。非正式地，对 *A* 执行释放操作会强制其他内存位置上先前的副作用对稍后对 *A* 执行获取或消耗操作的其他线程可见。宽松的原子操作不包括在同步操作中，尽管与同步操作一样，它们不能导致数据争用。

对特定原子对象 *M* 的所有修改都以某种特定的总顺序发生，称为 *M* 的修改顺序。如果 *A* 和 *B* 是原子对象 *M* 的修改，并且 *A* 发生在 *B* 之前，那么 *A* 应按照 *M* 的修改顺序在 *B* 之前。

每个原子对象都有单独的顺序。对于所有对象，不要求这些可以这些组合为所有对象的单个总顺序。一般来说，这是不可能的，因为不同的线程可以以不一致的顺序观察到对不同变量的修改。

以原子对象 *M* 上的释放操作 *A* 为首的释放序列是 *M* 修改顺序中副作用的最大连续子序列，其中第一个操作是 *A*，每个后续操作要么由执行释放的同一线程执行，要么是 *原子读-修改-写操作*。

某些库调用与另一个线程执行的其他库调用同步（“*synchronizes with*”）。具体而言，对对象 *M* 执行释放操作的原子操作 *A* 与对 *M* 执行获取操作的原子操作 *B* 同步，并读取以 *A* 为首的释放序列中任何副作用写入的值。

同步操作的规范定义了何时读取另一个值。对于原子变量，定义很明确。对给定互斥锁的所有操作都以单一的总顺序发生。每个获取互斥锁都会 “读取” 上一次释放互斥锁时 “写入的值”。

如果满足下列条件，则求值 *A* 依赖于（*carries a dependency*，“*synchronizes with*” 关系的子集）求值 *B*：
- *A* 的值用作 *B* 的操作数，除非：
  - *B* 是 `kill_dependency` 宏的调用，
  - *A* 是 `&&` 或 `||` 运算符的左操作数；
  - *A* 是 `? :` 运算符的左操作数，或，
  - *A* 是 `,` 运算符的左操作数。
- 或，*A* 写入标量对象或位域 *M*，*B* 从 *M* 中读取 *A* 写入的值，并且 *A* 顺序在 *B* 之前，或
- 对于某些求值 *X*，*A* 对 *X* 有依赖，*X* 对 *B* 有依赖。

如果满足以下条件，则求值 *A* “*dependency-ordered before*” 求值 *B*（类似于 “*synchronizes with*”，但是使用 *释放 / 消费* 来代替 *释放 / 获取*）：
- 求值 *A* 对原子对象 *M* 执行释放操作，在另一个线程中，求值 *B* 对 *M* 执行消耗操作，并读取在释放序列中以求值 *A* 为首的任何副作用写入的值，或者；
- 对于某些求值 *X*，求值 *A* “*dependency-ordered before*” 求值 *X*，并且 *X* 对 *B* 有依赖关系。

如果求值 *A* “*synchronizes with*” 求值 *B*，或求值 *A* “*dependency-ordered before*” 求值 *B*，或对于下列的某些求值 *X*，则求值 *A* “*inter-thread happens before*” 求值 *B* ：
- *A* “*synchronizes with*” *X*，*X* “*sequenced before*” *B*；
- *A* “*sequenced before*” *X*，且 *X* “*inter-thread happens before*” *B*；
- *A* “*inter-thread happens before*” *X*，且 *X* “*inter-thread happens before*” *B*。

“*inter-thread happens before*” 关系描述了 “*sequenced before*”、“*synchronizes with*” 和 “*dependency-ordered before*” 关系的任意串联，但有两个例外。
- 第一个例外是，串联不允许以 “*dependency-ordered before*” 后跟 “*sequenced before*” 结尾。造成此限制的原因是，参与 “*dependency-ordered before*” 关系的消耗操作仅针对此消耗操作具有依赖关系的操作提供排序。此限制仅适用于以此类串联结尾的原因是，任何后续发布操作都将为先前的消费操作提供所需的排序。
- 第二个例外是，串联不允许完全由 “*sequenced before*” 组成。这种限制的原因，一是允许 “*inter-thread happens before*” 被传递地关闭，二是 “*happens before*” 关系提供了完全由 “*sequenced before*” 组成的关系。

如果求值 *A* “*sequenced before*” 求值 *B*，或 *A* “*inter-thread happens before*” *B*，则求值 *A* “*happens before*” 求值 *B*。实现应确保没有程序执行在 “*happens before*” 关系的循环中。

对象 *M* 的可见副作用（“*visible side effect*”）*A* 相对 *M* 的值的计算过程 *B* 应满足：*A* *happens before* *B*；且 *X* 对 *M* 没有其他副作用，因此 *A* *happens before* *X*，*X* *happens before* *B*。由求值 *B* 确定的非原子标量对象 *M* 的值应为可见副作用 *A* 存储的值。

如果对非原子对象的副作用存在歧义，则存在数据争用，并且行为未定义。这说明对普通变量的运算不会明显地重新排序。如果没有数据争用，这是无法检测到的，但可以确保数据争用以及对原子的使用有适当的限制，与简单交错（顺序一致）执行中的数据争用相对应。

由求值 *B* 确定的原子对象 *M* 的值应为修改 *M* 的某个副作用 *A* 存储的值，其中 *B* 在 *A* 之前不会发生。

***写-写一致性*** (***write-write coherence***)：如果修改原子对象 *M* 的操作 *A* 发生在修改 *M* 的操作 *B* 之前，则 *A* 在 *M* 的修改顺序上应早于 *B*。

***读-读一致性*** (***read-read coherence***)：如果原子对象 *M* 的值计算 *A* 发生在 *M* 的值计算 *B* 之前，并且 *A* 从 *M* 上的副作用 *X* 中获取其值，则 *B* 计算的值应为 *X* 存储的值或副作用 *Y* 在 *M* 上存储的值，其中 *Y* 按照 *M* 的修改顺序跟随 *X*。

***读-写一致性*** (***read-write coherence***)：如果原子对象 *M* 的值计算 *A* 发生在对 *M* 的操作 *B* 之前，则 *A* 应从 *M* 上的副作用 *X* 中获取其值，其中 *X* 在 *M* 的修改顺序中先于 *B*。

***写-读一致性*** (***write-read coherence***)：如果原子对象 *M* 上的副作用 *X* 发生在 *M* 的值计算 *B* 之前，则求值 *B* 应从 *X* 或沿 *M* 的修改顺序跟随 *X* 的副作用 *Y* 中获取其值。

如果程序在不同的线程中包含两个冲突的操作，其中至少有一个不是原子的，并且都没有先于另一个发生，则程序的执行包含数据争用。任何此类数据争用都会导致未定义的行为。

>---
### 顺序与一致性


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
枚举类型 `memory_order` 指定上节定义的常规（非原子）内存同步操作，并提供可能的操作排序。它的枚举常量如下：
  - `memory_order_relaxed`	无需排序（宽松顺序）。
  - `memory_order_consume`	加载操作将充当内存位置上的消耗操作。
  - `memory_order_acquire`	加载操作将充当内存位置上的获取操作。
  - `memory_order_release`	存储操作将充当内存位置上的释放操作。
  - `memory_order_acq_rel`	将 `memory_order_acquire` 和 `memory_order_release` 结合。
  - `memory_order_seq_cst`	将 `memory_order_acquire` 和 `memory_order_release` 结合。标记为 `memory_order_seq_cst` 的内存访问必须顺序一致。

对于 `memory_order_relaxed`，无操作排序内存。

对于 `memory_order_release`、`memory_order_acq_rel` 和 `memory_order_seq_cst`，存储操作对受影响的内存位置执行释放操作。

对于 `memory_order_acquire`、`memory_order_acq_rel` 和 `memory_order_seq_cst`，加载操作对受影响的内存位置执行获取操作。

对于 `memory_order_consume`，加载操作对受影响的内存位置执行消耗操作。

所有 `memory_order_seq_cst` 操作上应该有一个单一的总排序 *S*，与所有受影响位置的 “*happens before*” 顺序和修改顺序一致，以便每个从原子对象 *M* 加载值的 `memory_order_seq_cst` 操作 *B* 都会观察到以下值之一：
- 在 *S* 排序中的操作 *B* 之前，观察到对 *M* 进行最后一次修改操作 *A* 的结果（如果存在），或者
- 如果 *A* 存在，则观察到对 *M* 进行某些修改的结果，该修改不是 `memory_order_seq_cst`，且在 *A* 之前不会发生，或者
- 如果 *A* 不存在，则观察到对 *M* 进行某些操作（非 `memory_order_seq_cst`）的结果。

虽然没有明确要求 *S* 包含锁定操作，但它始终可以扩展到包含锁定和解锁操作的顺序，因为这些操作之间的排序已经包含在 “*happens before*” 排序中。

指定 `memory_order_relaxed` 的原子运算仅在内存排序方面有所放宽。实现仍然保证对特定原子对象的任何给定原子访问相对于对该对象的所有其他原子访问是不可分割的。

对于读取原子对象 *M* 值的原子操作 *B*，如果存在一个 `memory_order_seq_cst` 屏障 *X* *sequenced before* *B*，则 *B* 要么观察到 *M* 在 *X* 之前以单一总排序 *S* 的最后一次 `memory_order_seq_cst` 的修改，要么观察到 *M* 自身的修改顺序的最近一次修改。

对于原子对象 *M* 上的原子运算 *A* 和 *B*，其中 *A* 修改 *M* 并且 *B* 取其值，如果有一个 `memory_order_seq_cst` 屏障 *X*，使得在单一总排序 *S* 上，*A* “*sequenced before*” *X* 且 *B* 紧随 *X* 之后，则 *B* 要么是观察到 *A* 副作用，要么观察到 *M* 自身的修改顺序的最近一次修改。

对于原子对象 *M* 的原子修改 *A* 和原子修改 *B*，如果满足以下条件，则在 *M* 的修改顺序中，*B* 发生在 *A* 之后：
- 存在一个 `memory_order_seq_cst` 屏障 *X*，使得在单一总排序 *S* 上，*A* “*sequenced before*” *X*，且 *X* 先于 *B*；或
- 存在一个 `memory_order_seq_cst` 屏障 *Y*，使得在单一总排序 *S* 上，*Y* “*sequenced before*” *B*，且 *A* 先于 *X*；或
- 存在 `memory_order_seq_cst` 屏障 *X* 和 *Y*，使得在单一总排序 *S* 上，*A* “*sequenced before*” *X*，*Y* “*sequenced before*” *B*，且 *X* 先于 *Y*。

原子 *读-修改-写操作* 应始终读取与 *读-修改-写操作* 关联的写入之前存储的最后一个值（按修改顺序）。

原子存储应仅存储通过有限程序求值序列，从常量和程序输入值中计算得出的值，以便每个求值都可以观察存储的有序列中最后一个先前赋值计算的对象值。按此序列进行求值的顺序如下：
- 如果求值 *B* 观察到 *A* 在不同线程中计算的值，则 *B* 不会在 *A* 之前发生。
- 如果序列中包含求值 *A*，则还包括分配给同一对象并在 *A* 之前发生的所有求值。

实现应使原子存储在合理的时间内对原子加载可见。

>---
#### kill_dependency

```c
/* type */ kill_dependency(/* type */ y);
```

`kill_dependency` 宏终止依赖关系链；该参数不附带对返回值的依赖。宏返回 `y` 的值。

>---
### Fences（屏障）

屏障可以有获取语义、释放语义、或两者都有。具有获取语义的屏障称为 *获取屏障*；具有释放语义的屏障称为 *释放屏障*。

对于释放屏障 *A* 与获取屏障 *B*，如果存在原子操作 *X* 和 *Y*，且两者都对某个原子对象 *M* 进行操作，并使得 *A* *sequenced before* *X*，*X* 修改 *M*，*Y* *sequenced before* *B* 且 *Y* 读取由 *X* 写入的值或由假定的释放序列 *X*（如果它是释放操作）中的任何副作用写入的值，则释放屏障 *A* 与获取屏障 *B* 同步。

对于释放屏障 *A* 与原子操作 *B*，原子操作 *B* 对原子对象 *M* 执行获取操作，如果存在原子操作 *X*，使得 *A* *sequenced before* *X*，*X* 修改 *M*，*B* 读取由 *X* 写入的值或由假定的释放序列 *X*（如果它是释放操作）中的任何副作用写入的值，则释放屏障 *A* 与原子操作 *B* 同步。

对于原子操作 *A* 和释放屏障 *B*，原子操作 *A* 在原子对象 *M* 上执行释放操作，如果在 *M* 上存在某俄歇原子操作 *X*，使得 *X* *sequenced before* *B*，并且 *X* 读取由 *A* 写入的值或由以 *A* 为首的释放序列中的任何副作用写入的值，则原子操作 *A* 与释放屏障 *B* 同步。

>---
#### atomic_thread_fence

```c
void atomic_thread_fence(memory_order order);
```

根据 `order` 的值，该操作 `atomic_thread_fence(order)`：
- `memory_order_relaxed`，没有效果；
- `memory_order_acquire` 或 `memory_order_consume`，是一个获取屏障；
- `memory_order_release`，是一个释放屏障；
- `memory_order_acq_rel`，是兼具释放和获取语义的屏障；
- `memory_order_seq_cst`，是顺序一致的释放和获取语义的屏障。

>---
#### atomic_signal_fence

```c
void atomic_signal_fence(memory_order order);
```

`atomic_signal_fence` 等效于 `atomic_thread_fence(order)`，不同之处在于生成的排序约束仅在线程和在同一线程中执行的信号处理程序之间建立。

`atomic_signal_fence` 函数可用于指定线程执行的操作对信号处理程序可见的顺序。

>---
### 无锁属性

原子无锁宏指示整数和地址原子类型的无锁属性。值为 0 表示该类型永远不会无锁；值为 1 表示该类型有时是无锁的；值为 2 表示该类型始终是无锁的。

无锁定的操作也应该是无地址的。也就是说，通过两个不同地址对同一内存位置的原子操作将进行原子通信。实现不应依赖于任何每个进程的状态。此限制允许通过多次映射到进程的内存和两个进程之间共享的内存进行通信。

>---
#### atomic_is_lock_free

```c
bool atomic_is_lock_free(const volatile A *obj);
```

`atomic_is_lock_free` 泛型函数确认对 `obj` 指向的类型的对象的原子操作是否是无锁的。当且仅当对参数指向的类型的对象的原子操作是无锁的时，泛型函数返回非零。在任何给定的程序执行中，无锁查询的结果对于相同类型的所有指针应是一致的。

---
### 原子整数类型

对于下表中的每一行，原子类型名称被声明为与相应的直接类型具有相同表示和对齐要求的类型。

| Atomic type             | Direct type                  |
| :---------------------- | :--------------------------- |
| `atomic_bool`           | `_Atomic bool`               |
| `atomic_char`           | `_Atomic char`               |
| `atomic_schar`          | `_Atomic signed char`        |
| `atomic_uchar`          | `_Atomic unsigned char`      |
| `atomic_short`          | `_Atomic short`              |
| `atomic_ushort`         | `_Atomic unsigned short`     |
| `atomic_int`            | `_Atomic int`                |
| `atomic_uint`           | `_Atomic unsigned int`       |
| `atomic_long`           | `_Atomic long`               |
| `atomic_ulong`          | `_Atomic unsigned long`      |
| `atomic_llong`          | `_Atomic long long`          |
| `atomic_ullong`         | `_Atomic unsigned long long` |
| `atomic_char8_t`        | `_Atomic char8_t`            |
| `atomic_char16_t`       | `_Atomic char16_t`           |
| `atomic_char32_t`       | `_Atomic char32_t`           |
| `atomic_wchar_t`        | `_Atomic wchar_t`            |
| `atomic_int_least8_t`   | `_Atomic int_least8_t`       |
| `atomic_uint_least8_t`  | `_Atomic uint_least8_t`      |
| `atomic_int_least16_t`  | `_Atomic int_least16_t`      |
| `atomic_uint_least16_t` | `_Atomic uint_least16_t`     |
| `atomic_int_least32_t`  | `_Atomic int_least32_t`      |
| `atomic_uint_least32_t` | `_Atomic uint_least32_t`     |
| `atomic_int_least64_t`  | `_Atomic int_least64_t`      |
| `atomic_uint_least64_t` | `_Atomic uint_least64_t`     |
| `atomic_int_fast8_t`    | `_Atomic int_fast8_t`        |
| `atomic_uint_fast8_t`   | `_Atomic uint_fast8_t`       |
| `atomic_int_fast16_t`   | `_Atomic int_fast16_t`       |
| `atomic_uint_fast16_t`  | `_Atomic uint_fast16_t`      |
| `atomic_int_fast32_t`   | `_Atomic int_fast32_t`       |
| `atomic_uint_fast32_t`  | `_Atomic uint_fast32_t`      |
| `atomic_int_fast64_t`   | `_Atomic int_fast64_t`       |
| `atomic_uint_fast64_t`  | `_Atomic uint_fast64_t`      |
| `atomic_intptr_t`       | `_Atomic intptr_t`           |
| `atomic_uintptr_t`      | `_Atomic uintptr_t`          |
| `atomic_size_t`         | `_Atomic size_t`             |
| `atomic_ptrdiff_t`      | `_Atomic ptrdiff_t`          |
| `atomic_intmax_t`       | `_Atomic intmax_t`           |
| `atomic_uintmax_t`      | `_Atomic uintmax_t`          |

转换到 `atomic_bool` 的行为与转换到 `bool` 相同。

原子整数类型的表示形式不需要与相应的常规类型具有相同的大小，但应尽可能具有相同的大小，因为它可以减轻移植现有代码所需的工作量。

---
### 原子操作

| Specifier                  | Description                                                                                             |
| :------------------------- | :------------------------------------------------------------------------------------------------------ |
| `atomic_init`              | 将 `obj` 指向的原子对象初始化为 `value` 的值，同时还初始化实现可能需要为原子对象携带的任何附加状态。    |
| `atomic_store`,            | 以原子方式存储 `object` 的值为 `desired`。                                                              |
| `atomic_store_explicit`    | `order` 参数不能是 `memory_order_acquire`、`memory_order_consume` 或 `memory_order_acq_rel`。           |
| `atomic_load`              | 以原子方式返回 `object` 指向的对象的值。                                                                |
| `atomic_load_explicit`     | `order` 参数不能是 `memory_order_release` 或 `memory_order_acq_rel`。内存受到 `order` 值的影响。        |
| `atomic_exchange`          | 以原子方式将 `object` 指向的值替换为 `desired` 的值。                                                   |
| `atomic_exchange_explicit` | 操作是读-修改-写操作。内存受到 `order` 值的影响。函数以原子方式返回在副作用发生之前 `object` 指向的值。 |


>---
#### atomic_compare_exchange

```c
bool atomic_compare_exchange_strong(volatile A *object, C *expected, C desired);
bool atomic_compare_exchange_strong_explicit(volatile A *object, C *expected, 
C desired, memory_order success, memory_order failure);
bool atomic_compare_exchange_weak(volatile A *object, C *expected, C desired);
bool atomic_compare_exchange_weak_explicit(volatile A *object, C *expected,
C desired, memory_order success, memory_order failure);
```
 
`failure` 参数不能是 `memory_order_release` 或 `memory_order_acq_rel`，且 `failure` 不能强于 `success`。

泛型函数以原子方式，将 `object` 指向的内存内容与 `expected` 指向的内存内容进行比较，若它们逐位相等（`true`），则将 `object` 指向的内存内容替换为 `desired`，且内存受到 `success` 的影响；否则（`false`）将 `expected` 指向的内存内容更新为 `object` 指向的内存内容，且内存受到 `failure` 的影响。这些操作是原子读-修改-写操作。
 
`atomic_compare_exchange_strong` 的效果类似于：

```c
if (memcmp(object, expected, sizeof(*object)) == 0)
    memcpy(object, &desired, sizeof(*object));
else
    memcpy(expected, object, sizeof(*object));
```

*weak* 的 `atomic_compare_exchange` 操作可能会虚假地失败。也就是说，即使 `expected` 和 `object` 引用的内存内容相等，它也可能返回零，并且将最初存在的相同内存内容存储回 `expected`。

虚假失败的一个后果是，几乎所有的 *weak* `atomic_compare_exchange` 的使用都将陷入循环。

```c
exp = atomic_load(&cur);
do {
    des = function(exp);
} while (!atomic_compare_exchange_weak(&cur, &exp, des));
```

当 `atomic_compare_exchange` 处于循环中时，*weak* 版本将在某些平台上产生更好的性能。当 *weak* `atomic_compare_exchange` 需要循环而 *strong* `atomic_compare_exchange` 不需要循环时，*strong* `atomic_compare_exchange` 更可取。

>---
#### atomic_fetch

以下操作执行算术和按位计算。所有这些操作都适用于除 `_Atomic bool`，`atomic_bool` 以外的任何原子整数类型的对象，或具有基础类型 `bool` 的枚举的原子版本。*key* 与运算符的关系为：

```c
C atomic_fetch_key(volatile A *object, M operand);
C atomic_fetch_key_explicit(volatile A *object, M operand, memory_order order);
/* key   >>>  op
   add        +     // 原子加法
   sub        -     // 原子减法
   or         |     // 原子按位或
   xor        ^     // 原子按位异或
   and        &     // 原子按位与
*/
```

这些泛型函数以原子方式将 `object` 指向的值替换为应用于 `object` 指向的值和给定操作数 `operand` 的计算结果。内存受到 `order` 值的影响。这些操作是原子读-修改-写操作。对于有符号整数类型，算术对整数溢出执行静默环绕（没有未定义的结果）。对于地址类型，结果可能是未定义的地址，对于其他操作则没有未定义的行为。

函数以原子方式返回操作之前 `object` 先前指向的值。

>---

### 原子标志类型及操作

| Specifier                    | Description                                                                |
| :--------------------------- | :------------------------------------------------------------------------- |
| `atomic_flag`                | 一种结构类型，表示无锁的原始原子标志。`atomic_flag` 不提供加载或存储操作。 |
| `ATOMIC_FLAG_INIT`           | 扩展为 `atomic_flag` 类型对象的初始化设定项。                              |
| `atomic_flag_clear`          | 以原子方式将 `object` 指向的原子标志置于清除状态。                         |
| `atomic_flag_clear_explicit` | `order` 参数不能是 `memory_order_acquire` 或 `memory_order_acq_rel`。      |
`atomic_flag_test_and_set` | 以原子方式将 `object` 指向的原子标志置于设置状态。
|`atomic_flag_test_and_set_explicit`|操作是原子读-修改-写操作，内存受 `order` 值的影响。|

`atomic_flag` 类型提供经典的测试和设置功能，它有两种状态，设置或清除。对类型为 `atomic_flag` 的对象的操作应无锁。宏 `ATOMIC_FLAG_INIT` 可用于将 `atomic_flag` 初始化为清除状态。未使用 `ATOMIC_FLAG_INIT` 显式初始化的 `atomic_flag` 最初具有不确定的表示形式。

```c
atomic_flag guard = ATOMIC_FLAG_INIT;
```

---
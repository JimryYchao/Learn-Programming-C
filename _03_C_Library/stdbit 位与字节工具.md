## C 位与字节工具：stdbit.h

```c
#define __STDC_VERSION_STDBIT_H__           202311L
```

`<stdbit.h>` 定义以下宏、类型和函数，以处理许多类型（通常是整数类型）的字节和位表示形式。头文件提供 `size_t` 类型名称以及实现定义的任何 `uintN_t`、`intN_t`、`uint_leastN_t` 或 `int_leastN_t` 类型名称。

最高有效指数是从 0 开始的索引，从最高有效位 0 到最低有效位 `w − 1` 进行计数，其中 `w` 是计算其最高有效索引的类型的宽度。

最低有效索引是从 0 开始的索引，从最低有效位 0 到最高有效位 `w − 1` 进行计数，其中 `w` 是计算其最低有效索引的类型的宽度。

多字节标量类型中常见的两种字节排序方法是 *little-endian* 和 *big-endian*。*Little-endian* 是一种用于存储或传输二进制数据的格式，其中最低有效字节放在第一位，其余字节按升序排列。或者，最低有效字节存储在最小的内存地址中。*Big-endian* 是一种用于存储或传输二进制数据的格式，其中最高有效字节放在最前面，其余字节按降序排列。或者，最高有效字节存储在最小的内存地址。其他字节排序也是可能的。

---
### Macros

```c
#define __STDC_ENDIAN_LITTLE__          
#define __STDC_ENDIAN_BIG__
#define __STDC_ENDIAN_NATIVE__
```

`__STDC_ENDIAN_LITTLE__` 表示一种字节顺序存储方法，其中最低有效字节放在第一位，其余字节按升序排列，并且是整数常量表达式。

`__STDC_ENDIAN_BIG__` 表示一种字节顺序存储方法，其中最高有效字节放在第一位，其余字节按降序排列，并且是一个整数常量表达式。

`__STDC_ENDIAN_NATIVE__` 它表示执行环境的字节顺序存储方法，是一个整数常量表达式。 `__STDC_ENDIAN_NATIVE__` 描述了执行环境相对于位精确整数类型、标准整数类型和没有填充位的扩展整数类型的字节序。

`__STDC_ENDIAN_NATIVE__` 应扩展为整数常量表达式，如果执行环境是 *little-endian*，则其值等于 `__STDC_ENDIAN_LITTLE__` 的值。否则，如果执行环境是 *big-endian*，则 `__STDC_ENDIAN_NATIVE__` 应扩展为整数常量表达式，其值等于 `__STDC_ENDIAN_BIG__` 的值。 如果执行环境既不是 *little-endian* 也不是 *big-endian*，那么 `__STDC_ENDIAN_NATIVE__` 应扩展为具有其他一些实现定义的字节顺序的宏。

---
### Functions

对于以下的类型泛型函数，根据输入值 `generic_value_type` 的类型返回相应的值，其类型参数的对象 `value` 可以是：
- 标准无符号整数类型，不包括 `bool`；
- 扩展的无符号整数类型；
- 宽度与标准或扩展整数类型匹配的位精确无符号整数类型，不包括 `bool`。

>---

#### stdc_leading_zeros：前导 0 计数

```c
unsigned int stdc_leading_zeros_uc(unsigned char value) [[unsequenced]];
unsigned int stdc_leading_zeros_us(unsigned short value) [[unsequenced]];
unsigned int stdc_leading_zeros_ui(unsigned int value) [[unsequenced]];
unsigned int stdc_leading_zeros_ul(unsigned long int value) [[unsequenced]];
unsigned int
stdc_leading_zeros_ull(unsigned long long int value) [[unsequenced]];
generic_return_type stdc_leading_zeros(generic_value_type value) [[unsequenced]];
```

这些函数返回 `value` 中的连续 0 的位数，从最高有效位开始。 

>---
#### stdc_leading_ones：前导 1 计数

```c
unsigned int stdc_leading_ones_uc(unsigned char value) [[unsequenced]];
unsigned int stdc_leading_ones_us(unsigned short value) [[unsequenced]];
unsigned int stdc_leading_ones_ui(unsigned int value) [[unsequenced]];
unsigned int stdc_leading_ones_ul(unsigned long int value) [[unsequenced]];
unsigned int
stdc_leading_ones_ull(unsigned long long int value) [[unsequenced]];
generic_return_type stdc_leading_ones(generic_value_type value) [[unsequenced]];
```

这些函数返回 `value` 中的连续 1 的位数，从最高有效位开始。 

>---
#### stdc_trailing_zeros：尾随 0 计数

```c
unsigned int stdc_trailing_zeros_uc(unsigned char value) [[unsequenced]];
unsigned int stdc_trailing_zeros_us(unsigned short value) [[unsequenced]];
unsigned int stdc_trailing_zeros_ui(unsigned int value) [[unsequenced]];
unsigned int stdc_trailing_zeros_ul(unsigned long int value) [[unsequenced]];
unsigned int
stdc_trailing_zeros_ull(unsigned long long int value) [[unsequenced]];
generic_return_type stdc_trailing_zeros(generic_value_type value) [[unsequenced]];
```

这些函数返回 `value` 中的连续 0 的位数，从最低有效位开始。 

>---
#### stdc_trailing_ones：尾随 1 计数

```c
unsigned int stdc_trailing_ones_uc(unsigned char value) [[unsequenced]];
unsigned int stdc_trailing_ones_us(unsigned short value) [[unsequenced]];
unsigned int stdc_trailing_ones_ui(unsigned int value) [[unsequenced]];
unsigned int stdc_trailing_ones_ul(unsigned long int value) [[unsequenced]];
unsigned int
stdc_trailing_ones_ull(unsigned long long int value) [[unsequenced]];
generic_return_type stdc_trailing_ones(generic_value_type value) [[unsequenced]];
```

这些函数返回 `value` 中的连续 1 的位数，从最低有效位开始。 

>---
#### stdc_first_leading_zero：首个前导 0 的索引

```c
unsigned int stdc_first_leading_zero_uc(unsigned char value) [[unsequenced]];
unsigned int stdc_first_leading_zero_us(unsigned short value) [[unsequenced]];
unsigned int stdc_first_leading_zero_ui(unsigned int value) [[unsequenced]];
unsigned int stdc_first_leading_zero_ul(unsigned long int value) [[unsequenced]];
unsigned int
stdc_first_leading_zero_ull(unsigned long long int value) [[unsequenced]];
generic_return_type stdc_first_leading_zero(generic_value_type value) [[unsequenced]];
```

函数返回 `value` 中首个前导 0 位的最高有效索引，并加上 1。如果未找到，则此函数返回 0。

>---
#### stdc_first_trailing_zero：首个尾随 0 的索引

```c
unsigned int stdc_first_trailing_zero_uc(unsigned char value) [[unsequenced]];
unsigned int stdc_first_trailing_zero_us(unsigned short value) [[unsequenced]];
unsigned int stdc_first_trailing_zero_ui(unsigned int value) [[unsequenced]];
unsigned int
stdc_first_trailing_zero_ul(unsigned long int value) [[unsequenced]];
unsigned int
stdc_first_trailing_zero_ull(unsigned long long int value) [[unsequenced]];
generic_return_type stdc_first_trailing_zero(generic_value_type value) [[unsequenced]];
```

函数返回 `value` 中首个尾随 0 位的最低有效索引，并加上 1。如果未找到，则此函数返回 0。

>---
#### stdc_first_leading_one：首个前导 1 的索引

```c
unsigned int stdc_first_leading_one_uc(unsigned char value) [[unsequenced]];
unsigned int stdc_first_leading_one_us(unsigned short value) [[unsequenced]];
unsigned int stdc_first_leading_one_ui(unsigned int value) [[unsequenced]];
unsigned int stdc_first_leading_one_ul(unsigned long int value) [[unsequenced]];
unsigned int
stdc_first_leading_one_ull(unsigned long long int value) [[unsequenced]];
generic_return_type stdc_first_leading_one(generic_value_type value) [[unsequenced]];
```

函数返回 `value` 中首个前导 1 位的最高有效索引，并加上 1。如果未找到，则此函数返回 0。

>---
#### stdc_first_trailing_one：首个尾随 1 的索引

```c
unsigned int stdc_first_trailing_one_uc(unsigned char value) [[unsequenced]];
unsigned int stdc_first_trailing_one_us(unsigned short value) [[unsequenced]];
unsigned int stdc_first_trailing_one_ui(unsigned int value) [[unsequenced]];
unsigned int
stdc_first_trailing_one_ul(unsigned long int value) [[unsequenced]];
unsigned int
stdc_first_trailing_one_ull(unsigned long long int value) [[unsequenced]];
generic_return_type stdc_first_trailing_one(generic_value_type value) [[unsequenced]];
```

函数返回 `value` 中首个尾随 1 位的最低有效索引，并加上 1。如果未找到，则此函数返回 0。

>---
#### stdc_count_zeros：0 位计数

```c
unsigned int stdc_count_zeros_uc(unsigned char value) [[unsequenced]];
unsigned int stdc_count_zeros_us(unsigned short value) [[unsequenced]];
unsigned int stdc_count_zeros_ui(unsigned int value) [[unsequenced]];
unsigned int stdc_count_zeros_ul(unsigned long int value) [[unsequenced]];
unsigned int
stdc_count_zeros_ull(unsigned long long int value) [[unsequenced]];
generic_return_type stdc_count_zeros(generic_value_type value) [[unsequenced]];
```

函数返回 `value` 中 0 位的总数。

>---
#### stdc_count_ones：1 位计数

```c
unsigned int stdc_count_ones_uc(unsigned char value) [[unsequenced]];
unsigned int stdc_count_ones_us(unsigned short value) [[unsequenced]];
unsigned int stdc_count_ones_ui(unsigned int value) [[unsequenced]];
unsigned int stdc_count_ones_ul(unsigned long int value) [[unsequenced]];
unsigned int
stdc_count_ones_ull(unsigned long long int value) [[unsequenced]];
generic_return_type stdc_count_ones(generic_value_type value) [[unsequenced]];
```

函数返回 `value` 中 1 位的总数。

>---
#### stdc_has_single_bit：单个 1 位检查

```c
bool stdc_has_single_bit_uc(unsigned char value) [[unsequenced]];
bool stdc_has_single_bit_us(unsigned short value) [[unsequenced]];
bool stdc_has_single_bit_ui(unsigned int value) [[unsequenced]];
bool stdc_has_single_bit_ul(unsigned long int value) [[unsequenced]];
bool stdc_has_single_bit_ull(unsigned long long int value) [[unsequenced]];
bool stdc_has_single_bit(generic_value_type value) [[unsequenced]];
```

函数仅当 `value` 位序列中只有一个 1 位时返回 `true`。

>---
#### stdc_bit_width：存储值的最小位数

```c
unsigned int stdc_bit_width_uc(unsigned char value) [[unsequenced]];
unsigned int stdc_bit_width_us(unsigned short value) [[unsequenced]];
unsigned int stdc_bit_width_ui(unsigned int value) [[unsequenced]];
unsigned int stdc_bit_width_ul(unsigned long int value) [[unsequenced]];
unsigned int
stdc_bit_width_ull(unsigned long long int value) [[unsequenced]];
generic_return_type stdc_bit_width(generic_value_type value) [[unsequenced]];
```

函数计算存储 `value` 所需的最小位数。

>---
#### stdc_bit_floor：不大于值的 2 的最大整数次幂

```c
unsigned char stdc_bit_floor_uc(unsigned char value) [[unsequenced]];
unsigned short stdc_bit_floor_us(unsigned short value) [[unsequenced]];
unsigned int stdc_bit_floor_ui(unsigned int value) [[unsequenced]];
unsigned long int stdc_bit_floor_ul(unsigned long int value) [[unsequenced]];
unsigned long long int
stdc_bit_floor_ull(unsigned long long int value) [[unsequenced]];
generic_value_type stdc_bit_floor(generic_value_type value) [[unsequenced]];
```

函数计算不大于 `value` 的 2 的最大整数次幂。如果 `value` 为 0，则 `stdc_bit_floor` 函数返回 0。否则，它们返回不大于 `value` 的 2 的最大整数次幂。

>---
#### stdc_bit_ceil：不小于值的 2 的最小整数次幂 

```c
unsigned char stdc_bit_ceil_uc(unsigned char value) [[unsequenced]];
unsigned short stdc_bit_ceil_us(unsigned short value) [[unsequenced]];
unsigned int stdc_bit_ceil_ui(unsigned int value) [[unsequenced]];
unsigned long int stdc_bit_ceil_ul(unsigned long int value) [[unsequenced]];
unsigned long long int
stdc_bit_ceil_ull(unsigned long long int value) [[unsequenced]];
generic_value_type stdc_bit_ceil(generic_value_type value) [[unsequenced]];
```

函数计算不小于 `value` 的 2 的最小整数次幂。如果计算不适合给定的返回类型，则 `stdc_bit_ceil` 函数返回 0。

---
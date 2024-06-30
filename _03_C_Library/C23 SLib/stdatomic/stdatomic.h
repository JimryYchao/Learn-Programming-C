#pragma once

#ifndef __STDC_NO_ATOMICS__

#define __STDC_VERSION_STDATOMIC_H__        202311L
#include

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

#define ATOMIC_FLAG_INIT

typedef enum{
    memory_order_relaxed = __ATOMIC_RELAXED,
    memory_order_consume = __ATOMIC_CONSUME,
    memory_order_acquire = __ATOMIC_ACQUIRE,
    memory_order_release = __ATOMIC_RELEASE,
    memory_order_acq_rel = __ATOMIC_ACQ_REL,
    memory_order_seq_cst = __ATOMIC_SEQ_CST
} memory_order;

typedef _Atomic atomic_bool             atomic_bool;
typedef _Atomic char                    atomic_char;
typedef _Atomic signed char             atomic_schar;
typedef _Atomic unsigned char           atomic_uchar;
typedef _Atomic short                   atomic_short;
typedef _Atomic unsigned short          atomic_ushort;
typedef _Atomic int                     atomic_int;
typedef _Atomic unsigned int            atomic_uint;
typedef _Atomic long                    atomic_long;
typedef _Atomic unsigned long           atomic_ulong;
typedef _Atomic long long               atomic_llong;
typedef _Atomic unsigned long long      atomic_ullong;
typedef _Atomic __CHAR8_TYPE__          atomic_char8_t;
typedef _Atomic __CHAR16_TYPE__         atomic_char16_t;
typedef _Atomic __CHAR32_TYPE__         atomic_char32_t;
typedef _Atomic __WCHAR_TYPE__          atomic_wchar_t;
typedef _Atomic __INT_LEAST8_TYPE__     atomic_int_least8_t;
typedef _Atomic __UINT_LEAST8_TYPE__    atomic_uint_least8_t;
typedef _Atomic __INT_LEAST16_TYPE__    atomic_int_least16_t;
typedef _Atomic __UINT_LEAST16_TYPE__   atomic_uint_least16_t;
typedef _Atomic __INT_LEAST32_TYPE__    atomic_int_least32_t;
typedef _Atomic __UINT_LEAST32_TYPE__   atomic_uint_least32_t;
typedef _Atomic __INT_LEAST64_TYPE__    atomic_int_least64_t;
typedef _Atomic __UINT_LEAST64_TYPE__   atomic_uint_least64_t;
typedef _Atomic __INT_FAST8_TYPE__      atomic_int_fast8_t;
typedef _Atomic __UINT_FAST8_TYPE__     atomic_uint_fast8_t;
typedef _Atomic __INT_FAST16_TYPE__     atomic_int_fast16_t;
typedef _Atomic __UINT_FAST16_TYPE__    atomic_uint_fast16_t;
typedef _Atomic __INT_FAST32_TYPE__     atomic_int_fast32_t;
typedef _Atomic __UINT_FAST32_TYPE__    atomic_uint_fast32_t;
typedef _Atomic __INT_FAST64_TYPE__     atomic_int_fast64_t;
typedef _Atomic __UINT_FAST64_TYPE__    atomic_uint_fast64_t;
typedef _Atomic __INTPTR_TYPE__         atomic_intptr_t;
typedef _Atomic __UINTPTR_TYPE__        atomic_uintptr_t;
typedef _Atomic __SIZE_TYPE__           atomic_size_t;
typedef _Atomic __PTRDIFF_TYPE__        atomic_ptrdiff_t;
typedef _Atomic __INTMAX_TYPE__         atomic_intmax_t;
typedef _Atomic __UINTMAX_TYPE__        atomic_uintmax_t; 

void atomic_init(volatile A *obj, C value);
type kill_dependency(type y);
void atomic_thread_fence(memory_order order);
void atomic_signal_fence(memory_order order);
bool atomic_is_lock_free(const volatile A *obj);
void atomic_store(volatile A *object, C desired);
void atomic_store_explicit(volatile A *object, C desired, memory_order order);
C atomic_load(const volatile A *object);
C atomic_load_explicit(const volatile A *object, memory_order order);
C atomic_exchange(volatile A *object, C desired);
C atomic_exchange_explicit(volatile A *object, C desired, memory_order order);
bool atomic_compare_exchange_strong(volatile A *object, C *expected, C desired);
bool atomic_compare_exchange_strong_explicit(volatile A *object, C *expected, C desired, memory_order success, memory_order failure);
bool atomic_compare_exchange_weak(volatile A *object, C *expected, C desired);
bool atomic_compare_exchange_weak_explicit(volatile A *object, C *expected, C desired, memory_order success, memory_order failure);
bool atomic_flag_test_and_set(volatile atomic_flag *object);
bool atomic_flag_test_and_set_explicit(volatile atomic_flag *object, memory_order order);
void atomic_flag_clear(volatile atomic_flag *object);
void atomic_flag_clear_explicit(volatile atomic_flag *object, memory_order order);
C atomic_fetch_add(volatile A *object, M operand);
C atomic_fetch_add_explicit(volatile A *object, M operand, memory_order order);
C atomic_fetch_sub(volatile A *object, M operand);
C atomic_fetch_sub_explicit(volatile A *object, M operand, memory_order order);
C atomic_fetch_or (volatile A *object, M operand);
C atomic_fetch_or _explicit(volatile A *object, M operand, memory_order order);
C atomic_fetch_xor(volatile A *object, M operand);
C atomic_fetch_xor_explicit(volatile A *object, M operand, memory_order order);
C atomic_fetch_and(volatile A *object, M operand);
C atomic_fetch_and_explicit(volatile A *object, M operand, memory_order order);
#endif
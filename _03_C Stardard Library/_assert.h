/*
$id: assert.h
  断言库，在程序中关键的地方进行断言。若为非真，程序将在标准错误流输出一条适当的信
  息，并且使执行异常终止
  <assert.h> 定义了宏 assert 和 static_assert 并引用了 NDEBUG 用于取消断言
*/

#ifdef t_Assert
#undef t_Assert

#undef _assert
#endif

// INCLUDE assert.h
#include <assert.h>

#ifndef t_Assert
#define t_Assert

// REGION: Program Diagnostics
#ifdef NDEBUG
// MACRO: 断言宏
#define m_assert(expr) assert(expr)
#else /* not define NDEBUG */
// MACRO: 断言宏
#define m_assert(expr) assert(expr)
#endif /* End NDEBUG */

#undef m_static_assert
// MACRO: 静态断言宏
#define m_static_assert static_assert
#endif
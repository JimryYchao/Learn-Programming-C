/*
$id: assert.h
  断言库，在程序中关键的地方进行断言。若为非真，程序将在标准错误流输出一条适当的信
  息，并且使执行异常终止
  <assert.h> 定义了宏 assert 和 static_assert 并引用了 NDEBUG 用于取消断言
*/

#include "Lib-Macros.h"

#ifdef t_Assert
#undef t_Assert

#undef _assert
#endif

/* assert.h */
#include PATH_ASSERT_H

#ifndef t_Assert
#define t_Assert

/* Program Diagnostics */
#ifdef NDEBUG
#define _assert(_expr) assert(_expr) /* 断言宏 */
#else /* not define NDEBUG */
#define _assert(_expr) assert(_expr) /* 断言宏 */
#endif /* End NDEBUG */

#undef _static_assert
#define _static_assert static_assert /* 静态断言宏 */
#endif
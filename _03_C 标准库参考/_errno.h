/*
$id: errno.h
  错误号，定义了几个宏，与错误条件的报告有关
*/

#ifndef _Errno
#define _Errno

/* errno.h */
#include <errno.h>

/* macros */
#define _EDOM EDOM	   /* 数学参数在定义域之外 */
#define _EILSEQ EILSEQ /* 非法字节序列 */
#define _ERANGE ERANGE /* 结果超出范围 */
/* 可以指定其他 E 开头的宏定义来扩展错误报告 */
#define ECUSTOM 999

/*
  扩展为可修改的左值 int, 由几个库函数设置为正错误数
  在初始线程中 errno 的值在程序启动时为零，无论是否存在错误，errno 的值均可以被标
  准库函数调用设置为非零
*/
#define _errno errno
/*
   宏 errno 可以扩展为由函数调用产生的可修改的左值(例如，*errno())
   因此，使用 errno 进行错误检查的程序将在库函数调用之前将其设置为 0，然后在后续
   的库函数调用之前检查它。当然，库函数可以在进入时保存 errno 的值，然后将其设置
   为零，只要在返回之前 errno 的值仍然为零，则恢复原始值即可)。
*/

#endif
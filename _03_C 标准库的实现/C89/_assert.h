/*
$id: assert.h
  断言库，在程序中关键的地方进行断言。若为非真，程序将在标准错误流输出一条适当的信
  息，并且使执行异常终止
*/
/* <assert.h> 定义了宏 assert 和引用了 NDEBUG 用于取消断言 */

#undef assert

#ifdef NDEBUG

/* 断言，依赖是否定义宏 NDEBUG，未定义时启用断言，表达式与 0 相等时在标准输出打印诊断信息 */
#define assert(_Expression) ((void)0)
#else
void _Assert(char *);
#define _STR(x) _VAL(x)
#define _VAL(x) #x

/* 断言，依赖是否定义宏 NDEBUG，未定义时启用断言，表达式与 0 相等时在标准输出打印诊断信息 */
#define assert(_Expression) (_Expression) ? (void)0 : _Assert(__FILE__ ":" _STR(__LINE__) " " #_Expression)
#endif
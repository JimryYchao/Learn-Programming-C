/*
$id: ctype.h
  字符处理，声明了可以用于识别和转换字符的函数，参数值可以是 unsigned char，int，
  或者是和宏 EOF 的值相等；这些函数受当前区域设置的影响
*/

#ifndef t_Ctype
#define t_Ctype

/* ctype.h */
#include <ctype.h>
#include <locale.h>

/* Character classification functions */
#define isalnum(C) (isalnum)(C)	  /* 检查一个字符是否是字母或数字 */
#define isalpha(C) (isalpha)(C)	  /* 检查一个字符是否是英文字母 */
#define islower(C) (islower)(C)	  /* 检查一个字符是否是小写字母 */
#define isupper(C) (isupper)(C)	  /* 检查一个字符是否是大写字母 */
#define isdigit(C) (isdigit)(C)	  /* 检查字符是否为数字 */
#define isxdigit(C) (isxdigit)(C) /* 检查一个字符是否是十六进制的字符 */
#define iscntrl(C) (iscntrl)(C)	  /* 检查一个字符是否是控制字符 */
#define isgraph(C) (isgraph)(C)	  /* 检查一个字符是否是可显示的字符 */
#define isspace(C) (isspace)(C)	  /* 检查一个字符是否是空白字符 */
#define isblank(C) (isblank)(C)	  /* 检查一个字符是否是空格字符 */
#define isprint(C) (isprint)(C)	  /* 检查一个字符是否是可打印字符 */
#define ispunct(C) (ispunct)(C)	  /* 检查一个字符是否是一个标点符号 */
#define _isascii(C) (isascii)(C)  /* 检查一个字符是否是 ASCII */

/* Character case mapping functions */
#define tolower(C) (tolower)(C) /* 将大写字母转换为对应的小写字母 */
#define toupper(C) (toupper)(C) /* 将小写字母转换为对应的大写字母 */
#endif
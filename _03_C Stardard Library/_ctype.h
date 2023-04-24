/*
$id: ctype.h
  字符处理，声明了可以用于识别和转换字符的函数，参数值可以是 unsigned char，int，
  或者是和宏 EOF 的值相等；这些函数受当前区域设置的影响
*/

#ifndef t_Ctype
#define t_Ctype

// INCLUDE ctype.h
#include <ctype.h>

// REGION: file Character classification functions

// MACRO: 检查一个字符是否是字母或数字
#define m_isalnum(C) isalnum(C)
// MACRO: 检查一个字符是否是英文字母
#define m_isalpha(C) isalpha(C)
// MACRO: 检查一个字符是否是小写字母
#define m_islower(C) islower(C)
// MACRO: 检查一个字符是否是大写字母
#define m_isupper(C) isupper(C)
// MACRO: 检查字符是否为数字
#define m_isdigit(C) isdigit(C)
// MACRO: 检查一个字符是否是十六进制的字符
#define m_isxdigit(C) isxdigit(C)
// MACRO: 检查一个字符是否是控制字符
#define m_iscntrl(C) iscntrl(C)
// MACRO: 检查一个字符是否是可显示的字符
#define m_isgraph(C) isgraph(C)
// MACRO: 检查一个字符是否是空白字符
#define m_isspace(C) isspace(C)
// MACRO: 检查一个字符是否是空格字符
#define m_isblank(C) isblank(C)
// MACRO: 检查一个字符是否是可打印字符
#define m_isprint(C) isprint(C)
// MACRO: 检查一个字符是否是一个标点符号
#define m_ispunct(C) ispunct(C)
// MACRO: 检查一个字符是否是 ASCII
#define m_isascii(C) isascii(C)

// REGION: Character case mapping functions

// MACRO: 将大写字母转换为对应的小写字母
#define m_tolower(C) tolower(C)
// MACRO: 将小写字母转换为对应的大写字母
#define m_toupper(C) toupper(C)
#endif
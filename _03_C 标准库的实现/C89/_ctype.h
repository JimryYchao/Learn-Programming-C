/*
$id: ctype.h
  字符处理，声明了可以用于识别和转换字符的函数，参数值可以是 unsigned char，int，
  或者是和宏 EOF 的值相等；这些函数受当前区域设置的影响
*/

#ifndef T_CTYPE
#define T_CTYPE

/* code bits */
#define _XA 0x200 /* extra alphabetic */
#define _XS 0x100 /* extra space */

#define _BB 0x80 /* BEL,BS,etc. */
#define _CN 0x40 /* CR,FF,HF,HL,VT */
#define _DI 0x20 /* '0'-'9' */
#define _LO 0x10 /* 'a'-'z' */
#define _PU 0x08 /* punctuation */
#define _SP 0x04 /* space */
#define _UP 0x02 /* 'A'-'Z' */
#define _XD 0x01 /* '0'-'9','A'-F','a'-'f' */

/* declarations */

/* 数字或字母 */
int isalnum(int);
/* 字母字符 */
int isalpha(int);
/* 控制字符 */
int iscntrl(int);
/* 数字字符 */
int isdigit(int);
/* 打印时可显示的字符 */
int isgraph(int);
/* 小写字母 */
int islower(int);
/* 可打印字符 */
int isprint(int);
/* 标点符号 */
int ispunct(int);
/* 空白字符 */
int isspace(int);
/* 大写字母 */
int isupper(int);
/* 十六进制数 */
int isxdigit(int);
/* 大写字母转换成小写字母 */
int tolower(int);
/* 小写字母转换成大写字母 */
int toupper(int);

extern const short *_Ctype, *_Tolower, *_Toupper;

/* macro overrides*/
#define isalnum(c) (_Ctype[(int)(c)] & (_DI | _LO | _UP | _XA))
#define isalpha(c) (_Ctype[(int)(c)] & (_LO | _UP | _XA))
#define iscntrl(c) (_Ctype[(int)(c)] & (_BB | _CN))
#define isdigit(c) (_Ctype[(int)(c)] & (_DI))
#define isgraph(c) (_Ctype[(int)(c)] & (_DI | _LO | _PU | _UP | _XA))
#define islower(c) (_Ctype[(int)(c)] & (_LO))
#define isprint(c) (_Ctype[(int)(c)] & (_DI | _LO | _PU | _SP | _UP | _XA))
#define ispunct(c) (_Ctype[(int)(c)] & (_PU))
#define isspace(c) (_Ctype[(int)(c)] & (_CN | _SP | _XS))
#define isupper(c) (_Ctype[(int)(c)] & (_UP))
#define isxdigit(c) (_Ctype[(int)(c)] & (_XD))

#define tolower(c) _Tolower[(int)(c)]
#define toupper(c) _Toupper[(int)(c)]
#endif
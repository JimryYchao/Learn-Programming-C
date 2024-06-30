#pragma once

#define __STDC_VERSION_STDARG_H__           202311L

typedef char *  va_list;

type va_arg(va_list ap, type);
void va_copy(va_list dest, va_list src);
void va_end(va_list ap);
void va_start(va_list ap, ...);
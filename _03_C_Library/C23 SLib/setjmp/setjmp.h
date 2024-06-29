#pragma once

#define __STDC_VERSION_SETJMP_H__           202311L

typedef _JPTYPE     jmp_buf

int setjmp(jmp_buf env);
[[noreturn]] void longjmp(jmp_buf env, int val);
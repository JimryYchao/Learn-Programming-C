#pragma once
// Compile with /std:c11
#include <stdarg.h>
#include <stdio.h>
#include "Utils.h"

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//	函数可变参数访问
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/* 可变参数访问案例，可变参数列表类型的顺序必须已知（int，double） */
void _Stdarg_VarParams(int preParam, ...)
{
	va_list args, cargs;
	va_start(args, preParam);
	printf("接收到 Int:%d\n", va_arg(args, int));
	va_copy(cargs, args);	// 复制当前状态下的 args
	printf("接收到 Double:%.2f\n", va_arg(args, double));
	va_end(args);
	printf("接收到 Copy Double:%.2f\n", va_arg(cargs, double));
	va_end(cargs);
}
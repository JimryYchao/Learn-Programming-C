#pragma once
#include <ctype.h>

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//	用来确定包含于字符数据中的类型的函数
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#include <stdio.h>
#include <stdbool.h>
/* 字符校验 */
void _Ctype_Character_Detect();
inline static void _detect(const char* funcName, int(*func)(int), int c)
{
	printf_s("[FUNC]:%s >>> %s\n", funcName, func(c) > 0 ? "true" : "false");
}

////==========================================================
void _Ctype_Character_Detect()
{
	char c = 0;
	printf("%s", "Please input character. (input # to exit)\n");
	scanf_s("%c", &c);
	if (c == '#')
		return;
	printf("%s", "start character detect. ");
	_detect("isalnum", isalnum, c);
	_detect("isalpha", isalpha, c);
	_detect("islower", islower, c);
	_detect("isupper", isupper, c);
	_detect("isdigit", isdigit, c);
	_detect("isxdigit", isxdigit, c);
	_detect("iscntrl", iscntrl, c);
	_detect("isgraph", isgraph, c);
	_detect("isspace", isspace, c);
	_detect("isblank", isblank, c);
	_detect("isprint", isprint, c);
	_detect("ispunct", ispunct, c);
}
////==========================================================

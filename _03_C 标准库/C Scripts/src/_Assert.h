#pragma once
#include <assert.h>
#include <stdio.h>

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//	条件编译宏，将参数与零比较
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/* 断言比较：若用户指定的条件为假（0），则异常终止程序。可以在发行版本禁用。 */
void _Assert_assert(int max, int min)
{
	assert(max > min);
}
/* 静态断言比较：编译时断言 */
void _Assert_Static_assert()
{
	static_assert(sizeof(int) == 4, "Int Size is not 4 Bits");
}
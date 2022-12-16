/*
	Test assert()
*/

#include "_assert.h"

int main()
{
	// static_assert(sizeof(int) == 1);

	_assert(sizeof(int) == 4);
	_assert("abc");
	_assert(1 != 1);
}
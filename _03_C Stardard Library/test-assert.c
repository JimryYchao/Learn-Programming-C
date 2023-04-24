/*
	Test assert()
*/

#include "_assert.h"

int main()
{
	// static_assert(sizeof(int) == 1);

	m_assert(sizeof(int) == 4);
	m_assert("abc");

#define NDEBUG
#include "_assert.h"
	m_assert(1 != 1);

#undef NDEBUG
#include "_assert.h"
	m_assert(1 != 1);
}
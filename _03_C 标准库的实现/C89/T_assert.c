/* test assert macro */

#define NDEBUG
#include "X_assert.c"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static int val = 0;
static void field_abort(int signal)
{
	if (val == 1)
	{
		puts("SUCCESS testing <_assert.h>");
		exit(EXIT_SUCCESS);
	}
	else
	{
		puts("FAILURE testing <_assert.h>");
		exit(EXIT_FAILURE);
	}
}
static void dummy()
{
	int i = 0;
	assert(i == 0);
	assert(i == 1);
}

#undef NDEBUG
#include "_assert.h"

int main(void)
{
	assert(signal(SIGABRT, &field_abort) != SIG_ERR);
	dummy();

	assert(val == 0);

	++val;
	fputs("Sample assertion failure message --\n", stderr);
	assert(val == 0);
	puts("FAILURE testing <_assert.h>");

	return (EXIT_FAILURE);
}
/*
正确输出:

Sample assertion failure message --
T_assert.c:43 val == 0 -- Assertion Failed
SUCCESS testing <_assert.h>

*/
/* _assert function */

#include "_assert.h"
#include <stdio.h>
#include <stdlib.h>

void _Assert(char *_message)
{
	/* print assertion message and abort */
	fputs(_message, stderr);
	fputs(" -- Assertion Failed\n", stderr);
	abort();
}
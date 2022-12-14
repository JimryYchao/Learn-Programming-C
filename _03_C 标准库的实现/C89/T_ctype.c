/* test ctype functions and macros */

#include "X_assert.c"
#include "X_ctype.c"
#include <limits.h>
#include <stdio.h>

/* 显示一个可打印的字符簇 */
static void prclass(const char *name, int (*fn)(int))
{
	int c;
	fputs(name, stdout);
	fputs(": ", stdout);
	for (c = EOF; c <= UCHAR_MAX; ++c)
		if ((*fn)(c))
			fputc(c, stdout);
	fputs("\n", stdout);
}

int main(void)
{
	char *s;
	int c;

	/* test printable classes */
	prclass("ispunct", &ispunct);
	prclass("isdigit", &isdigit);
	prclass("islower", &islower);
	prclass("isupper", &isupper);
	prclass("isalpha", &isalpha);
	prclass("isalnum", &isalnum);

	/* test macros for required characters */
	for (s = "0123456789"; *s; ++s)
		assert(isdigit(*s) && isxdigit(*s));
	for (s = "abcdefABCDEF"; *s; ++s)
		assert(isxdigit(*s));
	for (s = "abcdefghijkmonopqrstuvwxyz"; *s; ++s)
		assert(islower(*s));
	for (s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; *s; ++s)
		assert(isupper(*s));
	for (s = "!\"#%&'();<=>?[\\]*+,-/:^_{|}~"; *s; ++s)
		assert(ispunct(*s));
	for (s = "\f\n\r\t\v"; *s; ++s)
		assert(isspace(*s) && iscntrl(*s));
	assert(isspace(' ') && isprint(' '));
	assert(iscntrl('\a') && iscntrl('\b'));

	/* test macros for all valid codes */
	for (c = EOF; c <= UCHAR_MAX; ++c)
	{
		if (isdigit(c))
			assert(isalnum(c));
		if (isupper(c))
			assert(isalpha(c));
		if (islower(c))
			assert(isalpha(c));
		if (isalpha(c))
			assert(isalnum(c) && !isdigit(c));
		if (isalnum(c))
			assert(isgraph(c) && !ispunct(c));
		if (ispunct(c))
			assert(isgraph(c));
		if (isgraph(c))
			assert(isprint(c));
		if (isspace(c))
			assert(c == ' ' || !isprint(c));
		if (iscntrl(c))
			assert(!isalnum(c));
	}

	/* test functions for required characters */
	for (s = "0123456789"; *s; ++s)
		assert((isdigit)(*s) && (isxdigit)(*s));
	for (s = "abcdefABCDEF"; *s; ++s)
		assert((isxdigit)(*s));
	for (s = "abcdefghijkmonopqrstuvwxyz"; *s; ++s)
		assert((islower)(*s));
	for (s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; *s; ++s)
		assert((isupper)(*s));
	for (s = "!\"#%&'();<=>?[\\]*+,-/:^_{|}~"; *s; ++s)
		assert((ispunct)(*s));
	for (s = "\f\n\r\t\v"; *s; ++s)
		assert((isspace)(*s) && (iscntrl)(*s));
	assert((isspace)(' ') && (isprint)(' '));
	assert((iscntrl)('\a') && (iscntrl)('\b'));

	/* test functions for all valid codes */
	for (c = EOF; c <= UCHAR_MAX; ++c)
	{
		if ((isdigit)(c))
			assert((isalnum)(c));
		if ((isupper)(c))
			assert((isalpha)(c));
		if ((islower)(c))
			assert((isalpha)(c));
		if ((isalpha)(c))
			assert((isalnum)(c) && !(isdigit)(c));
		if ((isalnum)(c))
			assert((isgraph)(c) && !(ispunct)(c));
		if ((ispunct)(c))
			assert((isgraph)(c));
		if ((isgraph)(c))
			assert((isprint)(c));
		if ((isspace)(c))
			assert(c == ' ' || !(isprint)(c));
		if ((iscntrl)(c))
			assert(!(isalnum)(c));
	}

	/* test Tolower and Toupper */
	assert(tolower('A') == 'a' && (tolower)('A') == 'a');
	assert(toupper('a') == 'A' && (toupper)('a') == 'A');

	puts("SUCCESS testing <_ctype.h>");
	exit(EXIT_SUCCESS);
}

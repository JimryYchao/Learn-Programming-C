/*
	Test ctype functions
*/

#include "_ctype.h"
#include <stdio.h>
#include <stdlib.h>

#define ISLOWER(c) ('a' <= (c) && (c) <= 'z')
#define TOUPPER(c) (ISLOWER(c) ? 'A' + ((c) - 'a') : (c))
#define XOR(e, f) (((e) && !(f)) || (!(e) && (f)))

inline static void print_char(unsigned char c)
{
	printf("%d/", (int)c);
	if (isgraph(c))
		printf("%c", c);
	else
		printf("\\%.3o", c);
}

/* test */
int main()
{
	unsigned short int c;
	int lose = 0;

#define TRYEM          \
	do                 \
	{                  \
		TRY(isascii);  \
		TRY(isalnum);  \
		TRY(isalpha);  \
		TRY(iscntrl);  \
		TRY(isdigit);  \
		TRY(isgraph);  \
		TRY(islower);  \
		TRY(isprint);  \
		TRY(ispunct);  \
		TRY(isspace);  \
		TRY(isupper);  \
		TRY(isxdigit); \
		TRY(isblank);  \
	} while (0)

	for (c = 0; c <= UCHAR_MAX; ++c)
	{
		print_char(c);

		if (XOR(islower(c), ISLOWER(c)) || toupper(c) != TOUPPER(c))
		{
			fputs(" BOGUS", stdout);
			++lose;
		}

#define TRY(isfoo) \
	if (isfoo(c))  \
	fputs(" " #isfoo, stdout)
		TRYEM;
#undef TRY
		fputs("; lower = ", stdout);
		print_char(tolower(c));
		fputs("; upper = ", stdout);
		print_char(toupper(c));
		putchar('\n');
	}
	fputs("EOF", stdout);
	if (tolower(EOF) != EOF)
	{
		++lose;
		printf(" tolower BOGUS %d;", tolower(EOF));
	}
	if (toupper(EOF) != EOF)
	{
		++lose;
		printf(" toupper BOGUS %d;", toupper(EOF));
	}

#define TRY(isfoo)  \
	if (isfoo(EOF)) \
	fputs(" " #isfoo, stdout), ++lose
	TRYEM;
#undef TRY

	return lose ? EXIT_FAILURE : EXIT_SUCCESS;
}
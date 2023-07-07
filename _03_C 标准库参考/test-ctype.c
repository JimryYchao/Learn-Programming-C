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
	if (m_isgraph(c))
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
		TRY(m_isascii);  \
		TRY(m_isalnum);  \
		TRY(m_isalpha);  \
		TRY(m_iscntrl);  \
		TRY(m_isdigit);  \
		TRY(m_isgraph);  \
		TRY(m_islower);  \
		TRY(m_isprint);  \
		TRY(m_ispunct);  \
		TRY(m_isspace);  \
		TRY(m_isupper);  \
		TRY(m_isxdigit); \
		TRY(m_isblank);  \
	} while (0)

	for (c = 0; c <= UCHAR_MAX; ++c)
	{
		print_char(c);

		if (XOR(m_islower(c), ISLOWER(c)) || m_toupper(c) != TOUPPER(c))
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
		print_char(m_tolower(c));
		fputs("; upper = ", stdout);
		print_char(m_toupper(c));
		putchar('\n');
	}
	fputs("EOF", stdout);
	if (m_tolower(EOF) != EOF)
	{
		++lose;
		printf(" tolower BOGUS %d;", m_tolower(EOF));
	}
	if (m_toupper(EOF) != EOF)
	{
		++lose;
		printf(" toupper BOGUS %d;", m_toupper(EOF));
	}

#define TRY(isfoo)  \
	if (isfoo(EOF)) \
	fputs(" " #isfoo, stdout), ++lose
	TRYEM;
#undef TRY

	return lose ? EXIT_FAILURE : EXIT_SUCCESS;
}
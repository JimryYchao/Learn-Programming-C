#include <ctype.h>
#include <stdio.h>

char ASCII[] = { 'A', 'B', 'a', 'b', '1', '2', ',', '.', ' ', '\r', '\t', '\a', '\\' };

wchar_t UTF8[] = { 'A', 'B', 'a', 'b', '1', '2', ',', '.', ' ', '\r', '\t', '\a', '\\','Œ“', '£¨' };

void test_ctype(void);
void test_ctype(void) {

	int len = sizeof(ASCII) / sizeof(char);

	for (size_t i = 0; i < len; i++)
	{
		char c = ASCII[i];
		if (isalnum(c))
			printf_s("%c is alnum.\n", c);
		if (isalpha(c))
			printf_s("%c is alpha.\n", c);
		if (islower(c))
			printf_s("%c is lower.\n", c);
		if (isupper(c))
			printf_s("%c is upper.\n", c);
		if (isdigit(c))
			printf_s("%c is dight.\n", c);
		if (isxdigit(c))
			printf_s("%c is xdight.\n", c);
		if (iscntrl(c))
			printf_s("%c is cntrl.\n", c);
		if (isgraph(c))
			printf_s("%c is graph.\n", c);
		if (isspace(c))
			printf_s("%c is space.\n", c);
		if (isblank(c))
			printf_s("%c is blank.\n", c);
		if (isprint(c))
			printf_s("%c is print.\n", c);
		if (ispunct(c))
			printf_s("%c is punct.\n", c);

		char c_l = tolower(c);
		printf_s("%c tolower is %c\n", c, c_l);

		char c_u = toupper(c);
		printf_s("%c toupper is %c\n", c, c_u);
	}


	int wlen = sizeof(UTF8) / sizeof(wchar_t);

	for (size_t i = 0; i < wlen; i++)
	{
		wchar_t c = UTF8[i];
		if (iswalnum(c))
			printf_s("%c is walnum.\n", c);
		if (iswalpha(c))
			printf_s("%c is walpha.\n", c);
		if (iswlower(c))
			printf_s("%c is wlower.\n", c);
		if (iswupper(c))
			printf_s("%c is wupper.\n", c);
		if (iswdigit(c))
			printf_s("%c is wdight.\n", c);
		if (iswxdigit(c))
			printf_s("%c is wxdight.\n", c);
		if (iswcntrl(c))
			printf_s("%c is wcntrl.\n", c);
		if (iswgraph(c))
			printf_s("%c is wgraph.\n", c);
		if (iswspace(c))
			printf_s("%c is wspace.\n", c);
		if (iswblank(c))
			printf_s("%c is wblank.\n", c);
		if (iswprint(c))
			printf_s("%c is wprint.\n", c);
		if (iswpunct(c))
			printf_s("%c is wpunct.\n", c);

		char c_l = towlower(c);
		printf_s("%c towlower is %c\n", c, c_l);

		char c_u = towupper(c);
		printf_s("%c towupper is %c\n", c, c_u);
	}
}

int main() {
	test_ctype();
}
#define _CRT_SECURE_NO_WARNINGS 1 // 0
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void demo(wchar_t wc)
{
	printf("State-dependent encoding?   %d\n", wctomb(NULL, wc));
	char mb[512];
	int len = wctomb(mb, wc);
	if (len > 0)
	{
		wprintf(L"wide char '%lc' -> multibyte char '", wc);
		for (int idx = 0; idx < len; ++idx)
			printf("%#2x ", (unsigned char)mb[idx]);
		printf("'\n");
	}
}

int main(void)
{
	setlocale(LC_ALL, "en_US.utf8");
	printf("MB_CUR_MAX = %zu\n", MB_CUR_MAX);
	demo(L'A');
	demo(L'\u00df');
	demo(L'\U0001d10b'); // 过大
}
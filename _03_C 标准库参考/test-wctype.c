#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

int main(void)
{
    wchar_t c = L'\u2002'; // Unicode 字符 'EN SPACE'
    printf("in the default locale, iswprint(%#x) = %d\n", c, !!iswprint(c));
    setlocale(LC_ALL, "en_US.utf8");
    printf("in Unicode locale, iswprint(%#x) = %d\n", c, !!iswprint(c));
    wchar_t c2 = L'\x82'; // 容许的打断
    printf("in Unicode locale, iswprint(%#x) = %d\n", c2, !!iswprint(c2));
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// REGION: file Character classification functions

#define m_isalnum(C) isalnum(C)   // 是否是字母或数字
#define m_isalpha(C) isalpha(C)   // 是否是英文字母
#define m_islower(C) islower(C)   // 是否是小写字母
#define m_isupper(C) isupper(C)   // 是否是大写字母
#define m_isdigit(C) isdigit(C)   // 是否为数字
#define m_isxdigit(C) isxdigit(C) // 是否是十六进制的字符
#define m_iscntrl(C) iscntrl(C)   // 是否是控制字符
#define m_isgraph(C) isgraph(C)   // 是否是可显示的字符
#define m_isspace(C) isspace(C)   // 是否是空白字符
#define m_isblank(C) isblank(C)   // 是否是空格字符
#define m_isprint(C) isprint(C)   // 是否是可打印字符
#define m_ispunct(C) ispunct(C)   // 是否是一个标点符号
#define m_isascii(C) isascii(C)   // 是否是 ASCII 字符

// REGION: Character case mapping functions
#define m_tolower(C) tolower(C) // 将大写字母转换为对应的小写字母
#define m_toupper(C) toupper(C) // 将小写字母转换为对应的大写字母

#define ISLOWER(c) ('a' <= (c) && (c) <= 'z')
#define TOUPPER(c) (ISLOWER(c) ? 'A' + ((c) - 'a') : (c))
#define XOR(e, f) (((e) && !(f)) || (!(e) && (f)))

static void Test_Ctype_functions();
static void Test_Wctype();
inline static void print_char(unsigned char c)
{
    printf("%d/", (int)c);
    if (m_isgraph(c))
        printf("%c", c);
    else
        printf("\\%.3o", c);
}

void Test_Ctype_functions()
{
    unsigned short int c;
    int lose = 0;

#define TRYEM            \
    do                   \
    {                    \
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
}

int main(int argc, char const *argv[])
{
    Test_Ctype_functions();

    Test_Wctype();

    return 0;
}

//---------------------------------------------------
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

void Test_Wctype()
{
    wchar_t c = L'\u2002'; // Unicode 字符 'EN SPACE'
    printf("in the default locale, iswprint(%#x) = %d\n", c, !!iswprint(c));
    setlocale(LC_ALL, "en_US.utf8");
    printf("in Unicode locale, iswprint(%#x) = %d\n", c, !!iswprint(c));
    wchar_t c2 = L'\x82'; // 容许的打断
    printf("in Unicode locale, iswprint(%#x) = %d\n", c2, !!iswprint(c2));
}
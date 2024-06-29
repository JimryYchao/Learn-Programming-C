#include <stdio.h>
#include <locale.h>

static void Setlocale(const char *locale)
{
    char *sl = setlocale(LC_ALL, locale);
    if (sl)
    {
        printf("[%s] set successful >> %s\n", locale, sl);
        printf("         curr_symbol = %s\n", localeconv()->currency_symbol);
        printf("     int_curr_symbol = %s\n\n", localeconv()->int_curr_symbol);
    }
    else
        printf("[%s] set failed >> %s\n\n", locale, sl);
}

void test_setlocale()
{
    // locale-name
    puts("=====  TEST \"locale-name\" =====");
    Setlocale("zh-cn");
    Setlocale("zh-hk");

    // language[_country-region[.code-page]]
    puts("=====  TEST \"language\" =====");
    Setlocale("norwegian");  // language
    Setlocale("english-uk"); // language

    puts("=====  TEST \"language_country-region\" =====");
    Setlocale("chinese_china");  // language_country-region
    Setlocale("american_china"); // language_country-region (不匹配时应用 国家地区 country 设置)

    puts("=====  TEST \".code-page\" =====");
    Setlocale("us");           // language
    Setlocale("us.OCP");       // language.code-page
    Setlocale("us_china.ACP"); // language_country.code-page (不匹配时应用 国家地区 country 设置)
    Setlocale(".OCP");         // .code-page （language 应用本地区域设置）
    Setlocale("Japanese.437"); // language.code-page

    puts("=====  TEST \"C\" =====");
    Setlocale("C"); // 最小环境设置，大写 C

    puts("=====  TEST \"\" =====");
    Setlocale(""); // 应用本地区域设置

    puts("=====  TEST NULL =====");
    Setlocale("us"); // 预先 setlocale
    Setlocale(NULL); // 不修改并返回当前区域设置
}

static void print_locale()
{
#define PR(Format, value) printf("[" #value "] = " #Format "\n", value)
    struct lconv locale = *localeconv();

    puts("");
    PR("%s", locale.decimal_point);
    PR("%s", locale.thousands_sep);
    PR("%u", *locale.grouping);

    PR("%s", locale.mon_decimal_point);
    PR("%s", locale.mon_thousands_sep);
    PR("%u", *locale.mon_grouping);
    PR("%s", locale.positive_sign);
    PR("%s", locale.negative_sign);

    PR("%s", locale.currency_symbol);
    PR("%u", locale.frac_digits);
    PR("%u", locale.p_cs_precedes);
    PR("%u", locale.n_cs_precedes);
    PR("%u", locale.p_sep_by_space);
    PR("%u", locale.n_sep_by_space);
    PR("%u", locale.p_sign_posn);
    PR("%u", locale.n_sign_posn);

    PR("%s", locale.int_curr_symbol);
    PR("%u", locale.int_frac_digits);
}

void test_localeconv()
{
    setlocale(LC_ALL, "Chinese");
    print_locale();

    setlocale(LC_ALL, "USA");
    print_locale();

    setlocale(LC_ALL, "Japanese");
    print_locale();
}

int main()
{
    test_setlocale();

    test_localeconv();
}
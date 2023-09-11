#include <stdio.h>
#include <locale.h>

#define PR(Format, value) printf("[" #value "] = " #Format "\n", value)

void print_locale()
{
    struct lconv locale = *localeconv();

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
int main(void)
{
    // wprintf(L"我是你爸爸");
   _wsetlocale(LC_ALL, L"chinese");
    print_locale();
    wprintf(L"我是你爸爸");
}
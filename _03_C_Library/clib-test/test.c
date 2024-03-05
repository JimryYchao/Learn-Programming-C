// #include <locale.h>
// #include <wctype.h>
// #include <wchar.h>
// #include <stdio.h>

// int main(void)
// {
//     if (setlocale(LC_ALL, "ja_JP"))
//     {
//         const wchar_t kana[] = L"ヒラガナ";
//         size_t sz = sizeof kana / sizeof *kana;
//         wchar_t hira[sz];
//         for (size_t n = 0; n < sz; ++n)
//             hira[n] = towctrans(kana[n], wctrans("tojhira"));
//         printf("katakana characters %ls are %ls in hiragana\n", kana, hira);
//     }
// }

#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <wchar.h>
 
int main(void)
{
    // C 本地环境将为启用 UTF-8 的英文；
    // 小数点将为德文
    // 日期和时间格式将为日文
    auto rt = _wsetlocale(LC_ALL, L"");
    setlocale(LC_NUMERIC, "de_DE.utf8");
    setlocale(LC_TIME, "ja_JP.utf8");
 
    wchar_t str[100];
    time_t t = time(NULL);
    wcsftime(str, 100, L"%A %c", localtime(&t));
    wprintf(L"Number: %.2f\nDate: %ls\n", 3.14, str);
}
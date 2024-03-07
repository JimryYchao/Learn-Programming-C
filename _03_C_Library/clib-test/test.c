#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <wchar.h>
#include <math.h>

#include <float.h>


#ifdef __STDC_WANT_IEC_60559_DFP__
#if (DEC_EVAL_METHOD == 0)
typedef _Decimal32_t _Decimal32;
typedef _Decimal64_t _Decimal64;
#elif (DEC_EVAL_METHOD == 1)
typedef _Decimal32_t _Decimal64;
typedef _Decimal64_t _Decimal64;
#elif (DEC_EVAL_METHOD == 2)
typedef _Decimal32_t _Decimal128;
typedef _Decimal64_t _Decimal128;
#else 
// 其他值则是实现定义的 
#endif
#endif
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
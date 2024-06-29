#include <stdio.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>

void test_IntFormatOutput()
{
#define printInt(format, number) printf(#number "[" #format "] = %" format "\n", number)
    // 有符号整数输出
    puts("Signed Integers >>> ");
    printInt(PRId8, 12345);
    printInt(PRId16, -12345);
    printInt(PRId32, 12345);
    printInt(PRId64, -12345678987654321LL);

    printInt(PRIi8, 12345);
    printInt(PRIi32, -12345);

    printInt(PRIdLEAST32, 12345);
    printInt(PRIdFAST32, -12345);

    // 无符号整数输出
    puts("\nUnsigned Integers >>> ");
    printInt(PRIo32, 98765);
    printInt(PRIu32, 98765);
    printInt(PRIx32, 98765);
    printInt(PRIX32, 98765);

    printInt(PRIoLEAST32, 98765);
    printInt(PRIoFAST32, 98765);
}

void test_imaxdiv()
{
    intmax_t numer = 9876543210;
    intmax_t denom = 1234567890;
    imaxdiv_t rt = imaxdiv(numer, denom);

    printf("%" PRIiMAX " / "
           "%" PRIiMAX " = "
           "%" PRIiMAX " ... "
           "%" PRIiMAX,
           numer, denom, rt.quot, rt.rem);
}

void test_strtoimax()
{
#define STRTOIMAX(str, endptr, base) printf("[" #str "] to Int_max = %lld\n", strtoimax(str, endptr, base))
    char *endptr;

    STRTOIMAX(" -123junk", &endptr, 10); /* base 10                    */
    STRTOIMAX("11111111", &endptr, 2);   /* base 2                     */
    STRTOIMAX("XyZ", &endptr, 36);       /* base 36                    */
    STRTOIMAX("010", &endptr, 0);        /* octal auto-detection       */
    STRTOIMAX("10", &endptr, 0);         /* decimal auto-detection     */
    STRTOIMAX("0x10", &endptr, 0);       /* hexadecimal auto-detection */

    /* range error                */
    /* INT64_MAX + 1 --> LONG_MAX */
    // INT64_MAX = 9223372036854775807LL6
    errno = 0;
    puts("\nOut-of-Range test:");
    STRTOIMAX("9223372036854775808", &endptr, 10);
    printf("errno = %s\n", strerror(errno));
}

void main()
{
    test_IntFormatOutput();

    test_imaxdiv();

    test_strtoimax();
}
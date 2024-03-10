#pragma once

#define __STDC_VERSION_STDLIB_H__       202311L

typedef __size_t    size_t;
typedef __wchar_t   wchar_t;
typedef __div_t     div_t;
typedef __ldiv_t    ldiv_t;
typedef __lldiv_t   lldiv_t;
typedef __once_flag once_flag;

#define EXIT_FAILURE
#define EXIT_SUCCESS
#define MB_CUR_MAX
#define NULL
#define ONCE_FLAG_INIT
#define RAND_MAX

void call_once(once_flag *flag, void (*func)(void));
double atof(const char *nptr);
int atoi(const char *nptr);
long int atol(const char *nptr);
long long int atoll(const char *nptr);
int strfromd(char * restrict s, size_t n, const char * restrict format, double fp);
int strfromf(char * restrict s, size_t n, const char * restrict format, float fp);
int strfroml(char * restrict s, size_t n, const char * restrict format, long double fp);
double strtod(const char * restrict nptr, char ** restrict endptr);
float strtof(const char * restrict nptr, char ** restrict endptr);
long double strtold(const char * restrict nptr, char ** restrict endptr);
long int strtol(const char * restrict nptr, char ** restrict endptr, int base);
long long int strtoll(const char * restrict nptr, char ** restrict endptr, int base);
unsigned long int strtoul(const char * restrict nptr, char ** restrict endptr, int base);
unsigned long long int strtoull(const char * restrict nptr, char ** restrict endptr, int base);
int rand(void);
void srand(unsigned int seed);
void *aligned_alloc(size_t alignment, size_t size);
void *calloc(size_t nmemb, size_t size);
void free(void *ptr);
void free_sized(void *ptr, size_t size);
void free_aligned_sized(void *ptr, size_t alignment, size_t size);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
[[noreturn]] void abort(void);
int atexit(void (*func)(void));
int at_quick_exit(void (*func)(void));
[[noreturn]] void exit(int status);
[[noreturn]] void _Exit(int status);
char *getenv(const char *name);
[[noreturn]] void quick_exit(int status);
int system(const char *string);
QVoid *bsearch(const void *key, QVoid *base, size_t nmemb, size_t size,
int (*compar)(const void *, const void *));
void qsort(void *base, size_t nmemb, size_t size,
int (*compar)(const void *, const void *));
int abs(int j);
long int labs(long int j);
long long int llabs(long long int j);
div_t div(int numer, int denom);
ldiv_t ldiv(long int numer, long int denom);
lldiv_t lldiv(long long int numer, long long int denom);
int mblen(const char *s, size_t n);
int mbtowc(wchar_t * restrict pwc, const char * restrict s, size_t n);
int wctomb(char *s, wchar_t wc);
size_t mbstowcs(wchar_t * restrict pwcs, const char * restrict s, size_t n);
size_t wcstombs(char * restrict s, const wchar_t * restrict pwcs, size_t n);
size_t memalignment(const void *p);

#ifdef __STDC_IEC_60559_DFP__
int strfromd32(char * restrict s, size_t n, const char * restrict format, _Decimal32 fp);
int strfromd64(char * restrict s, size_t n, const char * restrict format, _Decimal64 fp);
int strfromd128(char * restrict s, size_t n, const char * restrict format, _Decimal128 fp);
_Decimal32 strtod32(const char * restrict nptr, char ** restrict endptr);
_Decimal64 strtod64(const char * restrict nptr, char ** restrict endptr);
_Decimal128 strtod128(const char * restrict nptr, char ** restrict endptr);
#endif

#define __STDC_LIB_EXT1__
#ifdef (__STDC_LIB_EXT1__ && __STDC_WANT_LIB_EXT1__)
typedef int     errno_t;
typedef size_t  rsize_t;
typedef int     constraint_handler_t;

constraint_handler_t set_constraint_handler_s(constraint_handler_t handler);
void abort_handler_s(const char * restrict msg, void * restrict ptr, errno_t error);
void ignore_handler_s(const char * restrict msg, void * restrict ptr, errno_t error);
errno_t getenv_s(size_t * restrict len, char * restrict value, rsize_t maxsize, const char * restrict name);
QVoid *bsearch_s(const void *key, QVoid *base, rsize_t nmemb, rsize_t size, int (*compar)(const void *k, const void *y, void *context), void *context);
errno_t qsort_s(void *base, rsize_t nmemb, rsize_t size, int (*compar)(const void *x, const void *y, void *context), void *context);
errno_t wctomb_s(int * restrict status, char * restrict s, rsize_t smax, wchar_t wc);
errno_t mbstowcs_s(size_t * restrict retval, wchar_t * restrict dst, rsize_t dstmax, const char * restrict src, rsize_t len);
errno_t wcstombs_s(size_t * restrict retval, char * restrict dst, rsize_t dstmax, const wchar_t * restrict src, rsize_t len);
#endif
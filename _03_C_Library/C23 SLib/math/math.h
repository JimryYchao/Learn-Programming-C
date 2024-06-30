#pragma once

#define __STDC_VERSION_MATH_H__         202311L

typedef float           float_t;        // at least
typedef double          double_t;       // at least

// pre-define
#include <float.h>
typedef __Decimal32__       _Decimal32;
typedef __Decimal64__       _Decimal64;
typedef __Decimal128__      _Decimal128;
// pre-define-end

#define HUGE_VAL
#define HUGE_VALF
#define HUGE_VALL

#define INFINITY
#define NAN

#define FP_INFINITE
#define FP_NAN
#define FP_NORMAL
#define FP_SUBNORMAL
#define FP_ZERO

#define FP_INT_UPWARD
#define FP_INT_DOWNWARD
#define FP_INT_TOWARDZERO
#define FP_INT_TONEARESTFROMZERO
#define FP_INT_TONEAREST

#define FP_FAST_FMA
#define FP_FAST_FMAF
#define FP_FAST_FMAL

#define FP_FAST_FADD
#define FP_FAST_FADDL
#define FP_FAST_DADDL

#define FP_FAST_FSUB
#define FP_FAST_FSUBL
#define FP_FAST_DSUBL

#define FP_FAST_FMUL
#define FP_FAST_FMULL
#define FP_FAST_DMULL

#define FP_FAST_FDIV
#define FP_FAST_FDIVL
#define FP_FAST_DDIVL

#define FP_FAST_FSQRT
#define FP_FAST_FSQRTL
#define FP_FAST_DSQRTL

#define FP_FAST_FFMA
#define FP_FAST_FFMAL
#define FP_FAST_DFMAL

#define FP_ILOGB0
#define FP_ILOGBNAN

#define FP_LLOGB0
#define FP_LLOGBNAN

#define MATH_ERRNO                  1
#define MATH_ERREXCEPT              2
#define math_errhandling            (MATH_ERRNO | MATH_ERREXCEPT)

#pragma STDC FP_CONTRACT on-off-switch
int fpclassify(real_floating x);
int signbit(real_floating x);
int iscanonical(real_floating x);
int isfinite(real_floating x);
int isinf(real_floating x);
int isnan(real_floating x);
int isnormal(real_floating x);
int issubnormal(real_floating x);
int issignaling(real_floating x);
int iszero(real_floating x);

int isgreater(real_floating x, real_floating y);
int isgreaterequal(real_floating x, real_floating y);
int isless(real_floating x, real_floating y);
int islessequal(real_floating x, real_floating y);
int islessgreater(real_floating x, real_floating y);
int isunordered(real_floating x, real_floating y);
int iseqsig(real_floating x, real_floating y);

double acos(double x);
double asin(double x);
double atan(double x);
double atan2(double y, double x);
double cos(double x);
double sin(double x);
double tan(double x);
double acospi(double x);
double asinpi(double x);
double atanpi(double x);
double atan2pi(double y, double x);
double cospi(double x);
double sinpi(double x);
double tanpi(double x);
double acosh(double x);
double asinh(double x);
double atanh(double x);
double cosh(double x);
double sinh(double x);
double tanh(double x);
double exp(double x);
double exp10(double x);
double exp10m1(double x);
double exp2(double x);
double exp2m1(double x);
double expm1(double x);
double frexp(double value, int *p);
int ilogb(double x);
double ldexp(double x, int p);
long int llogb(double x);
double log(double x);
double log10(double x);
double log10p1(double x);
double log1p(double x);
double logp1(double x);
double log2(double x);
double log2p1(double x);
double logb(double x);
double modf(double value, double *iptr);
double scalbn(double x, int n);
double scalbln(double x, long int n);
double cbrt(double x);
double compoundn(double x, long long int n);
double fabs(double x);
double hypot(double x, double y);
double pow(double x, double y);
double pown(double x, long long int n);
double powr(double y, double x);
double rootn(double x, long long int n);
double rsqrt(double x);
double sqrt(double x);
double erf(double x);
double erfc(double x);
double lgamma(double x);
double tgamma(double x);
double ceil(double x);
double floor(double x);
double nearbyint(double x);
double rint(double x);
long int lrint(double x);
long long int llrint(double x);
double round(double x);
long int lround(double x);
long long int llround(double x);
double roundeven(double x);
double trunc(double x);
double fromfp(double x, int rnd, unsigned int width);
double ufromfp(double x, int rnd, unsigned int width);
double fromfpx(double x, int rnd, unsigned int width);
double ufromfpx(double x, int rnd, unsigned int width);
double fmod(double x, double y);
double remainder(double x, double y);
double remquo(double x, double y, int *quo);
double copysign(double x, double y);
double nan(const char *tagp);
double nextafter(double x, double y);
double nexttoward(double x, long double y);
double nextup(double x);
double nextdown(double x);
int canonicalize(double *cx, const double *x);
double fdim(double x, double y);
double fmax(double x, double y);
double fmin(double x, double y);
double fmaximum(double x, double y);
double fminimum(double x, double y);
double fmaximum_mag(double x, double y);
double fminimum_mag(double x, double y);
double fmaximum_num(double x, double y);
double fminimum_num(double x, double y);
double fmaximum_mag_num(double x, double y);
double fminimum_mag_num(double x, double y);
double fma(double x, double y, double z);
float fadd(double x, double y);
float fsub(double x, double y);
float fmul(double x, double y);
float fdiv(double x, double y);
float ffma(double x, double y, double z);
float fsqrt(double x);


float acosf(float x);
float asinf(float x);
float atanf(float x);
float atan2f(float y, float x);
float cosf(float x);
float sinf(float x);
float tanf(float x);
float acospif(float x);
float asinpif(float x);
float atanpif(float x);
float atan2pif(float y, float x);
float cospif(float x);
float sinpif(float x);
float tanpif(float x);
float acoshf(float x);
float asinhf(float x);
float atanhf(float x);
float coshf(float x);
float sinhf(float x);
float tanhf(float x);
float expf(float x);
float exp10f(float x);
float exp10m1f(float x);
float exp2f(float x);
float exp2m1f(float x);
float expm1f(float x);
float frexpf(float value, int *p);
int ilogbf(float x);
float ldexpf(float x, int p);
long int llogbf(float x);
float logf(float x);
float log10f(float x);
float log10p1f(float x);
float log1pf(float x);
float logp1f(float x);
float log2f(float x);
float log2p1f(float x);
float logbf(float x);
float modff(float value, float *iptr);
float scalbnf(float x, int n);
float scalblnf(float x, long int n);
float cbrtf(float x);
float compoundnf(float x, long long int n);
float fabsf(float x);
float hypotf(float x, float y);
float powf(float x, float y);
float pownf(float x, long long int n);
float powrf(float y, float x);
float rootnf(float x, long long int n);
float rsqrtf(float x);
float sqrtf(float x);
float erff(float x);
float erfcf(float x);
float lgammaf(float x);
float tgammaf(float x);
float ceilf(float x);
float floorf(float x);
float nearbyintf(float x);
float rintf(float x);
long int lrintf(float x);
long long int llrintf(float x);
float roundf(float x);
long int lroundf(float x);
long long int llroundf(float x);
float roundevenf(float x);
float truncf(float x);
float fromfpf(float x, int rnd, unsigned int width);
float ufromfpf(float x, int rnd, unsigned int width);
float fromfpxf(float x, int rnd, unsigned int width);
float ufromfpxf(float x, int rnd, unsigned int width);
float fmodf(float x, float y);
float remainderf(float x, float y);
float remquof(float x, float y, int *quo);
float copysignf(float x, float y);
float nanf(const char *tagp);
float nextafterf(float x, float y);
float nexttowardf(float x, long double y);
float nextupf(float x);
float nextdownf(float x);
int canonicalizef(float *cx, const float *x);
float fdimf(float x, float y);
float fmaxf(float x, float y);
float fminf(float x, float y);
float fmaximumf(float x, float y);
float fminimumf(float x, float y);
float fmaximum_magf(float x, float y);
float fminimum_magf(float x, float y);
float fmaximum_numf(float x, float y);
float fminimum_numf(float x, float y);
float fmaximum_mag_numf(float x, float y);
float fminimum_mag_numf(float x, float y);
float fmaf(float x, float y, float z);
float faddl(long double x, long double y);
float fsubl(long double x, long double y);
float fmull(long double x, long double y);
float fdivl(long double x, long double y);
float ffmal(long double x, long double y, long double z);
float fsqrtl(long double x);

long double acosl(long double x);
long double asinl(long double x);
long double atanl(long double x);
long double atan2l(long double y, long double x);
long double cosl(long double x);
long double sinl(long double x);
long double tanl(long double x);
long double acospil(long double x);
long double asinpil(long double x);
long double atanpil(long double x);
long double atan2pil(long double y, long double x);
long double cospil(long double x);
long double sinpil(long double x);
long double tanpil(long double x);
long double acoshl(long double x);
long double asinhl(long double x);
long double atanhl(long double x);
long double coshl(long double x);
long double sinhl(long double x);
long double tanhl(long double x);
long double expl(long double x);
long double exp10l(long double x);
long double exp10m1l(long double x);
long double exp2l(long double x);
long double exp2m1l(long double x);
long double expm1l(long double x);
long double frexpl(long double value, int *p);
int ilogbl(long double x);
long double ldexpl(long double x, int p);
long int llogbl(long double x);
long double logl(long double x);
long double log10l(long double x);
long double log10p1l(long double x);
long double log1pl(long double x);
long double logp1l(long double x);
long double log2l(long double x);
long double log2p1l(long double x);
long double logbl(long double x);
long double modfl(long double value, long double *iptr);
long double scalbnl(long double x, int n);
long double scalblnl(long double x, long int n);
long double cbrtl(long double x);
long double compoundnl(long double x, long long int n);
long double fabsl(long double x);
long double hypotl(long double x, long double y);
long double powl(long double x, long double y);
long double pownl(long double x, long long int n);
long double powrl(long double y, long double x);
long double rootnl(long double x, long long int n);
long double rsqrtl(long double x);
long double sqrtl(long double x);
long double erfl(long double x);
long double erfcl(long double x);
long double lgammal(long double x);
long double tgammal(long double x);
long double ceill(long double x);
long double floorl(long double x);
long double nearbyintl(long double x);
long double rintl(long double x);
long int lrintl(long double x);
long long int llrintl(long double x);
long double roundl(long double x);
long int lroundl(long double x);
long long int llroundl(long double x);
long double roundevenl(long double x);
long double truncl(long double x);
long double fromfpl(long double x, int rnd, unsigned int width);
long double ufromfpl(long double x, int rnd, unsigned int width);
long double fromfpxl(long double x, int rnd, unsigned int width);
long double ufromfpxl(long double x, int rnd, unsigned int width);
long double fmodl(long double x, long double y);
long double remainderl(long double x, long double y);
long double remquol(long double x, long double y, int *quo);
long double copysignl(long double x, long double y);
long double nanl(const char *tagp);
long double nextafterl(long double x, long double y);
long double nexttowardl(long double x, long double y);
long double nextupl(long double x);
long double nextdownl(long double x);
int canonicalizel(long double *cx, const long double *x);
long double fdiml(long double x, long double y);
long double fmaxl(long double x, long double y);
long double fminl(long double x, long double y);
long double fmaximuml(long double x, long double y);
long double fminimuml(long double x, long double y);
long double fmaximum_magl(long double x, long double y);
long double fminimum_magl(long double x, long double y);
long double fmaximum_numl(long double x, long double y);
long double fminimum_numl(long double x, long double y);
long double fmaximum_mag_numl(long double x, long double y);
long double fminimum_mag_numl(long double x, long double y);
long double fmal(long double x, long double y, long double z);
double daddl(long double x, long double y);
double dsubl(long double x, long double y);
double dmull(long double x, long double y);
double ddivl(long double x, long double y);
double dfmal(long double x, long double y, long double z);
double dsqrtl(long double x);

#ifdef __STDC_IEC_60559_DFP__
#ifdef __STDC_WANT_IEC_60559_EXT__
typedef _Decimal32          _Decimal32_t 
typedef _Decimal64          _Decimal64_t     
#define HUGE_VAL_D32
#define HUGE_VAL_D64
#define HUGE_VAL_D128
#endif

#define DEC_INFINITY
#define DEC_NAN

#define FP_FAST_FMAD32
#define FP_FAST_FMAD64
#define FP_FAST_FMAD128

#define FP_FAST_D32ADDD64
#define FP_FAST_D32ADDD128
#define FP_FAST_D64ADDD128

#define FP_FAST_D32SUBD64
#define FP_FAST_D32SUBD128
#define FP_FAST_D64SUBD128

#define FP_FAST_D32MULD64
#define FP_FAST_D32MULD128
#define FP_FAST_D64MULD128

#define FP_FAST_D32DIVD64
#define FP_FAST_D32DIVD128
#define FP_FAST_D64DIVD128

#define FP_FAST_D32FMAD64
#define FP_FAST_D32FMAD128
#define FP_FAST_D64FMAD128

#define FP_FAST_D32SQRTD64
#define FP_FAST_D32SQRTD128
#define FP_FAST_D64SQRTD128

_Decimal32 acosd32(_Decimal32 x);
_Decimal32 asind32(_Decimal32 x);
_Decimal32 atand32(_Decimal32 x);
_Decimal32 atan2d32(_Decimal32 y, _Decimal32 x);
_Decimal32 cosd32(_Decimal32 x);
_Decimal32 sind32(_Decimal32 x);
_Decimal32 tand32(_Decimal32 x);
_Decimal32 acospid32(_Decimal32 x);
_Decimal32 asinpid32(_Decimal32 x);
_Decimal32 atanpid32(_Decimal32 x);
_Decimal32 atan2pid32(_Decimal32 y, _Decimal32 x);
_Decimal32 cospid32(_Decimal32 x);
_Decimal32 sinpid32(_Decimal32 x);
_Decimal32 tanpid32(_Decimal32 x);
_Decimal32 acoshd32(_Decimal32 x);
_Decimal32 asinhd32(_Decimal32 x);
_Decimal32 atanhd32(_Decimal32 x);
_Decimal32 coshd32(_Decimal32 x);
_Decimal32 sinhd32(_Decimal32 x);
_Decimal32 tanhd32(_Decimal32 x);
_Decimal32 expd32(_Decimal32 x);
_Decimal32 exp10d32(_Decimal32 x);
_Decimal32 exp10m1d32(_Decimal32 x);
_Decimal32 exp2d32(_Decimal32 x);
_Decimal32 exp2m1d32(_Decimal32 x);
_Decimal32 expm1d32(_Decimal32 x);
_Decimal32 frexpd32(_Decimal32 value, int *p);
int ilogbd32(_Decimal32 x);
_Decimal32 ldexpd32(_Decimal32 x, int p);
long int llogbd32(_Decimal32 x);
_Decimal32 logd32(_Decimal32 x);
_Decimal32 log10d32(_Decimal32 x);
_Decimal32 log10p1d32(_Decimal32 x);
_Decimal32 log1pd32(_Decimal32 x);
_Decimal32 logp1d32(_Decimal32 x);
_Decimal32 log2d32(_Decimal32 x);
_Decimal32 log2p1d32(_Decimal32 x);
_Decimal32 logbd32(_Decimal32 x);
_Decimal32 modfd32(_Decimal32 x, _Decimal32 *iptr);
_Decimal32 scalbnd32(_Decimal32 x, int n);
_Decimal32 scalblnd32(_Decimal32 x, long int n);
_Decimal32 cbrtd32(_Decimal32 x);
_Decimal32 compoundnd32(_Decimal32 x, long long int n);
_Decimal32 fabsd32(_Decimal32 x);
_Decimal32 hypotd32(_Decimal32 x, _Decimal32 y);
_Decimal32 powd32(_Decimal32 x, _Decimal32 y);
_Decimal32 pownd32(_Decimal32 x, long long int n);
_Decimal32 powrd32(_Decimal32 y, _Decimal32 x);
_Decimal32 rootnd32(_Decimal32 x, long long int n);
_Decimal32 rsqrtd32(_Decimal32 x);
_Decimal32 sqrtd32(_Decimal32 x);
_Decimal32 erfd32(_Decimal32 x);
_Decimal32 erfcd32(_Decimal32 x);
_Decimal32 lgammad32(_Decimal32 x);
_Decimal32 tgammad32(_Decimal32 x);
_Decimal32 ceild32(_Decimal32 x);
_Decimal32 floord32(_Decimal32 x);
_Decimal32 nearbyintd32(_Decimal32 x);
_Decimal32 rintd32(_Decimal32 x);
long int lrintd32(_Decimal32 x);
long long int llrintd32(_Decimal32 x);
_Decimal32 roundd32(_Decimal32 x);
long int lroundd32(_Decimal32 x);
long long int llroundd32(_Decimal32 x);
_Decimal32 roundevend32(_Decimal32 x);
_Decimal32 truncd32(_Decimal32 x);
_Decimal32 fromfpd32(_Decimal32 x, int rnd, unsigned int width);
_Decimal32 ufromfpd32(_Decimal32 x, int rnd, unsigned int width);
_Decimal32 fromfpxd32(_Decimal32 x, int rnd, unsigned int width);
_Decimal32 ufromfpxd32(_Decimal32 x, int rnd, unsigned int width);
_Decimal32 fmodd32(_Decimal32 x, _Decimal32 y);
_Decimal32 remainderd32(_Decimal32 x, _Decimal32 y);
_Decimal32 copysignd32(_Decimal32 x, _Decimal32 y);
_Decimal32 nand32(const char *tagp);
_Decimal32 nextafterd32(_Decimal32 x, _Decimal32 y);
_Decimal32 nexttowardd32(_Decimal32 x, _Decimal128 y);
_Decimal32 nextupd32(_Decimal32 x);
_Decimal32 nextdownd32(_Decimal32 x);
int canonicalized32(_Decimal32 *cx, const _Decimal32 *x);
_Decimal32 fdimd32(_Decimal32 x, _Decimal32 y);
_Decimal32 fmaxd32(_Decimal32 x, _Decimal32 y);
_Decimal32 fmind32(_Decimal32 x, _Decimal32 y);
_Decimal32 fmaximumd32(_Decimal32 x, _Decimal32 y);
_Decimal32 fminimumd32(_Decimal32 x, _Decimal32 y);
_Decimal32 fmaximum_magd32(_Decimal32 x, _Decimal32 y);
_Decimal32 fminimum_magd32(_Decimal32 x, _Decimal32 y);
_Decimal32 fmaximum_numd32(_Decimal32 x, _Decimal32 y);
_Decimal32 fminimum_numd32(_Decimal32 x, _Decimal32 y);
_Decimal32 fmaximum_mag_numd32(_Decimal32 x, _Decimal32 y);
_Decimal32 fminimum_mag_numd32(_Decimal32 x, _Decimal32 y);
_Decimal32 fmad32(_Decimal32 x, _Decimal32 y, _Decimal32 z);
_Decimal32 d32addd64(_Decimal64 x, _Decimal64 y);
_Decimal32 d32subd64(_Decimal64 x, _Decimal64 y);
_Decimal32 d32muld64(_Decimal64 x, _Decimal64 y);
_Decimal32 d32divd64(_Decimal64 x, _Decimal64 y);
_Decimal32 d32fmad64(_Decimal64 x, _Decimal64 y, _Decimal64 z);
_Decimal32 d32sqrtd64(_Decimal64 x);
_Decimal32 quantized32(_Decimal32 x, _Decimal32 y);
bool samequantumd32(_Decimal32 x, _Decimal32 y);
_Decimal32 quantumd32(_Decimal32 x);
long long int llquantexpd32(_Decimal32 x);
void encodedecd32(unsigned char encptr[restrict static 4], const _Decimal32 * restrict xptr);
void decodedecd32(_Decimal32 * restrict xptr, const unsigned char encptr[restrict static 4]);
void encodebind32(unsigned char encptr[restrict static 4], const _Decimal32 * restrict xptr);
void decodebind32(_Decimal32 * restrict xptr, const unsigned char encptr[restrict static 4]);

_Decimal64 acosd64(_Decimal64 x);
_Decimal64 asind64(_Decimal64 x);
_Decimal64 atand64(_Decimal64 x);
_Decimal64 atan2d64(_Decimal64 y, _Decimal64 x);
_Decimal64 cosd64(_Decimal64 x);
_Decimal64 sind64(_Decimal64 x);
_Decimal64 tand64(_Decimal64 x);
_Decimal64 acospid64(_Decimal64 x);
_Decimal64 asinpid64(_Decimal64 x);
_Decimal64 atanpid64(_Decimal64 x);
_Decimal64 atan2pid64(_Decimal64 y, _Decimal64 x);
_Decimal64 cospid64(_Decimal64 x);
_Decimal64 sinpid64(_Decimal64 x);
_Decimal64 tanpid64(_Decimal64 x);
_Decimal64 acoshd64(_Decimal64 x);
_Decimal64 asinhd64(_Decimal64 x);
_Decimal64 atanhd64(_Decimal64 x);
_Decimal64 coshd64(_Decimal64 x);
_Decimal64 sinhd64(_Decimal64 x);
_Decimal64 tanhd64(_Decimal64 x);
_Decimal64 expd64(_Decimal64 x);
_Decimal64 exp10d64(_Decimal64 x);
_Decimal64 exp10m1d64(_Decimal64 x);
_Decimal64 exp2d64(_Decimal64 x);
_Decimal64 exp2m1d64(_Decimal64 x);
_Decimal64 expm1d64(_Decimal64 x);
_Decimal64 frexpd64(_Decimal64 value, int *p);
int ilogbd64(_Decimal64 x);
_Decimal64 ldexpd64(_Decimal64 x, int p);
long int llogbd64(_Decimal64 x);
_Decimal64 logd64(_Decimal64 x);
_Decimal64 log10d64(_Decimal64 x);
_Decimal64 log10p1d64(_Decimal64 x);
_Decimal64 log1pd64(_Decimal64 x);
_Decimal64 logp1d64(_Decimal64 x);
_Decimal64 log2d64(_Decimal64 x);
_Decimal64 log2p1d64(_Decimal64 x);
_Decimal64 logbd64(_Decimal64 x);
_Decimal64 modfd64(_Decimal64 x, _Decimal64 *iptr);
_Decimal64 scalbnd64(_Decimal64 x, int n);
_Decimal64 scalblnd64(_Decimal64 x, long int n);
_Decimal64 cbrtd64(_Decimal64 x);
_Decimal64 compoundnd64(_Decimal64 x, long long int n);
_Decimal64 fabsd64(_Decimal64 x);
_Decimal64 hypotd64(_Decimal64 x, _Decimal64 y);
_Decimal64 powd64(_Decimal64 x, _Decimal64 y);
_Decimal64 pownd64(_Decimal64 x, long long int n);
_Decimal64 powrd64(_Decimal64 y, _Decimal64 x);
_Decimal64 rootnd64(_Decimal64 x, long long int n);
_Decimal64 rsqrtd64(_Decimal64 x);
_Decimal64 sqrtd64(_Decimal64 x);
_Decimal64 erfd64(_Decimal64 x);
_Decimal64 erfcd64(_Decimal64 x);
_Decimal64 lgammad64(_Decimal64 x);
_Decimal64 tgammad64(_Decimal64 x);
_Decimal64 ceild64(_Decimal64 x);
_Decimal64 floord64(_Decimal64 x);
_Decimal64 nearbyintd64(_Decimal64 x);
_Decimal64 rintd64(_Decimal64 x);
long int lrintd64(_Decimal64 x);
long long int llrintd64(_Decimal64 x);
_Decimal64 roundd64(_Decimal64 x);
long int lroundd64(_Decimal64 x);
long long int llroundd64(_Decimal64 x);
_Decimal64 roundevend64(_Decimal64 x);
_Decimal64 truncd64(_Decimal64 x);
_Decimal64 fromfpd64(_Decimal64 x, int rnd, unsigned int width);
_Decimal64 ufromfpd64(_Decimal64 x, int rnd, unsigned int width);
_Decimal64 fromfpxd64(_Decimal64 x, int rnd, unsigned int width);
_Decimal64 ufromfpxd64(_Decimal64 x, int rnd, unsigned int width);
_Decimal64 fmodd64(_Decimal64 x, _Decimal64 y);
_Decimal64 remainderd64(_Decimal64 x, _Decimal64 y);
_Decimal64 copysignd64(_Decimal64 x, _Decimal64 y);
_Decimal64 nand64(const char *tagp);
_Decimal64 nextafterd64(_Decimal64 x, _Decimal64 y);
_Decimal64 nexttowardd64(_Decimal64 x, _Decimal128 y);
_Decimal64 nextupd64(_Decimal64 x);
_Decimal64 nextdownd64(_Decimal64 x);
int canonicalized64(_Decimal64 *cx, const _Decimal64 *x);
_Decimal64 fdimd64(_Decimal64 x, _Decimal64 y);
_Decimal64 fmaxd64(_Decimal64 x, _Decimal64 y);
_Decimal64 fmind64(_Decimal64 x, _Decimal64 y);
_Decimal64 fmaximumd64(_Decimal64 x, _Decimal64 y);
_Decimal64 fminimumd64(_Decimal64 x, _Decimal64 y);
_Decimal64 fmaximum_magd64(_Decimal64 x, _Decimal64 y);
_Decimal64 fminimum_magd64(_Decimal64 x, _Decimal64 y);
_Decimal64 fmaximum_numd64(_Decimal64 x, _Decimal64 y);
_Decimal64 fminimum_numd64(_Decimal64 x, _Decimal64 y);
_Decimal64 fmaximum_mag_numd64(_Decimal64 x, _Decimal64 y);
_Decimal64 fminimum_mag_numd64(_Decimal64 x, _Decimal64 y);
_Decimal64 fmad64(_Decimal64 x, _Decimal64 y, _Decimal64 z);
_Decimal32 d32addd128(_Decimal128 x, _Decimal128 y);
_Decimal32 d32subd128(_Decimal128 x, _Decimal128 y);
_Decimal32 d32muld128(_Decimal128 x, _Decimal128 y);
_Decimal32 d32divd128(_Decimal128 x, _Decimal128 y);
_Decimal32 d32fmad128(_Decimal128 x, _Decimal128 y, _Decimal128 z);
_Decimal64 d64sqrtd128(_Decimal128 x);
_Decimal64 quantized64(_Decimal64 x, _Decimal64 y);
bool samequantumd64(_Decimal64 x, _Decimal64 y);
_Decimal64 quantumd64(_Decimal64 x);
long long int llquantexpd64(_Decimal64 x);
void encodedecd64(unsigned char encptr[restrict static 8], const _Decimal64 * restrict xptr);
void decodedecd64(_Decimal64 * restrict xptr, const unsigned char encptr[restrict static 8]);
void encodebind64(unsigned char encptr[restrict static 8], const _Decimal64 * restrict xptr);
void decodebind64(_Decimal64 * restrict xptr, const unsigned char encptr[restrict static 8]);

_Decimal128 acosd128(_Decimal128 x);
_Decimal128 asind128(_Decimal128 x);
_Decimal128 atand128(_Decimal128 x);
_Decimal128 atan2d128(_Decimal128 y, _Decimal128 x);
_Decimal128 cosd128(_Decimal128 x);
_Decimal128 sind128(_Decimal128 x);
_Decimal128 tand128(_Decimal128 x);
_Decimal128 acospid128(_Decimal128 x);
_Decimal128 asinpid128(_Decimal128 x);
_Decimal128 atanpid128(_Decimal128 x);
_Decimal128 atan2pid128(_Decimal128 y, _Decimal128 x);
_Decimal128 cospid128(_Decimal128 x);
_Decimal128 sinpid128(_Decimal128 x);
_Decimal128 tanpid128(_Decimal128 x);
_Decimal128 acoshd128(_Decimal128 x);
_Decimal128 asinhd128(_Decimal128 x);
_Decimal128 atanhd128(_Decimal128 x);
_Decimal128 coshd128(_Decimal128 x);
_Decimal128 sinhd128(_Decimal128 x);
_Decimal128 tanhd128(_Decimal128 x);
_Decimal128 expd128(_Decimal128 x);
_Decimal128 exp10d128(_Decimal128 x);
_Decimal128 exp10m1d128(_Decimal128 x);
_Decimal128 exp2d128(_Decimal128 x);
_Decimal128 exp2m1d128(_Decimal128 x);
_Decimal128 expm1d128(_Decimal128 x);
_Decimal128 frexpd128(_Decimal128 value, int *p);
int ilogbd128(_Decimal128 x);
_Decimal128 ldexpd128(_Decimal128 x, int p);
long int llogbd128(_Decimal128 x);
_Decimal128 logd128(_Decimal128 x);
_Decimal128 log10d128(_Decimal128 x);
_Decimal128 log10p1d128(_Decimal128 x);
_Decimal128 log1pd128(_Decimal128 x);
_Decimal128 logp1d128(_Decimal128 x);
_Decimal128 log2d128(_Decimal128 x);
_Decimal128 log2p1d128(_Decimal128 x);
_Decimal128 logbd128(_Decimal128 x);
_Decimal128 modfd128(_Decimal128 x, _Decimal128 *iptr);
_Decimal128 scalbnd128(_Decimal128 x, int n);
_Decimal128 scalblnd128(_Decimal128 x, long int n);
_Decimal128 cbrtd128(_Decimal128 x);
_Decimal128 compoundnd128(_Decimal128 x, long long int n);
_Decimal128 fabsd128(_Decimal128 x);
_Decimal128 hypotd128(_Decimal128 x, _Decimal128 y);
_Decimal128 powd128(_Decimal128 x, _Decimal128 y);
_Decimal128 pownd128(_Decimal128 x, long long int n);
_Decimal128 powrd128(_Decimal128 y, _Decimal128 x);
_Decimal128 rootnd128(_Decimal128 x, long long int n);
_Decimal128 rsqrtd128(_Decimal128 x);
_Decimal128 sqrtd128(_Decimal128 x);
_Decimal128 erfd128(_Decimal128 x);
_Decimal128 erfcd128(_Decimal128 x);
_Decimal128 lgammad128(_Decimal128 x);
_Decimal128 tgammad128(_Decimal128 x);
_Decimal128 ceild128(_Decimal128 x);
_Decimal128 floord128(_Decimal128 x);
_Decimal128 nearbyintd128(_Decimal128 x);
_Decimal128 rintd128(_Decimal128 x);
long int lrintd128(_Decimal128 x);
long long int llrintd128(_Decimal128 x);
_Decimal128 roundd128(_Decimal128 x);
long int lroundd128(_Decimal128 x);
long long int llroundd128(_Decimal128 x);
_Decimal128 roundevend128(_Decimal128 x);
_Decimal128 truncd128(_Decimal128 x);
_Decimal128 fromfpd128(_Decimal128 x, int rnd, unsigned int width);
_Decimal128 ufromfpd128(_Decimal128 x, int rnd, unsigned int width);
_Decimal128 fromfpxd128(_Decimal128 x, int rnd, unsigned int width);
_Decimal128 ufromfpxd128(_Decimal128 x, int rnd, unsigned int width);
_Decimal128 fmodd128(_Decimal128 x, _Decimal128 y);
_Decimal128 remainderd128(_Decimal128 x, _Decimal128 y);
_Decimal128 copysignd128(_Decimal128 x, _Decimal128 y);
_Decimal128 nand128(const char *tagp);
_Decimal128 nextafterd128(_Decimal128 x, _Decimal128 y);
_Decimal128 nexttowardd128(_Decimal128 x, _Decimal128 y);
_Decimal128 nextupd128(_Decimal128 x);
_Decimal128 nextdownd128(_Decimal128 x);
int canonicalized128(_Decimal128 *cx, const _Decimal128 *x);
_Decimal128 fdimd128(_Decimal128 x, _Decimal128 y);
_Decimal128 fmaxd128(_Decimal128 x, _Decimal128 y);
_Decimal128 fmind128(_Decimal128 x, _Decimal128 y);
_Decimal128 fmaximumd128(_Decimal128 x, _Decimal128 y);
_Decimal128 fminimumd128(_Decimal128 x, _Decimal128 y);
_Decimal128 fmaximum_magd128(_Decimal128 x, _Decimal128 y);
_Decimal128 fminimum_magd128(_Decimal128 x, _Decimal128 y);
_Decimal128 fmaximum_numd128(_Decimal128 x, _Decimal128 y);
_Decimal128 fminimum_numd128(_Decimal128 x, _Decimal128 y);
_Decimal128 fmaximum_mag_numd128(_Decimal128 x, _Decimal128 y);
_Decimal128 fminimum_mag_numd128(_Decimal128 x, _Decimal128 y);
_Decimal128 fmad128(_Decimal128 x, _Decimal128 y, _Decimal128 z);
_Decimal64 d64addd128(_Decimal128 x, _Decimal128 y);
_Decimal64 d64subd128(_Decimal128 x, _Decimal128 y);
_Decimal64 d64muld128(_Decimal128 x, _Decimal128 y);
_Decimal64 d64divd128(_Decimal128 x, _Decimal128 y);
_Decimal64 d64fmad128(_Decimal128 x, _Decimal128 y, _Decimal128 z);
_Decimal64 d64sqrtd128(_Decimal128 x);
_Decimal128 quantized128(_Decimal128 x, _Decimal128 y);
bool samequantumd128(_Decimal128 x, _Decimal128 y);
_Decimal128 quantumd128(_Decimal128 x);
long long int llquantexpd128(_Decimal128 x);
void encodedecd128(unsigned char encptr[restrict static 16], const _Decimal128 * restrict xptr);
void decodedecd128(_Decimal128 * restrict xptr, const unsigned char encptr[restrict static 16]);
void encodebind128(unsigned char encptr[restrict static 16], const _Decimal128 * restrict xptr);
void decodebind128(_Decimal128 * restrict xptr, const unsigned char encptr[restrict static 16]);

#ifdef __STDC_WANT_IEC_60559_EXT__
typedef _Decimal32          _Decimal32_t
typedef _Decimal64          _Decimal64_t
#define HUGE_VAL_D32
#define HUGE_VAL_D64
#define HUGE_VAL_D128

int totalorderd32(const _Decimal32 *x, const _Decimal32 *y);
int totalordermagd32(const _Decimal32 *x, const _Decimal32 *y);
_Decimal32 getpayloadd32(const _Decimal32 *x);
int setpayloadd32(_Decimal32 *res, _Decimal32 pl);
int setpayloadsigd32(_Decimal32 *res, _Decimal32 pl);

int totalorderd64(const _Decimal64 *x, const _Decimal64 *y);
int totalordermagd64(const _Decimal64 *x, const _Decimal64 *y);
_Decimal64 getpayloadd64(const _Decimal64 *x);
int setpayloadd64(_Decimal64 *res, _Decimal64 pl);
int setpayloadsigd64(_Decimal64 *res, _Decimal64 pl);

int totalorderd128(const _Decimal128 *x, const _Decimal128 *y);
int totalordermagd128(const _Decimal128 *x, const _Decimal128 *y);
_Decimal128 getpayloadd128(const _Decimal128 *x);
int setpayloadd128(_Decimal128 *res, _Decimal128 pl);
int setpayloadsigd128(_Decimal128 *res, _Decimal128 pl);
#endif
#endif
#pragma once

#ifndef __STDC_NO_COMPLEX__

#define __STDC_VERSION_COMPLEX_H__      202311L

#define complex         _Complex
#define _Complex_I      float _Complex
#define imaginary       _Imaginary
#define _Imaginary_I    float _Imaginary
#define I               _Complex_I   // or _Imaginary_I

#pragma STDC CX_LIMITED_RANGE on-off-switch
// double complex
double complex CMPLX(double x, double y);
double complex cacos(double complex z);
double complex casin(double complex z);
double complex catan(double complex z);
double complex ccos(double complex z);
double complex csin(double complex z);
double complex ctan(double complex z);
double complex cacosh(double complex z);
double complex casinh(double complex z);
double complex catanh(double complex z);
double complex ccosh(double complex z);
double complex csinh(double complex z);
double complex ctanh(double complex z);
double complex cexp(double complex z);
double complex clog(double complex z);
double cabs(double complex z);
double complex cpow(double complex x, double complex y);
double complex csqrt(double complex z);
double carg(double complex z);
double cimag(double complex z);
double complex conj(double complex z);
double complex cproj(double complex z);
double creal(double complex z);

// float complex
float complex CMPLXF(float x, float y);
float complex cacosf(float complex z);
float complex casinf(float complex z);
float complex catanf(float complex z);
float complex ccosf(float complex z);
float complex csinf(float complex z);
float complex ctanf(float complex z);
float complex cacoshf(float complex z);
float complex casinhf(float complex z);
float complex catanhf(float complex z);
float complex ccoshf(float complex z);
float complex csinhf(float complex z);
float complex ctanhf(float complex z);
float complex cexpf(float complex z);
float complex clogf(float complex z);
float cabsf(float complex z);
float complex cpowf(float complex x, float complex y);
float complex csqrtf(float complex z);
float cargf(float complex z);
float cimagf(float complex z);
float complex conjf(float complex z);
float complex cprojf(float complex z);
float crealf(float complex z);

// long double complex
long double complex CMPLXL(long double x, long double y);
long double complex casinl(long double complex z);
long double complex cacosl(long double complex z);
long double complex catanl(long double complex z);
long double complex ccosl(long double complex z);
long double complex csinl(long double complex z);
long double complex ctanl(long double complex z);
long double complex cacoshl(long double complex z);
long double complex casinhl(long double complex z);
long double complex catanhl(long double complex z);
long double complex ccoshl(long double complex z);
long double complex csinhl(long double complex z);
long double complex ctanhl(long double complex z);
long double complex cexpl(long double complex z);
long double complex clogl(long double complex z);
long double cabsl(long double complex z);
long double complex cpowl(long double complex x, long double complex y);
long double complex csqrtl(long double complex z);
long double cargl(long double complex z);
long double cimagl(long double complex z);
long double complex conjl(long double complex z);
long double complex cprojl(long double complex z);
long double creall(long double complex z);
#endif
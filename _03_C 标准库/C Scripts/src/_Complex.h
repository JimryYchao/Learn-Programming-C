#pragma once
#include <complex.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//	复数数学运算库
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/* MSVC C 复数类型自定义支持加法、减法、除法，与浮点数的加法、减法、除法 */

#define CAddition(X,Y) _Generic((Y), \
		_Fcomplex:_FCaddcc(X,Y),\
		_Dcomplex:_Caddcc(X,Y),\
		_Lcomplex:_LCaddcc(X,Y),\
		default:CAddcr(X,Y))

#define CAddcr(X,Y) _Generic((X),\
		_Fcomplex:_FCaddcr(X,Y),\
		_Dcomplex:_Caddcr(X,Y),\
		_Lcomplex:_LCaddcr(X,Y),\
		default:exit(EXIT_FAILURE))



/* 复数与复数加法 */
_Dcomplex __cdecl _Caddcc(_In_ _Dcomplex _X, _In_ _Dcomplex _Y) {
	return _DCOMPLEX_(_X._Val[0] + _Y._Val[0], _X._Val[1] + _Y._Val[1]);
}
_Fcomplex __cdecl _FCaddcc(_In_ _Fcomplex _X, _In_ _Fcomplex _Y) {
	return _FCOMPLEX_(_X._Val[0] + _Y._Val[0], _X._Val[1] + _Y._Val[1]);
}
_Lcomplex __cdecl _LCaddcc(_In_ _Lcomplex _X, _In_ _Lcomplex _Y) {
	return _LCOMPLEX_(_X._Val[0] + _Y._Val[0], _X._Val[1] + _Y._Val[1]);
}

/* 复数与浮点数加法 */
_Dcomplex __cdecl _Caddcr(_In_ _Dcomplex _X, _In_ double _Y) {
	return _DCOMPLEX_(_X._Val[0] + _Y, _X._Val[1]);
}
_Fcomplex __cdecl _FCaddcr(_In_ _Fcomplex _X, _In_ float _Y) {
	return _FCOMPLEX_(_X._Val[0] + _Y, _X._Val[1]);
}
_Lcomplex __cdecl _LCaddcr(_In_ _Lcomplex _X, _In_ long double _Y) {
	return _LCOMPLEX_(_X._Val[0] + _Y, _X._Val[1]);
}


/* 复数与复数减法 */
_Dcomplex __cdecl _Csubcc(_In_ _Dcomplex _X, _In_ _Dcomplex _Y) {
	return _DCOMPLEX_(_X._Val[0] - _Y._Val[0], _X._Val[1] - _Y._Val[1]);
}
_Fcomplex __cdecl _FCsubcc(_In_ _Fcomplex _X, _In_ _Fcomplex _Y) {
	return _FCOMPLEX_(_X._Val[0] - _Y._Val[0], _X._Val[1] - _Y._Val[1]);
}
_Lcomplex __cdecl _LCsubcc(_In_ _Lcomplex _X, _In_ _Lcomplex _Y) {
	return _LCOMPLEX_(_X._Val[0] - _Y._Val[0], _X._Val[1] - _Y._Val[1]);
}

/* 复数与浮点数减法 */
_Dcomplex __cdecl _Csubcr(_In_ _Dcomplex _X, _In_ double _Y) {

	return _DCOMPLEX_(_X._Val[0] - _Y, _X._Val[1]);
}
_Fcomplex __cdecl _FCsubcr(_In_ _Fcomplex _X, _In_ float _Y) {
	return _FCOMPLEX_(_X._Val[0] - _Y, _X._Val[1]);
}
_Lcomplex __cdecl _LCsubcr(_In_ _Lcomplex _X, _In_ long double _Y) {
	return _LCOMPLEX_(_X._Val[0] - _Y, _X._Val[1]);
}

/* 复数与复数除法 */
_Dcomplex __cdecl _Cdivcc(_In_ _Dcomplex _X, _In_ _Dcomplex _Y) {
	assert(cabs(_Y) != 0);
	double D = sqrt(_Y._Val[0]) + sqrt(_Y._Val[1]);
	return _DCOMPLEX_((_X._Val[0] * _Y._Val[0] + _X._Val[1] * _Y._Val[1]) / D, (_X._Val[1] * _Y._Val[0] - _X._Val[0] * _Y._Val[1]) / D);
}
_Fcomplex __cdecl _FCdivcc(_In_ _Fcomplex _X, _In_ _Fcomplex _Y) {
	assert(cabsf(_Y) != 0);
	float D = sqrtf(_Y._Val[0]) + sqrtf(_Y._Val[1]);
	return _FCOMPLEX_((_X._Val[0] * _Y._Val[0] + _X._Val[1] * _Y._Val[1]) / D, (_X._Val[1] * _Y._Val[0] - _X._Val[0] * _Y._Val[1]) / D);
}
_Lcomplex __cdecl _LCdivcc(_In_ _Lcomplex _X, _In_ _Lcomplex _Y) {
	assert(cabsl(_Y) != 0);
	long double D = sqrtl(_Y._Val[0]) + sqrtl(_Y._Val[1]);
	return _LCOMPLEX_((_X._Val[0] * _Y._Val[0] + _X._Val[1] * _Y._Val[1]) / D, (_X._Val[1] * _Y._Val[0] - _X._Val[0] * _Y._Val[1]) / D);
}

/* 复数与浮点数除法 */
_Dcomplex __cdecl _Cdivcr(_In_ _Dcomplex _X, _In_ double _Y) {
	assert(fabs(_Y - 0.0) >= DBL_EPSILON);
	return _DCOMPLEX_(_X._Val[0] / _Y, _X._Val[1] / _Y);
}
_Fcomplex __cdecl _FCdivcr(_In_ _Fcomplex _X, _In_ float _Y) {
	assert(fabs(_Y - 0.0) >= DBL_EPSILON);
	return _FCOMPLEX_(_X._Val[0] / _Y, _X._Val[1] / _Y);
}
_Lcomplex __cdecl _LCdivcr(_In_ _Lcomplex _X, _In_ long double _Y) {
	assert(fabs(_Y - 0.0) >= DBL_EPSILON);
	return _LCOMPLEX_(_X._Val[0] / _Y, _X._Val[1] / _Y);
}
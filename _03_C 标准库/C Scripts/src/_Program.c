#include <stdio.h>
#include "_Assert.h"
#include "_Stdarg.h"
#include "_Complex.h"

#pragma region

#pragma endregion

//#define __STDC_IEC_559_COMPLEX__

void D();

int main(void)
{
	Func();
	D();
	_Assert_assert(2, 1);
}

void F();
void D() {
	Func();
}
void F() {

}

extern void _Assert_assert(int, int);
extern void _Assert_Static_assert();

extern void _Ctype_Character_Detect();
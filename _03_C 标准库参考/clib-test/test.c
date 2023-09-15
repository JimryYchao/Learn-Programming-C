// pragma_directive_fp_contract.cpp
// On x86 and x64 compile with: /O2 /fp:fast /arch:AVX2

#include <stdio.h>

#include <math.h>
// remove the following line to enable FP contractions

#pragma fp_contract(off)

int main()
{
    double z, b, t;

    for (int i = 0; i < 10; i++)
    {
        b = i * 5.5;
        t = i * 56.025;
fpclassify

        printf("out = %.15e\n", z);
    }

    /*
    out = 0.000000000000000e+000
    out = 6.152500000000000e+001
    out = 2.351000000000000e+002
    out = 5.207249999999999e+002
    out = 9.184000000000000e+002
    out = 1.428125000000000e+003
    out = 2.049900000000000e+003
    out = 2.783725000000000e+003
    out = 3.629600000000000e+003
    out = 4.587525000000000e+003
        */
    // #pragma fp_contract (on)
    //	double _z, _b, _t;
    //
    //	for (int i = 0; i < 10; i++) {
    //		_b = i * 5.5;
    //		_t = i * 56.025;
    //
    //		_z = _t * i + _b;
    //		printf("out = %.15e\n", _z);
    //	}
}
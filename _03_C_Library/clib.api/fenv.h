#pragma once
#include <fenv.h>

#define __STDC_VERSION_FENV_H__     202311L

typedef __fenv_t              fenv_t;
typedef __fexcept_t         fexcept_t;
typedef __femode_t          femode_t;

#define FE_INVALID          
#define FE_DIVBYZERO        
#define FE_OVERFLOW         
#define FE_UNDERFLOW        
#define FE_INEXACT          
#define FE_ALL_EXCEPT       (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW | FE_INEXACT)

#define FE_TONEAREST	       
#define FE_DOWNWARD	           
#define FE_UPWARD	           
#define FE_TOWARDZERO	       
#define FE_TONEARESTFROMZERO   

#ifdef __STDC_IEC_60559_DFP__
#define FE_DEC_DOWNWARD
#define FE_DEC_TONEAREST
#define FE_DEC_TONEARESTFROMZERO
#define FE_DEC_TOWARDZERO
#define FE_DEC_UPWARD
#endif

#define FE_DFL_ENV              ((const fenv_t *) 0)
#define FE_DFL_MODE             ((const femode_t *) 0)

#pragma STDC FENV_ACCESS    on-off-switch
#pragma STDC FENV_ROUND     direction
#pragma STDC FENV_ROUND     FE_DYNAMIC

int fesetexcept(int excepts);
int feraiseexcept(int excepts);
int feclearexcept(int excepts);
int fetestexcept(int excepts);

int fegetexceptflag(fexcept_t *flagp, int excepts);
int fesetexceptflag(const fexcept_t *flagp, int excepts);
int fetestexceptflag(const fexcept_t *flagp, int excepts);

int fegetround(void);
int fesetround(int rnd);
#ifdef __STDC_IEC_60559_DFP__
#pragma STDC FENV_DEC_ROUND dec-direction
int fe_dec_getround(void);
int fe_dec_setround(int rnd);
#endif

int fegetenv(fenv_t *envp);
int fesetenv(const fenv_t *envp);
int feholdexcept(fenv_t *envp);
int feupdateenv(const fenv_t *envp);

int fegetmode(femode_t *modep);
int fesetmode(const femode_t *modep);
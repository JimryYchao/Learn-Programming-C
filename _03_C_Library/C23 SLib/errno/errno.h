#pragma once

#define errno 

#define EDOM
#define EILSEQ
#define ERANGE

#define __STDC_LIB_EXT1__
#ifdef __STDC_WANT_LIB_EXT1__
typedef __errno_t errno_t;
#endif
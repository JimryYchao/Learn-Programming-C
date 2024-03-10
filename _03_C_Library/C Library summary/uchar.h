#pragma once

#define __STDC_VERSION_UCHAR_H__        202311L

typedef __mbstate_t     mbstate_t;
typedef __size_t        size_t;
typedef __char8_t       char8_t;
typedef __char16_t      char16_t;
typedef __char32_t      char32_t;

size_t mbrtoc8(char8_t * restrict pc8, const char * restrict s, size_t n, mbstate_t * restrict ps);
size_t c8rtomb(char * restrict s, char8_t c8, mbstate_t * restrict ps); 
size_t mbrtoc16(char16_t * restrict pc16, const char * restrict s, size_t n, mbstate_t * restrict ps);
size_t c16rtomb(char * restrict s, char16_t c16, mbstate_t * restrict ps); 
size_t mbrtoc32(char32_t * restrict pc32, const char * restrict s, size_t n, mbstate_t * restrict ps);
size_t c32rtomb(char * restrict s, char32_t c32, mbstate_t * restrict ps);
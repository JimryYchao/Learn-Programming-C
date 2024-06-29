#pragma once

#define __STDC_VERSION_INTTYPES_H__     202311L

typedef struct __imaxdiv_t imaxdiv_t

#define PRIb8
#define PRIb16
#define PRIb32
#define PRIb64

#define PRIB8
#define PRIB16
#define PRIB32
#define PRIB64

#define PRId8
#define PRId16
#define PRId32
#define PRId64

#define PRIi8
#define PRIi16
#define PRIi32
#define PRIi64

#define PRIo8
#define PRIo16
#define PRIo32
#define PRIo64

#define PRIu8
#define PRIu16
#define PRIu32
#define PRIu64

#define PRIx8
#define PRIx16
#define PRIx32
#define PRIx64

#define PRIX8
#define PRIX16
#define PRIX32
#define PRIX64

#define SCNb8
#define SCNb16
#define SCNb32
#define SCNb64

#define SCNd8
#define SCNd16
#define SCNd32
#define SCNd64

#define SCNi8
#define SCNi16
#define SCNi32
#define SCNi64

#define SCNo8
#define SCNo16
#define SCNo32
#define SCNo64

#define SCNu8
#define SCNu16
#define SCNu32
#define SCNu64

#define SCNx8
#define SCNx16
#define SCNx32
#define SCNx64

#define PRIbLEAST8
#define PRIbLEAST16
#define PRIbLEAST32
#define PRIbLEAST64

#define PRIBLEAST8
#define PRIBLEAST16
#define PRIBLEAST32
#define PRIBLEAST64

#define PRIdLEAST8
#define PRIdLEAST16
#define PRIdLEAST32
#define PRIdLEAST64

#define PRIiLEAST8
#define PRIiLEAST16
#define PRIiLEAST32
#define PRIiLEAST64

#define PRIoLEAST8
#define PRIoLEAST16
#define PRIoLEAST32
#define PRIoLEAST64

#define PRIuLEAST8
#define PRIuLEAST16
#define PRIuLEAST32
#define PRIuLEAST64

#define PRIxLEAST8
#define PRIxLEAST16
#define PRIxLEAST32
#define PRIxLEAST64

#define PRIXLEAST8
#define PRIXLEAST16
#define PRIXLEAST32
#define PRIXLEAST64

#define SCNbLEAST8
#define SCNbLEAST16
#define SCNbLEAST32
#define SCNbLEAST64

#define SCNdLEAST8
#define SCNdLEAST16
#define SCNdLEAST32
#define SCNdLEAST64

#define SCNiLEAST8
#define SCNiLEAST16
#define SCNiLEAST32
#define SCNiLEAST64

#define SCNoLEAST8
#define SCNoLEAST16
#define SCNoLEAST32
#define SCNoLEAST64

#define SCNuLEAST8
#define SCNuLEAST16
#define SCNuLEAST32
#define SCNuLEAST64

#define SCNxLEAST8
#define SCNxLEAST16
#define SCNxLEAST32
#define SCNxLEAST64

#define PRIbFAST8
#define PRIbFAST16
#define PRIbFAST32
#define PRIbFAST64

#define PRIBFAST8
#define PRIBFAST16
#define PRIBFAST32
#define PRIBFAST64

#define PRIdFAST8
#define PRIdFAST16
#define PRIdFAST32
#define PRIdFAST64

#define PRIiFAST8
#define PRIiFAST16
#define PRIiFAST32
#define PRIiFAST64

#define PRIoFAST8
#define PRIoFAST16
#define PRIoFAST32
#define PRIoFAST64

#define PRIuFAST8
#define PRIuFAST16
#define PRIuFAST32
#define PRIuFAST64

#define PRIxFAST8
#define PRIxFAST16
#define PRIxFAST32
#define PRIxFAST64

#define PRIXFAST8
#define PRIXFAST16
#define PRIXFAST32
#define PRIXFAST64

#define SCNbFAST8
#define SCNbFAST16
#define SCNbFAST32
#define SCNbFAST64

#define SCNdFAST8
#define SCNdFAST16
#define SCNdFAST32
#define SCNdFAST64

#define SCNiFAST8
#define SCNiFAST16
#define SCNiFAST32
#define SCNiFAST64

#define SCNoFAST8
#define SCNoFAST16
#define SCNoFAST32
#define SCNoFAST64

#define SCNuFAST8
#define SCNuFAST16
#define SCNuFAST32
#define SCNuFAST64

#define SCNxFAST8
#define SCNxFAST16
#define SCNxFAST32
#define SCNxFAST64

#define PRIbMAX 
#define PRIBMAX 
#define PRIdMAX 
#define PRIiMAX 
#define PRIoMAX 
#define PRIuMAX 
#define PRIxMAX 
#define PRIXMAX 
#define SCNbMAX 
#define SCNdMAX 
#define SCNiMAX 
#define SCNoMAX 
#define SCNuMAX 
#define SCNxMAX 

#define PRIbPTR
#define PRIBPTR
#define PRIdPTR
#define PRIiPTR
#define PRIoPTR
#define PRIuPTR
#define PRIxPTR
#define PRIXPTR
#define SCNbPTR
#define SCNdPTR
#define SCNiPTR
#define SCNoPTR
#define SCNuPTR
#define SCNxPTR

intmax_t imaxabs(intmax_t j);
imaxdiv_t imaxdiv(intmax_t numer, intmax_t denom);
intmax_t strtoimax(const char * restrict nptr, char ** restrict endptr, int base);
uintmax_t strtoumax(const char * restrict nptr, char ** restrict endptr, int base);
intmax_t wcstoimax(const wchar_t *restrict nptr, wchar_t **restrict endptr, int base);
uintmax_t wcstoumax(const wchar_t *restrict nptr, wchar_t **restrict endptr, int base);
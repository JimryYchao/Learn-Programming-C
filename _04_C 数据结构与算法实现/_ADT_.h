#ifndef _ADT_H_ /* _ADT.h_ */
#define _ADT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct
{
	int elem;
} ElemType;

bool IsEqual(const ElemType a, const ElemType b)
{
	if (a.elem != b.elem)
		return false;
	else
		return true;
}

#define Debug(X) printf("Error: %s\n", X)
#define INVALID_VALUE "Invalid value"
#define OVERFLOW "Memory overflow"
#define NULL_REFERENCE "Null reference"
#define OUT_OF_RANGE "Out of range"

#define IsNull(L)              \
	if (!(L))                  \
	{                          \
		Debug(NULL_REFERENCE); \
		return;                \
	}
#define IsNull_R(L, R)         \
	if (!(L))                  \
	{                          \
		Debug(NULL_REFERENCE); \
		return (R);            \
	}

#endif /* _ADT.h_ */
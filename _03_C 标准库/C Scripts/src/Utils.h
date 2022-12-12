#pragma once
#include<stdio.h>

typedef enum {
	Other,
	Char,
	UChar,
	Int16,
	UInt16,
	Int32,
	UInt32,
	Single,
	Double,
	LDouble,
} Type;


#define print(X) printf("%s\n",(X))

#define GetType(X) _Generic((X),\
	char:Char,\
	unsigned char: UChar,\
	short:Int16,\
	unsigned short:UInt16,\
	int:Int32,\
	unsigned int:UInt32,\
	float:Single,\
	double:Double,\
	long double:LDouble,\
	default:Other)



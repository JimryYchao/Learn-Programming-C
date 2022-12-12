#include <stdio.h>
#include <stdlib.h>
#include "src\LinkedList.h"
#include "src\SqList.h"

#include <limits.h>
#include <float.h>
#include "h.h"
#include <math.h>

#define G_code 0x0000000A

int OddCheck(int binary)
{
	int mask = 1;
	int rt = binary & mask;
	mask <<= 1;
	while (mask != 0)
	{
		rt <<= 1;
		rt = rt ^ (binary & mask);
		mask <<= 1;
	}
	return  rt ? 1 : 0;
}

int CRC_Create(short data){
	


}

int main(void)
{
	printf("%d", OddCheck(0b01101));
}

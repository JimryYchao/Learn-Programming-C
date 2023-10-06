#include <stdio.h>
#include <stdlib.h>
#include "SqList.h"


int main(void)
{
	SqList L = SqListCreate(10);
	SqListAddElem(L, (ElemType) { 1 });
	SqListAddElem(L, (ElemType) { 2 });
	SqListAddElem(L, (ElemType) { 3 });
	SqListAddElem(L, (ElemType) { 4 });
	SqListAddElem(L, (ElemType) { 5 });
	SqListInsertElem(L, 2, (ElemType) { 6 });
	if (SqListContains(L, (ElemType) { 6 }))
		SqListRemoveElemAt(L, 0);

	SqListTraverse(L);
	SqListClear(L);
	SqListDestroy(L);
}
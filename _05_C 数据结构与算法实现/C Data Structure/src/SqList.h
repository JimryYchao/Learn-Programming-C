/* �̶�������С��˳���������ɾ��Ĳ��� */

#ifndef _SQLIST_H_
#define _SQLIST_H_

#include "_ADT_.h"

typedef struct
{
	ElemType* List;
	size_t len;
	size_t capacity;
} SequenceList, * SqList;

/* SqList: ����һ��˳��洢�� */
SqList SqListCreate(size_t Capacity)
{
	if (Capacity <= 0)
	{
		Debug(INVALID_VALUE);
		return NULL;
	}
	SqList L = (SqList)calloc(1, sizeof(SequenceList));
	ElemType* List = (ElemType*)calloc(Capacity, sizeof(ElemType));
	if (!L || !List)
	{
		Debug(OVERFLOW);
		return NULL;
	}
	L->List = List;
	L->capacity = Capacity;
	L->len = 0;
	return L;
}
/* SqList: ����һ��˳��洢�� */
void SqListDestroy(SqList L)
{
	IsNull(L);
	SqList tmpList = L;
	ElemType* data = L->List;
	L->List = NULL;
	L = NULL;
	free(tmpList);
	free(data);
}
/* SqList: ���һ��˳��洢�� */
void SqListClear(SqList L)
{
	IsNull(L);
	memset(L->List, 0, L->len);
	L->len = 0;
}
/* SqList: �ж�˳����Ƿ��ǿձ����Ч�� */
bool SqListIsNullOrEmpty(SqList L)
{
	return !L || L->len == 0;
}
/* SqList: ���һ��Ԫ�ص�˳����� */
size_t SqListAdd(SqList L, ElemType e)
{
	IsNull_R(L, -1);
	if (L->len >= L->capacity)
	{
		Debug(OUT_OF_RANGE);
		return -1;
	}
	else
	{
		L->List[L->len].elem = e.elem;
		L->len++;
		return L->len - 1;
	}
}
/* SqList: ���ص� i λ�õ�Ԫ�ص�ֵ */
ElemType SqListGetElem(SqList L, size_t i)
{
	IsNull_R(L, (ElemType) { 0 }) if (i < 0 || i >= L->len)
	{
		Debug(OUT_OF_RANGE);
		return (ElemType) { 0 };
	}
	ElemType e = { .elem = L->List[i].elem };
	return e;
}
/* SqList: ����˳������� e ���Ԫ�ص�λ�� */
size_t SqListIndexOf(SqList L, ElemType e)
{
	IsNull_R(L, -1);
	for (size_t i = 0; i < L->len; i++)
	{
		if (L->List[i].elem == e.elem)
			return i;
	}
	return -1;
}
/* SqList: ����һ��Ԫ�� */
bool SqListInsert(SqList L, size_t i, ElemType newElem)
{
	IsNull_R(L, false);
	if (L->len >= L->capacity)
	{
		Debug(OUT_OF_RANGE);
		return false;
	}
	if (i < 0 || i > L->len)
	{
		Debug(OUT_OF_RANGE);
		return false;
	}
	for (size_t j = L->len; j > i; j--)
		L->List[j].elem = L->List[j - 1].elem;
	L->List[i].elem = newElem.elem;
	L->len++;
	return true;
}
/* SqList: �Ƴ��� i λ��Ԫ�� */
bool SqListRemoveAt(SqList L, size_t i)
{
	IsNull_R(L, false);
	if (i < 0 || i >= L->len)
	{
		Debug(OUT_OF_RANGE);
		return false;
	}
	for (size_t j = i; j < L->len - 1; j++)
		L->List[j].elem = L->List[j + 1].elem;
	L->len--;
	return true;
}
/* SqList: �Ƴ�һ��Ԫ�� */
bool SqListRemove(SqList L, ElemType e)
{
	IsNull_R(L, false);
	size_t index = -1;
	if ((index = SqListIndexOf(L, e)) >= 0)
	{
		SqListRemoveAt(L, index);
		return true;
	}
	return false;
}
/* SqList: ˳������Ƿ������Ԫ�ص�ֵ */
bool SqListContains(SqList L, ElemType e)
{
	IsNull_R(L, false);
	if (SqListIndexOf(L, e) < 0)
		return false;
	return true;
}
/* SqList: �޸ĵ� i λ��Ԫ�ص�ֵ */
bool SqListModifyElem(SqList L, size_t i, ElemType newElem)
{
	IsNull_R(L, false);
	if (i < 0 || i >= L->len)
	{
		Debug(OUT_OF_RANGE);
		return false;
	}
	L->List[i].elem = newElem.elem;
	return true;
}
/* SqListL: ����˳����Ԫ�ز��������׼��� */
void SqListTraverse(SqList L)
{
	IsNull(L);
	if (L->len > 0)
	{
		for (size_t i = 0; i < L->len; i++)
			printf("i=%lld, v=%d\n", i, (L->List[i]).elem);
	}
}
#endif
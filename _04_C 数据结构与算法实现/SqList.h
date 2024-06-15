/* 固定容量大小的顺序表，具有增删查改操作 */

#ifndef _SQLIST_H_
#define _SQLIST_H_

#include "_ADT_.h"

typedef struct
{
	ElemType* List;
	size_t len;
	size_t capacity;
} SequenceList, * SqList;

/* SqList: 创建一个顺序存储表 */
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
/* SqList: 销毁一个顺序存储表 */
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
/* SqList: 清空一个顺序存储表 */
void SqListClear(SqList L)
{
	IsNull(L);
	memset(L->List, 0, L->len);
	L->len = 0;
}
/* SqList: 判断顺序表是否是空表或无效表 */
bool SqListIsNullOrEmpty(SqList L)
{
	return !L || L->len == 0;
}
/* SqList: 添加一个元素到顺序表中 */
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
/* SqList: 返回第 i 位置的元素的值 */
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
/* SqList: 返回顺序表中与 e 相等元素的位置 */
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
/* SqList: 插入一个元素 */
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
/* SqList: 移除第 i 位置元素 */
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
/* SqList: 移除一个元素 */
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
/* SqList: 顺序表中是否包含此元素的值 */
bool SqListContains(SqList L, ElemType e)
{
	IsNull_R(L, false);
	if (SqListIndexOf(L, e) < 0)
		return false;
	return true;
}
/* SqList: 修改第 i 位置元素的值 */
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
/* SqListL: 遍历顺序表的元素并输出到标准输出 */
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
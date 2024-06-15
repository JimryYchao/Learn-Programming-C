/* 单链表 */

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "_ADT_.h"

typedef struct LNode
{
	ElemType data;
	struct LNode *next;
} LNode, *PtrToLNode;
typedef PtrToLNode Position, LinkedListNode;

typedef struct HeadLNode
{
	int len;
	Position Head;
	Position Tail;

} HeadLNode, *LinkedList;

/* LinkedList: 创建一个单链表 */
LinkedList LinkedListCreate()
{
	LinkedList L = (HeadLNode *)calloc(1, sizeof(HeadLNode));
	Position head = (LNode *)calloc(1, sizeof(LNode));
	L->Head = head;
	L->Tail = L->Head;
	L->len = 0;
	return L;
}
/* LinkedList: 销毁一个单链表 */
void LinkedListDestroy(LinkedList L)
{
	IsNull(L);
	LinkedList tmpList = L;
	Position p = L->Head;
	PtrToLNode temPtr;
	L->Head = NULL;
	L->Tail = NULL;
	L = NULL;

	while (p)
	{
		temPtr = p;
		p = p->next;
		free(temPtr);
	}
	free(tmpList);
}
/* LinkedList: 清空链表 */
void LinkedListClear(LinkedList L)
{
	IsNull(L);
	Position p = L->Head->next;
	PtrToLNode temPtr;
	L->Tail = L->Head;
	L->len = 0;

	while (p)
	{
		temPtr = p;
		p = p->next;
		free(temPtr);
	}
}
/* LinkedList: 是否为空链表 */
bool LinkedListIsEmpty(LinkedList L)
{
	IsNull_R(L, false);
	if (L->Head == L->Tail)
	{
		L->len = 0;
		return true;
	}
	return false;
}
/* LinkedList: 在某结点后插入一个元素 */
bool LinkedListInsertAt(LinkedList L, LinkedListNode posNode, ElemType e)
{
	IsNull_R(L || posNode, false);
	Position tmp = (LNode *)calloc(1, sizeof(LNode));
	if (!tmp)
	{
		Debug(OVERFLOW);
		return false;
	}

	tmp->data = e;
	tmp->next = posNode->next;
	posNode->next = tmp;
	++L->len;

	if (!tmp->next)
		L->Tail = tmp;
	return true;
}
/* LinkedList: 从头结点插入元素 */
bool LinkedListInsertAtHead(LinkedList L, ElemType e)
{
	return LinkedListInsertAt(L, L->Head, e);
}
/* LinkedList: 在链尾插入元素 */
bool LinkedListInsertAtTail(LinkedList L, ElemType e)
{
	return LinkedListInsertAt(L, L->Tail, e);
}
/* LinkedList: 查找元素在链中的位置，未找到返回空指针 */
LinkedListNode LinkedListFind(LinkedList L, ElemType e)
{
	LinkedListNode outNode = L->Head->next;
	while (outNode && !IsEqual(outNode->data, e))
		outNode = outNode->next;
	if (outNode)
		return outNode;
	return NULL;
}
// bool LinkedListContains(LinkedList L, LinkedListNode node){
// 	if(LinkedListFind(L,))
// }
bool LinkedListRemoveAt(LinkedList L, LinkedListNode node)
{
	IsNull_R(L, false);
	if (!node)
		return false;

	Position p = L->Head->next;
	// while (p &&)
}
/* LinkedList: 在 pos 位置插入一个结点 */
bool LinkedListInsert(LinkedList L, size_t pos, ElemType e)
{
	IsNull_R(L, false);
	if (pos < 0 || pos > L->len)
	{
		Debug(OUT_OF_RANGE);
		return false;
	}
	size_t i = 0;
	Position p = L->Head;
	while (p && i < pos)
	{
		p = p->next;
		++i;
	}
	Position node = (LNode *)calloc(1, sizeof(LNode));
	if (!node)
	{
		Debug(OVERFLOW);
		return false;
	}
	node->data = e;
	node->next = p->next;
	p->next = node;
	++L->len;
	return true;
}

LinkedListNode LinkedListGetNode(LinkedList L, size_t pos)
{
	IsNull_R(L, NULL);
	if (pos < 0 || pos > L->len - 1)
	{
		Debug(OUT_OF_RANGE);
		return NULL;
	}
	size_t i = 0;
	Position p = L->Head;
	while (!p && i < pos - 1)
	{
	}
}

LinkedListNode LinkedListFindPrevious(LinkedList L, ElemType e);

#endif
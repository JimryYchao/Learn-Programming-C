# C Plus 高级数据结构

- molloc() 综合使用
- 抽象数据类型（ADT）
- 不同类型的数据结构

---
- [C Plus 高级数据结构](#c-plus-高级数据结构)
	- [1. 从数组到链表](#1-从数组到链表)
		- [1.1 链表的使用](#11-链表的使用)
	- [2. 抽象数据类型 (ADT)--- 以链表为例](#2-抽象数据类型-adt----以链表为例)
		- [2.1 建立抽象](#21-建立抽象)
		- [2.2 建立接口](#22-建立接口)
		- [2.3 使用接口](#23-使用接口)
		- [2.4 实现接口](#24-实现接口)
	- [3. 队列 (ADT)](#3-队列-adt)
		- [3.1 定义队列抽象数据类型](#31-定义队列抽象数据类型)
		- [3.2 定义接口](#32-定义接口)
		- [3.3 实现接口](#33-实现接口)
		- [3.4 测试队列](#34-测试队列)
	- [4. 链表与数组](#4-链表与数组)
	- [5. 二叉查找树](#5-二叉查找树)
		- [5.1 二叉树 (ADT)](#51-二叉树-adt)
		- [5.2 二叉查找树接口](#52-二叉查找树接口)
		- [5.3 二叉树的实现](#53-二叉树的实现)
		- [5.4 使用二叉树](#54-使用二叉树)

---
## 1. 从数组到链表

> 定义链表（linked list）的基础

- 结构不能含有与本身类型相同的结构，但是可以含有指向同类型结构的指针

- 声明结构的时候, 动态分配空间的同时也为新指针分配空间, 但是，还得需要另一个指针来跟踪新分配的指针，用于跟踪新指针的指针本身，也需要一个指针来跟踪，以此类推

- 还需要一个单独的指针储存第 1 个结构的地址，该指针被称为头指针（head pointer）。头指针指向链表中的第 1 项。

```c
#define TSIZE 45
#define NAMELEN 15

struct books{
	char title[TSIZE];
	char author[NAMELEN];
	int cost;
	struct books * next;
}
struct books * head;

struct books headBook;
head = &headBook;

struct books secondBook;
headBook.next = &secondBook;
//.......链式结构, 尾部的指针为 NULL, 有下一个元素时指向该元素地址, 需要一个头指针, 才能正常遍历链表
```

> 链式结构的内存特征

- 元素与元素之间的地址并不是连续的, 内部含有一个指针结构用来指向下一个元素的地址, 通过各自的内部指针串联起来的单向链表

- 可以根据指针指向的方向与数量, 组成丰富的数据结构 (双向链表, 树, 图等)

---
### 1.1 链表的使用

> 用链表而不是数组来储存电影信息

```c
#include <stdio.h>
#include <stdlib.h> /* 提供malloc()原型 */
#include <string.h> /* 提供strcpy()原型 */
#define TSIZE 45	/* 储存片名的数组大小 */
struct film
{
	char title[TSIZE];
	int rating;
	struct film *next; /* 指向链表中的下一个结构 */
};
char *s_gets(char *st, int n); // 处理字符串

int main(void)
{
	struct film *head = NULL;	 	// 创建头指针置空
	struct film *prev, *current; 	// 用来串联链表
	char input[TSIZE];
	/* 1. 收集并储存信息 */
	puts("Enter first movie title:");
	while (s_gets(input, TSIZE) != NULL && input[0] != '\0')
	{
		// 为当前输入的结构动态分配空间
		current = (struct film *)malloc(sizeof(struct film));
		if (head == NULL) 				/* 第 1 个结构 */
			head = current; 			// 头指针
		else 							/* 后续的结构 */
			prev->next = current;		
		current->next = NULL;
		strcpy(current->title, input);
		puts("Enter your rating <0-10>:");
		scanf("%d", &current->rating);
		while (getchar() != '\n')
			continue;
		puts("Enter next movie title (empty line to stop) : ");
		prev = current;
	}
	/* 显示电影列表 */
	if (head == NULL)
		printf("No data entered. ");
	else
		printf("Here is the movie list:\n");
	current = head;
	while (current != NULL)
	{
		printf("Movie: %s Rating: %d\n",
			   current->title, current->rating);
		current = current->next;
	}
	/* 完成任务，释放已分配的内存 */
	current = head;
	while (current != NULL)
	{
		current = head;
		head = current->next;
		free(current);
	}
	printf("Bye!\n");
	return 0;
}
char *s_gets(char *st, int n)
{
	char *ret_val;
	char *find;
	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n'); // 查找换行符
		if (find)				 // 如果地址不是 NULL，
			*find = '\0';		 // 在此处放置一个空字符
		else
			while (getchar() != '\n')
				continue; // 处理剩余输入行
	}
	return ret_val;
}
```

- 链表用来储存数据比数组相对会灵活一些

---
## 2. 抽象数据类型 (ADT)--- 以链表为例

- 把一系列结构构成一个链表。本质上，我们使用 C 语言的功能设计了一种符合程序要求的新数据类型。但是，我们的做法并不系统

- 类型特指两类信息：属性和操作

- 假设要定义一个新的数据类型。首先，必须提供储存数据的方法，例如设计一个结构。其次，必须提供操控数据的方法

> 一种定义新类型的好方法, 用 3 个步骤完成从抽象到具体的过程。

1. 提供类型属性和相关操作的抽象描述, 这些描述既不能依赖特定的实现，也不能依赖特定的编程语言。这种正式的抽象描述被称为抽象数据类型（ADT）。

2. 开发一个实现 ADT 的编程接口, 指明如何储存数据和执行所需操作的函数。可以提供结构定义和操控该结构的函数原型

3. 编写代码实现接口。这一步至关重要，但是使用该新类型的程序员无需了解具体的实现细节

---
### 2.1 建立抽象

- 对于链表（电影项目所需的是一个项链表。每一项包含电影名和评级），所需的操作是把每一个新项添加到链表的末尾和显示链表中的内容

* 链表的有效操作：
  - 初始化一个空链表
  - 再链表末尾添加一个新项
  - 确定链表是否为空
  - 确定链表是否已满
  - 访问列表中的项数
  - 链表的任意位置插入一个项
  - 移除链表中的一个项
  - 用另一个项替换链表中的一个项
  - 在链表中搜索一个项

- 链表的抽象定义：链表是一个能储存一系列项且可以对其进行所需操作的数据对象（该定义既未说明链表中可以储存什么项，也未指定是用数组、结构还是其他数据形式来储存项，而且并未规定用什么方法来实现操作）

- 确定新类型模型：
  - 类型名： 简单链表
  - 类型属性： 可以储存一系列项
  - 类型操作： 初始化链表为空、确定链表为空、确定链表已满、确定链表中的项数、在链表末尾添加项、遍历链表，处理链表中的项、清空链表

---
### 2.2 建立接口

- 简单链表的接口有两个部分，一是描述如何表示数据，第二部分是描述实现 ADT 操作的函数

- 应该使用某种通用的 Item 类型而不是一些特殊类型，可以用 typedef 功能来定义所需的 Item 类型

```c
/* list.h -- 简单链表类型的头文件 */
#ifndef LIST_H_
#define LIST_H_
#include <stdbool.h> /* C99特性 */
/* 特定程序的声明 */
#define TSIZE 45 /* 储存电影名的数组大小 */
struct film
{
	char title[TSIZE];
	int rating;
};
/* 一般类型定义 */
typedef struct film Item;
typedef struct node
{
	Item item;
	struct node* next;
} Node;
typedef Node* List;	//头节点指针
/* 函数原型 */
/* 操作： 初始化一个链表 */
/* 前提条件： plist 指向一个链表 */
/* 后置条件： 链表初始化为空 */
void InitializeList(List* plist);
/* 操作： 确定链表是否为空定义，plist指向一个已初始化的链表 */
/* 后置条件： 如果链表为空，该函数返回true；否则返回false */
bool ListIsEmpty(const List* plist);
/* 操作： 确定链表是否已满，plist指向一个已初始化的链表 */
/* 后置条件： 如果链表已满， 该函数返回真； 否则返回假 */
bool ListIsFull(const List* plist);
/* 操作： 确定链表中的项数, plist指向一个已初始化的链表 */
/* 后置条件： 该函数返回链表中的项数 */
unsigned int ListItemCount(const List* plist);
/* 操作： 在链表的末尾添加项 */
/* 前提条件： item是一个待添加至链表的项, plist指向一个已初始化的链表 */
/* 后置条件： 如果可以，该函数在链表末尾添加一个项，且返回true；否则返回false */
bool AddItem(Item item, List* plist);
/* 操作： 把函数作用于链表中的每一项 */
/* plist 指向一个已初始化的链表 */
/* pfun指向一个函数，该函数接受一个Item类型的参数，且无返回值 */
/* 后置条件： pfun指向的函数作用于链表中的每一项一次 */
void Traverse(const List* plist, void(*pfun)(Item item));
/* 操作： 释放已分配的内存（ 如果有的话） */
/* plist 指向一个已初始化的链表 */
/* 后置条件： 释放了为链表分配的所有内存，链表设置为空 */
void EmptyTheList(List* plist);
#endif
```

---
### 2.3 使用接口

- 先使用这个接口编写程序, 在具体实现之前, 使用接口本身是不必知道具体的实现细节的

* 预先编写一个伪代码方案
  - 创建一个 List 类型的变量。
  - 创建一个 Item 类型的变量。
  - 初始化链表为空。
  - 当链表未满且有输入时：
  - 把输入读取到Item类型的变量中。
  - 在链表末尾添加项。
  - 访问链表中的每个项并显示它们。

> 使用抽象数据类型（ADT）风格的链表

```c
/* films.c -- 使用抽象数据类型（ADT）风格的链表 */
/* 与list.c一起编译 */
#include <stdio.h>
#include <stdlib.h> /* 提供exit()的原型 */
#include "linkedList.h" /* 定义List、Item */
void showmovies(Item item);
char* s_gets(char* st, int n);
int main(void)
{
	List movies;
	Item temp;
	/* 1. 初始化 */
	InitializeList(&movies);
	if (ListIsFull(&movies))
	{
		fprintf(stderr, "No memory available! Bye!\n");
		exit(1);
	}
	
	/* 2. 获取用户输入并储存 */
	puts("Enter first movie title:");
	while (s_gets(temp.title, TSIZE) != NULL && temp.title[0] != '\0') {
		puts("Enter your rating <0-10>:");
		scanf("%d", &temp.rating);
		while (getchar() != '\n')
			continue;
		if (AddItem(temp, &movies) == false)
		{
			fprintf(stderr, "Problem allocating memory\n");
			break;
		}
		if (ListIsFull(&movies))
		{
			puts("The list is now full.");
			break;
		}
		puts("Enter next movie title (empty line to stop) :");
	}
	/* 显示 */
	if (ListIsEmpty(&movies))
		printf("No data entered. ");
	else
	{
		printf("Here is the movie list:\n");
		Traverse(&movies, showmovies);
	}
	printf("You entered %d movies.\n", ListItemCount(&movies)); 
	
	/* 清理 */
	EmptyTheList(&movies);
	printf("Bye!\n");
	return 0;
}
void showmovies(Item item)
{
	printf("Movie: %s Rating: %d\n", item.title, item.rating);
}
char* s_gets(char* st, int n)
{
	char* ret_val;
	char* find;
	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n'); // 查找换行符
		if (find) // 如果地址不是NULL，
			*find = '\0'; // 在此处放置一个空字符
		else
			while (getchar() != '\n')
				continue; // 处理输入行的剩余内容
	} return ret_val;
}
```

---
### 2.4 实现接口

- 把函数定义统一在 list.c 中 (函数原型在 list.h)

- 将整个程序 (list.h, list.c, films.c 组成) 一起编译和链接

```c
/* list.c -- 支持链表操作的函数 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* 局部函数原型 */
static void CopyToNode(Item item, Node* pnode);

/* >>>> 接口函数实现 <<<< */

/* 1. 把链表设置为空 */
void InitializeList(List* plist)
{
	*plist = NULL;
	// 指向链表元素 Node*, 将其置空
}
/* 2. 如果链表为空，返回true */
bool ListIsEmpty(const List* plist)
{
	if (*plist == NULL)
		return true;
	else
		return false;
}
/* 3. 如果链表已满，返回 true */
bool ListIsFull(const List* plist)
{
	Node* pt;
	bool full;
	// 检查内存是否能申请到
	pt = (Node*)malloc(sizeof(Node));
	if (pt == NULL)
		full = true;
	else
		full = false;
	free(pt);
	return full;
}
/* 4. 返回节点的数量 */
unsigned int ListItemCount(const List* plist)
{
	unsigned int count = 0;
	Node* pnode = *plist; /* 设置链表的开始 */
	while (pnode != NULL)
	{
		++count;
		pnode = pnode->next; /* 设置下一个节点 */
	} return count;
}
/* 5. 创建储存项的节点，并将其添加至由 plist 指向的链表末尾（较慢的实现） */
bool AddItem(Item item, List* plist)
{
	Node* pnew;
	Node* scan = *plist;
	pnew = (Node*)malloc(sizeof(Node));
	if (pnew == NULL)
		return false;	/* 失败时退出函数 */
	CopyToNode(item, pnew);
	pnew->next = NULL;

	if (scan == NULL)	/* 空链表，所以把 */
		*plist = pnew;	/* pnew 放在链表的开头 */

	else
	{
		while (scan->next != NULL)
			scan = scan->next;	/* 找到链表的末尾 */
		scan->next = pnew;		/* 把pnew添加到链表的末尾 */
	} return true;
}
/* 6. 访问每个节点并执行pfun指向的函数 */
void Traverse(const List* plist, void(*pfun)(Item item))
{
	Node* pnode = *plist; /* 设置链表的开始 */
	while (pnode != NULL)
	{
		(*pfun)(pnode->item); /* 把函数应用于链表中的项 */
		pnode = pnode->next; /* 前进到下一项 */
	}
}
/* 7. 设置链表指针为NULL, 释放由malloc()分配的内存 */
void EmptyTheList(List* plist)
{
	Node* psave;
	while (*plist != NULL)
	{
		psave = (*plist)->next; /* 保存下一个节点的地址
		*/
		free(*plist); /* 释放当前节点 */
		*plist = psave; /* 前进至下一个节点 */
	}
}
/* >>>> 局部函数定义 <<<< */
/* 把一个项拷贝到节点中 */
static void CopyToNode(Item item, Node* pnode)
{
	pnode->item = item;  /* 拷贝结构 */
}
```

---
## 3. 队列 (ADT)

### 3.1 定义队列抽象数据类型

- 队列 (queue) 是具有两个特殊属性的链表: 新项只能添加到链表的末尾, 只能从链表的开头移除项

- 队列的特征是 "先进先出 (first in, first out; FIFO)" 的数据形式

* 队列的非正式的抽象定义
  - 类型名: 队列
  - 类型属性: 可以储存一系列项
  - 类型操作: 初始化队列为空、确定队列为空、确定队列中的项数、在队列末尾添加项、在队列开头删除或恢复项、清空队列

---
### 3.2 定义接口

- 我们使用 C 的 typedef 工具创建两个类型名：Item 和 Queue。

```c
/* queue.h -- Queue的接口 */
#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>
// 在这里插入 Item 类型的定义，例如
typedef int Item;	// 用于use_q.c
/*
或者 
typedef struct item {
	int gumption; 
	int charisma;
} Item;
*/

/* Queue 元素定义 */
typedef struct node
{
	Item item;
	struct node* next;
} Node;
typedef struct queue
{
	Node* front; /* 指向队列首项的指针 */
	Node* rear; /* 指向队列尾项的指针 */
	int items; /* 队列中的项数 */
	size_t maxCount; /* 队列最大数目 */
} Queue;

/* 操作： 初始化队列 */
/* 前提条件： pq 指向一个队列, maxCount 是定义该队列最大的元素数目 */
/* 后置条件： 队列被初始化为空 */
void InitializeQueue(Queue* pq, size_t maxCount);

/* 操作： 检查队列是否已满 */
/* 前提条件： pq 指向之前被初始化的队列 */
/* 后置条件： 如果队列已满则返回true ， 否则返回false */
bool QueueIsFull(const Queue* pq);

/* 操作： 检查队列是否为空 */
/* 前提条件： pq 指向之前被初始化的队列 */
/* 后置条件： 如果队列为空则返回true ， 否则返回false */
bool QueueIsEmpty(const Queue* pq);

/* 操作： 确定队列中的项数 */
/* 前提条件： pq 指向之前被初始化的队列 */
/* 后置条件： 返回队列中的项数 */
int QueueItemCount(const Queue* pq);

/* 操作： 在队列末尾添加项 */
/* 前提条件： pq 指向之前被初始化的队列, item 是要被添加在队列末尾的项 */
/* 后置条件： 如果队列不为空，item将被添加在队列的末尾，
   该函数返回true；否则，队列不改变，该函数返回false*/
bool EnQueue(Item item, Queue* pq);

/* 操作： 从队列的开头删除项 */
/* 前提条件： pq 指向之前被初始化的队列 */
/* 后置条件： 如果队列不为空，队列首端的item将被拷贝到 *pitem 中 
   并被删除， 且函数返回true; 如果该操作使得队列为空， 则重置队列
   为空; 如果队列在操作前为空， 该函数返回false */
bool DeQueue(Item* pitem, Queue* pq);

/* 操作： 清空队列 */
/* 前提条件： pq 指向之前被初始化的队列 */
/* 后置条件： 队列被清空 */
void EmptyTheQueue(Queue* pq);
#endif
```

---
### 3.3 实现接口

```c
/* queue.c -- Queue类型的实现 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
/* 局部函数 */
static void CopyToNode(Item item, Node* pn);
static void CopyToItem(Node* pn, Item* pi);

// 1. 实例化队列
void InitializeQueue(Queue* pq, size_t maxCount)
{
	pq->maxCount = maxCount;
	pq->front = pq->rear = NULL;
	pq->items = 0;
}

// 2. 校验队列是否已满
bool QueueIsFull(const Queue* pq)
{
	return pq->items == pq->maxCount;
}

// 3. 队列是否为空
bool QueueIsEmpty(const Queue* pq)
{
	return pq->items == 0;
}

// 4. 队列中元素的数目
int QueueItemCount(const Queue* pq)
{
	return pq->items;
}

// 5. 压入队列 (从头部添加)
bool EnQueue(Item item, Queue* pq)
{
	Node* pnew;
	if (QueueIsFull(pq))
		return false;
	pnew = (Node*)malloc(sizeof(Node));
	if (pnew == NULL)
	{
		fprintf(stderr, "Unable to allocate memory!\n");
		exit(1);
	}
	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (QueueIsEmpty(pq))
		pq->front = pnew; /* 项位于队列的首端 */
	else
		pq->rear->next = pnew; /* 链接到队列的尾端 */
	pq->rear = pnew; /* 记录队列尾端的位置 */
	pq->items++; /* 队列项数加 1 */
	return true;
}

// 6. 出队列 (从尾部出)
bool DeQueue(Item* pitem, Queue* pq)
{
	Node* pt;
	if (QueueIsEmpty(pq))
		return false;
	CopyToItem(pq->front, pitem);
	pt = pq->front;
	pq->front = pq->front->next;
	free(pt);
	pq->items--;
	if (pq->items == 0)
		pq->rear = NULL;
	return true;
}

// 7. 清空队列 
void EmptyTheQueue(Queue* pq)
{
	Item dummy;
	while (!QueueIsEmpty(pq))
		DeQueue(&dummy, pq);
}

/* 局部函数 */
static void CopyToNode(Item item, Node* pn)
{
	pn->item = item;
}
static void CopyToItem(Node* pn, Item* pi)
{
	*pi = pn->item;
}
```

---
### 3.4 测试队列

```c
/* films3.c -- 使用抽象数据类型（ADT）风格的链表 */
/* 与list.c一起编译 */
#include <stdio.h>
#include <stdlib.h> /* 提供exit()的原型 */
#include "list.h" /* 定义List、Item */
void showmovies(Item item);
char* s_gets(char* st, int n);
int main(void)
{
	List movies;
	Item temp;
	/* 1. 初始化 */
	InitializeList(&movies);
	if (ListIsFull(&movies))
	{
		fprintf(stderr, "No memory available! Bye!\n");
		exit(1);
	}
	
	/* 2. 获取用户输入并储存 */
	puts("Enter first movie title:");
	while (s_gets(temp.title, TSIZE) != NULL && temp.title[0] != '\0') {
		puts("Enter your rating <0-10>:");
		scanf("%d", &temp.rating);
		while (getchar() != '\n')
			continue;
		if (AddItem(temp, &movies) == false)
		{
			fprintf(stderr, "Problem allocating memory\n");
			break;
		}
		if (ListIsFull(&movies))
		{
			puts("The list is now full.");
			break;
		}
		puts("Enter next movie title (empty line to stop) :");
	}
	/* 显示 */
	if (ListIsEmpty(&movies))
		printf("No data entered. ");
	else
	{
		printf("Here is the movie list:\n");
		Traverse(&movies, showmovies);
	}
	printf("You entered %d movies.\n", ListItemCount(&movies)); 
	
	/* 清理 */
	EmptyTheList(&movies);
	printf("Bye!\n");
	return 0;
}
void showmovies(Item item)
{
	printf("Movie: %s Rating: %d\n", item.title, item.rating);
}

char* s_gets(char* st, int n)
{
	char* ret_val;
	char* find;
	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n'); // 查找换行符
		if (find) // 如果地址不是NULL，
			*find = '\0'; // 在此处放置一个空字符
		else
			while (getchar() != '\n')
				continue; // 处理输入行的剩余内容
	} return ret_val;
}
```

---
## 4. 链表与数组

> 区别

- 数组：C 直接支持的数据结构，提供随机访问的能力，但在编译时就确定大小，插入和删除元素很费时

- 链表：在运行时确定大小，有快速插入和删除元素的能力，但不能随便访问，用户必须提供编程实现

> 访问方式

- 对数组而言，可以使用数组下标直接访问该数组中的任意元素，这叫做随机访问（random access）

- 对链表而言，必须从链表首节点开始，逐个节点移动到要访问的节点，这叫做顺序访问（sequential access）。

> 查找

- 数组可以采用下标的方式, 通过二分查找方式查找指定的元素, 但链表只能通过顺序查找的方式遍历, 无法直接获取中间节点的元素

---
## 5. 二叉查找树

- 二叉查找树是一种结合了二分查找策略的链接结构。

- 二叉树的每个节点都包含一个项和两个指向其他节点（称为子节点）的指针。

- 二叉树中的每个节点都包含两个子节点——左节点和右节点，其顺序按照如下规定确定：左节点的项在父节点的项前面，右节点的项在父节点的项后面

- 该树的顶部被称为根（root）。树具有分层组织，所以以这种方式储存的数据也
以等级或层次组织。

- 一般而言，每级都有上一级和下一级。如果二叉树是满的，那么每一级的节点数都是上一级节点数的两倍。

- 二叉查找树中的每个节点是其后代节点的根，该节点与其后代节点构成称了一个子树（subtree）

> 二叉树查找

- 在二叉树中查找一个项（即目标项）。如果目标项在根节点项的前面，则只需查找左子树；如果目标项在根节点项的后面，则只需查找右子树。因此，每次比较就排除半个树。
  
- 假设查找左子树，这意味着目标项与左子节点项比较。如果目标项在左子节点项的前面，则只需查找其后代节点的左半部分，以此类推。与二分查找类似，每次比较都能排除一半的可能匹配项。

- 二叉查找树在链式结构中结合了二分查找的效率

---
### 5.1 二叉树 (ADT)

> 非正式二叉树定义:
  
- 类型名: 二分查找树

* 类型属性: 
  - 二叉树要么是空节点的集合(空树), 要么是有一个根节点的节点集合
  - 每个节点都有两个子树，叫做左子树和右子树; 
  - 每个子树本身也是一个二叉树，也有可能是空树;
  - 二叉查找树是一个有序的二叉树，每个节点包含一个项;
  - 左子树的所有项都在根节点项的前面，右子树的所有项都在根节点项的后面
  
- 类型操作: 
  * 初始化树为空
  * 确定树是否为空
  * 确定树是否已满
  * 确定树中的项数
  * 在树中添加一个项
  * 在树中删除一个项
  * 在树中查找一个项
  * 在树中访问一个项
  * 清空树

---
### 5.2 二叉查找树接口

- 实现二叉查找树最直接的方法是通过指针动态分配链式节点

```c
/* tree.h -- 二叉查找数 */
/* 树中不允许有重复的项 */
#ifndef _TREE_H_
#define _TREE_H_
#include <stdbool.h>
/* 根据具体情况重新定义 Item */
#define SLEN 20
typedef struct item
{
	char petname[SLEN];
	char petkind[SLEN];
} Item;

// 二叉树元素定义
typedef struct trnode
{
	Item item;
	struct trnode* left; /* 指向左分支的指针 */
	struct trnode* right; /* 指向右分支的指针 */
} Trnode;
typedef struct tree
{
	Trnode* root;/* 指向根节点的指针 */
	int size; /* 树的项数 */
	size_t maxSize; /* 树最大可包含项数 */
} Tree;


/* 操作： 把树初始化为空*/
/* 前提条件： ptree 指向一个树 */
/* 后置条件： 树被初始化为空 */
void InitializeTree(Tree* ptree, size_t maxCount);

/* 操作： 确定树是否为空 */
/* 前提条件： ptree指向一个树 */
/* 后置条件： 如果树为空，该函数返回true */
/* 否则，返回false */
bool TreeIsEmpty(const Tree* ptree);

/* 操作： 确定树是否已满 */
/* 前提条件： ptree指向一个树 */
/* 后置条件： 如果树已满，该函数返回true */
/* 否则，返回false */
bool TreeIsFull(const Tree* ptree);

/* 操作： 确定树的项数 */
/* 前提条件： ptree指向一个树 */
/* 后置条件： 返回树的项数 */
int TreeItemCount(const Tree* ptree);

/* 操作： 在树中添加一个项 */
/* 前提条件： pi是待添加项的地址 */
/* ptree指向一个已初始化的树 */
/* 后置条件： 如果可以添加，该函数将在树中添加一个项并返回true；否则，返回false */
bool AddItem(const Item* pi, Tree* ptree);

/* 操作： 在树中查找一个项 */
/* 前提条件： pi指向一个项 */
/* ptree指向一个已初始化的树 */
/* 后置条件： 如果在树中添加一个项，该函数返回true; 否则，返回false */
bool InTree(const Item* pi, const Tree* ptree);

/* 操作： 从树中删除一个项 */
/* 前提条件： pi是删除项的地址 */
/* ptree指向一个已初始化的树 */
/* 后置条件： 如果从树中成功删除一个项，该函数返回true*/
/* 否则，返回false */
bool DeleteItem(const Item* pi, Tree* ptree);

/* 操作： 把函数应用于树中的每一项 */
/* 前提条件： ptree指向一个树 */
/* pfun指向一个函数， */
/* 该函数接受一个Item类型的参数，并无返回
值*/
/* 后置条件： pfun指向的这个函数为树中的每一项执行一次*/
void Traverse(const Tree* ptree, void(*pfun)(Item item));

/* 操作： 删除树中的所有内容 */
/* 前提条件： ptree指向一个已初始化的树 */
/* 后置条件： 树为空 */
void DeleteAll(Tree* ptree);
#endif
```

---
### 5.3 二叉树的实现

> 添加项

- 在树中添加一个项，首先要检查该树是否有空间放得下一个项。其中的项不能重复, 同时也要检查是否有该项

- 创建一个新节点，把待添加项拷贝到该节点中，并设置节点的左指针和右指针都为 NULL

- 更新 Tree 结构的 size 成员，统计新增了一项

- 必须找出应该把这个新节点放在树中的哪个位置, 如果树为空，则应设置根节点指针指向该新节点。否则，遍历树找到合适的位置放置该节点

> 如何确定节点的位置

- 要比较新项和根项，以确定应该把新项放在左子树还是右子树中

- 如果新项是一个数字，则使用 \< 和 \> 进行比较；如果新项是一个字符串，则使用 strcmp() 函数来比较, 根据不同的结构元素需要自行实现比较的函数, 

- 如果新项应放在左子树中，ToLeft() 函数（稍后定义）返回 true；如果新项应放在右子树中，ToRight() 函数（稍后定义）返回 true。

- AddNode() 函数应该把新项和左子节点中的项做比较，以确定新项应该放在该子节点的左子树还是右子树。这个过程一直持续到函数发现一个空子树为止，并在此此处添加新节点。
  
- 递归是一种实现这种查找过程的方法，即把 AddNode() 函数应用于子节点，而不是根节点。当左子树或右子树为空时，即当 root->left 或 root->right 为 NULL 时，函数的递归调用序列结束

> 查找项

- 使用 SeekItem() 函数进行查找, 返回该节点的子父节点指针

- 我们设计 SeekItem() 函数返回的结构包含两个指针：
  * 一个指针指向包含项的节点（如果未找到指定项则为 NULL）；
  * 一个指针指向父节点（如果该节点为根节点，即没有父节点，则为 NULL）。

* SeekItem() 需要使用 ToLeft() 和 ToRight() 在树中导航:
  - SeekItem() 设置 look.child 指针指向该树的根节点，然后沿着目标项应在的路径重置 look.child 指向后续的子树
  - 同时，设置 look.parent 指向后续的父节点。如果没有找到匹配的项，look.child 则被设置为 NULL
  - 如果在根节点找到匹配的项，则设置 look.parent 为 NULL，因为根节点没有父节点

> 删除项

- 删除项是最复杂的任务，因为必须重新连接剩余的子树形成有效的树

- 最简单的情况, 该节点没有子节点 (称为叶节点, leaf), 只需要把父节点中的指针重置为 NULL, 并 free 释放内存

- 删除带有一个子节点的情况, 需要将该节点的子节点与父节点建立连接关系, 将父节点的指针指向它的子节点

- 删除一个带有两个子节点的情况, 其中一个子树（如左子树）可连接在被删除节点之前连接的位置: 
  * 根据树的特征, 当前(子)根节点的左分支都在后面, 右分支都在前面
  * 假设删除节点在父节点左侧, 该节点的左节点可连接在被删除节点的位置, 对于右子树, 只要沿着父节点左子树向下查找
  * 要查看左子树的右支是否右新节点的空位。如果没有，就要沿着左子树的右支向下找，一直找到一个空位为止

> 接口实现

```c
/* tree.c -- 树的支持函数 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/* 局部数据类型 */
typedef struct pair { //储存子父节点的指针
	Trnode* parent;
	Trnode* child;
} Pair;
/* 局部函数的原型 */
static Trnode* MakeNode(const Item* pi);
static bool ToLeft(const Item* i1, const Item* i2);
static bool ToRight(const Item* i1, const Item* i2);
static void AddNode(Trnode* new_node, Trnode* root);
static void InOrder(const Trnode* root, void(*pfun)(Item item));
static Pair SeekItem(const Item* pi, const Tree* ptree);
static void DeleteNode(Trnode** ptr);
static void DeleteAllNodes(Trnode* ptr);

/* 函数定义 */

// 1. 初始化二叉树
void InitializeTree(Tree* ptree, size_t maxCount)
{
	ptree->maxSize = maxCount;
	ptree->root = NULL;
	ptree->size = 0;
}

// 2. 是否为空树
bool TreeIsEmpty(const Tree* ptree)
{
	if (ptree->root == NULL)
		return true;
	else
		return false;
}

// 3. 树是否已满
bool TreeIsFull(const Tree* ptree)
{
	if (ptree->size == ptree->maxSize)
		return true;
	else
		return false;
}

// 4. 树中元素的数目
int TreeItemCount(const Tree* ptree)
{
	return ptree->size;
}

// 5. 添加元素
bool AddItem(const Item* pi, Tree* ptree)
{
	Trnode* new_node;
	// a. 判断是否已满
	if (TreeIsFull(ptree))
	{
		fprintf(stderr, "Tree is full\n");
		return false;			/* 提前返回 */
	}
	// b. 查找目标树是否包含该元素
	if (SeekItem(pi, ptree).child != NULL)
	{
		fprintf(stderr, "Attempted to add duplicate item\n");
		return false;			/* 提前返回 */
	}
	// c. 创建一个新节点
	new_node = MakeNode(pi);	/* 指向新节点 */
	if (new_node == NULL)
	{
		fprintf(stderr, "Couldn't create node\n");
		return false;			/* 提前返回 */
	}
	/* d. 成功创建了一个新节点 */
	ptree->size++;
	if (ptree->root == NULL)	/* 情况1 ： 树为空 */
		ptree->root = new_node;	/* 新节点为树的根节点 */
	else						/* 情况2：树不为空 */
		AddNode(new_node, ptree->root);	/* 在树中添加新节点 */
	return true; /* 成功返回 */
}

// 6. 判断是否包含该元素
bool InTree(const Item* pi, const Tree* ptree)
{
	return (SeekItem(pi, ptree).child == NULL) ?
		false : true;
}

// 7. 删除一个元素
bool DeleteItem(const Item* pi, Tree* ptree)
{
	Pair look;
	look = SeekItem(pi, ptree);
	if (look.child == NULL)
		return false;
	if (look.parent == NULL) /* 删除根节点
	项 */
		DeleteNode(&ptree->root);
	else if (look.parent->left == look.child)
		DeleteNode(&look.parent->left);
	else
		DeleteNode(&look.parent->right);
	ptree->size--;
	return true;
}

// 8. 顺序执行函数
void Traverse(const Tree* ptree, void(*pfun)(Item item))
{
	if (ptree != NULL)
		InOrder(ptree->root, pfun);
}

// 9. 清空树
void DeleteAll(Tree* ptree)
{
	if (ptree != NULL)
		DeleteAllNodes(ptree->root);
	ptree->root = NULL;
	ptree->size = 0;
}

/* 局部函数 */

// 内部: 自左向右遍历树, 对每一项执行函数 pfun
static void InOrder(const Trnode* root, void(*pfun)(Item item)) {
	if (root != NULL)
	{
		InOrder(root->left, pfun);
		(*pfun)(root->item);
		InOrder(root->right, pfun);
	}
}

// 内部: 删除所有节点, 需要遍历整个树, 每个节点释放(自下向顶)
static void DeleteAllNodes(Trnode* root)
{
	Trnode* pright;
	if (root != NULL)
	{
		pright = root->right;
		DeleteAllNodes(root->left);
		free(root);
		DeleteAllNodes(pright);
	}
}

// 内部: 添加一个节点到二叉树
static void AddNode(Trnode* new_node, Trnode* root)
{
	// 判断节点位置
		// a. 左侧比较
	if (ToLeft(&new_node->item, &root->item))
	{
		if (root->left == NULL)		/* 空子树 */
			root->left = new_node;	/* 把节点添加到此处 */
		else    /* 否则处理该子树 */
			AddNode(new_node, root->left); //嵌套处理
	}

	// b. 右侧比较
	else if (ToRight(&new_node->item, &root->item))
	{
		if (root->right == NULL)
			root->right = new_node;
		else
			AddNode(new_node, root->right);
	}

	else /* 不允许有重复项 */
	{
		fprintf(stderr, "location error in AddNode()\n");
		exit(1);
	}
}
// 内部: 比较两个元素, i1 是否在 i2 的左侧.....用户定义比较规则
static bool ToLeft(const Item* i1, const Item* i2)
{
	// 以 petName 排序为基准
	int comp1;
	// 小于
	if ((comp1 = strcmp(i1->petname, i2->petname)) < 0)
		return true;
	// 相等时, 增添比较规则
	else if (comp1 == 0 && strcmp(i1->petkind, i2->petkind) < 0)
		return true;
	// 表示 i1 应该在 i2 的右侧(后面)
	else
		return false;
}

// 内部: 比较两个元素, i1 是否在 i2 的右侧.....用户定义比较规则
static bool ToRight(const Item* i1, const Item* i2)
{
	int comp1;
	if ((comp1 = strcmp(i1->petname, i2->petname)) > 0)
		return true;
	else if (comp1 == 0 && strcmp(i1->petkind, i2->petkind) > 0)
		return true;
	else
		return false;
}

// 内部: 创建一个二叉树元素(分配相应的空间), 并初始化左右节点为空
static Trnode* MakeNode(const Item* pi)
{
	Trnode* new_node;
	new_node = (Trnode*)malloc(sizeof(Trnode));
	if (new_node != NULL)// 检查空间是否分配成功
	{
		new_node->item = *pi; // 连接 item
		new_node->left = NULL;
		new_node->right = NULL;
	} return new_node;
}

// 内部: 查找树中是否包含该元素, 找到将返回该节点的父节点与子节点信息
static Pair SeekItem(const Item* pi, const Tree* ptree)
{
	// a. 先定位根节点, 并把父节点对象置空, 根节点没有父节点
	Pair look;
	look.parent = NULL;
	look.child = ptree->root;

	// b. 检查当前根节点是否为空
	if (look.child == NULL)
		return look; /* 提前返回 */

	// c. 顺着该节点的左右子节点方向开始查找
	while (look.child != NULL)
	{	// 先从左子树开始, 找到时返回它的父子节点(左子节点)
		if (ToLeft(pi, &(look.child->item)))
		{
			look.parent = look.child;
			look.child = look.child->left;
		}

		else if (ToRight(pi, &(look.child->item)))
		{
			look.parent = look.child;
			look.child = look.child->right;
		}
		/* 如果前两种情况都不满足，则必定是相等的情况 */
		else
			break;	/* look.child 目标项的节点 */
	} return look;	/* 成功返回*/
}

// 内部: 删除一个节点, 并释放分配的内存, 需要将删除节点的父节点指针成员地址传入(要修改指针值)
static void DeleteNode(Trnode** ptr)
/* ptr 是指向目标节点的父节点指针成员的地址 */
{
	Trnode* temp;
	/* 假设单条链结构(当前节点只有一个子节点) */
		// a. 右节点存在, 左侧为 NULL
	if ((*ptr)->left == NULL)
	{
		temp = *ptr;
		*ptr = (*ptr)->right;
		free(temp);
	}

	// b. 左侧存在, 右侧为空
	else if ((*ptr)->right == NULL)
	{
		temp = *ptr;
		*ptr = (*ptr)->left;
		free(temp);
	}

	// c 被删除的节点有两个子节点
	else
	{
		/* 找到重新连接右子树的位置, 沿着右节点方向查找空节点的位置 */
		for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right)
			continue;
		temp->right = (*ptr)->right;
		temp = *ptr;
		*ptr = (*ptr)->left;
		free(temp);

		/*
			当前节点的左节点与父节点连接, 右节点在左子树的右分支向下查找空节点, 并与之关联
		*/
	}
}
```

---
### 5.4 使用二叉树

> 向俱乐部成员花名册添加宠物、显示成员列表、报告成员数量、核实成员及退出

```c
/* petclub.c -- 使用二叉查找数 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"
char menu(void);
void addpet(Tree* pt);
void droppet(Tree* pt);
void showpets(const Tree* pt);
void findpet(const Tree* pt);
void printitem(Item item);
void uppercase(char* str);
char* s_gets(char* st, int n);
int main(void)
{
	Tree pets;
	char choice;
	InitializeTree(&pets, 20);
	while ((choice = menu()) != 'q')
	{
		switch (choice)
		{
		case 'a': addpet(&pets);
			break;
		case 'l': showpets(&pets);
			break;
		case 'f': findpet(&pets);
			break;
		case 'n': printf("%d pets in club\n",
			TreeItemCount(&pets));
			break;
		case 'd': droppet(&pets);
			break;
		default: puts("Switching error");
		}
	}
	DeleteAll(&pets);
	puts("Bye.");
	return 0;
}
char menu(void)
{
	int ch;
	puts("Nerfville Pet Club Membership Program");
	puts("Enter the letter corresponding to your choice:");
	puts("a) add a pet l) show list of pets");
	puts("n) number of pets f) find pets");
	puts("d) delete a pet q) quit");
	while ((ch = getchar()) != EOF)
	{
		while (getchar() != '\n') /* 处理输入行的剩余内容 */
			continue;
		ch = tolower(ch);
		if (strchr("alrfndq", ch) == NULL)
			puts("Please enter an a, l, f, n, d, or q:");
		else
			break;
	}
	if (ch == EOF) /* 使程序退出 */
		ch = 'q';
	return ch;
}
void addpet(Tree* pt)
{
	Item temp;
	if (TreeIsFull(pt))
		puts("No room in the club!");
	else
	{
		puts("Please enter name of pet:");
		s_gets(temp.petname, SLEN);
		puts("Please enter pet kind:");
		s_gets(temp.petkind, SLEN);
		uppercase(temp.petname);
		uppercase(temp.petkind);
		AddItem(&temp, pt);
	}
}
void showpets(const Tree* pt)
{
	if (TreeIsEmpty(pt))
		puts("No entries!");
	else
		Traverse(pt, printitem);
}
void printitem(Item item)
{
	printf("Pet: %-19s Kind: %-19s\n",
		item.petname, item.petkind);
}
void findpet(const Tree* pt)
{
	Item temp;
	if (TreeIsEmpty(pt))
	{
		puts("No entries!");
		return; /* 如果树为空，则退出该函数 */
	}
	puts("Please enter name of pet you wish to find:");
	s_gets(temp.petname, SLEN);
	puts("Please enter pet kind:");
	s_gets(temp.petkind, SLEN);
	uppercase(temp.petname);
	uppercase(temp.petkind);
	printf("%s the %s ", temp.petname,
		temp.petkind);
	if (InTree(&temp, pt))
		printf("is a member.\n");
	else
		printf("is not a member.\n");
}
void droppet(Tree* pt)
{
	Item temp;
	if (TreeIsEmpty(pt))
	{
		puts("No entries!");
		return; /* 如果树为空，则退出该函数 */
	}
	puts("Please enter name of pet you wish to delete:");
	s_gets(temp.petname, SLEN);
	puts("Please enter pet kind:");
	s_gets(temp.petkind, SLEN);
	uppercase(temp.petname);
	uppercase(temp.petkind);
	printf("%s the %s ", temp.petname,
		temp.petkind);
	if (DeleteItem(&temp, pt))
		printf("is dropped from the club.\n");
	else
		printf("is not a member.\n");
}
void uppercase(char* str)
{
	while (*str)
	{
		*str = toupper(*str);
		str++;
	}
}
char* s_gets(char* st, int n)
{
	char* ret_val;
	char* find;
	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n'); // 查找换行符
		if (find) // 如果地址不是 NULL，
			*find = '\0'; // 在此处放置一个空字符
		else
			while (getchar() != '\n')
				continue; // 处理输入行的剩余内容
	} return ret_val;
}
```

---
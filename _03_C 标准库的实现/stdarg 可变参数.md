# stdarg.h 可变参数

---
- [stdarg.h 可变参数](#stdargh-可变参数)
- [1. stdarg.h 可变参数](#1-stdargh-可变参数)
- [2. 宏函数定义](#2-宏函数定义)
- [3. 可变参数示例](#3-可变参数示例)

---
# 1. stdarg.h 可变参数

- 当函数中存在可变参数时，```stdarg.h``` 头文件提供了访问可变参数的宏方法
- 在使用 ```va_list``` 之前必须使用 ```va_start``` 初始化；```va_arg``` 用于顺次检索可变参数列表，需要类型顺序已知；```va_end``` 用于释放 ```va_start``` 或 ```va_copy``` 生成的 ```va_list``` 对象
- ```va_copy``` 可用于复制 ```va_start``` 创建的 ```va_list``` 对象

---
# 2. 宏函数定义

- ```va_list```：首次初始化时表示为指向可选参数首元的指针

```c
typedef char* va_list;
```

- ```va_start```：返回一个 ```va_list``` 类型，并传递到第一个可选参数

```c
void __cdecl __va_start(va_list*, ...);

#define va_start(ap, preParam) ((void)(__va_start(&ap, preParam)))
/* ap 必须是一个 va_list 类型，preParam 表示可选参数列表的前一个参数 */
```

- ```va_arg```：从可变参数列表中检索自变量

```c
#define va_arg(ap, type) \
	((sizeof(type) > sizeof(__int64) || (sizeof(type) & (sizeof(type) - 1)) != 0) \
        ? **(type**)((ap += sizeof(__int64)) - sizeof(__int64))             \
        :  *(type* )((ap += sizeof(__int64)) - sizeof(__int64)))
```

- ```va_copy```： 复制当前状态下的参数列表

```c
#define va_copy(destination, source) ((destination) = (source))
```

- ```va_end```：检索所有参数后，重置 ```va_list``` 指针为 ```NULL```；在重置之后使用这些指针的行为是未定义的

```c
#define va_end(ap) ((void)(ap = (va_list)0))
```

# 3. 可变参数示例

```c
/* 可变参数访问案例，可变参数列表类型的顺序必须已知（int，double） */
void _Stdarg_VarParams(int preParam, ...)
{
	va_list args, cargs;
	va_start(args, preParam);
	printf("接收到 Int:%d\n", va_arg(args, int));
	va_copy(cargs, args);	// 复制当前状态下的 args
	printf("接收到 Double:%.2f\n", va_arg(args, double));
	va_end(args);
	printf("接收到 Copy Double:%.2f\n", arg(cargs, double));
	va_end(cargs);
}
/* OUTPUT
	接收到 Int:1
	接收到 Double:5.10
	接收到 Copy Double:5.10
*/
```

---
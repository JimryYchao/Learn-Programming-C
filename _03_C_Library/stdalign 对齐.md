## C 对齐（Alignment）：stdalign.h

`stdalign` 提供类型对齐关键字的便利宏定义。C23 起，不提供任何内容。

---
### Macros

#### alignas、alignof  

```c
#define alignas _Alignas
#define alignof _Alignof
```

`alignas` 用于设置类型的对齐属性，`alignof` 用于查看类型的对齐属性。C23 起从该头文件中移除，`alignas`、`alignof` 将作为 C 关键字。

```c
#include <stdio.h>
#include <stdalign.h>

typedef struct {
	alignas(8) int a;
} book;

int main() {
	book b = {0};
	printf("alignof = %zd\n", _Alignof(book)); // 8
}
```

>---

#### 适用于预处理 `#if` 的宏定义 （从 C23 起移除）

```c
#define __alignas_is_defined 1
#define __alignof_is_defined 1
```

---
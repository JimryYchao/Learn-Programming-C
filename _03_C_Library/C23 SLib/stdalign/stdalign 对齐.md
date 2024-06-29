## C 对齐：stdalign.h

`stdalign` 提供类型对齐关键字的便利宏定义。C23 起弃用。

| Specifier | Description                    |
| :-------- | :----------------------------- |
| `alignas` | 设置类型或结构成员的对齐方式。 |
| `alignof` | 获取类型或结构成员的对齐方式。 |

C23 起从该头文件中移除，`alignas`、`alignof` 将作为 C 关键字。

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

---
## C 常用定义：stddef.h

`stddef.h` 声明了一些常用的类型和宏定义，并在其他文件中引用。

|Specifier|Description|
|:--|:--|
|`ptrdiff_t`|指针差值。|
|`size_t`| `sizeof` 运算符的结果的无符号整数类型。用于 `size_t` 的类型不应具有大于 `unsigned long int` 的整数转换秩。|
`max_align_t` | 一种对象类型，它的对齐是最大的基本对齐。
|`wchar_t`|可以表示在支持的区域设置中指定的最大扩展字符集字符的整数类型。|
`nullptr_t` | 预定义空指针常量 `nullptr` 的类型。可以隐式转换到任何指针类型或 `bool`
`NULL` | 扩展为实现定义的空指针常量。
`unreachable` | 仿函数宏 `unreachable` 的调用表明永远不会采用导致调用的特定流控制。如果在执行期间到达该值，则行为未定义。
`offsetof` | 返回指定类型 `type` 对象的成员（由 `member-designator` 指定）的字节偏移量。成员不能是位域

> offsetof

```c
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdalign.h>

struct S
{
    char c;
    double d[10];
};

int main(void)
{
    printf("the first element is at offset %zu\n", offsetof(typeof(struct S),c));
    
     // member 不限于直接成员，可以是数组成员的元素
    printf("the double is at offset %zu\n", offsetof(typeof(struct S), d[4])); 
}
/*
the first element is at offset 0
the double is at offset 40
*/
```

---
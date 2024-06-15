## C 内联汇编

<!-- TODO -->

---
### 内联汇编

内联汇编（常由 asm 关键词引入）给予在 C 程序中嵌入汇编语言源代码的能力，不同的 C 编译器拥有差异巨大的汇编声明规则。不同于 C++ 中，内联汇编在 C 中被当作扩展。它是条件性支持及由实现定义的，意思是它可以不存在，而且即使实现有所提供，它也并不拥有固定的含义。

汇编声明可出现于块（函数体或其他复合语句）内，而且同所有其他声明，此声明亦可出现于块外。

> GCC 内联汇编

```c
#include <stdio.h>

extern int func(void);
// func 的定义以汇编语言书写
__asm__(".globl func\n\t"
        ".type func, @function\n\t"
        "func:\n\t"
        ".cfi_startproc\n\t"
        "movl $7, %eax\n\t"
        "ret\n\t"
        ".cfi_endproc");

int main(void)
{
    int n = func();
    // gcc 的扩展内联汇编
    __asm__ ("leal (%0,%0,4),%0"
           : "=r" (n)
           : "0" (n));

    printf("7*5 = %d\n", n);
    fflush(stdout); // 冲刷是有意的

    // C++ 中的标准内联汇编
    __asm__ ("movq $60, %rax\n\t" // Linux 上的 “退出” 的系统调用序号
             "movq $2,  %rdi\n\t" // 此程序返回 2
             "syscall");
}
```

---
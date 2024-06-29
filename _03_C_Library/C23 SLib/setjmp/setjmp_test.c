#include <stdio.h>
#include <setjmp.h>

// noreturn (c23)
[[noreturn]] void jump(jmp_buf env, int count)
{
    printf("Jump count = %d\n", count);
    longjmp(env, count + 1); // 将在 setjmp 中返回 count+1
}

static volatile int count = 0; 
int main(void)
{
    jmp_buf env;
    if (setjmp(env) < 10)
        jump(env, count++);
}
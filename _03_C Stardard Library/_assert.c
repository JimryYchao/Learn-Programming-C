#include <stdio.h>

// #define NDEBUG    // 取消断言库诊断
#include <assert.h>

#define ASSERT_FAILED "assert failed."

int test(void);

int test(void)
{
    puts("========== assert.h ==========");
    assert(1 == 1);
    assert(1 > 2);

    static_assert(1 == 1, ASSERT_FAILED);
    // static_assert(1 > 2, ASSERT_FAILED);  // 静态断言不受 NDEBUG 宏影响
}

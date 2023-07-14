#include "_test_head.h"
#define NDEBUG // 取消 assert 断言功能，静态断言不受影响
#include <assert.h>

static void Test_Undef_Assert();
static void Test_Def_Assert();
static void Test_StaticAssert();

static void Test_C_Lib()
{
    Test_Undef_Assert();

    Test_Def_Assert();
}

void Test_Undef_Assert()
{
    assert(2 > 1);
    assert(1 > 2);
    Test_StaticAssert();
}

#undef NDEBUG // 恢复断言
#include <assert.h>

void Test_Def_Assert()
{
    assert(2 > 1);
    assert(1 > 2);  // Assertion failed!
    Test_StaticAssert();
}

void Test_StaticAssert()
{
    // static_assert(1 > 2, "static_assert failed."); // failed
    static_assert(2 > 1, "static_assert successful.");
}

int main(int argc, char const *argv[])
{
    Test_C_Lib();

    return 0;
}

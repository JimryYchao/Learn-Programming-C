// #define NDEBUG    // ȡ�����Կ����
#include <assert.h>

#define ASSERT_FAILED "assert failed."

int test(void);

int test(void) {

	assert(1 == 1);
	assert(1 > 2);

	static_assert(1 == 1, ASSERT_FAILED);
	// static_assert(1 > 2, ASSERT_FAILED);  // ��̬���Բ��� NDEBUG ��Ӱ��
}
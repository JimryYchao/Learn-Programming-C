#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdint.h>

// struct book
// {
//    intmax_t
// };

int main(void)
{
    printf("%zu\n", alignof(WCHAR_MAX));

    size_t a = _Alignof(max_align_t);
    printf("Alignment of max_align_t is %zu (%#zx)\n", a, a);

    void *p = malloc(123);
    printf("The address obtained from malloc(123) is %#" PRIxPTR "\n",
           (uintptr_t)p);
    free(p);
}
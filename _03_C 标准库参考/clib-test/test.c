#include <stdbool.h>
#include <stdlib.h>

size_t hash(char const[static 32]) [[reproducible]] {}

int main()
{
    (void)hash(NULL);
}
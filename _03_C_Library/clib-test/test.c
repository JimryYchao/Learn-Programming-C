#include <stdbool.h>
#include <stdlib.h>

int main()
{
    int arr[10] = {};

    for (size_t i = 0; i < 10;)
    {
        arr[i] = i;
        i++;
    }

    return arr[10 - 1];
}
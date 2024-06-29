#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>

void show_errno(void)
{
    const char *err_info = "unknown error";
    switch (errno)
    {
    case EDOM:
        err_info = "domain error";
        break;
    case EILSEQ:
        err_info = "illegal sequence";
        break;
    case ERANGE:
        err_info = "pole or range error";
        break;
    case 0:
        err_info = "no error";
    }
    fputs(err_info, stdout);
    puts(" occurred");
}

int main(void)
{
    1.0 / 0.0;
    show_errno(); // no error occurred

    acos(+1.1);
    show_errno(); // domain error occurred

    log(0.0);
    perror("log(0.0)"); // log(0.0): Result too large

    float a = sqrtf(-1);
    printf(strerror(errno)); // Domain error
}
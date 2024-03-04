#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signal_handler(int signal)
{
    printf("Received signal %d\n", signal);
}

int Raise(int sig)
{
    printf("Sending signal %d\n", sig);
    return raise(sig);
}

int main(void)
{
    /* 安装信号处理函数。 */
    if (signal(SIGBREAK, signal_handler) == SIG_ERR)
    {
        printf("Error while installing a signal handler.\n");
        exit(EXIT_FAILURE);
    }

    if (Raise(SIGINT) != 0)
    {
        printf("Error while raising the SIGTERM signal.\n");
        exit(EXIT_FAILURE);
    }

    printf("Exit main()\n");
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
 
void signal_handler(int signal)
{
    printf("signal %d\n", signal);
}
 
int main(void)
{
    /* 安装信号处理函数。 */
    if (signal(SIGTERM, signal_handler) == SIG_ERR)
    {
        perror("Error while installing a signal handler: ");
        exit(EXIT_FAILURE);
    }
 
    if (raise(SIGTERM) != 0)   // signal 15
    {
        printf("Error while raising the SIGTERM signal.\n");
        exit(EXIT_FAILURE);
    }

    signal(SIGABRT, signal_handler);
    abort();  // signal 22
}
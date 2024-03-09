#pragma once

typedef int sig_atomic_t;

#define SIG_DFL
#define SIG_ERR
#define SIG_IGN

#define SIGABRT
#define SIGFPE
#define SIGILL
#define SIGINT
#define SIGSEGV
#define SIGTERM

void (*signal(int sig, void (*func)(int)))(int);
int raise(int sig);
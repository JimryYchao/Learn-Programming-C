#pragma once

#define __STDC_VERSION_TIME_H__         202311L


typedef long        clock_t;
typedef long long    time_t; 

struct timespec        
{
    time_t tv_sec;            
    signed int tv_nsec;
};

struct tm         
{
    int tm_sec;   
    int tm_min;   
    int tm_hour;  
    int tm_mday;  
    int tm_mon;   
    int tm_year;  
    int tm_wday;  
    int tm_yday;  
    int tm_isdst; 
};

#define NULL                ((void*)0)
#define CLOCKS_PER_SEC      ((clock_t)1000)
#define TIME_UTC

#define TIME_MONOTONIC
#define TIME_ACTIVE
#define TIME_THREAD_ACTIVE

clock_t clock(void);
double difftime(time_t time1, time_t time0);
time_t mktime(struct tm *timeptr);
time_t timegm(struct tm *timeptr);
time_t time(time_t *timer);
int timespec_get(struct timespec *ts, int base);
int timespec_getres(struct timespec *ts, int base);
[[deprecated]] char *asctime(const struct tm *timeptr);
[[deprecated]] char *ctime(const time_t *timer);
struct tm *gmtime(const time_t *timer);
struct tm *gmtime_r(const time_t *timer, struct tm *buf);
struct tm *localtime(const time_t *timer);
struct tm *localtime_r(const time_t *timer, struct tm *buf);
size_t strftime(char * restrict s, size_t maxsize, const char * restrict format, const struct tm * restrict timeptr);
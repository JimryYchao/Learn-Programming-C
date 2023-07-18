#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

static void Test_errno();
static void Test_Macros();

void Test_errno()
{
  errno = 0;
  1.0 / 0.0;
  Test_Macros();

  errno = 0;
  acos(+1.1);
  Test_Macros();

  errno = 0;
  log(0.0);
  Test_Macros();

  errno = 0;
  sin(0.0);
  Test_Macros();
}
void Test_Macros()
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
  Test_errno();
  return 0;
}
/*
  no error occurred
  domain error occurred
  pole or range error occurred
  no error occurred
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char pass[80];

void m(void)
{
  printf("%s - %d\n", pass, time(0));
  return;
}

int main(int argc,char **argv)
{
  char *a;
  char *b;
  FILE *f;

  a = (char *)malloc(8);
  *a = 1;
  b = (char *)malloc(8);
  *b = 2;

  strcpy(a[1], argv[1]);
  strcpy(b);
  f = fopen("/home/user/level8/.pass","r");
  fgets(pass, 68, f);
  puts("~~");
  return 0;
}
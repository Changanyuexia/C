#include <stdio.h>

int main(void)
{
  int i =127;
  char str[3];
  sprintf(str,"%d",i);
  printf("%s\n",str );
  return 0;
}

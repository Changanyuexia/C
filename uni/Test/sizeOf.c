#include <stdio.h>

int main(void)
{
  int A[10];
  printf("charachter   size :%ld\n",sizeof(char));
  printf("Ucharachter  size :%ld\n",sizeof(unsigned char));
  printf("short        size :%ld\n",sizeof(short int));
  printf("integer      size :%ld\n",sizeof(int));
  printf("long         size :%ld\n",sizeof(long int));
  printf("float        size :%ld\n",sizeof(float));
  printf("double       size :%ld\n",sizeof(double));
  printf("intA[10]_(A) size :%ld\n",sizeof(A));
  printf("intA[10]_(A) size :%ld\n",sizeof(A[0]));
  return 0;
}

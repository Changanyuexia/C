#include <stdio.h>
#include <assert.h>

int main(void)
{
   int i=2,j;
   scanf("%d",&j);
   assert(i==j);
   printf("i = %d, j = %d",i,j);
   return(0);
}

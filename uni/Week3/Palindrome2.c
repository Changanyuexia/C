#include <stdio.h>
#include <ctype.h>

#define LENGTH 100

int main(void)
{
   int i;
   char c;
   char a[100];
   memset(a,0,sizeof(a));
   while((c = getchar()) !=EOF){
      printf("%d\n",a[i]);
      
      i++;
  }
  return(0);
}

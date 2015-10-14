/* aDDUP Evens of fIBONACCI SEQUENCE*/
#include <stdio.h>

#define MAX_I 4000000

int main(void)
{
   int x=1, y=2, sum=0;
   while(y<MAX_I && x<MAX_I){
   if(x%2==0){sum+=x;}
   if(y%2==0){sum+=y;}
   printf("x:%9d --- y:%9d --- sum:%9d\n",x ,y ,sum);
   x+=y;
   y+=x;
   }   
printf("%d \n ",sum);
return(0);
}

/* Euler Project Problem 1
   Find the sum of all the 
   multiples of 3 or 5 below 1000. */
#include <stdio.h>

#define MAX_I 1000

int main(void)
{
   int i,sum=0;
   for(i=1;i<MAX_I;i++){
     if(i%3==0 || i%5==0){
     sum +=i;
     }
   }
printf("%d \n ",sum);
return(0);
}

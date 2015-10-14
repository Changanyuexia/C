/*Hailstone Sequence*/
/*User inputs a number which is used as the 
initial of the Hailstone Sequence*/

#include <stdio.h>

#define REPEAT_N 8

int main(void)
{
   int n,i=0;
   printf("Please input sequence's initial number ");
     if(scanf("%d",&n) == 1){
     printf("%d\n",n);
       while(i<REPEAT_N){
         if(n%2 == 0){n=n/2;  printf("%d\n",n);}
         if(n%2 == 1){n=3*n+1; printf("%d\n",n);} 
         ++i;
       }
     }
     else{printf("Please input positive integer only\n");}
     return(0);
}

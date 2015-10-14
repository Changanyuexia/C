/* A program that sums three integers, input by the user,
   and then adds 7 and returns the result               */

#include <stdio.h>
int main(void)
{
   int a, b, c;
   printf("Input three integers: \n");
   scanf("%i %i %i", &a, &b, &c);
   printf("Twice the sum of integers plus 7 is %i !\n", 2*(a+b+c)+7);
   return(0);
}

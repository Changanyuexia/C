/*A program that finds the largest number from user input---only integers*/
#include <stdio.h>

int main(void)
{
   int x, i, max, temp;
   x = i = max = temp = 0; 
   printf("How many odd integers do you wish to enter? ");
   scanf("%d",&x);
   while(i<x)
   {
   scanf("%d" , &temp);
   if(temp % 2 == 1 && temp>max){max=temp;}
   i++;
   }
   printf("Maximum value: %d\n",max);
 return(0);
}

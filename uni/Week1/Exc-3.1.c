/*A program that finds the largest number from user input*/
#include <stdio.h>

int main(void)
{
   int x=0,i=0;
   float max=0, temp=0;
   printf("How many numbers do you wish to enter? ");
   scanf("%d",&x);
   while(i<x)
   {
   scanf("%f" , &temp);
   if(temp>max){max=temp;}
   i++;
   }
   printf("Maximum value: %.2f\n",max);
 return(0);
}

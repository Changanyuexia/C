#include <stdio.h>

#define DIVISOR 20

int isPossible (int a, int b);
int smallerAlt(int a, int b);
int largerAlt(int a, int b);

int main(void)
{
   int money, decision, alt1, alt2;
   do {
      printf("How much money would you like ? ");
         if(scanf("%d", &money)!=1){
            printf("Program exits unable to scan number\n");
            return(0);
         }
      decision = isPossible(money, DIVISOR);
         if(decision==1){
            printf("OK Dispencing...\n");
         }
         if(decision==0){
           alt1=smallerAlt(money, DIVISOR);
           alt2=largerAlt(money, DIVISOR);
           printf("I can give you %d or %d, try again\n", alt1, alt2);
         }
      else{
      printf("Program exits unable to scan number\n");
      return(0);
      }
    }
      while(decision==0||decision==1);
      return(0);
}

int isPossible(int a, int b)
{
   if(a%b==0 && a>=0){
      return(1);
   }
   else if(a<0){
     return(-1);
   }
   else{
      return(0);
   }
}

int smallerAlt(int a, int b)
{
  int temp;
  temp = a%b;
  return(a-temp);
}

int largerAlt(int a, int b)
{
  int temp;
  temp = a%b;
  return(a-temp+b);
}

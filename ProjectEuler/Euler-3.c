/* aDDUP Evens of fIBONACCI SEQUENCE*/
#include <stdio.h>
#include <string.h>


#define N_DIVIDEND 600851475143

int isprime(long int a);
int isfactor(long int a);

int main(void)
{
   long int y=1,result=0;
   /*char s[20];*/

   while(y<N_DIVIDEND){
     if (isfactor(y)&&isprime(y)){
    /*
         if(){
           result=y;
           strcpy(s,"is prime");
         }
         else{
           strcpy(s,"is not prime");
         }*/
         printf("N_DIVIDEND:%ld --- y:%9ld --- \n",N_DIVIDEND ,y);
        /* break;
       default:
       break;
*/
     }
     if(!(y%1000000000))
     printf("%ld%c\n",100*y/N_DIVIDEND,'%' );
   y++;
   }
printf("%ld %ld\n ",N_DIVIDEND,result);
return(0);
}
int isprime(long int a)
{
   long int i=2;
   int cnt=0;

   while(i<a){
     if(a%i == 0){
     cnt++;
     }
     i++;
   }
   if(cnt==0){
   return(1);
   }
   else{
     return(0);
   }
}

int isfactor(long int a)
{
  if(!(N_DIVIDEND%a)){
    return 1;
  }
  else{
    return 0;
  }
}

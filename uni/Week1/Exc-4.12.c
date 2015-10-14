/*Prime Numbers from i=1 to user_input*/
#include <stdio.h>

#define FIRST_PRIME 2

int isprime(int a);

int main(void)
{
   int i, x, y, cnt=0;
   printf("\nhello from np\n How many prime numbers do you wish me to calculate? \n");
   scanf("%d", &x);
     for(i=FIRST_PRIME;i>cnt;i++){
     y=isprime(i);   
       if (y != 0 ){
       printf("%d \n", y);
       cnt++;
       }
       if(cnt==x){
       return(0);
       }
 
     }
   return(0);
}

int isprime(int a)
{
   int i=FIRST_PRIME, cnt=0;
 
   while(i<a){
     if(a%i == 0){
     cnt++;
     }
     i++;     
   }   
   if(cnt==0){
   return(a);
   }
   else{return(0);}
}


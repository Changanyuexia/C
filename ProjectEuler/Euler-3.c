/* aDDUP Evens of fIBONACCI SEQUENCE*/
#include <stdio.h>

#define MAX_I 4000000

int isprime(int a);

int main(void)
{
   int x=13195, y=1;
      
   while(y<x){
     switch (x%y){
       case 0:
         printf("x:%9d --- y:%9d\n",x ,y);
         break;
       default:
       break;
     }
   y++;
   }
y=isprime(y);   
if(y>0){
printf("%d %d\n ",x,y);
}
return(0);
}
int isprime(int a)
{
   int i=2, cnt=0;
 
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

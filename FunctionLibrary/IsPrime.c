#define FIRST_PRIME 2

/*Takes and number and returns it if it's Prime*/
/*returns 0 if it's not*/
int isprime(int a);

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

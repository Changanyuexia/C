#include <stdio.h>
#include <ctype.h>

#define LENGTH 100


int main(void)
{
   int i=0,j=0,k=0;
   char c;
   char a[100];
   while((c = getchar()) !='\n'){
      i++;
      a[i]=c;
      printf("a[%d] = %d\n",i,a[i]);

  }
printf("%d\n",i );
/*if(i%2==0){*/
for(j=1;j<=i/2;j++){
  a[j]-=a[i-j+1];
printf("%d\n",a[j] );
}
/*}*/
for(j=1;j<=i/2;j++){
if(a[j!=0]){
  k++;

}
}
if(k==0){
  printf("it is a palindrome\n" );
}
else{printf("it is not a palindrome\n");}
  return(0);
}

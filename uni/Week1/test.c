#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
  int i,ball;
  delay(100);
  for(i=0;i<10;i++){
    printf("%d\n",i);
  }
  for(i=0;i<10;i++){
    ball=rand() % 10;
    printf("%d\n",ball);}
 return(0);
}

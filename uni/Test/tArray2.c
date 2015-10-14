#include <stdio.h>

#define H 9
#define W 9

int main(void)
{
   int i, j;
   int A[H][W];
   int *p;
   p=A;
   for (i=0;i<W;i++){
      for(j=0;j<H;j++){
         A[j][i]=0;
      }
   }
   A[0][W/2]=1;
      for (j=0;j<H;j++){
         for(i=0;i<W;i++){
            printf("%4d",A[j][i]);
        }
        printf("\n");
      }
   /*printf("\n");
      for (i=0;i<W*H;i++){
         printf("%4d",*((A+i));
         if((i+1)%W==0){
            printf("\n");
      }
   }*/
   printf("\n");
      for (i=0;i<W*H;i++){
         printf("%4d",*p++);
         if((i+1)%W==0){
            printf("\n");
         }
      }
      p=A;
   printf("\n");
      for (i=0;i<W*H;i++){
         printf("%4d",*(p+i));
         if((i+1)%W==0){
            printf("\n");
         }
      }
   printf("\n");
   return(0);
}

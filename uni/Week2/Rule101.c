#include <stdio.h>

#define H 9
#define W 9

int main(void)
{
   int i, j, sum;
   int A[H][W];
   int *p;
   p=A;
   /*Set array = 0*/
   for (i=0;i<W;i++){
      for(j=0;j<H;j++){
         A[j][i]=0;
      }
   }
   /*Set one cell value=1*/
   A[0][W/2]=1;
   printf("\n");
      for (i=0;i<W*H;i++){
         printf("%4d",*p++);
         if((i+1)%W==0){
            printf("\n");
         }
      }
      p=A;
   printf("\n");
   /*algorhythm*/
   for (i=W;i<W*H;i++){
     sum=*(p-W+i)+*(p-W+i+1)+*(p-W+i+2);
      if(sum==2||sum==1){
        *(p+i)=1;
      }

      printf("%4d",*(p+i));
      if((i+1)%W==0){
         printf("\n");
      }
   }
   p=A;
   printf("\n");
   /*print NEW array*/
   for (i=0;i<W*H;i++){
      printf("%4d",*p++);
      if((i+1)%W==0){
         printf("\n");
      }
   }
   p=A;
printf("\n");
   return(0);
}

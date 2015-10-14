#include <stdio.h>

#define H 30
#define W 34

int main(void)
{
   int i, j, sum;
   int A[H][W];
   /*Set array = 0*/
      for(j=0;j<H;j++){
         for (i=0;i<W;i++){
         A[j][i]=0;
         }
      }
   /*Set one cell value=1*/
   A[0][W-1-3]=1;

   printf("\n");
     for(j=0;j<H;j++){
       for (i=0;i<W;i++){
          printf("%2d",A[j][i]);
       }
    printf("\n");
    }
    printf("\n");
   /*algorhythm*/
      for(j=1;j<H;j++){
   for (i=1;i<W-1;i++){
     sum=A[j-1][i-1]+A[j-1][i]+A[j-1][i+1];
         if(sum==3||sum==0||sum==1&&A[j-1][i-1]==1){
            A[j][i]=0;
         }
         else {A[j][i]=1;}
       }
    }
   printf("\n");
   /*print NEW array*/
      for(j=0;j<H;j++){
   for (i=0;i<W;i++){
           printf("%2d",A[j][i]);
      }
      printf("\n");
  }

   return(0);
}

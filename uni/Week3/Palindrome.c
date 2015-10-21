/*--Checks if a string is a palindrome--*/
/*has commented code block for repeated file testing*/
/*outputs to screen and file*/
#include <stdio.h>
#include <ctype.h>

#define LENGTH 100


int main(void)
{
   int i=0,j=0,k=0;
   char c;
   char a[100];
   FILE *fp;
   /*start block code for file testing*//*
   for(times=0;times<5;times++){
     for (i=0;i<100;i++){
       a[i]=0;
     }
     i=0;
     printf("----------------------------%d\n",times );
     /*end code forfile testing remaining "}"at the end*/
    fp= fopen("outfile.txt", "w");

      while((c = getchar()) !='\n'){
         if(isalpha((int)c)){
         i++;
         a[i]=c;
         /*printing to screen*/
         printf("a[%d] = %d\n",i,a[i]);
         /*printing to file*/
         fprintf(fp,"a[%d] = %d\n",i,a[i]);
         }
     }
          /*printing to screen*/
      printf("%d\n",i );
      /*printing to file*/
      fprintf(fp,"%d\n",i );
      for(j=1;j<=i/2;j++){
         a[j]-=a[i-j+1];
         printf("a[%d]=%d\n",j,a[j] );
         fprintf(fp,"a[%d]=%d\n",j,a[j] );
      }
      for(j=1;j<=i/2;j++){
         if(a[j]!=0){
            k++;
            printf("k=%d\n", k);
            fprintf(fp,"k=%d\n", k);
         }
      }
      if(k==0){
         printf("it is a palindrome\n" );
         fprintf(fp,"it is a palindrome\n" );
      }
      else{
         printf("it is not a palindrome\n");
         fprintf(fp,"it is not a palindrome\n");
      }
  /* }*/
  fclose(fp);
  return(0);
}

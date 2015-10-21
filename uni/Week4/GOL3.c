#include <stdio.h>

#define HEIGHT             25
#define WIDTH              50
#define AREA HEIGHT*WIDTH
#define MAX_FILE          120

void fFillArray(int *p,FILE *fp);
void zFillArray(int *p);
void printBoardX(void);
void printArray(int p[HEIGHT][WIDTH]);
void printArrayz(int p[HEIGHT][WIDTH]);
void nextStep(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH]);
void mySleep(int a);

int main (int argc, char **argv)
{
   int i=1,iNum;
   int a[HEIGHT][WIDTH], b[HEIGHT][WIDTH];
   char *fName, *iter;
   int *p;
   FILE *fp;
  if( argc==3 ){
     fName=argv[1];
     iter=argv[2];
     sscanf(iter, "%d",&iNum);
     printf("Your agv input is %s\n%d\n%d\n", argv[1],iNum,iter[2]);
   fp= fopen(fName, "r");
   p=a[0];
   zFillArray(p);
     p=b[0];
   zFillArray(p);
     p=a[0];
   fFillArray(p,fp);
   fclose(fp);
     p=a[0];
   printf("ARRAY A\n");
   printArrayz(a);
     p=a[0];
     while(i<=iNum){
   /*WHERE THE ARRAY PROCESS HAPPENS*/
mySleep(1);
   nextStep(a,b);
   printf("ARRAY [%d]\n",i);
   p=b[0];
   printArrayz(b);

   /*WHERE THE ARRAY PROCESS HAPPENS--again*/
mySleep(1);
    nextStep(b,a);
   printf("ARRAY [%d]\n",i+1);
     p=a[0];
   printArrayz(a);
     i+=2;
   }
return(0);
 }
return(0);
}
void nextStep(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH])
{
   int j,i,sum;
      for(i=0;i<HEIGHT;i++){
         for(j=0;j<WIDTH;j++){
               sum = p[i][j+1]+p[i][j-1]+       /*summing cells right-left  */
                     p[i+1][j]+p[i-1][j]+       /*summing cells up-down     */
                     p[i-1][j+1]+p[i-1][j-1]+   /*summing cells right-left  */
                     p[i+1][j+1]+p[i+1][j-1];   /*summing cells right-left  */
         switch (p[i][j]) {
            case 0:

               switch (sum){
                  case 3:
                     q[i][j]=1;
                     break;
                  default:
                     q[i][j]=0;
                     break;
               }
               break;

            case 1:
               switch (sum){
                  case 2:
                  case 3:
                     q[i][j]=1;
                     break;
                  default:
                     q[i][j]=0;
                     break;
               }
           break;
        }
     }
   }
}
void zFillArray(int *p)
{
  int i;
  for(i=0;i<AREA;i++){
     *p++=0;
  }
}
void printArray(int p[HEIGHT][WIDTH])
{
   int j,i;
      for(i=0;i<HEIGHT;i++){
         for(j=0;j<WIDTH;j++){
            printf("%d",p[i][j]);
         }
printf("\n" );
      }
   printf("\n\n" );

}

void printArrayz(int p[HEIGHT][WIDTH])
{
   int j,i;
   printBoardX();
      for(i=0;i<HEIGHT;i++){
         for(j=0;j<WIDTH;j++){
            if(p[i][j]==0){printf("   ");}
            if(p[i][j]==1){printf(" * ");}
         }
printf("\n%d",i+1 );
      }
   printf("\n\n" );

}
void fFillArray(int *p,FILE *fp)
{
   int i,x,y;
   for(i=0;i<14;i++){
      if(fscanf(fp,"%d%d",&x,&y)!=2){
         printf("ERRORGRANERROR\n");
      }
      *(p+(x-1)+WIDTH*(y-1))=1;
   }
}
void printBoardX(void)
{
   int i;
   for(i=1;i<=WIDTH;i++){
      printf("%3d",i);
   }
   printf("\n");
}
void mySleep(int a)
{
   int i;
      for(i=0;i<a*50000000;i++){}
}

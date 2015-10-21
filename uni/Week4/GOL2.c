#include <stdio.h>
#include <stdlib.h>

#define HEIGHT             25
#define WIDTH              30
#define AREA HEIGHT*WIDTH
#define MAX_FILE          120

void fFillArray(int *p,FILE *fp);
void zFillArray(int *p);
void printArray(int *p);
void putAsses(int *p);
void nextStep(int *p, int *q);



int main (int argc, char **argv)
{
   int i=1,iNum;
   int a[HEIGHT][WIDTH], b[HEIGHT][WIDTH];
   char *fName, *iter;
   int *p, *q;
   FILE *fp;
  if( argc==3 ){
     fName=argv[1];
     iter=argv[2];
     sscanf(iter, "%d",&iNum);
     printf("Your agv input is %s\n%d\n%d\n", argv[1],iNum,iter[2]);
   fp= fopen(fName, "r");
   p=a[0];
   q=b[0];
   zFillArray(p);
     p=a[0];
   zFillArray(q);
     q=b[0];
   fFillArray(p,fp);
   fclose(fp);
     p=a[0];
   printf("ARRAY A\n");
   printArray(p);
     p=a[0];
     while(i<=iNum){
   /*WHERE THE ARRAY PROCESS HAPPENS*/
sleep(1);
   nextStep(p,q);
   printf("ARRAY [%d]\n",i);
   printArray(q);
     q=b[0];

   /*WHERE THE ARRAY PROCESS HAPPENS--again*/
sleep(1);
   nextStep(q,p);
     p=a[0];
     q=b[0];
   printf("ARRAY [%d]\n",i+1);
   printArray(p);
     p=a[0];
     i+=2;
   }
return(0);
 }
return(0);
}
void nextStep(int *p, int *q)
{
   int j;
   for(j=0;j<AREA;j++){
      switch (*p) {
         case 0:
            switch (*(p+1)+*(p-1)+ *(p-HEIGHT)+ *(p+HEIGHT)+ *(p-HEIGHT-1)+ *(p+HEIGHT-1)+ *(p-HEIGHT+1)+ *(p+HEIGHT+1)){
              case 3:
                 *q=1;
                 break;
              default:
                 *q=0;
                 break;
            }
            break;

        case 1:
           switch (*(p+1)+*(p-1)+ *(p-HEIGHT)+ *(p+HEIGHT)+
           *(p-HEIGHT-1)+ *(p+HEIGHT-1)+ *(p-HEIGHT+1)+ *(p+HEIGHT+1)){
              case 2:
              case 3:
              *q=1;
              break;
              default:
              *q=0;
              break;
            }
           break;
     }
     p++;
     q++;
   }
}
void zFillArray(int *p)
{
  int i;
  for(i=0;i<AREA;i++){
     *p++=0;
  }
}
void printArray(int *p)
{
  int i;
  for(i=0;i<AREA;i++){

     printf("%d",*p++ );

     if((i+1)%HEIGHT==0){printf("\n");}
  }
     printf("\n\n" );

}
void putAsses(int *p)
{
   int i;
   for(i=0;i<AREA;i++){
   if(i==7||i==12||i==17){*(p)=1;}
   p++;
}
}

void fFillArray(int *p,FILE *fp)
{
   int i,x,y;
   for(i=0;i<14;i++){
      if(fscanf(fp,"%d%d",&y,&x)!=2){
         printf("ERRORGRANERROR\n");
      }
      *(p+(x-1)+HEIGHT*(y-1))=1;
   }
}

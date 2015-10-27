#include <stdio.h>

#define HEIGHT             18
#define WIDTH              40
#define H            HEIGHT-1
#define W             WIDTH-1
#define AREA     HEIGHT*WIDTH
#define MAX_FILE          120
#define SLEEP_T      50000000
#define POINTS            100
/*#include "video.c"*/

int sumSpecial(int i, int j, int p[HEIGHT][WIDTH]);
void fFillArrayz(int p[HEIGHT][WIDTH],FILE *fp);
void zFillArray(int p[HEIGHT][WIDTH]);
void zFillArrayz(int p[HEIGHT][WIDTH]);
void printBoardX(void);
void printArray(int p[HEIGHT][WIDTH]);
void printArrayz(int p[HEIGHT][WIDTH]);
void nextStep(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH], int sum[HEIGHT][WIDTH]);
void calculateNeighb(int p[HEIGHT][WIDTH], int upper[HEIGHT][WIDTH], int lower[HEIGHT][WIDTH],
  int left[HEIGHT][WIDTH], int right[HEIGHT][WIDTH], int uRight[HEIGHT][WIDTH], int uLeft[HEIGHT][WIDTH]);
void mySleep(int a);


struct life {
  int self[HEIGHT][WIDTH], left[HEIGHT][WIDTH], right[HEIGHT][WIDTH], upper[HEIGHT][WIDTH];
  int lower[HEIGHT][WIDTH], upperLeft[HEIGHT][WIDTH], upperRight[HEIGHT][WIDTH];
  int lowerLeft[HEIGHT][WIDTH], lowerRigth[HEIGHT][WIDTH], sum[HEIGHT][WIDTH];
};


int main (int argc, char **argv)
{
   int i,j,iNum;
   struct life a;
   struct life b;
   char *fName, *iter;
   FILE *fp;

      if( argc==3 ){
         fName=argv[1];
         iter=argv[2];
         sscanf(iter, "%d",&iNum);
         printf("Your agv input is %s\n%d\n%d\n", argv[1],iNum,iter[2]);
      }
      else{
         printf("Your agv input is unknown");
         return(0);
      }
   fp= fopen(fName, "r");
   for(i=0;i<HEIGHT;i++){
      for(j=0;j<WIDTH;j++){
         a.self[i][j]=0;
         b.self[i][j]=0;
       }
   }
   fFillArrayz(a.self,fp);
   fclose(fp);
   printf("ARRAY A\n");
   printArray(a.self);
   i=0;
     while(i<iNum){
   /*WHERE THE ARRAY PROCESS HAPPENS*/
mySleep(1);
   calculateNeighb(a.self,b.upper,b.lower,b.left,b.right,b.upperRight,b.upperLeft);
   printf("ARRAY [upper]\n");

   printArray(b.upper);
   printf("ARRAY [lower]\n");

   printArray(b.lower);

   printf("ARRAY [left]\n");

   printArray(b.left);

      printf("ARRAY [right]\n");

      printArray(b.right);

            printf("ARRAY [upperRight]\n");

            printArray(b.upperRight);
   nextStep(a.self,b.self,b.sum);
   printf("ARRAY [%d]\n",i);
   printArrayz(b.self);
   i++;
}
return(0);
}
void nextStep(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH], int sum[HEIGHT][WIDTH])
{
   int j,i;
      for(i=0;i<HEIGHT;i++){
         for(j=0;j<WIDTH;j++){
      sum[i][j] = sumSpecial(i,j,p);
         switch (p[i][j]) {
            case 0:
               switch (sum[i][j]){
                  case 3:
                     q[i][j]=1;
                     break;
                  default:
                     q[i][j]=0;
                     break;
               }
               break;
            case 1:
               switch (sum[i][j]){
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

void calculateNeighb(int p[HEIGHT][WIDTH], int upper[HEIGHT][WIDTH], int lower[HEIGHT][WIDTH],
   int left[HEIGHT][WIDTH], int right[HEIGHT][WIDTH], int uRight[HEIGHT][WIDTH], int uLeft[HEIGHT][WIDTH])
{
   int i,j;
      for(i=0;i<HEIGHT;i++){
         for(j=0;j<WIDTH;j++){
                 upper[i][j]=p[i-1][j];
                 lower[i][j]=p[i+1][j];
                 left[i][j]=p[i][j-1];
                 right[i][j]=p[i][j+1];
                 uLeft[i][j]=p[i-1][j-1];
                 uRight[i][j]=p[i-1][j+1];
            switch (i) {
               case 0:
                  upper[i][j]=p[H][j];
                  uRight[i][j]=p[H][j+1];
                     switch(j){
                       case 0:
                          left[i][j]=p[i][W];
                          break;
                       case W:
                          right[i][j]=p[i][0];
                          uRight[i][j]=p[H][0];
                          break;
                     }
                  break;
               case H:
                 lower[i][j]=p[0][j];
                 switch(j){
                   case 0:

                      left[i][j]=p[i][W];
                      break;
                   case W:
                      right[i][j]=p[i][0];
                      uRight[i][j]=p[i-1][0];
                      break;
                 }
                 break;
               default:
               switch(j){
                 case 0:

                    left[i][j]=p[i][W];
                    break;
                 case W:
                    right[i][j]=p[i][0];
                    break;
                 default:
                    break;
               }

                  break;
           }
         }
      }
}
void zFillArray(int p[HEIGHT][WIDTH])
{
  int i,j;
     for(i=0;i<HEIGHT;i++){
        for(j=0;j<WIDTH;j++){
           p[i][j]=0;
        }
     }
}

void printArray(int p[HEIGHT][WIDTH])
{
   int j,i;
   printBoardX();
      for(i=0;i<HEIGHT;i++){
         for(j=0;j<WIDTH;j++){
            printf("%2d",p[i][j]);
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
printf("%d",i);
         for(j=0;j<WIDTH;j++){
            if(p[i][j]==0){printf("   ");}
            if(p[i][j]==1){printf(" * ");}
         }
printf("\n");
      }
   printf("\n\n" );

}

void fFillArrayz(int p[HEIGHT][WIDTH],FILE *fp)
{
   int i,x,y;
   for(i=0;i<POINTS;i++){
      if(fscanf(fp,"%d%d",&x,&y)!=2){
         printf("ERRORGRANERROR\n");
      }
      p[y][x]=1;
   }
}
void printBoardX(void)
{
   int i;
   for(i=0;i<WIDTH;i++){
      printf("%2d",i);
   }
   printf("\n");
}

int sumSpecial(int i, int j, int p[HEIGHT][WIDTH])
{
   int sum;
   switch (i) {
      case 0:
         switch (j) {
            case 0:
               sum = p[i][j+1]+p[i][WIDTH-1]+       /*summing cells right-left  */
               p[i+1][j]+p[HEIGHT-1][j]+       /*summing cells up-down     */
               p[HEIGHT-1][j+1]+p[HEIGHT-1][WIDTH-1]+   /*summing cells right-left  */
               p[i+1][j+1]+p[i+1][WIDTH-1];   /*summing cells right-left  */
               break;
            case WIDTH-1:
               sum = p[i][0]+p[i][j-1]+       /*summing cells right-left  */
               p[i+1][j]+p[HEIGHT-1][j]+       /*summing cells up-down     */
               p[HEIGHT-1][0]+p[HEIGHT-1][j-1]+   /*summing cells right-left  */
               p[i+1][0]+p[i+1][j-1];   /*summing cells right-left  */
               break;
            default:
               sum = p[i][j+1]+p[i][j-1]+       /*summing cells right-left  */
               p[i+1][j]+p[HEIGHT-1][j]+       /*summing cells up-down     */
               p[HEIGHT-1][j+1]+p[HEIGHT-1][j-1]+   /*summing cells right-left  */
               p[i+1][j+1]+p[i+1][j-1];   /*summing cells right-left  */
              break;
        }
         break;
      case HEIGHT-1:
      switch (j) {
        case 0:
            sum =
            p[i][j+1]+p[i][WIDTH-1]+       /*summing cells right-left  */
            p[0][j]+p[i-1][j]+       /*summing cells up-down     */
            p[i-1][j+1]+p[i-1][WIDTH-1]+   /*summing cells right-left  */
            p[0][j+1]+p[0][WIDTH-1];   /*summing cells right-left  */
            break;
         case WIDTH-1:
            sum =
            p[i][0]+p[i][j-1]+       /*summing cells right-left  */
            p[0][j]+p[i-1][j]+       /*summing cells up-down     */
            p[i-1][0]+p[i-1][j-1]+   /*summing cells right-left  */
            p[0][0]+p[0][j-1];   /*summing cells right-left  */
            break;
         default:
           sum =
           p[i][j+1]+p[i][j-1]+       /*summing cells right-left  */
           p[0][j]+p[i-1][j]+       /*summing cells up-down     */
           p[i-1][j+1]+p[i-1][j-1]+   /*summing cells up right-left  */
           p[0][j+1]+p[0][j-1];   /*summing cells down right-left  */
           break;
}
      default:
         sum =
         p[i][j+1]+p[i][j-1]+       /*summing cells right-left  */
         p[i+1][j]+p[i-1][j]+       /*summing cells up-down     */
         p[i-1][j+1]+p[i-1][j-1]+   /*summing cells right-left  */
         p[i+1][j+1]+p[i+1][j-1];   /*summing cells right-left  */
         break;
}
   return(sum);
}

void mySleep(int a)
{
   int i;
      for(i=0;i<a*SLEEP_T;i++){}
}

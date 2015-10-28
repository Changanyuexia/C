/*last version*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT                      90
#define WIDTH                       150
#define TEAM_ONE                     1
#define TEAM_TWO                    10
#define DEAD_CELL                    0
#define H                   (HEIGHT-1)
#define W                    (WIDTH-1)
#define AREA            (HEIGHT*WIDTH)
#define MAX_FILE                   120
#define SLEEP_T               500000000
#define POINTS                     100
#define TEAM_ONE_TWO      (2*TEAM_ONE)
#define TEAM_ONE_THREE    (3*TEAM_ONE)
#define TEAM_TWO_TWO      (2*TEAM_TWO)
#define TEAM_TWO_THREE    (3*TEAM_TWO)

time_t t;

int sumSpecial(int i, int j, int p[HEIGHT][WIDTH]);
int overspill(int i, int a);
void zFillArraySmart(int p[HEIGHT][WIDTH], int player);
void arrayCopy(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH]);
void arraySum(int p [HEIGHT][WIDTH],int a);
int fFillArray(int p[HEIGHT][WIDTH],FILE *fp, int a);
void zFillArray(int p[HEIGHT][WIDTH]);
void printBoardX(void);
void printArray(int p[HEIGHT][WIDTH]);
void printArrayz(int p[HEIGHT][WIDTH]);
void nextStep2(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH], int sum[HEIGHT][WIDTH]);
void mySleep(int a);

struct life {
  int self[HEIGHT][WIDTH], left[HEIGHT][WIDTH], right[HEIGHT][WIDTH], upper[HEIGHT][WIDTH];
  int lower[HEIGHT][WIDTH], upperLeft[HEIGHT][WIDTH], upperRight[HEIGHT][WIDTH];
  int lowerLeft[HEIGHT][WIDTH], lowerRigth[HEIGHT][WIDTH], sum[HEIGHT][WIDTH];
};

int main (int argc, char **argv)
{
   int i=0,iNum;
   struct life a;
   struct life b;
   char *fName1, *fName2, *iter;
   FILE *fp1, *fp2;
   if( argc==4 ){
      fName1=argv[1];
      fName2=argv[2];
      iter=argv[3];
      sscanf(iter, "%d",&iNum);
      printf("Your agv input is %s\n%d\n%d\n", argv[1],iNum,iter[2]);
   }
   else{
      printf("Your agv input is unknown");
      return(0);
   }
   zFillArray(a.self);
   zFillArray(b.self);
   while(i<2){
   i=0;
     fp1= fopen(fName1, "r");
     printf("file1open\n");
     fp2= fopen(fName2, "r");
     printf("file2open\n");
      zFillArraySmart(a.self,TEAM_ONE);
   i+=fFillArray(a.self, fp1, TEAM_ONE);
   fclose(fp1);
   printf("file1close\n");
      zFillArraySmart(a.self,TEAM_TWO);
   i+=fFillArray(a.self, fp2, TEAM_TWO);
      fclose(fp2);
            printf("file2close\n");
   }
   printf("reaches printfirstarray" );
   printf("ARRAY A\n");
   printf("reches hanfle while loop\n");
   /*printArrayz(a.self);*/
     while(i<=iNum){
   /*WHERE THE ARRAY PROCESS HAPPENS*/
   mySleep(50000000);
   nextStep2(a.self,b.self,b.sum);
   /*printArray(b.sum);*/
   printf("ARRAY [%d]\n",i);
   printArrayz(b.self);
   arraySum(b.self,TEAM_ONE);
   arraySum(b.self,TEAM_TWO);
   arrayCopy(b.self,a.self);
   i++;
   }
return(0);
 }
 void zFillArraySmart(int p[HEIGHT][WIDTH], int player)
 {
    int i,j;
       for(i=0;i<HEIGHT;i++){
          for(j=0;j<WIDTH;j++){
             if(p[i][j]==player){
                p[i][j]=0;
             }
          }
       }
 }
void nextStep2(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH], int sum[HEIGHT][WIDTH])
{
   int j,i;
      for(i=0;i<HEIGHT;i++){
         for(j=0;j<WIDTH;j++){
            sum[i][j] = sumSpecial(i,j,p);
               switch (p[i][j]) {
                  case DEAD_CELL:
                     if(sum[i][j] == TEAM_ONE_THREE){
                        q[i][j]=TEAM_ONE;
                     }
                     else if(sum[i][j] == TEAM_TWO_THREE){
                        q[i][j]=TEAM_TWO;
                     }
                     else{
                        q[i][j]=DEAD_CELL;
                     }
                     break;
                  case TEAM_ONE:
                     if (sum[i][j]==TEAM_ONE_TWO||sum[i][j]==TEAM_ONE_THREE){
                        q[i][j]=TEAM_ONE;
                     }
                     else{
                        q[i][j]=DEAD_CELL;
                     }
                     break;
                  case TEAM_TWO:
                     if (sum[i][j]==TEAM_TWO_TWO||sum[i][j]==TEAM_TWO_THREE){
                        q[i][j]=TEAM_TWO;
                     }
                     else{
                        q[i][j]=DEAD_CELL;
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
      for(i=0;i<HEIGHT;i++){
         for(j=0;j<WIDTH;j++){
            printf("%3d",p[i][j]);
         }
printf("\n" );
      }
   printf("\n\n" );

}
void arraySum(int p[HEIGHT][WIDTH],int a)
{
  int i,j,sum=0;
  for(i=0;i<HEIGHT;i++){
     for(j=0;j<WIDTH;j++){
        if(p[i][j]==a){
        sum++;
        }
     }
   }
   if(a==TEAM_ONE){
     printf("Team One Score: %d \n", sum);
   }
   if(a==TEAM_TWO){
     printf("Team Two Score: %d \n", sum);
   }
}
void printArrayz(int p[HEIGHT][WIDTH])
{
   int j,i;
   printBoardX();
      for(i=0;i<HEIGHT;i++){
         printf("%3d",i+1 );
         for(j=0;j<WIDTH;j++){
            if(p[i][j]==DEAD_CELL){printf(" ' ");}
            if(p[i][j]==TEAM_ONE){printf (" * ");}
            if(p[i][j]==TEAM_TWO){printf (" X ");}
         }
         printf("\n");
      }
   printf("\n\n" );

}
int fFillArray(int p[HEIGHT][WIDTH],FILE *fp, int a)
{
   int i,x,y,xOrigin,yOrigin,xFin,yFin;
srand((unsigned) time(&t)+rand());
   xOrigin=rand()%WIDTH;
   yOrigin=rand()%HEIGHT;
   fscanf(fp,"#Life1.06");
   for(i=0;i<POINTS;i++){
           printArrayz(p);
           mySleep(500000);
      if(fscanf(fp,"%d%d",&x,&y)!=2){
         printf("EOF\n");
         return(1);
      }
      printf("x0:%d\n",xOrigin+x+1 );
      printf("y0:%d\n",yOrigin+y+1 );
      xFin=overspill(xOrigin+x,WIDTH);
      yFin=overspill(yOrigin+y,HEIGHT);

      printf("reacheddeadcellcontol\n");
      if(p[yFin][xFin]==DEAD_CELL){
         p[yFin][xFin]=a;
         printf("a[%d][%d] is dead\n",yFin+1,xFin+1 );
      }
      else if(p[yFin][xFin]!=DEAD_CELL){
         printf("a[%d][%d] is dead\n",yFin+1,xFin+1 );
        return(0);}
   }
   return(1);
}
void printBoardX(void)
{
   int i;
   printf("  ");
   for(i=1;i<=WIDTH;i++){
      printf("%3d",i);
   }
   printf("\n");
}
int sumSpecial(int i, int j, int p[HEIGHT][WIDTH])
{
int iUp, iLow, jLeft, jRight, sum;
   i=overspill(i,HEIGHT);
   iUp=overspill(i-1,HEIGHT);
   iLow=overspill(i+1,HEIGHT);
   j=overspill(j,WIDTH);
   jLeft=overspill(j-1,WIDTH);
   jRight=overspill(j+1,WIDTH);

  sum =
  p[i][jRight]+p[i][jLeft]+       /*summing cells right-left  */
  p[iLow][j]+p[iUp][j]+       /*summing cells up-down     */
  p[iUp][jRight]+p[iUp][jLeft]+   /*summing cells right-left  */
  p[iLow][jRight]+p[iLow][jLeft];   /*summing cells right-left  */

   return(sum);
}
int overspill(int i, int max)
{
  int division;
    division=i/(max-1);
  if (i>(max-1)){
    i-=(division*(max));
  }
  if (i<0){i+=(max);}
  return (i);
}
void arrayCopy(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH])
{
   int i,j;
      for(i=0;i<HEIGHT;i++){
         for(j=0;j<WIDTH;j++){
           q[i][j]=p[i][j];
         }
      }
}
void mySleep(int a)
{
   int i,j;
      for(i=0;i<a*SLEEP_T;){
      j=i+1;
        i=j;
    }
}
/*void nextStep(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH], int sum[HEIGHT][WIDTH])
{
   int j,i;
      for(i=0;i<HEIGHT;i++){
         for(j=0;j<WIDTH;j++){
            sum[i][j] = sumSpecial(i,j,p);
               switch (p[i][j]) {
                  case DEAD_CELL:
                     switch (sum[i][j]){
                        case TEAM_ONE_THREE:
                           q[i][j]=TEAM_ONE;
                           break;
                        case TEAM_TWO_THREE:
                           q[i][j]=TEAM_TWO;
                           break;
                        default:
                           q[i][j]=DEAD_CELL;
                        break;
                     }
                     break;
                  case TEAM_ONE:
                     switch (sum[i][j]){
                        case 2:
                        case 3:
                           q[i][j]=TEAM_ONE;
                           break;
                        default:
                           q[i][j]=DEAD_CELL;
                           break;
                     }
                     break;
                  case TEAM_TWO:
                     switch (sum[i][j]){
                        case TEAM_TWO_TWO:
                        case TEAM_TWO_THREE:
                           q[i][j]=TEAM_TWO;
                           break;
                        default:
                           q[i][j]=DEAD_CELL;
                           break;
                        }
                        break;
               }
         }
      }
}
*/

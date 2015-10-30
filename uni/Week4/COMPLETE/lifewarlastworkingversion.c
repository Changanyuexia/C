/*last version*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT                      90
#define WIDTH                      150
#define TEAM_ONE                     1
#define TEAM_TWO                    10
#define DEAD_CELL                    0
#define H                     HEIGHT-1
#define W                      WIDTH-1
#define AREA              HEIGHT*WIDTH
#define MAX_FILE                   120
#define SLEEP_T               50000000
#define POINTS                     100
#define TEAM_ONE_TWO        2*TEAM_ONE
#define TEAM_ONE_THREE      3*TEAM_ONE
#define TEAM_TWO_TWO        2*TEAM_TWO
#define TEAM_TWO_THREE      3*TEAM_TWO

void arrayCopy(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH]);
void arraySum(int p [HEIGHT][WIDTH],int a);
int fFillArray(int p[HEIGHT][WIDTH],FILE *player, int a);
void zFillArray(int p[HEIGHT][WIDTH]);
void zFillArraySmart(int p[HEIGHT][WIDTH], int player);
void nextStep(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH], int sum[HEIGHT][WIDTH]);
int sumSpecial(int i, int j, int p[HEIGHT][WIDTH]);
int overspill(int i, int max);



struct life {
  int self[HEIGHT][WIDTH], sum[HEIGHT][WIDTH];
};

int main (int argc, char **argv)
{
   int i=0,iNum;
   struct life a;
   struct life b;
   char *fName1, *fName2;
   FILE *player1, *player2;
   if( argc==4 ){
      fName1=argv[1];
      fName2=argv[2];
      /*iteration=argv[3];*/
      sscanf(argv[3], "%d",&iNum);
   }
   else{
      printf("Unable to input you 'arguments'");
      return(0);
   }
   zFillArray(a.self);
   zFillArray(b.self);
   while(i<2){
      i=0;
      player1= fopen(fName1, "r");
      player2= fopen(fName2, "r");
      zFillArraySmart(a.self,TEAM_ONE);
      i+=fFillArray(a.self, player1, TEAM_ONE);
      fclose(player1);
      zFillArraySmart(a.self,TEAM_TWO);
      i+=fFillArray(a.self, player2, TEAM_TWO);
      fclose(player2);
   }
   i=0;
   while(i<=iNum){
   /*WHERE THE WAR HAPPENS*/
      nextStep(a.self,b.self,b.sum);
      arraySum(b.self,TEAM_ONE);
      arraySum(b.self,TEAM_TWO);
      arrayCopy(b.self,a.self);
      i++;
   }
   return(0);
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
int fFillArray(int p[HEIGHT][WIDTH],FILE *player, int a)
{
   int i,x,y,xOrigin,yOrigin,xFin,yFin;
   time_t t;
   srand((unsigned) time(&t)+rand());
   xOrigin=rand()%WIDTH;
   yOrigin=rand()%HEIGHT;
   fscanf(player,"#Life1.06");
   for(i=0;i<POINTS;i++){
      if(fscanf(player,"%d%d",&x,&y)!=2){
         printf("EOF\n");
         return(1);
      }
      printf("x0:%d\n",xOrigin+x+1 );
      printf("y0:%d\n",yOrigin+y+1 );
      xFin=overspill(xOrigin+x,WIDTH);
      yFin=overspill(yOrigin+y,HEIGHT);
      if(p[yFin][xFin]==DEAD_CELL){
         p[yFin][xFin]=a;
      }
      else if(p[yFin][xFin]!=DEAD_CELL){
        return(0);}
   }
   return(1);
}

void nextStep(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH], int sum[HEIGHT][WIDTH])
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
  p[i][jRight]+p[i][jLeft]+         /*summing cells right-left  */
  p[iLow][j]+p[iUp][j]+             /*summing cells up-down     */
  p[iUp][jRight]+p[iUp][jLeft]+     /*summing cells right-left  */
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
void arrayCopy(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH])
{
   int i,j;
      for(i=0;i<HEIGHT;i++){
         for(j=0;j<WIDTH;j++){
           q[i][j]=p[i][j];
         }
      }
}

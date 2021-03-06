#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SLEEP_T                11000000
#define HEIGHT                      70
#define WIDTH                      110
#define TOTAL_GAMES                 50
#define TEAM_ONE                     1
#define TEAM_TWO                    10
#define DEAD_CELL                    0
#define GENERATIONS               5000
#define H                     HEIGHT-1
#define W                      WIDTH-1
#define AREA              HEIGHT*WIDTH
#define MAX_FILE                   120
#define POINTS                     100
#define TEAM_ONE_2          2*TEAM_ONE
#define TEAM_ONE_3          3*TEAM_ONE
#define TEAM_TWO_2          2*TEAM_TWO
#define TEAM_TWO_3          3*TEAM_TWO

void printBoardX(void);
void printArray(int p[HEIGHT][WIDTH]);
void printArrayz(int p[HEIGHT][WIDTH]);
void mySleep(int a);
/*last version*/
void arrayCopy(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH]);
int arraySum(int p [HEIGHT][WIDTH], int team);
/*Seeds the board from a file    */
int fileFillBoard(int p[HEIGHT][WIDTH], FILE *player, int team);
void zeroFillArray(int p[HEIGHT][WIDTH]);
/* Resets all cells belonging to input player */
void zeroFillArraySmart(int p[HEIGHT][WIDTH], int player);
void nextStep(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH], int sum[HEIGHT][WIDTH]);
int sumNeighbours(int i, int j, int p[HEIGHT][WIDTH]);
int overspill(int coordinate, int max);


struct life {
   int self[HEIGHT][WIDTH], sum[HEIGHT][WIDTH];
};
struct score {
   int score, win[GENERATIONS];
};

int main (int argc, char **argv)
{
   int i = 0, games = 0;
   char *winner;
   struct life board, temporary;
   struct score p1, p2;
   char *fName1, *fName2;
   FILE *player1, *player2;
   p1.score = p2.score = 0;
   if( argc == 3 ){
      fName1 = argv[1];
      fName2 = argv[2];
   }
   else{
      printf("Unable to input you 'arguments'");
      return(0);
   }
   while (games<TOTAL_GAMES){
      zeroFillArray(board.self);
      zeroFillArray(temporary.self);
      while(i<2){
         i=0;
         player1= fopen(fName1, "r");
         zeroFillArray(board.self);
         i+=fileFillBoard(board.self, player1, TEAM_ONE);
         fclose(player1);
         player2= fopen(fName2, "r");
         i+=fileFillBoard(board.self, player2, TEAM_TWO);
         fclose(player2);
      }
      i=0;
      /*WHERE THE WAR HAPPENS*/
      while(i<=GENERATIONS){
         nextStep(board.self,temporary.self,temporary.sum);
         arrayCopy(temporary.self,board.self);
         printArrayz(temporary.self);
         mySleep(2);
         i++;
      }
      i=0;
      p1.score += arraySum(temporary.self,TEAM_ONE);
      p2.score += arraySum(temporary.self,TEAM_TWO);
      if(p1.score > p2.score){
         winner="Player 1";
      }
      else if(p1.score < p2.score){
         winner = "Player 2";
      }
      else{
         winner = "Tie";
      }
      printf("%2d %5d %5d %s\n", games, p1.score, p2.score, winner );
      games++;
      }
      if(p1.score == p2.score){
         winner = "Nobody";
      }
      printf("%s wins by %d cells to %d cells\n",
winner,p1.score,p2.score );
      return(0);
}
void zeroFillArray(int p[HEIGHT][WIDTH])
{
   int i,j;
   for(i=0; i<HEIGHT; i++){
      for(j=0; j < WIDTH; j++){
         p[i][j] = 0;
      }
   }
}
void zeroFillArraySmart(int p[HEIGHT][WIDTH], int player)
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
int fileFillBoard(int p[HEIGHT][WIDTH],FILE *player, int team)
{
   int i,x,y,xOrigin,yOrigin,xFin,yFin;
   time_t t;
   srand((unsigned) time(&t)+rand());
   xOrigin=rand()%WIDTH;
   yOrigin=rand()%HEIGHT;
   fscanf(player,"#Life 1.06");
   for(i=0;i<=POINTS;i++){
      if(fscanf(player,"%d%d",&x,&y)!=2){
         return(1);
      }
      xFin=overspill(xOrigin+x,WIDTH);
      yFin=overspill(yOrigin+y,HEIGHT);
      if(p[yFin][xFin]==DEAD_CELL){
         p[yFin][xFin]=team;
      }
      else if(p[yFin][xFin]!=DEAD_CELL){
        return(0);
      }
   }
   return(1);
}
void nextStep(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH], int sum[HEIGHT][WIDTH])
{
   int j,i;
      for(i=0;i<HEIGHT;i++){
         for(j=0;j<WIDTH;j++){
            sum[i][j] = sumNeighbours(i,j,p);
               switch (p[i][j]) {
                  case DEAD_CELL:
                     if(sum[i][j] == TEAM_ONE_3 || sum[i][j] == (TEAM_ONE_2 + TEAM_TWO)){
                        q[i][j]=TEAM_ONE;
                     }
                     else if(sum[i][j] == TEAM_TWO_3 || sum[i][j] == (TEAM_ONE + TEAM_TWO_2)){
                        q[i][j]=TEAM_TWO;
                     }
                     else{
                        q[i][j]=DEAD_CELL;
                     }
                     break;
                  case TEAM_ONE:
                     if (sum[i][j]==TEAM_ONE_2||sum[i][j]==TEAM_ONE_3){
                        q[i][j]=TEAM_ONE;
                     }
                     else{
                        q[i][j]=DEAD_CELL;
                     }
                     break;
                  case TEAM_TWO:
                     if (sum[i][j]==TEAM_TWO_2||sum[i][j]==TEAM_TWO_3){
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
int sumNeighbours(int i, int j, int p[HEIGHT][WIDTH])
{
   int iUp, iLow, jLeft, jRight, sum;
   i      = overspill(i,  HEIGHT);
   iUp    = overspill(i-1,HEIGHT);
   iLow   = overspill(i+1,HEIGHT);
   j      = overspill(j,  WIDTH);
   jLeft  = overspill(j-1,WIDTH);
   jRight = overspill(j+1,WIDTH);
   sum =
   p[i][jRight]+p[i][jLeft]+         /*summing cells right-left  */
   p[iLow][j]+p[iUp][j]+             /*summing cells up-down     */
   p[iUp][jRight]+p[iUp][jLeft]+     /*summing cells right-left  */
   p[iLow][jRight]+p[iLow][jLeft];   /*summing cells right-left  */
   return(sum);
}
int overspill(int coordinate, int max)
{
   int division;
   division=coordinate/(max-1);
   if (coordinate>(max-1)){
      coordinate-=(division*(max));
   }
   if (coordinate<0){
     coordinate+=(max);
   }
   return (coordinate);
}
int arraySum(int p[HEIGHT][WIDTH],int player)
{
   int i,j,sum=0;
   for(i=0;i<HEIGHT;i++){
      for(j=0;j<WIDTH;j++){
         if(p[i][j]==player){
         sum++;
         }
      }
   }
   return(sum);
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

void printArrayz(int p[HEIGHT][WIDTH])
{
   int j,i;
   printBoardX();
      for(i=0;i<HEIGHT;i++){
         printf("%2d",i+1 );
         for(j=0;j<WIDTH;j++){
            if(p[i][j]==DEAD_CELL){printf("  ");}
            if(p[i][j]==TEAM_ONE){printf (" *");}
            if(p[i][j]==TEAM_TWO){printf (" X");}
         }
         printf("\n");
      }
   printf("\n\n" );

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
void mySleep(int a)
{
   int i,j;
      for(i=0;i<a*SLEEP_T;){
      j=i+1;
        i=j;
    }
}

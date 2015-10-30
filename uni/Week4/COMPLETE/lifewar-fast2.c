#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT                      90
#define WIDTH                      150
#define TOTAL_GAMES                 50
/* I assign team one number 1 and team two number 10
so that the sumNeighbour switch doesn't get clashing cases*/
#define TEAM_ONE                     1
#define TEAM_TWO                    10
#define DEAD_CELL                    0
#define GENERATIONS               5000
#define MAX_FILE                   120
#define POINTS                     100
#define TEAM_ONE_2          2*TEAM_ONE
#define TEAM_ONE_3          3*TEAM_ONE
#define TEAM_TWO_2          2*TEAM_TWO
#define TEAM_TWO_3          3*TEAM_TWO

void zeroFillArray(int p[HEIGHT][WIDTH]);
int  fileFillBoard(int p[HEIGHT][WIDTH], FILE *player, int team);
void nextStep(int p[HEIGHT][WIDTH], int q[HEIGHT][WIDTH], int sum[HEIGHT][WIDTH]);
int  sumNeighbours(int i, int j, int p[HEIGHT][WIDTH]);
int  overspill(int coordinate, int max);
int  scoreSum(int p [HEIGHT][WIDTH], int team);
void scorePrint(int scoreP1, int scoreP2, int games);

struct life {
   int self[HEIGHT][WIDTH], sum[HEIGHT][WIDTH];
};

time_t t;

int main (int argc, char **argv)
{
   int i =0, games =0, timer;
   struct life boardA, boardB;
   int scoreP1 =0, scoreP2 =0;
   char *fName1, *fName2;
   FILE *player1, *player2;
   if( argc == 3 ){
      fName1 = argv[1];
      fName2 = argv[2];
   }
   else{
      printf("Unable to input your 'arguments'\n");
      return(0);
   }
   timer=t;
   while (games<TOTAL_GAMES){
      zeroFillArray(boardA.self);
      zeroFillArray(boardB.self);
      i=0;
      /*File Input */
      while(i<2){
         i = 0;
         player1 = fopen(fName1, "r");
         zeroFillArray(boardA.self);
         i += fileFillBoard(boardA.self, player1, TEAM_ONE);
         fclose(player1);
         player2 = fopen(fName2, "r");
         i += fileFillBoard(boardA.self, player2, TEAM_TWO);
         fclose(player2);
      }
      i=1;
      timer=t-timer;
      printf("%ds passed until game begins\n",timer );
      /*WHERE THE WAR HAPPENS*/
      while(i < GENERATIONS/2){
         /*Instead of copying the board to a temporary
         array it oscilates between two boards--FASTER */
         nextStep(boardA.self, boardB.self, boardB.sum);
         nextStep(boardB.self, boardA.self, boardA.sum);
         i++;
      }
   scoreP1+=scoreSum(boardA.self, TEAM_ONE);
   scoreP2+=scoreSum(boardA.self, TEAM_TWO);
   scorePrint( scoreP1, scoreP2, games);
   games++;
   timer=t-timer;
   printf("%ds passed until game ends\n",timer );
   }
   return(0);
}
/*FUNCTIONS*/
void scorePrint(int scoreP1, int scoreP2, int games)
{
   char *winner;
   if(scoreP1 > scoreP2){
      winner="Player 1";
   }
   else if(scoreP1 < scoreP2){
      winner = "Player 2";
   }
   else{
      winner = "Tie";
   }
   printf("%2d %5d %5d %s\n", games, scoreP1, scoreP2, winner );
   if(scoreP1 == scoreP2){
      winner = "Nobody";
   }
   if(games == TOTAL_GAMES-1){
      printf("%s wins by %d cells to %d cells\n", \
winner,scoreP1,scoreP2 );
  }
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
int fileFillBoard(int p[HEIGHT][WIDTH],FILE *player, int team)
{
   int i,x,y,xOrigin,yOrigin,xFin,yFin;
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
                     if (sum[i][j] == TEAM_ONE_3 ||
                         sum[i][j] == (TEAM_ONE_2 + TEAM_TWO)){
                        q[i][j]=TEAM_ONE;
                     }
                     else if (sum[i][j] == TEAM_TWO_3 ||
                              sum[i][j] == (TEAM_ONE + TEAM_TWO_2)){
                        q[i][j]=TEAM_TWO;
                     }
                     else{
                        q[i][j]=DEAD_CELL;
                     }
                     break;
                  case TEAM_ONE:
                     if (sum[i][j] == TEAM_ONE_2 ||
                         sum[i][j] == TEAM_ONE_3){
                        q[i][j]=TEAM_ONE;
                     }
                     else{
                        q[i][j]=DEAD_CELL;
                     }
                     break;
                  case TEAM_TWO:
                     if (sum[i][j] == TEAM_TWO_2 ||
                         sum[i][j]==TEAM_TWO_3){
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
   i      = overspill(i,  HEIGHT);   /*Checking if coordinates*/
   iUp    = overspill(i-1,HEIGHT);   /*fall outside the board*/
   iLow   = overspill(i+1,HEIGHT);   /*and assigns them the */
   j      = overspill(j,  WIDTH);    /*equivalent inside the board*/
   jLeft  = overspill(j-1,WIDTH);
   jRight = overspill(j+1,WIDTH);
   sum = p[i][jRight]+p[i][jLeft]+   /*summing cells right-left  */
   p[iLow][j]+p[iUp][j]+             /*summing cells up-down     */
   p[iUp][jRight]+p[iUp][jLeft]+     /*summing cells up, right-left  */
   p[iLow][jRight]+p[iLow][jLeft];   /*summing cells lright-left  */
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
int scoreSum(int p[HEIGHT][WIDTH],int player)
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

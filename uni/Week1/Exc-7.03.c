#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 35
#define INITIAL_BAN 100
#define WIN_EXACT 32
#define WIN_FIFTY 2
#define LOSE -1

int isbankrupt(int a);
int winCheck (int a, int b, int c);

int main(void)
{
   int betnum, ball;
   int bet=1;
   int bankroll = INITIAL_BAN;
   time_t t;

   printf("Welcome to the Roulette Game\n"
           "Your initial Bankroll is %d GBP\n"
           "Please place your bet (0-%d) or 40 -even,41 -odd, \nnegative to end game\n",INITIAL_BAN,MAX_NUM);
   while(bankroll>0 && betnum >= 0){

       scanf("%d", &betnum);
     

   /* Intializes random number generator */
   /*The following line of code has been
     copied from "www.tutorialspoint.com"
     rand() example library              */
     srand((unsigned) time(&t));
   ball=rand() % 36;
     printf("The ball stopped on number: %d\n", ball);
    bankroll += winCheck(ball, betnum, bet);
     printf("Current Bankroll : %d\n", bankroll);
   }
     if(!bankroll>0){
        printf("You are bankrupt, GAMeOVER!\n");
        return(0);
     }
     else{printf("You left the game\n");}
   return(0);
   }

int winCheck (int a, int b, int c){
   if(b == a){
     printf("!!!you WON %d times your bet!!!--- %d GBP\n",WIN_EXACT ,c*WIN_EXACT);
     return(WIN_EXACT*c);
   }
   if(b==40 && a%2==0){
     printf("!!!you WON %d times your bet!!!--- %d GBP\n",WIN_FIFTY, c*WIN_FIFTY );
     return(WIN_FIFTY*c);
   }
   if(b==41 && a%2!=0){
     printf("!!!you WON %d times your bet!!!--- %d GBP\n",WIN_FIFTY, c*WIN_FIFTY );
     return(WIN_FIFTY*c);
   }
   if(b>=36 && b!=40 && b!=41){
     printf("Please make a valid bet\n" );
     return(0);
   }
   else{return(LOSE);}
}
int isbankrupt(int a)
{
   if(a>0){

     return(0);
   }
   else{return(1);}
}

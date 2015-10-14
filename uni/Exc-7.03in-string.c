#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INITIAL_BAN 100

int isbankrupt(int a);

int main(void)
{
   int betnum, ball;
   int bet=1;
   int bankroll = INITIAL_BAN;
   time_t t;

   printf("Welcome to the Roulette Game\n"
           "Your initial Bankroll is %d GBP\n"  
           "Please place your bet (0-35)\n",INITIAL_BAN);
   while(bankroll>0 && betnum >= 0){
     scanf("%d", &betnum);
   /* Intializes random number generator */
   /*The following line of code has been 
     copied from "www.tutorialspoint.com" 
     rand() example library              */
     srand((unsigned) time(&t));
     ball=rand() % 36 ;
     printf("The ball stopped on number: %d\n", ball);
       if(betnum == ball){
         bankroll += bet*32;
       }
       else{bankroll -=bet;}
     printf("Current Bankroll : %d\n", bankroll);
   }
     if(!bankroll>0){
       printf("You are bankrupt, GAMeOVER!\n");
     }
     else{printf("You left the game\n");}
   return(0);

}

int isbankrupt(int a)
{ 
   if(a>0){
 
     return(0);
   }
   else{return(1);}
}

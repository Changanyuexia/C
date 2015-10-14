/*24-h format time difference
  Where h:hour, m:minute 
  index 1: first input 
  index 2: second input
  index 3: output           */

#include <stdio.h>

#define MAX_H 24
#define MAX_M 60
int main(void)
{
   int h1, h2, h3, m1, m2, m3;
   printf("Enter two times : ");
   scanf("%d:%d %d:%d", &h1, &m1, &h2, &m2);
   if(h2>=24|| h1>=24){
     printf("Please input valid time (HH:MM) \n"); 
     return(0);
   }
   if(m1>=MAX_M|| m2>=MAX_M){
     printf("Please input valid time (HH:MM) \n"); 
     return(0);
   }
   h3=h2-h1;
/*Negative hour difference implies +1 day*/
     if(h3<0){h3 += MAX_H;}  
   m3=m2-m1;
/*Negative minute difference impliees +1 hour*/
     if(m3<0){m3 += MAX_M; h3 -=1;}	
   printf("%02d:%02d\n", h3, m3); 
   return(0);
}

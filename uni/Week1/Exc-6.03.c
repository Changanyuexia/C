#include <stdio.h>
#include <math.h>

#define X_MIN -99.999
#define X_MAX  99.999
#define TOLERANCE 0.000000000001
int main(void)
{
   int i = 0;
   double x = X_MIN,y;
  
     while(x<X_MAX){
       x=(double)i/1000+X_MIN;
       y=pow(sin(x),2.0)+pow(cos(x), 2.0);
       printf(" Iteration: %7d x = %7.3f  y= %5.1f\n", i, x, y );
       i++;
       if(y-1<TOLERANCE && y-1>TOLERANCE){
         printf("Proved Wrong\n");
         return(0);}
     }
   printf("Proved\n"); 
   return(0);
}

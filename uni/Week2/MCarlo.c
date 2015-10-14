#include <stdio.h>
#include <math.h>

#define R 1000

int main(void)
{
   int i,x,y,h_a,h_c,cnt=0;
   double pi;
   h_c=h_a=0;
      for(i=0;i<700000;i++){
        cnt++;
         x=rand() %R-R/2;
         y=rand() %R-R/2;
         printf("%2d. x=%d---y=%d\n",cnt,x,y);
         h_a++;
            if(x*x+y*y<R*R/4){
            h_c++;
            }
         pi=4*(double)h_c/(double)h_a;
         printf("h_a=%d---h_c=%d\n pi=%f\n\n",h_a,h_c,pi);
      }
   return(0);
}

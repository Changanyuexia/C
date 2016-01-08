/*A program that randomly  */
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

int main(void)
{
   int i = 0, cnt = 0, temp;
   double minus_cnt = 0, plus_cnt = 0, median = RAND_MAX/2;
   while(i++ <500)
   {
     temp=rand();
     printf( "%f %f %f\n", minus_cnt, plus_cnt, minus_cnt - plus_cnt);
     if(temp > median){plus_cnt++;}
     if(temp < median){minus_cnt++;}
     cnt++;
   }
   printf("Difference: %f\n", plus_cnt-minus_cnt);
   printf("Median: %f\n", median);
   printf("Iterations: %d\n", cnt);
   return(0);
}

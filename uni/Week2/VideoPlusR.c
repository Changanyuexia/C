#include <stdio.h>
#include <time.h>
/* Defining starting date/time ---  6-10-2015 00:00 */
#define START 16714
int main(void)
{
   long int s, code, date;
   s=time(NULL);
   code=430095;
   date=(code/10)*5;
   s=16714*24*60*60;
   printf("VPdate--%ld----seconds since beginning-- %ld\n",date,s );
return 0;

}

#include <stdio.h>
#include <time.h>

#define D_INIT 1444089600
#define S_DAY       86400
#define S_HOUR       3600
#define S_MIN          60
#define DIVISOR         5

int timeInput(void);
int process(long int s);

int main(void)
{
   long int s0, s1, m, h, d, mon, y, code, videoP;
   s0=time(NULL)-D_INIT+45*S_DAY+S_HOUR-10*S_MIN;
   m=s0/60;
   h=m/60;
   d=h/24;
   mon=d/30;
   y=d/365;
   m=m-d*24*60;
   h=m/60;
   m=m-h*60;
   code=d+100*m+10000*h;
   videoP=(code/DIVISOR)*10+DIVISOR;
   printf("There have been %10ld seconds begining\n", s0);
   printf("            and %10ld minutes \n", m);
   printf("            and %10ld hours \n", h);
   printf("            and %10ld days \n", d);
   printf("            and %10ld months \n", mon);
   printf("            and %10ld years \n", y);
   printf("code is %10ld\n", code);
   printf("VPNum is %10ld\n", videoP);
   s1=timeInput();
   process( s1 );
return (0);
}
int timeInput(void)
{
   int h, m, d;
   scanf("%d:%d:%d",&h, &m, &d );
   return(10000*h+100*m+d);
}
int process(long int a)
{
  long int videoP;


  videoP=(a/DIVISOR)*10+DIVISOR;
  printf("code is %10ld\n", a);
  printf("VPNum is %10ld\n", videoP);
return (0);
}

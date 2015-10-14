#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define TOLERANCE 0.000000000001
#define TEST_NUM 100
#define NUM 48

int numberScan(int);
int numberDef(int a, char t);
int isFeasible( int a, int b, int c);
void isEquillateral(int a, int b , int c);
void isIsosceles(int a, int b, int c);
void isScalene(int a, int b, int c);
void isRight(double a, double b, double c);

double removeSign(double a);

int main(void)
{
   int a, b, c, i,t;
   printf("Provide the longitude of each side of your triangle\n");

   for(i=0;i<TEST_NUM;i++){
     t='a';
     a = numberDef(numberScan(t), t);
       if(a==-999){return(0);}
     t='b';
     b = numberDef(numberScan(t), t);
       if(b==-999){return(0);}
     t='c';
     c = numberDef(numberScan(t), t);
       if(c==-999){return(0);}

     printf("a = %d --- b = %d --- c = %d\n", a,b,c);
       if(isFeasible(a, b, c)==1){

         isEquillateral(a, b, c);
         isIsosceles(a, b, c);
         isScalene(a, b, c);
         isRight( (double) a, (double) b, (double) c);

       }
   }
   return(0);
}

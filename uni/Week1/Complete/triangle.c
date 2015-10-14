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
int numberScan(int t)
{

   int i;
   char buffer [256];
   printf ("Enter side %c: ",t);
   fgets (buffer, 256, stdin);
   i = atoi (buffer);
   return i;

}
int numberDef(int a, char t)
{
   if(a <= 0 && a != -999){
      printf("Please provide valid longtitudes (Non-negative Integers)\n");
      a = numberDef(numberScan(t), t);
      return(a);
   }
   else if(a>0){
      return(a);
   }
   if(a ==-999){
      printf("Program terminated by user\n");
      return(a);
   }
   return(0);
}

void isEquillateral(int a, int b , int c)
{
   if(a == b && a == c){
   printf("The triangle is equilateral\n");
   }
}
void isIsosceles(int a, int b, int c)
{
   if((a == b && a != c) || (c == b && a != c) || (a == c && b != c)){
   printf("The triangle is isosceles\n");
   }
}
void isScalene(int a, int b, int c)
{
   if((a != b) && (a != c) && (b != c)){
   printf("The triangle is scalene\n");
   }
}
void isRight(double a, double b, double c)
{
   if(removeSign(a - sqrt( pow(b, 2.0) + pow(c, 2.0)))< TOLERANCE || removeSign(b - sqrt( pow(a, 2.0) + pow(c, 2.0)))< TOLERANCE || removeSign(c - sqrt( pow(b, 2.0) + pow(a, 2.0)))< TOLERANCE){
   printf("The triangle is right\n");

   }
}
int isFeasible(int a, int b, int c)
{
   if ((a >= b+c) || (b >= a+c) || (c>= a+b)){
   printf("The triangle is not feasible\n");
   return(0);
   }
   else{
   return(1);
   }
}
double removeSign(double a)
{
   if(a<0){
   return(-a);
   }
   else{return(a);}
}

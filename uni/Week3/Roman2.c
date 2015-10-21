#include <stdio.h>
#include <string.h>
#include <ctype.h>

int romanToArabic( char *roman ,int lenght);
int num(char *roman);
int romSumArray(int *p, int length);
void clearArray(int a[]);
void printArray(int a[]);
int main(int argc, char **argv)
{
   if( argc==2 ){
      printf("The roman numeral %s is equal to %d\n", \
      argv[1], romanToArabic(argv[1],strlen(argv[1])));

   }
   else{
      return(0);
   }
   return(romanToArabic(argv[1],strlen(argv[1])));
}

int romanToArabic( char *roman , int length)
{
   int res=0,i=0;
   int a[10];
   int *p;
   p=a;
   clearArray(a);
   printArray(a);
     for(i=0;i<length;i++){
         a[i]=num(roman+i);
         printf("%d. %d   -  \n",i,a[i] );
      }
   res=romSumArray( p, length);
   clearArray(a);

   return(res);
}
int romSumArray(int *p , int length)
{
   int i,res=0;
   for(i=0;i<length;i++){
      if(*p>=*(p+1) || *p<=0){
      res+=*p++;
      printf("1........+\n");
      }
      if(*(p+1)>*p && ( *(p+2)>=*p || *(p+2)==0) ){
      res-=*p++;
      printf("2........-\n");
      }
      printf("1.%d......../*testing p*/-i=%d\n", *p,i);/*testing p*/
   }
   return(res);
}

void clearArray(int a[])
{
   int i;
   for (i=0;i<10;i++){
      a[i]=0;
   }
}
void printArray(int a[])
{
   int i;
   for (i=0;i<10;i++){
    printf("%d\n",a[i] );
   }
}
int num( char *roman)
{
  int res;
switch (toupper(*roman)) {
  case 'M':
     res=1000;
     break;
  case 'D':
     res=500;
     break;
  case 'C':
     res=100;
     break;
  case 'L':
     res=50;
     break;
  case 'X':
     res=10;
     break;
  case 'V':
     res=5;
     break;
  case 'I':
     res=1;
     break;
}
return(res);
}

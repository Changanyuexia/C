#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* toRoman(int ar[]);
int division(int a, int b);
void printing(int a[]);
int ArabicToRoman(char *arab);
int romanToArabic( char *roman ,int lenght);
int num(char *roman);
int main(int argc, char **argv)
{
   int  a;
   int ar[8];
   printf("type arabic\n" );
   scanf("%d",&a );
   ar[0]=division(a,1000);
   a-=ar[0]*1000;
   ar[1]=division(a,500);
   a-=ar[1]*500;
   ar[2]=division(a,100);
   a-=ar[2]*100;
   ar[3]=division(a,50);
   a-=ar[3]*50;
   ar[4]=division(a,10);
   a-=ar[4]*10;
   ar[5]=division(a,5);
   a-=ar[5]*5;
   a-=ar[6];
      ar[7]=a;
printing(ar);
printf("%s\n", toRoman(ar));
   /*aqui empieza la cosa romana*/
   if( argc==2 ){
      printf("The roman numeral %s is equal to %d\n", \
      argv[1], romanToArabic(argv[1],strlen(argv[1])));

   }
   else{
      return(0);
   }
   return(0);
}
/*int ArabicToRoman(int b[])
{
  int b=0;
  b[0]=0;
return(b);
}*/
char* toRoman(int ar[])
{
   int i=0;
   char* rom;
   switch (ar[0]) {
     case 0:
     break;
     case 1:
     rom="M";
     rom++;
     i++;
     break;
     case 2:
     rom="MM";
     rom+=2;
     i+=2;
     break;
     case 3:
     rom="MMM";
     rom+=3;
     i+=3;
     break;
   }
    switch (ar[1]) {
      case 1:
      rom="D";
   }
   rom=rom-i;
   return(rom);
}
int division(int a ,int b)
{
   return(a/b);
}
void printing(int a[])
{
     int i;
     printf("  1000  " );
     printf("   500  ");
     printf("   100  ");
     printf("    50  ");
     printf("    10  ");
     printf("     5  ");
     printf("     1  ----a=%d",a[8]);
     printf("\n");
   for(i=0;i<8;i++){
     printf("  %4d  ",a[i] );
   }
   printf("\n");
 }

int romanToArabic( char *roman , int length)
{
   int res=0,i=0;
   int a[10];
      do{

           if (i==length-1){
           res+=num(roman);
           printf("//3-----------%d\n",res );
           return(res);
           }
           else{
              a[i]=num(roman);
              roman++;
              a[i+1]=num(roman);
              printf("%d----%d\n",a[i],a[i+1] );
           }
            if (a[i]>=a[i+1]){
               res+=a[i];
               printf("//2----------%d\n",res );
               roman++;
               i++;
            }
            if (a[i]<a[i+1]&& a[i+1]<=10*a[i]){
               res+=a[i+1]-a[i];
               printf("//1----------%d\n",res );
               roman++;
               i+=2;
            }

           else{printf("Roman not valid\n" );
              return(0);
           }
      }while(i<length);
   return(res);
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

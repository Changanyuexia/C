#include <stdio.h>

int romanToArabic( char *roman );

int main(int argc, char **argv)
{
   if( argc==2 ){
      printf("The roman numeral %s is equal to %d\n", \
      argv[1], romanToArabic(argv[1]));
   }
   else{
      return(0);
   }
   return(0);
}

int romanToArabic( char *roman )
{
   int i=0;
   if(*roman=='M'||*roman=='m'){
      i=1000;
      roman++;
      printf("%c\n",*roman );
      if(*roman=='D'||*roman=='d'){
        i+=500;
      roman++;
      }
      if(*roman=='C'||*roman=='c'){
        i+=100;
      }
      return(i);
   }
   if(*roman=='D'||*roman=='d'){
      i=500;
   }
   if(*roman=='C'||*roman=='c'){
      i=100;
   }
   if(*roman=='L'||*roman=='l'){
      i=50;
   }
   if(*roman=='X'||*roman=='x'){
      i=10;
   }
   if(*roman=='V'){
      i=5;
   }

   return(i);
}

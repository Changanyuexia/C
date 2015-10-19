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

   return(1);
}

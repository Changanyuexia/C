#include <stdio.h>
#include <stdlib.h>

int main(void)
{

   int i,j=0;
while(j<100){
   char buffer [256];
   printf ("Enter a number: ");
   fgets (buffer, 256, stdin);
   i = atoi (buffer);
   printf ("The value entered is %d.\n",i);
   j++;
   }
   return 0;
}

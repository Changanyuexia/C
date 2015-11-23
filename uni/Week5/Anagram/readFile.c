#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
   char *buffer;
   int i=1;
   FILE *dict;
   dict=fopen("eowl_english_words.txt", "r");
  while(i>0){
  i=fscanf(dict,"%s",buffer);
printf("%d - %s\n", i, buffer );
   }
   printf("OLE!\n");
   return(0);
}

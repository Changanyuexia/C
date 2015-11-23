#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD      100
#define ALPHABET       26
#define NUM            97
#define DNAME           "eowl_english_words.txt"

void copyArray(int length, int *p, int *q);
int compare(char *buffer);
int existChar(int c, int ch[ALPHABET]);
void histogram(int character[ALPHABET],char *word);
void phistogram(int character[ALPHABET]);
int main (int argc, char **argv)
{
   int wrdlen, choice=0;
   int *character;
   char *word, *component1, *buffer;
   if(argc==2){
   word=argv[1];
   }
   else{
      return(0);
   }
   word = argv[1];
   wrdlen = (int)strlen(word);
   character = (int *) calloc(ALPHABET, sizeof(int));
   if(character == NULL ){
     printf("memory low\n");
     return(0);
   }
   printf("%d\n",wrdlen );
   /*while( word[i] )
  {
     word[i] = tolower(word[i]);
     i++;
  }
*/
   component1 = (char *) calloc(wrdlen,sizeof(char));
   if (component1 == NULL){
      printf("component1=NULL\n");
      return(0);
   }
   histogram(character,word);
   phistogram(character);
   printf("now we will compare\n");
   choice=compare(buffer);
            /*
      printf("component length %d\n",(int)strlen(component1) );
*/
   /*
   component1[0]=toupper(component1[0]);
*/
   free(component1);
   free(character);
   return(0);
}
void histogram(int character[ALPHABET],char* word)
{
  int i,j;
  for(i=0;i<ALPHABET;i++){
     for(j=0;j<(int)strlen(word);j++){
        if(i == word[j]-NUM){
           character[i]++;
        }
     }
  }
}
void phistogram(int character[ALPHABET])
{
  int i;
  for(i=0;i<ALPHABET;i++){
     printf("%c-%d\n",i+NUM,character[i] );
  }

}

int compare(char *buffer)
{
   int i=0;
   int *histo;
   FILE *fp;
   fp=fopen(DNAME,"r");
   if (fp==NULL){
     printf("wrong file\n" );
     return(1);
   }
   histo = (int *) calloc(ALPHABET, sizeof(int));
   while ( fscanf(fp,"%s", buffer)==1 && i<10) {
     printf("%s\n", buffer );
   histogram(histo, buffer);
   phistogram(histo);
   printf("i=%d\n",i );
   i++;
   }
free(histo);
   return(0);
}
void copyArray(int length, int *p, int *q){
int i;
  for(i=0;i<length;i++){
   *p++=*q++;
  }
}
int compareS(char *s1, char *s2){
   if(strcmp(s1,s2)==0){
      printf("it is string\n");
      return(0);
   }
   return(1);
}
int compareS2(char *s1, char *s2){

   if(strcmp(s1,s2)==0){

      return(0);
   }
   return(1);
}

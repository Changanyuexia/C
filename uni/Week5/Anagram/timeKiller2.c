#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD      100
#define ALPHABET       26
#define NUM            97
#define DNAME           "eowl_english_words.txt"

void copyArray(int length, int *p, int *q);
int check( int ch[ALPHABET],int wrdlen);
int existChar(int c, int ch[ALPHABET]);
int histogram(int wrdlen, int character[ALPHABET],char *word);

int main (int argc, char **argv)
{
   int i=0, wrdlen;
   int *character;
   char *word, *component1;
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
   histogram(wrdlen, character,word);
   for(i=0;i<26;i++){
      printf("%c-%d\n",i+NUM,character[i] );
   }
      /*choice=check(character);*/
      printf("component1=%s\n", component1);
      /*
      printf("component length %d\n",(int)strlen(component1) );
*/
   /*
   component1[0]=toupper(component1[0]);
*/
   printf("%s\n", component1);
   for(i=0;i<26;i++){
      printf("%c-%d\n",i+NUM,character[i] );
   }
   free(component1);
   free(character);
   return(0);
}
int check( int ch[ALPHABET],int wrdlen)
{
   int i;
   FILE *dictionary;
   char *buffer;
   dictionary = fopen(DNAME, "r");
   if(dictionary == NULL){
      printf("file no good\n");
      return(0);
   }

   while(fscanf(dictionary,"%s",buffer) ==1 && strlen(buffer)!=wrdlen){
      if(existChar(buffer[i],ch)==1){

         i++;
         return (1);
         fclose(dictionary);
     }
  }

     fclose(dictionary);
     return(0);
}
int existChar(int c, int ch[ALPHABET])
{
   int i;
   for(i=0;i<ALPHABET;i++){
      if (ch[c-NUM]>0){
         printf("found commin letter\n");
         ch[c-NUM]--;
         return (1);
      }
   }
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
int histogram(int wrdlen,int character[ALPHABET],char* word)
{
  int i,j;
  for(i=0;i<ALPHABET;i++){
     for(j=0;j<wrdlen;j++){
        if(i == word[j]-NUM){
           character[i]++;
        }
     }
  }
  return(0);
}

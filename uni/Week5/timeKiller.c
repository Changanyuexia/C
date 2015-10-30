#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD      100
#define ALPHABET       26
#define NUM            97

void copyArray(int length, int *p, int *q);
int compareS(char *s1, char *s2);

int main (int argc, char **argv)
{
   int i, j, cnt, wrdlen, complen;
   int *character, Scharacter[ALPHABET];
   int *q;
   char *word, *fName, *temp, comp1[MAX_WORD];
   FILE *dict;
   q=Scharacter;
   if(argc==3){
   word=argv[1];
   printf("%s\n",word);
   fName=argv[2];
   printf("%s\n",fName );
   }
   else{
      return(0);
   }
   cnt=0;
   j=0;
   wrdlen = (int) strlen(argv[1]);
   word = (char *) malloc(wrdlen);
   word=argv[1];
   character = (int *) calloc(ALPHABET, sizeof(int));
   if(word == NULL || character == NULL ){
     printf("memory low\n");
     return(0);
   }
   printf("%d\n",(int)strlen(argv[1]) );
   dict= fopen(fName, "r");
   if(dict==NULL){
     printf("Couldn't load file\n");
     return(0);
   }
   if (wrdlen%2==0){
      complen=wrdlen/2;
   }
   if(word[0] == comp1[0])
   {
     printf("it is\n");
   }
   temp = (char *) malloc(complen);
   if (temp == NULL){
      printf("temp=NULL\n");
     return(0);
   }
   for(i=0;i<ALPHABET;i++){
      for(j=0;j<wrdlen;j++){
         /*printf("%c\n",word[j] );*/
         if(i == word[j]-NUM){
            character[i]++;
         }
      }
   }
copyArray(ALPHABET,q,character);

   while(cnt<complen){

        for(i=0;i<cnt;i++){
        while(character[j]==0){
        j++;
        }
        character[j]--;
        }
   printf("cnt:%d\n",cnt );
   for(i=0;i<ALPHABET;i++){
      printf("%c : %d\n",i+NUM,character[i]);
   }
   for(i=0;i<complen;i++){
      j=0;
      while(character[j]==0){
         j++;
      }
      temp[i]=j+NUM;
      character[j]--;
   }
   copyArray(ALPHABET,character,q);
   while (compareS(temp,comp1)!=0 &&
      fscanf(dict,"%s",comp1)==1 && i<50) {
      /*  printf("%s\n",comp1 )*/
      i++;
   }
   printf("%s does not exist\n%d\n",temp,complen );
   cnt++;
   }
   fclose(dict);
   free(temp);

   free(character);
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

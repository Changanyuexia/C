/*last version*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD      100
#define ALPHABET       26
#define NUM            97
#define DNAME           "eowl_english_words.txt"

int compare(int character[ALPHABET],char lib[5][MAX_WORD]);
void histogram(int character[ALPHABET],char *word);
void phistogram(int character[ALPHABET]);
void zhistogram(int character[ALPHABET]);
int chistogram(int character1[ALPHABET], int character2[ALPHABET]);
void copyArray(int length, int *p, int *q);
int existChar(int c, int ch[ALPHABET]);

int main (int argc, char **argv)
{
   int i,j,a,b, wrdlen, choice1=0, choice2=0,cnt=0;
   int *character1, *character2;
   char *word;
   char library1[5][MAX_WORD], library2[5][MAX_WORD];
   if(argc==2){
      word=argv[1];
   }
   else{
      return(0);
   }
   word = argv[1];
   wrdlen = (int)strlen(word);
   character1 = (int *) calloc(ALPHABET, sizeof(int));
   character2 = (int *) calloc(ALPHABET, sizeof(int));
   if(character1 == NULL || character2 == NULL ){
      printf("memory low\n");
      return(0);
   }
   printf("%d\n",wrdlen );
   i=0;
   while( word[i] ){
      word[i] = tolower(word[i]);
      i++;
  }
   /*copyArray(ALPHABET,character2,character1);
*/
   for(j=1;j<=wrdlen;j++){
      cnt=0;
      zhistogram(character1);
      zhistogram(character2);
      histogram(character1,word);
      for(i=0;i<ALPHABET;i++){
         if(character1[i]>0&&cnt<j){
            character2[i]++;
            character1[i]--;
            cnt++;
 /*printf("HISTO1\n" );
   phistogram(character1);
   printf("HISTO2\n" );
   phistogram(character2);*/
            printf("%d now we will compare\n",j);
            phistogram(character1);
            phistogram(character2);
            choice1 = compare(character1, library1);
            choice2 = compare(character2, library2);
         }
      }
      /*printf("%d--choice1 = %d\nchoice2 = %d\n",j, choice1,choice2);*/
      if(choice1>0&&choice2>0){

         for(a=0;a<choice1;a++){
            for(b=0;b<choice2;b++){
               printf("results--%s",library1[a]);
               printf("%s\n",library2[b]);
            }
         }
      }
      choice1=choice2=0;
   }
   free(character1);
   printf("freed C1\n" );
   free(character2);
   printf("freed C2\n" );
   return(0);
}

int compare(int character[ALPHABET],char lib[5][MAX_WORD])
{
   int i=0,cnt=0;
   int *histo;
   char buffer[MAX_WORD];
   FILE *dict;
   dict=fopen(DNAME,"r");

   if (dict==NULL){
     printf("wrong file\n" );
     return(1);
   }
   histo = (int *) calloc(ALPHABET, sizeof(int));
   while ( fscanf(dict,"%s", buffer)==1) {


   zhistogram(histo);
   histogram(histo, buffer);
   if(chistogram(histo,character)==0){
     /*
   printf("i=%d, component=%s\n",i,buffer );
*/
/*   for(j=0;j!=' ';j++){
     lib[cnt][j]=buffer[j];
   }*/
   strcpy(lib[cnt], buffer);
   cnt++;
   }
   i++;
   }

free(histo);
fclose(dict);
   return(cnt);
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
void zhistogram(int character[ALPHABET])
{
  int i;
  for(i=0;i<ALPHABET;i++){
     character[i]=0;
  }

}
int chistogram(int character1[ALPHABET], int character2[ALPHABET])
{
  int i, cnt;
  cnt=0;
  for(i=0;i<ALPHABET;i++){
    if(character1[i]!=character2[i]){
     cnt++;
    }

  }
  if(cnt==0){
    return(0);
  }
  else{
    return(cnt);
  }

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

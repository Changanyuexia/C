/*last version*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD      100
#define ALPHABET       26
#define NUM            97
#define DNAME           "eowl_english_words.txt"

int compare(int character[ALPHABET]);
void histogram(int character[ALPHABET],char *word);
void phistogram(int character[ALPHABET]);
void zhistogram(int character[ALPHABET]);
int chistogram(int character1[ALPHABET], int character2[ALPHABET]);
void copyArray(int length, int *p, int *q);
int existChar(int c, int ch[ALPHABET]);

int main (int argc, char **argv)
{
   int i,j, wrdlen,cnt=0;
   int *character1;
   char *word;
   if(argc==2){
      word=argv[1];
   }
   else{
      return(0);
   }
   word = argv[1];
   wrdlen = (int)strlen(word);
   character1 = (int *) calloc(ALPHABET, sizeof(int));
   if(character1 == NULL){
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
         zhistogram(character1);
      histogram(character1,word);

 /*printf("HISTO1\n" );
   phistogram(character1);
   printf("HISTO2\n" );
   phistogram(character2);*/
            printf("%d now we will compare\n",j);
            cnt = compare(character1);
printf("%d\n",cnt );


      /*printf("%d--choice1 = %d\nchoice2 = %d\n",j, choice1,choice2);*/
   free(character1);
   printf("freed C1\n" );
   return(0);
}

int compare(int character[ALPHABET])
{
   int i=0,cnt=0;
   int *histo1, *histo2;
   char buffer1[MAX_WORD], buffer2[MAX_WORD];
   FILE *dict1, *dict2;
   dict1=fopen(DNAME,"r");

   if (dict1==NULL){
     printf("wrong file\n" );
     return(-1);
   }
   histo1 = (int *) calloc(ALPHABET, sizeof(int));
   histo2 = (int *) calloc(ALPHABET, sizeof(int));
   while ( fscanf(dict1,"%s", buffer1)==1 && buffer1[0]!=EOF) {
   dict2=fopen(DNAME,"r");
   if (dict2==NULL){
     printf("wrong file\n" );
     return(-2);
   }
while( fscanf(dict2,"%s", buffer2)==1){
   zhistogram(histo1);
   zhistogram(histo2);
   histogram(histo1, buffer1);

   histogram(histo2, buffer2);
   for(i=0;i<ALPHABET;i++){
     histo1[i]+=histo2[i];
   }
   if(chistogram(histo1,character)==0){
     /*
   printf("i=%d, component=%s\n",i,buffer );
*/
/*   for(j=0;j!=' ';j++){
     lib[cnt][j]=buffer[j];
   }*/
   printf("histo1\n");
   phistogram(histo1);
   printf("histo2\n");
   phistogram(histo2);
   buffer1[0]=buffer1[0]-('a'-'A');
   cnt++;
   }
   printf("%d. %s%s\n",cnt, buffer1,buffer2 );

fclose(dict2);
}
 }

free(histo1);
free(histo2);
fclose(dict1);
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

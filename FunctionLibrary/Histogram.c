#include <string.h>

#define ALPHABET 26

/*Makes a histogram af the input string and passes it back to the input Array*/
void histogram(int character[ALPHABET],char *word);
/*Prints a histogram corresponding to the input Array*/
void phistogram(int character[ALPHABET]);
/*Resets the input histogram to zero values*/
void zhistogram(int character[ALPHABET]);
/*Compares two histograms returns edit distance*/
int chistogram(int character1[ALPHABET], int character2[ALPHABET]);

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

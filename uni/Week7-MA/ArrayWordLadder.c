#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define L_LENGTH 3000
#define W_LENGTH    5


int insert(char buf[W_LENGTH], char A[L_LENGTH][W_LENGTH],int i);

int main(int argc, char **argv)
{
  int i=0;
  char words[L_LENGTH][W_LENGTH];
  /*char wordsOrig[L_LENGTH][W_LENGTH];*/
  char buf[W_LENGTH];
  char *fileN;
  FILE *fp, *output;
  if(argc==2){
    fileN=argv[1];
  }
  else{
    printf("could not load file\n");
    return 1;
  }
  fp=fopen(fileN, "r");
  output=fopen("ladder.log", "w");
  while(fscanf(fp,"%s",buf)==1){
    insert(buf,words,i);
    i++;
  }
  printf("END\n");
  fprintf(output, "END\n" );
  fclose(fp);
  i=0;
  printf("%s\n",words[i] );
  while(isalpha(words[i][0])){
  fprintf(output, "%s\n",words[i] );
  i++;
  }
  fclose(output);
  return 0;
}

int insert(char buf[W_LENGTH], char A[L_LENGTH][W_LENGTH],int i)
{
  char temp[W_LENGTH];
  /*First Input*/
  if(i==0){
    strcpy(A[i],buf);
    return 0;
  }
  /*In Between Inputs*/
  if(strcmp(buf,A[i-1])>0){
    strcpy(temp,A[i-1]);
    strcpy(A[i],buf);
    return 0;
  }
  return 0;
}

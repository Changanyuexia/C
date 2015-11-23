#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define L_LENGTH 3000
#define W_LENGTH  5
#define NUMBER L_LENGTH

int insert(char buf[W_LENGTH], char A[L_LENGTH][W_LENGTH],int i);
void swap(char A[L_LENGTH][W_LENGTH],int i);
void printA(char A[L_LENGTH][W_LENGTH],char B[L_LENGTH][W_LENGTH],char *fileN);
void printN(char A[L_LENGTH][W_LENGTH]);

int main(int argc, char **argv)
{
  int i=0,cnt=0,j;
  char words[L_LENGTH][W_LENGTH];
  char wordsOrig[L_LENGTH][W_LENGTH];
  char buf[W_LENGTH];
  char *fileN;
  FILE *fp;
  if(argc==2){
    fileN=argv[1];
  }
  else{
    printf("could not load file\n");
    return 1;
  }
  fp=fopen(fileN, "r");
  while(fscanf(fp,"%s",buf)==1&&i<NUMBER){
    insert(buf,words,i);
    i++;
  }
  j=i-1;
  i=0;
  printf("END\n");
  fclose(fp);

  printA(words,wordsOrig,fileN);
  printf("close/open file\n");
  while(i<j){
    if(strcmp(words[i],words[i+1])>0){
      cnt++;
      printf("Wrong\n");
    }
    i++;
  }
  if(cnt==0){
    printf("correct %d\n",cnt);
  }
  return(-1);
}
/*------------------------------------------------------------------*/

int insert(char buf[W_LENGTH], char A[L_LENGTH][W_LENGTH],int i)
{
  char temp[W_LENGTH];
  /*First Input*/
  if(i==0){
    strcpy(A[i],buf);
    return(0);
  }
  /*Second Input*/
  if(i==1000000){
    strcpy(A[i],buf);
    return(0);
  }
  /*In Between Inputs*/
  if(strcmp(buf,A[i-1])>0){
    strcpy(temp,A[i-1]);
    strcpy(A[i],buf);
    return(0);
  }
  else{
    strcpy(A[i],A[i-1]);
    insert(buf,A,i-1);
    return(1);
  }
}
/*------------------------------------------------------------------*/
void printA(char A[L_LENGTH][W_LENGTH],char B[L_LENGTH][W_LENGTH],char *fileN)
{
  int i=0;
  FILE *fp, *fpo;
  fp=fopen(fileN, "r");
  fpo=fopen("wordsoutput.txt", "w");
  printf("\noriginal            version\n------------------------\n");
  while(fscanf(fp,"%s",B[i])==1&&i<NUMBER){
    fprintf(fpo,"%3d.-%5s",i,B[i] );
    fprintf(fpo,"%12d.-%5s\n",i,A[i] );
    i++;
  }
  fclose(fpo);
  fclose(fp);
}

void printB(char A[L_LENGTH][W_LENGTH])
{
  int i=0;
  printf("\nTEMPORARY            version\n------------------------\n");
  while(i<NUMBER){
    printf("%12d.-%5s\n",i,A[i] );
    i++;
  }

}

void swap(char A[L_LENGTH][W_LENGTH],int i)
{
  char temp[5];
  strcpy(temp,A[i-1]);
  strcpy(A[i-1],A[i]);
  strcpy(A[i],temp);
}

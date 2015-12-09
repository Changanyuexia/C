/*check the top of the treee
get tree printed */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#define ASCII   128
#define STRSIZE 50000

typedef struct huffman Huf;
struct huffman{
  char c;
  char code[50];
  int freq;
  int used;
  Huf *left,*right;
};
void structInit(Huf A[], int length);
void printArray(Huf A[], unsigned int length);
void charCount(Huf A[], char *str);
int findLeastF(Huf A[]);
void coding(Huf *t);
int ScanArray(Huf auxnodes[]);

int main(int argc, char **argv)
{
  int i=0;
  Huf nodes[2*ASCII];
  Huf *current;
  if(argc!=2){
    fprintf(stderr, "Too few arguments\n");
    exit(1);
  }
  structInit(nodes,2*ASCII);
  charCount(nodes,argv[1]);
  i=ScanArray(nodes);
  current=&nodes[i];
  coding(current);
  printArray(nodes,ASCII);
  return 0;
}
int ScanArray(Huf auxnodes[])
{
  int i=0,j=0,a=ASCII;
  do{
    i=findLeastF(auxnodes);
    auxnodes[i].used=1;
    j=findLeastF(auxnodes);
    auxnodes[j].used=1;
    auxnodes[a].freq=auxnodes[i].freq+auxnodes[j].freq;
    auxnodes[a].left=&auxnodes[i];
    auxnodes[a].right=&auxnodes[j];
    a++;
    }while(i&&j);
  return i;
}
void coding(Huf *t)
{
  static int start=0;
  char i[2];
  char j[2];
  if(t->left==NULL && t->right==NULL){
   return;
  }
  i[0]='0';
  j[0]='1';
  i[1]=j[1]='\0';
  if(start==0){
    strcat(t->left->code,i);
    strcat(t->right->code,j);
    start++;
  }
  strcpy(t->left->code,t->code);
  strcpy(t->right->code,t->code);
  strcat(t->left->code,i);
  strcat(t->right->code,j);
  coding(t->left);
  coding(t->right);
}
int findLeastF(Huf A[])
{
  int i,min=0,cursor=0;
  for(i=0;i<2*ASCII;i++){
    if (min==0&& !(A[i].used)&&(A[i].freq!=0)){
      min=A[i].freq;
      cursor=i;
    }
    else if(min>A[i].freq&&A[i].freq!=0&& !(A[i].used)){
      min=A[i].freq;
      cursor=i;
    }
  }
  return cursor;
}
void structInit(Huf A[],int length)
{
  int i;
  for (i=0;i<length;i++){
    if(i<ASCII){
    A[i].c=i;
    }
    else{
    A[i].c='@';
    }
    A[i].used=0;
    A[i].freq=0;
    A[i].left=NULL;
    A[i].right=NULL;
  }
}
void charCount(Huf A[],char *str)
{
  FILE *fp;
  char c;
  fp=fopen(str,"r");
  if(fp==NULL){
    fprintf(stderr,"Couln't load file\n");
    exit(1);
  }
  while ( (c=fgetc(fp)) && c!=EOF){
    A[(int)c].freq++;
  }
  fclose(fp);
}
void printArray(Huf A[], unsigned int length)
{
  unsigned int i;
  int count=0;
  for(i=0;i<length;i++){
    if(A[i].freq!=0){
        count+=(int)strlen(A[i].code)*A[i].freq;
      if(!isprint(A[i].c)&& A[i].c!='@'){
        printf("%c%d%c: %20s (%3lu * %7d)\n",
        '"',A[i].c,'"',A[i].code,strlen(A[i].code),A[i].freq);
      }
      else{
        printf("%c%c%c : %20s (%3lu * %7d)\n",
        '"',A[i].c,'"',A[i].code,strlen(A[i].code),A[i].freq);
      }
    }
  }
  printf("%10d bytes\n",count/8 );
}

/*check the top of the treee
get tree printed */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#define ASCII   128
#define ALPHA    65
#define STRSIZE 500

typedef struct huffman Huf;
struct huffman{
  char c;
  char code[50];
  int freq;
  int used;
  Huf *left;
  Huf *right;
};
void structInit(Huf A[]);
void structInit2(Huf A[]);
void printArray(Huf A[], unsigned int length);
void charCount(Huf A[]);
int findLeastF(Huf A[]);
void printTree1(Huf A[],int i,int j);
char* PrintTree(Huf *t,char *str);
void coding(Huf *t);
char* coding1(Huf *t);

int main(void)
{
  int i=0,j=0,a=ASCII;
  char *str;
  Huf nodes[ASCII];
  Huf auxnodes[2*ASCII];
  Huf *current;
  str = calloc(STRSIZE, sizeof(char));
  assert(str != NULL);

  structInit(nodes);
  structInit2(auxnodes);
  charCount(nodes);
  printArray(nodes,ASCII);
  memcpy(auxnodes,nodes ,sizeof(nodes));
  do{
    i=findLeastF(auxnodes);
    auxnodes[i].used=1;
    printf("least common:%c , index:%d\n",auxnodes[i].c,i);
    j=findLeastF(auxnodes);
    auxnodes[j].used=1;
    printf("least common:%c , index:%d\n",auxnodes[j].c,j);
    auxnodes[a].freq=auxnodes[i].freq+auxnodes[j].freq;
    auxnodes[a].left=&auxnodes[i];
    auxnodes[a].right=&auxnodes[j];
    printf("%d+%d=%d\n",auxnodes[i].freq,auxnodes[j].freq, auxnodes[a].freq);
    /*printf("%c\n", auxnodes[a].left->c);
    printf("%c\n", auxnodes[a].right->c);*/
    a++;
  }while(i&&j);
  printf("niksoprint---i:%d--j:%d-\n",i, j);
  current=&auxnodes[i];
  str=PrintTree(current,str);
  printf("%s\n", str);
  printArray(auxnodes,2*ASCII);
  free(str);
  /*coding(current);*/
  return 0;
}
void coding(Huf *t)
{
  int start=0;
  char i[50];
  char j[50];
  if(t==NULL)
  return;
  i[0]='0';
  j[0]='1';
  i[1]=j[1]='\0';
  if(start==0){
    strcat(t->left->code,i);
    strcat(t->right->code,j);
  }
  strcpy(t->left->code,t->code);
  strcat(t->left->code,i);
  strcpy(t->right->code,t->code);
  strcat(t->right->code,j);
}
/*int coding1(Huf *t)
{
  int branch;
  if(t==NULL){
  return -1;
  }
  branch=coding1(t->left);
  if (branch==-1){
    return
  }
  strcat(t->code,itoa());
  printf("coding\n");
  if(t->left!=NULL){
    branch=0;
    coding(t->left);
  }
  else if(t->right!=NULL){
    coding(t->right);
    branch=1;
  }
  else{
  return -1;
  }
  return branch;
}
char* coding1(Huf *t)
{
  char *str;
  str = calloc(STRSIZE, sizeof(char));
  assert(str != NULL);
  if(t == NULL){
    strcpy(str, '\0');
    return str;
  }
    strcpy(str,t->code)
    strcat(t->code,coding1(t->left));
    strcat(t->code,coding1(t->right));
  return str;
}
*/
char* PrintTree(Huf *t, char* str)
{
  if(t == NULL){
    strcpy(str, "*");
    return str;
  }
  if(t->c=='\n')
    sprintf(str, "%d-%d(%s)(%s)", 010,t->freq,
    PrintTree(t->left,str),
    PrintTree(t->right,str));
  else{
    sprintf(str, "%c-%d(%s)(%s)", t->c,t->freq,
    PrintTree(t->left,str),
    PrintTree(t->right,str));
  }
  return str;
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
  printf("%c\n",A[cursor].c );
  return cursor;
}
void structInit(Huf A[])
{
  int i;
  for (i=0;i<ASCII;i++){
    A[i].c=i;
    /*A[i].code="0";*/
    A[i].used=0;
    A[i].freq=0;
    A[i].left=NULL;
    A[i].right=NULL;
  }
}
void structInit2(Huf A[])
{
  int i;
  for (i=0;i<2*ASCII;i++){
    A[i].c='@';
    /*A[i].code="0";*/
    A[i].used=0;
    A[i].freq=0;
    A[i].left=NULL;
    A[i].right=NULL;
  }
}

void charCount(Huf A[])
{
  FILE *fp;
  char c;
  fp=fopen("34words.txt","r");
  while ( (c=fgetc(fp)) && c!=EOF){
    /*printf("%c%d%d\n",c,c,(int)c );*/
    A[(int)c].freq++;
  }
  fclose(fp);
}
void printArray(Huf A[], unsigned int length)
{
  unsigned int i;
  for(i=0;i<length;i++){
    if(A[i].freq!=0){
      if(i=='\n'){
        printf("%4d. %8s--%c10%c: %d\n",i,A[i].code,'"','"',A[i].freq);
      }
      else{
        printf("%4d. %8s--%c%c%c : %d\n",i,A[i].code,'"',A[i].c,'"',A[i].freq);
      }
    }
  }
}

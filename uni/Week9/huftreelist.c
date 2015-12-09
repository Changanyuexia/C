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
  int x;
  int y;
  long int freq;
  int used;
  Huf *left,*right;
};
void structInit(Huf A[]);
void structInit2(Huf A[]);
void printArray(Huf A[], unsigned int length);
void charCount(Huf A[], char *str);
int findLeastF(Huf A[]);
char* PrintTreeLong(Huf *t);
char* PrintTree(Huf *t,int depth);
/*this function also marks the depth to the right of each branch*/
void coding(Huf *t);
int brLength(Huf *t,int n);
void coording(Huf *t);
int ScanArray(Huf auxnodes[]);
int sortfqc(const void *a, const void *b);
int findBranchDepth(Huf *t);

int main(int argc, char **argv)
{
  int i=0,depth=0;
  char *str=NULL;
  Huf nodes[ASCII];
  Huf auxnodes[2*ASCII];
  Huf *current;
  if(argc!=2){
    fprintf(stderr, "Too few arguments\n");
    exit(1);
  }
  structInit(nodes);
  structInit2(auxnodes);
  charCount(nodes,argv[1]);
  memcpy(auxnodes,nodes ,sizeof(nodes));
  i=ScanArray(auxnodes);
  current=&auxnodes[i];
  coding(current);
  printArray(auxnodes,ASCII);
  /*depth=findBranchDepth(current->left);*/
  /*str=PrintTree(current,depth);
  printf("%s\n",str);
  str=NULL;*/
  str=PrintTreeLong(current);
  printf("%s\n",str);
  free(str);
  printf("%d\n",depth);
  printf("ws edw\n");

  printArray(auxnodes,ASCII);
  /*qsort(auxnodes,2*ASCII,sizeof(Huf),sortfqc);*/
  printArray(auxnodes,2*ASCII);
  return 0;
}
int sortfqc(const void *a, const void *b)
{
  Huf *ta, *tb;
  ta= (Huf*)a;
  tb= (Huf*)b;
  return ta->freq - tb->freq;
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
  /*  auxnodes[i].parent=auxnodes[j].parent=&auxnodes[a];*/
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

int findBranchDepth(Huf *t)
{
  Huf *p=t;
  int depth=0;
  int i=0;
  if(t==NULL)
  return depth;
   while (p->right!=NULL){
     depth++;
     p=p->right;
  }
  printf("%d\n",depth );
  i=findBranchDepth(t->left);
  if(i>depth){
    depth=i;
  }
  return depth;
}

char* PrintTree(Huf *t,int depth)
{
  int i=0;
  char *str, *rstr, *lstr;
  char dash[2]={'-','\0'};
  char nline[2]={'\n','\0'};
  str = (char*) calloc(STRSIZE, sizeof(char));
  assert(str != NULL);
  if( t==NULL){
    strcpy(str, "*");
    return str;
  }
    rstr=PrintTree(t->right,depth);
    lstr=PrintTree(t->left,0);
    if(t->left!=NULL)
    depth=findBranchDepth(t->left);
    if(!isgraph(t->c)){
      sprintf(str, "%d", t->c);
      for(i=0;i<=depth;i++){
        strcat(str,dash);
      }
      strcat(str,rstr);
      strcat(str,nline);
      strcat(str,lstr);
  }
  else{
    sprintf(str, "%c", t->c);
      for(i=0;i<=depth;i++){
        strcat(str,dash);
      }
      strcat(str,rstr);
      strcat(str,nline);
      strcat(str,lstr);
  }
  free(lstr);
  free(rstr);
  return str;
}
char* PrintTreeLong(Huf *t)
{
  char *str, *rstr, *lstr;
  str = (char*) calloc(STRSIZE, sizeof(char));
  assert(str != NULL);
  if(t == NULL){
    strcpy(str, "*");
    return str;
  }
    lstr=PrintTreeLong(t->left);
    rstr=PrintTreeLong(t->right);
  if(!isgraph(t->c)){
    sprintf(str, "%d(%s)(%s)", t->c,
    lstr,rstr);
  }
  else{
    sprintf(str, "%c(%s)(%s)", t->c,
    lstr,rstr);
  }
  free(lstr);
  free(rstr);
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
  return cursor;
}
void structInit(Huf A[])
{
  int i;
  for (i=0;i<ASCII;i++){
    A[i].c=i;
    A[i].used=0;
    A[i].freq=0;
    A[i].left=NULL;
    A[i].right=NULL;
  }
}
void structInit2(Huf A[])
{
  int i;
  for (i=ASCII;i<2*ASCII;i++){
    A[i].c='@';
    /*A[i].code="0";*/
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
    if(A[i].freq!=0 && A[i].c !='@'){
        count+=(int)strlen(A[i].code)*A[i].freq;
      if(!isprint(A[i].c)&& A[i].c!='@'){
        printf("%c%d%c: %20s (%3lu * %7ld)\n",'"',A[i].c,'"',A[i].code,strlen(A[i].code),A[i].freq);
      }
      else{
        printf("%c%c%c : %20s (%3lu * %7ld)\n",'"',A[i].c,'"',A[i].code,strlen(A[i].code),A[i].freq);
      }
    }
  }
  printf("%10d bytes\n",count/8 );
}
/*int brLength(Huf *t, int n)
{
  int n1,n2;
if(t->left==NULL && t->right==NULL)
return n;
else{
  n++;
  n1=brLength(t->left,n);
  n2=brLength(t->right,n);
  if(n1 >= n2)
  n=n1;
  else
  n=n2;
  return n;
}
}*/

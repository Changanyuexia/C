/*check the top of the treee
get tree printed */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#define ASCII   128
#define STRSIZE 50000
#define DEPTH_INIT -1
#define SCREEN_WIDTH 58
#define SCREEN_HEIGHT 20
typedef struct rect Rect;
struct rect{
  int x;
  int y;
  int width;
  int height;
};
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
void structInit(Huf A[], int length);
void printArray(Huf A[], unsigned int length);
void charCount(Huf A[], char *str);
int findLeastF(Huf A[]);
char* PrintTreeLong(Huf *t);
void coding(Huf *t);
void coordinating(Huf *t, int d);
int ScanArray(Huf auxnodes[]);
int sortfqc(const void *a, const void *b);
Rect findNodeXY(Huf *t, Rect C);
void makeBufferTable(Huf A[], char[][SCREEN_WIDTH]);
void printScreen(char tree[][SCREEN_WIDTH]);
void placeNodes(Huf A[], char tree[][SCREEN_WIDTH]);
void placeORs(char tree[][SCREEN_WIDTH]);
void TableInit(char tree[][SCREEN_WIDTH]);
void placeDashes(char tree[][SCREEN_WIDTH]);

int main(int argc, char **argv)
{
  int i=0;
  Rect C;
  char *str=NULL;
  char treeView[SCREEN_HEIGHT][SCREEN_WIDTH];
  Huf nodes[2*ASCII];
  Huf *current;
  if(argc!=2){
    fprintf(stderr, "Too few arguments\n");
    exit(1);
  }
  C.x=C.y=C.height=0;
  C.width=-1;
  structInit(nodes, 2*ASCII);
  charCount(nodes,argv[1]);
  i=ScanArray(nodes);
  current=&nodes[i];
  coding(current);
  findNodeXY(current, C);
  str=PrintTreeLong(current);
  printf("%s\n",str);
  free(str);
  printArray(nodes,2*ASCII);
  makeBufferTable(nodes, treeView);
  printScreen(treeView);

  /*qsort(auxnodes,2*ASCII,sizeof(Huf),sortfqc);*/
  return 0;
}
void placeDashes(char tree[][SCREEN_WIDTH])
{
  int i,j,cnt;
    for(j=0;j<SCREEN_WIDTH-1;j++){
      if(!isgraph(tree[0][j])){
        tree[0][j]='-';
      }
    }
  do{
    cnt=0;
    for(i=0;i<SCREEN_HEIGHT-1;i++){
      for(j=1;j<SCREEN_WIDTH;j++){
        if(tree[i-1][j]==' '&&tree[i][j-1]==' '&&isgraph(tree[i][j])){
          tree[i][j-1]='-';
          cnt++;
        }
      }
    }
  }while(cnt);
}
void TableInit(char tree[][SCREEN_WIDTH])
{
  int i,j;
  for(i=0;i<SCREEN_HEIGHT;i++){
    for(j=0;j<SCREEN_WIDTH;j++){
      tree[i][j]=' '  ;
    }
    tree[i][SCREEN_WIDTH-1]='\0';
  }
}
void placeORs(char tree[][SCREEN_WIDTH])
{
  int i,j;
  for(i=1;i<SCREEN_HEIGHT;i++){
    for(j=0;j<SCREEN_WIDTH;j++){
      if(isgraph(tree[i-1][j])&&isgraph(tree[i+1][j])){
        tree[i][j]='|';
      }
    }
  }

}
void placeNodes(Huf A[], char tree[][SCREEN_WIDTH])
{
  int i;
  for(i=0;i<2*ASCII;i++){
    if(A[i].freq!=0){
      tree[A[i].y*2][A[i].x*2]=A[i].c;
    }
  }
}
void printScreen(char tree[][SCREEN_WIDTH])
{
  int i;
  for(i=0;i<SCREEN_HEIGHT;i++){
      printf("%s\n",tree[i]);
  }
}

void makeBufferTable(Huf A[], char tree[][SCREEN_WIDTH])
{
  TableInit(tree);
  placeNodes(A,tree);
  placeORs(tree);
  placeDashes(tree);
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

Rect findNodeXY(Huf *t, Rect C)
{
  if(t==NULL){
    return C;
  }
  t->x=C.width+1;
  t->y=C.height+C.y;
  C.height++;
  C=findNodeXY(t->left, C);
  C.y--;
  if(t->right!=NULL)
  {
  C.width++;
  C=findNodeXY(t->right, C);
  }
  return C;
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
void structInit(Huf A[], int length)
{
  int i;
  for (i=0;i<length;i++){
    if(isprint(i)){
    A[i].c=i;
    }
    else{
      A[i].c='#';
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
    if(isalpha(c)){
      c=toupper(c);
      A[(int)c].freq++;
    }
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
        printf("%c%d%c: %20s (%3lu * %7ld)\n",'"',A[i].c,'"',A[i].code,strlen(A[i].code),A[i].freq);
      }
      else{
        printf("%c%c%c : %20s (%3lu * %7ld  x:%d , y:%d )\n",'"',A[i].c,'"',A[i].code,strlen(A[i].code),A[i].freq,A[i].x,A[i].y);
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

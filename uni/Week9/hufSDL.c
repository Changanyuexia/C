#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "neillsdl2.h"
#define FNTFILENAME "m7fixed.fnt"

#define ASCII   128

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
Rect rectInit(Rect R);
void structInit(Huf A[], int length);
void printArray(Huf A[], unsigned int length);
void charCount(Huf A[], char *str);
int findLeastF(Huf A[]);
char* PrintTreeLong(Huf *t);
char* PrintTree(Huf *t,int depth);
void coding(Huf *t);
void coordinating(Huf *t, int d);
int ScanArray(Huf auxnodes[]);
int sortfqc(const void *a, const void *b);
Rect findNodeX(Huf *t, Rect C);
void printScreen(char **tree, Rect R);
void placeNodes(Huf A[], char **tree);
void placeORs(char **tree, Rect R);
void TableInit(char **tree, Rect R);
void placeDashes(char **tree, Rect R);
void SDL(char **A, Rect R);
char** makeBufferTable(Huf A[], Rect *p);
Rect findTableLimits(Huf A[]);
int max(int a, int b);
char** mallocTable(Rect R);
void freeTable(char **Table, Rect R);

int main(int argc, char **argv)
{
  int i=0;
  Rect R;
  Rect *pR=&R;
  Huf nodes[2*ASCII];
  Huf *top;
  char **tree;
  if(argc!=2){
    fprintf(stderr, "Too few arguments\n");
    exit(1);
  }
  R=rectInit(R);
  structInit(nodes, 2*ASCII);
  charCount(nodes,argv[1]);
  i=ScanArray(nodes);
  top=&nodes[i];
  coding(top);
  findNodeX(top, R);
  printArray(nodes,2*ASCII);
  tree=makeBufferTable(nodes,pR);
  /*qsort(auxnodes,2*ASCII,sizeof(Huf),sortfqc);*/
  printScreen(tree,R);
  SDL(tree,R);
  freeTable(tree,R);
  return 0;
}
void freeTable(char **Table, Rect R)
{
  int i;
  for (i=0; i<=R.height; i++){
   free(Table[i]);
  }
  free(Table);
}
void SDL(char **A, Rect R)
{
  int i;
  SDL_Simplewin sw;
  fntrow fontdata[FNTCHARS][FNTHEIGHT];

     Neill_SDL_Init(&sw, FNTWIDTH*(R.width+3),FNTHEIGHT*(R.height+3));
     Neill_SDL_ReadFont(fontdata, (char *)FNTFILENAME);
     while(!sw.finished){
       for(i=0;i<=R.height;i++){
         Neill_SDL_DrawString(&sw, fontdata,A[i], 0, FNTHEIGHT*(i+1));
       }
       SDL_RenderPresent(sw.renderer);
       SDL_UpdateWindowSurface(sw.win);
     Neill_SDL_Events(&sw);
     }
     SDL_RenderClear(sw.renderer);
     SDL_DestroyRenderer(sw.renderer);
     SDL_DestroyWindow(sw.win);
     SDL_Quit();
}
void placeDashes(char **tree, Rect R)
{
  int i,j,cnt;
  do{
    cnt=0;
    for(i=0;i<R.height;i++){
      for(j=1;j<=R.width;j++){
        /*First row differs because there is no upper charachter to check*/
        if(i==0){
          if(tree[0][j-1]==' '&&isgraph(tree[0][j])){
            tree[0][j-1]='-';
            cnt++;
          }
        }
         /*Rest of the table*/
        else{
          if(tree[i-1][j]==' '&&tree[i][j-1]==' '&&isgraph(tree[i][j])){
            tree[i][j-1]='-';
            cnt++;
          }
        }
      }
    }
  }while(cnt);
}
void TableInit(char **tree, Rect R)
{
  int i,j;
  for(i=0;i<=R.height;i++){
    for(j=0;j<=R.width;j++){
      tree[i][j]=' '  ;
    }
    tree[i][R.width+1]='\0';
  }
}
void placeORs(char **tree, Rect R)
{
  int i,j;
  for(i=1;i<R.height;i++){
    for(j=0;j<=R.width;j++){
      if(isgraph(tree[i-1][j])&&isgraph(tree[i+1][j])){
        tree[i][j]='|';
      }
    }
  }

}
void placeNodes(Huf A[], char **tree)
{
  int i;
  for(i=0;i<2*ASCII;i++){
    if(A[i].freq!=0){
      tree[A[i].y*2][A[i].x*2]=A[i].c;
    }
  }
}
void printScreen(char **tree,Rect R)
{
  int i;
  for(i=0;i<=R.height;i++){
      printf("%s\n",tree[i]);
  }
}
char** makeBufferTable(Huf A[], Rect *p)
{
  char **tree;
  Rect R;
  R=findTableLimits(A);
  *p=R;
  tree=mallocTable(R);
  TableInit(tree, R);
  placeNodes(A,tree);
  placeORs(tree, R);
  placeDashes(tree, R);
  return tree;
}
char** mallocTable(Rect R)
{
  int i;
  char **tree;
  tree = (char**) malloc((R.height+1)*sizeof(char*));
  assert(tree!=NULL);
  for (i = 0; i<=R.height; i++){
    tree[i] = (char*) malloc((R.width+1)*sizeof(char));
    assert(tree[i]!=NULL);
  }
  return tree;
}
Rect findTableLimits(Huf A[])
{
  int i;
  Rect R;
  R.width=R.height=0;
  for(i=0;i<2*ASCII;i++){
   R.width=max(2*A[i].x, R.width);
   R.height=max(2*A[i].y, R.height);
  }
  return R;
}
int max(int a, int b)
{
  if(a>b){
    return a;
  }
  else{
    return b;
  }
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
Rect findNodeX(Huf *t, Rect C)
{
  if(t==NULL){
    return C;
  }
  t->x=C.width+1;
  t->y=C.height+C.y;
  C.height++;
  C=findNodeX(t->left, C);
  C.y--;
  if(t->right!=NULL){
    C.width++;
    C=findNodeX(t->right, C);
  }
  return C;
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
    A[i].x=0;
    A[i].y=0;
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
        printf("%c%d%c: %20s (%3lu * %7ld)\n",'"',
        A[i].c,'"',A[i].code,strlen(A[i].code),A[i].freq);
      }
      else{
        printf("%c%c%c : %20s (%3lu * %7ld  x:%d , y:%d )\n",'"',
        A[i].c,'"',A[i].code,strlen(A[i].code),A[i].freq,A[i].x,A[i].y);
      }
    }
  }
  printf("%10d bytes\n",count/8 );
}
Rect rectInit(Rect R)
{
  R.x=R.y=R.height=0;
  R.width=-1;
  return R;
}

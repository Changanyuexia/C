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
typedef enum pDir{left,right} pDir;
typedef struct huffman Huf;
struct huffman{
  char c;
  char *code;
  int bitLength;
  int depth;
  int x;
  int SDLx;
  int y;
  long int freq;
  int used;
  pDir parentDirection;
  Huf *parent;
  Huf *left,*right;
};

Rect rectInit(Rect R);
void structInit(Huf A[], int length);
void printArray(Huf A[], unsigned int length);
void charCount(Huf A[], char *str);
int ScanArray(Huf auxnodes[]);
int findLeastFreq(Huf A[]);
void findBranchLenght(Huf *t);
int findMaxDepth(Huf *t,int depth);
void mallocCodeStrings(Huf *t);
void coding(Huf *t);
Rect findNodeCoords(Huf *t, Rect C);
char** makeBufferTable(Huf A[], Rect *p);
Rect findTableLimits(Huf A[]);
char** mallocTable(Rect R);
void TableInit(char **tree, Rect R);
void placeNodes(Huf A[], char **tree);
void placeORs(char **tree, Rect R);
void placeDashes(char **tree, Rect R);
void SDL(char **tree, Huf *t, int depth,Rect R);
int findTotBytes(Huf A[], int lenght);
void N_SDL_print(Huf *t,int x,int maxDepth, SDL_Simplewin *s,fntrow fontdata[FNTCHARS][FNTHEIGHT]);
void SDL_FREE(SDL_Simplewin *s);
void freeCodeStrings(Huf *t);
void freeTable(char **Table, Rect R);
int max(int a, int b);

int main(int argc, char **argv)
{
  int i=0;
  int maxDepth=0;
  int totBytes=0;
  Rect R;
  Rect *pR=&R;
  Huf nodes[2*ASCII];
  Huf *top;
  char **tree;
  if(argc!=2){
    fprintf(stderr, "Bad arguments\n");
    exit(1);
  }
  R=rectInit(R);
  structInit(nodes, 2*ASCII);
  charCount(nodes,argv[1]);
  i=ScanArray(nodes);
  top=&nodes[i];
  findBranchLenght(top);
  maxDepth=findMaxDepth(top,0);
  mallocCodeStrings(top);
  coding(top);
  findNodeCoords(top, R);
  totBytes=findTotBytes(nodes,ASCII);
  printArray(nodes,ASCII);
  fprintf(stdout,"%d bytes\n",totBytes);
  freeCodeStrings(top);
  tree=makeBufferTable(nodes,pR);
  SDL(tree,top,maxDepth,R);
  freeTable(tree,R);
  return 0;
}
int findTotBytes(Huf A[], int length)
{
  int i,cnt=0;
  for(i=0;i<length;i++){
    if(A[i].code!=NULL){
      A[i].bitLength=(int)strlen(A[i].code);
      cnt+=(A[i].bitLength*A[i].freq);
    }
  }
  return cnt/8;
}
void mallocCodeStrings(Huf *t)
{
  if(t==NULL){
    return;
  }
  t->code = (char *)malloc(sizeof(char *));
  if(t->code==NULL){
    fprintf(stderr, "Unable to allocate code string of %c\n",t->c );
    exit(1);
  }
  mallocCodeStrings(t->left);
  mallocCodeStrings(t->right);
}
void freeCodeStrings(Huf *t)
{
  if(t==NULL){
    return;
  }
  free (t->code);
  freeCodeStrings(t->left);
  freeCodeStrings(t->right);
}
void findBranchLenght(Huf *t)
{
  if(t==NULL){
    return;
  }
  if(t->left!=NULL){
    t->left->depth=t->depth+1;
    findBranchLenght(t->left);
  }
  if(t->right!=NULL){
    t->right->depth=t->depth+1;
    findBranchLenght(t->right);
  }
}
void freeTable(char **Table, Rect R)
{
  int i;
  for (i=0; i<=R.height; i++){
   free(Table[i]);
  }
  free(Table);
}
void SDL(char **tree, Huf *t, int maxDepth,Rect R)
{
  int i;
  SDL_Simplewin sw;
  SDL_Simplewin *s=&sw;
  fntrow fontdata[FNTCHARS][FNTHEIGHT];
  Neill_SDL_Init(s, FNTWIDTH*(maxDepth*10),FNTHEIGHT*(maxDepth*5));
  Neill_SDL_ReadFont(fontdata, (char *)FNTFILENAME);
  for(i=0;i<=R.height;i++){
    Neill_SDL_DrawString(&sw, fontdata,tree[i], 0, FNTHEIGHT*(i+1));
  }
  SDL_RenderPresent(s->renderer);
  SDL_UpdateWindowSurface(s->win);
  Neill_SDL_SetDrawColour(s,10,100,100);
  SDL_RenderClear(s->renderer);
  while(!s->finished){
    SDL_Delay(100);
    N_SDL_print(t,4*maxDepth,maxDepth,s,fontdata);
    SDL_RenderPresent(s->renderer);
    SDL_UpdateWindowSurface(s->win);
    Neill_SDL_Events(s);
  }
  SDL_FREE(s);

}
void N_SDL_print(Huf *t, int x,int maxDepth, SDL_Simplewin *s,fntrow fontdata[FNTCHARS][FNTHEIGHT])
{
  int offset=0;
  if(t==NULL){
    return;
  }
   Neill_SDL_SetDrawColour(s,255,255,255);
  if(t->parent!=NULL&&t->parentDirection==left){
    SDL_RenderDrawLine(s->renderer, x*FNTWIDTH+FNTWIDTH/2, FNTHEIGHT*(t->depth*2-1/2),
       t->parent->SDLx*FNTWIDTH+FNTWIDTH/2, FNTHEIGHT*(t->parent->depth*2-1/2));
  }
  if(t->parent!=NULL&&t->parentDirection==right){
    SDL_RenderDrawLine(s->renderer, x*FNTWIDTH+FNTWIDTH/2, FNTHEIGHT*(t->depth*2-1/2),
       t->parent->SDLx*FNTWIDTH+FNTWIDTH/2, FNTHEIGHT*(t->parent->depth*2-1/2));
  }
  t->SDLx=x;
  Neill_SDL_DrawChar(s,fontdata, t->c, FNTWIDTH*x, FNTHEIGHT*t->depth*2);
  offset=maxDepth-t->depth;
  N_SDL_print(t->left, x-offset,maxDepth, s,fontdata);
  N_SDL_print(t->right, x+offset,maxDepth, s,fontdata);

}
void SDL_FREE(SDL_Simplewin *s)
{
  SDL_RenderClear(s->renderer);
  SDL_DestroyRenderer(s->renderer);
  SDL_DestroyWindow(s->win);
  s->renderer=NULL;
  s->win=NULL;
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
      fprintf(stdout,"%s\n",tree[i]);
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
  if(tree==NULL){
    fprintf(stderr,"Unable to malloc rows\n");
    exit(1);
  }
  for (i = 0; i<=R.height; i++){
    tree[i] = (char*) malloc((R.width+1)*sizeof(char));
    if(tree[i]==NULL){
      fprintf(stderr,"Unable to malloc column %d\n",i);
      exit(1);
    }
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
int findMaxDepth(Huf *t,int depth)
{
  if(t==NULL){
    return depth;
  }
  depth=max(depth,t->depth);
  depth=max(findMaxDepth(t->left,depth),depth);
  depth=max(findMaxDepth(t->right,depth),depth);
  return depth;
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
int ScanArray(Huf nodes[])
{
  int i=0,j=0,a=ASCII;
  do{
    i=findLeastFreq(nodes);
    nodes[i].used=1;
    j=findLeastFreq(nodes);
    nodes[j].used=1;
    nodes[a].freq=nodes[i].freq+nodes[j].freq;
    nodes[i].parent=&nodes[a];
    nodes[j].parent=&nodes[a];
    nodes[i].parentDirection=right;
    nodes[j].parentDirection=left;
    nodes[a].left=&nodes[i];
    nodes[a].right=&nodes[j];

    a++;
    }while(i&&j);
    nodes[i].parent=NULL;
  return i;
}
void coding(Huf *t)
{
  char i[2];
  char j[2];
  if(t->left==NULL && t->right==NULL){
   return;
  }
  i[0]='0';
  j[0]='1';
  i[1]=j[1]='\0';
  /*if(t->code==NULL){
    strcat(t->left->code,i);
    strcat(t->right->code,j);
  }*/
  strcpy(t->left->code,t->code);
  strcpy(t->right->code,t->code);
  if(strcat(t->left->code,i)==NULL){
    fprintf(stderr,"Unale to perform ""strcat""\n");
    exit(1);
  }
  if(strcat(t->right->code,j)==NULL){
    fprintf(stderr,"Unale to perform ""strcat""\n");
    exit(1);
  }
  coding(t->left);
  coding(t->right);
}
Rect findNodeCoords(Huf *t, Rect C)
{
  if(t==NULL){
    return C;
  }
  t->x=C.width+1;
  t->y=C.height+C.y;
  C.height++;
  C=findNodeCoords(t->left, C);
  C.y--;
  if(t->right!=NULL){
    C.width++;
    C=findNodeCoords(t->right, C);
  }
  return C;
}
int findLeastFreq(Huf A[])
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
    A[i].code=NULL;
    A[i].bitLength=0;
    A[i].depth=0;
    A[i].used=0;
    A[i].freq=0;
    A[i].parent=NULL;
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
  for(i=0;i<length;i++){
    if(A[i].code!=NULL){
      if(!isprint(A[i].c)&& A[i].c!='@'){
        fprintf(stdout,"%c%d%c: %20s (%3d * %7ld)\n",'"',
        A[i].c,'"',A[i].code,A[i].bitLength,A[i].freq);
      }
      else{
        fprintf(stdout,"%c%c%c : %20s (%3d * %7ld)\n",'"',
        A[i].c,'"',A[i].code,A[i].bitLength,A[i].freq);
      }
    }
  }
}
Rect rectInit(Rect R)
{
  R.x=R.y=R.height=0;
  R.width=-1;
  return R;
}
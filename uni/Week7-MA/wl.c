/*last version*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct ladder{
  struct ladder *parent;
  int depth;
  int index;
  int used;
  char *s;
  struct ladder *next;

};
typedef struct ladder Ladder;

int findMaxLength(char *fileN);

char *userInput();
/*takes input from file and builds a list using AllocateNode*/
void importList(char *fileN, Ladder *l, int m);
/*returns a node to the end of the list*/
Ladder *AllocateNode(char *s, int m);
/*print list to a file*/
void filePrintList(Ladder *l,FILE *out);
/*checks if words are in the list - returns 1 if true*/
int check(char *w1, Ladder *l);
/*marks input word's children*/
int mark(char *w1, char *w2,Ladder *l,Ladder *c);
/*returns editing distance of two words*/
int fEditDist(char *t1, char *t2);
/*returns a pointer to the struct that contains char w1*/
Ladder *search(char *w1,Ladder *l);
Ladder *searchDepth(int d,Ladder *l);
/*print list from child to parent*/
void parentPrintList(Ladder *l);
/*freeing everything*/
void freedom(Ladder *l);

int main (int argc, char **argv)
{
  int i=1,r,maxWordLength;
  char *fileN;
  char *w1=NULL,*w2=NULL;
  FILE *output;
  Ladder *start, *current;
  if(argc==2){
    fileN=argv[1];
    output=fopen(fileN,"r");
    if(output==NULL){
      printf("Incorrect file name\n");
      return 1;
    }
  }
  else{
    printf("File name not indicated\n");
    return 1;
  }
  output=fopen("ladder.log", "w");
  start=AllocateNode(" ",10);
  maxWordLength = findMaxLength(fileN);
  printf("%d\n",maxWordLength );
  importList(fileN,start,maxWordLength);
  fprintf(stderr,"Source word: ");
  w1=userInput();
  fprintf(stderr,"Target word: ");
  w2=userInput();
  if(strlen(w1)!=strlen(w2)){
    printf("The two words must have the same length\n");
    return -1;
  }
  if (check(w1,start)!=1){
    return -1;
  }
  if (check(w2,start)!=1){
    return -1;
  }
  current=search(w1,start);
  r=mark(w1,w2,start,current);
  while(current!=NULL && r){
    for(i=1;r;){
      current=searchDepth(i,start);
      /*printf("%d--%s\n",i,current->s );*/
      if(current!=NULL){
        r=mark(current->s,w2,start,current);
        /*printf("%d is not NULL\n",r);*/
      }
      if(r==-1)
      i++;
    }
  }
  printf("%d\n",current->depth );
  filePrintList(start,output);
  fclose(output);
  freedom(start);
  return 0;
}
int userInput1(char *w1, char *w2)
{
  printf(  "Source word: ");
  assert(scanf("%s",w2 ));
  printf(  "Target word: ");
  assert(scanf("%s",w1 ));
  if(strlen(w1) != strlen(w2)){
    printf("The words must have the same length\n");
    return 0;
  }
  else{
    return 1;
  }
}
char *userInput(int m)
{
  char *w1;
  w1=(char *)malloc(m);
  assert(fscanf(stdin,"%s",w1 ));
  if(w1==NULL){
    printf("w1=null\n");
    return 0;
  }

  return w1;
}
int findMaxLength(char *fileN)
{
  unsigned int max=0,i=0;
  char c;
  FILE *dictionary;
  dictionary = fopen(fileN,"r");
  while((c = fgetc(dictionary)) && c != EOF){
    if (c!='\n'){
      i++;
    }
    else{
      if(max<i){
        max=i;
        printf("%d\n",max );
      }
        i=0;
    }
  }
  return max;
}
void parentPrintList(Ladder *l)
{
  do{
    printf("Word %6d : %5s, used: %d, depth: %d\n",l->index , l->s,l->used,l->depth);
    l = l ->parent;
  }while(l != NULL);
  printf("END OF LIST\n");
}
void parentPrintList1(Ladder *l)
{
  do{
    printf("%s->", l->s);
    l = l ->parent;
  }while(l!= NULL);
  printf("END OF LIST\n");
}
Ladder *search(char *w1,Ladder *l)
{
  while(strcmp(w1,l->s)){
    l=l->next;
  }
  return l;
}
Ladder *searchDepth(int d,Ladder *l)
{
  while( l->used != 0 || (l->depth == 0||l->depth<d-1)){
    if(l->next==NULL){
      return NULL;
    }
    else{
      l=l->next;
    }
  }
  return l;
}
int mark( char *w1, char*w2, Ladder *l,Ladder *c)
{
  int cnt=0;
  c->used=1;
  while(l!=NULL){
   if(l->used==0 && strlen(w1)==strlen(l->s) && fEditDist(l->s,c->s)==1){
   l->depth=c->depth+1;
   l->parent=c;
   cnt--;
   if(!strcmp(l->s, w2)){
     parentPrintList(l);
    return 0;
  }
   }
   l=l->next;
  }
  if(cnt==0){
  return -1;
  }
  else{ return cnt-1;}
}
int fEditDist(char *t1, char *t2)
{
  unsigned int i;
  int eDist=0;
  for(i=0;i<strlen(t1);i++){
    if(t1[i]!=t2[i]){
      eDist++;
    }

  }
  return eDist;
}
void importList(char *fileN, Ladder *l, int m)
{
  int i=1;
  char *buffer;
  FILE *dictionary;
  dictionary = fopen(fileN,"r");
  buffer=(char *)malloc(m);
  assert(fscanf(dictionary,"%s",buffer));
  strcpy(l->s,buffer);
  l->depth=0;
  l->index=i;
  l->parent=NULL;
  l->used=0;
  i++;
  while(fscanf(dictionary,"%s",buffer)==1){
    l->next=AllocateNode(buffer,m);
    l->next->depth=0;
    l->next->index=i;
    l->next->parent=NULL;
    l->next->used=0;
    if(l->next==NULL){
      printf("could'n allocate node %d\n",i);
    }
    l=l->next;
    l->next=NULL;
    i++;
  }
  free(buffer);
}
Ladder *AllocateNode(char *s, int m)
{
   Ladder *p;
   p = (Ladder *)malloc(sizeof(Ladder));
   if(p==NULL){
      printf("Cannot Allocate Node\n");
      exit(2);
   }
   p->s=(char *)malloc(m+2);
   if (p->s==NULL){
     printf("NULL\n" );
     return 0;
   }
   strcpy(p->s, s);
   p->next = NULL;
   p->parent=NULL;
   return p;
}
int check(char *w1, Ladder *l)
{
  while(l!=NULL){
    if(strcmp(w1,l->s)==0){
      printf("%s exists\n",w1 );
      return 1;
    }
  l=l->next;
  }
  return 0;
}
void filePrintList(Ladder *l,FILE *out)
{
  int i=1;
  fprintf(stderr,"file printing\n");
  do{
    fprintf(out,"Word %3d : %5s, used: %d, depth %d\n",i, l->s,l->used,l->depth);
    if(l->parent!=NULL){
      fprintf(out, "parent: %s\n",l->parent->s );
    }
    else{fprintf(out,"\n");}
    l = l ->next;
    i++;
  }while(l != NULL);
  fprintf(out,"END OF LIST\n");
}
void freedom(Ladder *l)
{
  do{
    free(l->s);
    free (l);
    l=l->next;
  }while(l!=NULL);
}

/*last working version*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define W_LENGTH 10

struct ladder{
  struct ladder *parent;
  int depth;
  int index;
  int used;
  char s[W_LENGTH];
  struct ladder *next;

};
typedef struct ladder Ladder;

/*takes input from file and builds a list using AllocateNode*/
void importList(char *fileN, Ladder *l);
/*returns a node to the end of the list*/
Ladder *AllocateNode(char *s);
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
  int i=1,r;
  char *fileN;
  char w1[W_LENGTH],w2[W_LENGTH];
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
  printf(  "Source word: ");
  assert(scanf("%s",w1 ));
  printf(  "Target word: ");
  assert(scanf("%s",w2 ));
  output=fopen("ladder.log", "w");
  start=AllocateNode(" ");
  current=start;
  importList(fileN,current);
  if (check(w1,start)!=1){
    return 1;
  }
  if (check(w2,start)!=1){
    return 1;
  }
  current=search(w1,start);
  r=mark(w1,w2,start,current);
  while(current!=NULL && r){
    for(i=1;r;i++){
      current=searchDepth(i,start);
      r=mark(current->s,w2,start,current);
    }
  }
  filePrintList(start,output);
  fclose(output);
  current=start;
  freedom(start);
  return 0;
}

void parentPrintList(Ladder *l)
{
  do{
    printf("Word %5d : %5s, used: %d, depth: %d\n",l->index , l->s,l->used,l->depth);
    l = l ->parent;
  }while(l != NULL);
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
  while( l->used != 0 || l->depth != d){
    if(l->next==NULL){
      return NULL;
    }
    else{
      l=l->next;
    }
  }
  return l;
}
int mark(char *w1, char*w2, Ladder *l,Ladder *c)
{
  c->used=1;
  while(l!=NULL){
   if(l->used==0 && strlen(w1)==strlen(l->s) && fEditDist(l->s,c->s)==1){
   l->depth=c->depth+1;
   l->parent=c;
   if(!strcmp(l->s, w2)){
     parentPrintList(l);
    return 0;
  }
   }
   l=l->next;
  }
  return 1;
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

void importList(char *fileN, Ladder *l)
{
  int i=1;
  char buffer[W_LENGTH];
  FILE *dictionary;
  dictionary = fopen(fileN,"r");
  assert(fscanf(dictionary,"%s",buffer));
  strcpy(l->s,buffer);
  l->depth=0;
  l->index=i;
  l->parent=NULL;
  l->used=0;
  while(fscanf(dictionary,"%s",buffer)==1){
    l->next=AllocateNode(buffer);
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
}

Ladder *AllocateNode(char *s)
{
   Ladder *p;
   p = (Ladder *)malloc(sizeof(Ladder));
   if(p==NULL){
      printf("Cannot Allocate Node\n");
      exit(2);
   }

   strcpy(p->s, s);
   p->next = NULL;
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
  while(l!=NULL){
    free (l);
    l=l->next;
    }
}

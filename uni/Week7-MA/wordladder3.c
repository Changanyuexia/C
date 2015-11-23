/*this is a spellchecker input one word and executes
an exhoustive searche from the top till it finds the word
cfaster version could be created by indexing first character for example*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define L_LENGTH    3000
#define W_LENGTH      10
#define NUMBER  L_LENGTH
#define SIZE_OF_ALPHA 26
#define NUM           48
#define INT2CHAR      97

struct word{
  int index;
  char s[W_LENGTH];
};
/*sould merge the two structures*/
typedef struct word Word;

struct  ladder{
  struct ladder *parent;
  int isParent;
  int index;
  int depth;
  int used;
  char s[W_LENGTH];
  struct ladder *next;
};

typedef struct ladder Ladder;

void importList(char A[L_LENGTH][W_LENGTH], Ladder *l);
int insert(char buf[W_LENGTH], char A[L_LENGTH][W_LENGTH],int i);
void printWrong(char *s);
void printCorrect(char *s, int i);
void swap(char A[L_LENGTH][W_LENGTH],int i);
void printA(char A[L_LENGTH][W_LENGTH],char B[L_LENGTH][W_LENGTH],char *fileN);
void printN(char A[L_LENGTH][W_LENGTH]);
int check(char *s,char A[L_LENGTH][W_LENGTH], int wordNum);
int fEditDist(char *t1, char *t2);
int checkStep3(int j, Word t1, Word t2, Ladder* p, Ladder* c);
void PrintList(Ladder *l);
void parentPrintList(Ladder *l);
void filePrintList(Ladder *l,FILE *out);
void step(Word t1, Word t2, Ladder* p);
Ladder *AllocateNode(char *s);
void compare(int i,Word w2, Word wtemp,Ladder *start,Ladder *current);
int main(int argc, char **argv)
{
  int i=0, j=2;
  int editD;
  char words[L_LENGTH][W_LENGTH];
  /*char wordsOrig[L_LENGTH][W_LENGTH];*/
  char buf[W_LENGTH];
  char *fileN;
  FILE *fp, *output;
  Word w1,w2,wtemp;
  Ladder *start, *current;
  if(argc==2){
    fileN=argv[1];
  }
  else{
    printf("could not load file\n");
    return 1;
  }

  fp=fopen(fileN, "r");
  output=fopen("ladder.log", "w");
  while(fscanf(fp,"%s",buf)==1 && i<NUMBER){
    insert(buf,words,i);
    i++;
  }
  printf("END\n");
  fclose(fp);
  start=AllocateNode(words[0]);
  printf("start->s:%s\n",start->s );
  importList(words, start);
  printf("printing List\n");
  PrintList(start);
  printf("\n------------------------------- \n-------------------------------\n");
  printf(  "Source word: ");
  assert(scanf("%s",w1.s));
  printf(  "Target word: ");
  assert(scanf("%s",w2.s));
  /*i assigns the maximum index value A[<i]*/
  w1.index = check(w1.s,words,i);
  w2.index = check(w2.s,words,i);
  editD=fEditDist(w1.s,w2.s);
  fprintf(output,"cat-dog = %d\n",editD );
    current=start;

  while(strcmp(current->s,w1.s)&& current!=NULL){
    current=current->next;
  }
  fprintf(output, "%s\n",current->s );
  checkStep3(1,w1,w2,start,current);
  current=start;
  compare(1,w2,wtemp,start,current);
  current=start;
  while(current!=NULL){
  while(current->depth!=editD-j){
    current=current->next;
  }
  if(current!=NULL){
  compare(j,w2,wtemp,start,current);
  parentPrintList(current);
  }
 current=current->next;
  }
current=start;
  filePrintList(start,output);
    /*parent pointer and mark used ones and free everything*/
  while(current!=NULL){
    free(current);
    current=current->next;
    printf("freed");
    }
  /*printA(words,wordsOrig,fileN);*/
  printf("close out file\n");
  fclose(output);
  printf("-----------------------------------\n");
  return -1;
}
void compare(int i,Word w2, Word wtemp,Ladder *start,Ladder *current)
{
  int j;
  for(j=i;j<=3;j++){
  current=start;
  while((current->used==0 || current->depth!=j-1) && current->next!=NULL){
    current=current->next;
  }
  strcpy(wtemp.s,current->s);
printf("loop %d  %s\n", j, current->s );
  printf("%d\n",checkStep3(j,wtemp,w2,start,current));
  current=current->next;

}
}
void parentPrintList(Ladder *l)
{
  printf("ole ole\n");
  do{
    printf("Word %4d : %5s, used: %d, depth: %d\n",l->index, l->s,l->used,l->depth);
    l = l ->parent;
  }while(l != NULL);
  printf("END OF LIST\n");

}
int checkStep3(int j, Word t1, Word t2, Ladder* p, Ladder* c)
{
  Word tc;
  int i=0;
  c->used=1;
  c->isParent=1;
  while(p!=NULL){
    strcpy(tc.s,p->s);
  if(p->used==0 &&strlen(t1.s)==strlen(p->s)&&fEditDist(c->s,tc.s)==1){
    p->depth=j;
    p->parent=c;
    p->used=1;
    i++;
  }
    p=p->next;
  }
  return strcmp(t2.s,tc.s);
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
void importList(char A[L_LENGTH][W_LENGTH], Ladder *l)
{
  int i;
  for(i=1;isalpha(A[i][0]);i++){
    l->isParent=0;
    l->depth=0;
    l->index=i;
    l->parent=NULL;
    l->used=0;
    l->next=AllocateNode(A[i]);
    if(l->next==NULL){
      printf("could'n allocate node\n");
    }
    l=l->next;
    l->next=NULL;
  }
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
void PrintList(Ladder *l)
{
  int i=1;
  printf("ole ole\n");
  do{
    printf("Word %3d : %5s, used: %d\n",i, l->s,l->used);
    l = l ->next;
    i++;
  }while(l != NULL);
  printf("END OF LIST\n");
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
int check(char *s, char A[L_LENGTH][W_LENGTH],int wordNum)
{
  int i=0;
  while(i < wordNum){
    if(strcmp(A[i], s) == 0){
      printCorrect(s,i);
      return(i);
    }
    i++;
  }
  printWrong(s);
  return(0);
}

int insert(char buf[W_LENGTH], char A[L_LENGTH][W_LENGTH],int i)
{
  char temp[W_LENGTH];
  /*First Input*/
  if(i==0){
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

void printWrong(char *s)
{
/*printf("                     *        *\n");
printf("                       *    *  \n");
printf("                         **    \n");
printf("                       *    *  \n");
printf("                     *        *\n");*/
printf("%s is not a word              \n\
------------------------------------\n",s);
}
void printCorrect(char *s, int i)
{
  /*printf("                              *\n");
  printf("                  *         *  \n");
  printf("                    *    *    \n");
  printf("                      **  \n");
  printf("                             \n");*/
  printf("%s is the word %d in the array)\n\
------------------------------------\n",s,i);
}
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

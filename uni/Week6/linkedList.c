#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
  char name[20];
  struct node *next;
  struct node *prev;
};
typedef struct node Node;

Node *AllocateNodeUp(char *s);
void PrintList(Node *l);
void PrintListRev(Node *l);
void sort(Node *l);

int main(int argc, char **argv)
{
  Node *start, *current, *last;
  char name[30];
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
   printf("input name\n");
   if (fscanf(fp,"%s",name )==1){
      start=current=AllocateNodeUp(name);
   }
   else{
      printf("cound not scan\n");
      return 1;
    }
     while(fscanf(fp,"%s", name) == 1 &&
           name[0]!=EOF){
      last=current->next = AllocateNodeUp(name);
      current->next->prev=current;
      current=current->next;
       }

  PrintList(start);
  sort(start->next);
  PrintList(start);
  printf("%s\n", last->name);
  /*PrintListRev(last);*/
  fclose(fp);
  return(0);
}

Node *AllocateNodeUp(char *s)
{
Node *p;
p = (Node *)malloc(sizeof(Node));
if(p==NULL){
printf("Cannot Allocate Node\n");
exit(2);
}

strcpy(p->name, s);
p->next = NULL;
return p;
}

void PrintList(Node *l)
{
printf("\n");
do{
printf("Word : %s\n", l->name);
l = l ->next;
}while(l != NULL);
printf("END\n");
}
void sort(Node *l){
  Node *p;
  p = (Node *)malloc(sizeof(Node));
  while(l->next->next!=NULL){
    printf("%4d  %s-   -%s\n", strcmp(l->prev->name,l->name) ,l->prev->name, l->name);
    while(strcmp(l->name,l->next->name)>0){
    p->next=l->prev;
    p->prev=NULL;
    strcpy(p->name,l->name);
    l->prev->next=l->next;
    l->next->prev=l->prev;
    l->prev->prev=p;
    l=p;
    printf("ws edw\n");
    }

  }
  free(p);
}
void PrintListRev(Node *l)
{
printf("\n");
do{
printf("Word : %s\n", l->name);
l = l ->prev;
}while(l != NULL);
printf("END\n");
}

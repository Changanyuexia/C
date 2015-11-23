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

      current->next = AllocateNodeUp(name);
      current=current->next;
      last=current;
/*printf("%d\n",strcmpy(current->next->name,current->name) );*/
      /*       while(current->prev!=NULL&&strcmp(current->next->name,current->name)<0){
               current->next->prev = current->prev;
               current->prev->next = current;

             }*/

   }
  start->prev=NULL;
  printf("%s\n", last->name );
    printf("ws edw\n" );
  PrintList(start);
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
printf("Word : %s  strcmpr:%4d\n", l -> name,strcmp(l->name,l->prev->name));
l = l ->next;
}while(l != NULL);
printf("END\n");
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

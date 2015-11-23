#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
  char word[20];
  struct node *next;
  struct node *prev;
};
typedef struct node Node;

Node *insert(Node *t,char *s);
Node *AllocateNode(char *s);
Node *AllocateNodeSorted(char *s, Node *l);
void PrintList(Node *l);
void PrintListRev(Node *l);
Node *sort(Node *l);
Node *sort2(Node *l);

int main(int argc, char **argv)
{
  Node *start, *current, *last;
  char buf[30];
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
                            /*allocate first node*/
  if (fscanf(fp,"%s",buf )==1){
    start=current=AllocateNode(buf);
  }
  else{
    printf("cound not scan\n");
    return 1;
  }
                           /*allocate second node*/

  if (fscanf(fp,"%s",buf )==1){
    last=current=AllocateNode(buf);
    current->prev=start;
    current->prev->next=current;
  }
  else{
    printf("cound not scan\n");
    return 1;
  }
  current=last;
  if (fscanf(fp,"%s",buf )==1){
    last=current=AllocateNode(buf);
    current->prev=start;
    current->prev->next=current;
  }
  else{
    printf("cound not scan\n");
    return 1;
  }

start=insert(start,buf);
/*
  while(fscanf(fp,"%s", buf) == 1 &&
    buf[0]!=EOF){
      if(strcmp(buf,current->)>0){
current=current->next}
    current->next = AllocateNode(buf);
    current->next->prev=current;
    current=current->next;
  }
  current=start;
  */
  PrintList(start);
  printf("last %s\ncurrent %s\n",last->word,current->word);
  /*PrintListRev(last);*/
  fclose(fp);
  return(0);
}
Node *insert(Node *t,char *s)
{
  Node *p;
  Node *q;
  q=t->next;
  /*empty list waiting to be coded
  if(t==NULL){
  p=AllocateNode(s);
  return p;
  }*/
  if(strcmp(s,t->word)<0){
    p = AllocateNode(s);
    p->next = t;
    return t;
  }
  do{

/*insert end*/
    if (q->next ==NULL){
       p = AllocateNode(s);
       q->next=p;
    }
/* combine  insert end   insert in the middle*/
/*insert in the middle*/

     if ((strcmp(s,q->word)>0  )&& (strcmp(s,q->next->word)>0)){
       p =AllocateNode(s);
       p->next = q-> next;
       q->next =p;
     }
     q=q->next;
  }while(q!=NULL);
  return q;
}
Node *AllocateNode(char *s)
{
   Node *p;
   p = (Node *)malloc(sizeof(Node));
   if(p==NULL){
      printf("Cannot Allocate Node\n");
      exit(2);
   }

   strcpy(p->word, s);
   p->next = NULL;
   return p;
}
/*
Node *AllocateNodeSorted(char *s, Node *l)
{
   Node *p;
   p = (Node *)malloc(sizeof(Node));
   if(p==NULL){
      printf("Cannot Allocate Node\n");
      exit(2);
   }
   printf("%d\n", strcmp(s,l->name));

   strcpy(p->name, s);
   p->next = NULL;
   return p;
}
Node *sort(Node *l)
{
  Node *p;
  p = (Node *)malloc(sizeof(Node));
  if(p==NULL){
     printf("Cannot Allocate Node\n");
     exit(2);
  }
     printf("%s %s\n",l->name,l->next->name );
   if(strcmp(l->name,l->next->name)>0){
   strcpy(p->name, l->next->name);
     p->next=l;
     l->prev=p;
     l->next=l->next->next;
     p->prev=NULL;
   }
   else{
     p=l;
   }
   return(p);
}

Node *sort2(Node *l)
{
  Node *p;
  p = (Node *)malloc(sizeof(Node));
  if(p==NULL){
     printf("Cannot Allocate Node\n");
     exit(2);
  }
     printf("%s  %s\n",l->name ,l->next->name );
   if(strcmp(l->name,l->next->name)>0){
   strcpy(p->name, l->next->name);
     p->prev=l->prev;
     p->next=l->next;
     l->prev=p;
     l->next=l->next->next;
     l->prev->next=p;
   }
   else{
     p=l;
   }
   return(p);
}

*/
void PrintList(Node *l)
{
   int i=1;
   printf("\n");
   do{
   printf("Word %3d : %s\n",i, l->word);
   l = l ->next;
   i++;
   }while(l != NULL);
   printf("END\n");
}
void PrintListRev(Node *l)
{
printf("\n");
do{
printf("Word : %s\n", l->word);
l = l ->prev;
}while(l != NULL);
printf("END\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct list{
  int index;
  char *s;
  struct list *next;
};
typedef struct list List;

/*Takes input from file and builds a list using AllocateNode*/
int importList(char *fileN, List *l, int m);
/*Returns a node to the end of the list*/
List *AllocateNode(char *s, int m);
/*fREE STUFF*/
void listMemFree(List *l);

int main(void)
{
  char *dictionary="eowl_english_words.txt";
  List *top=NULL;
  importList(dictionary,top,20);
  listMemFree(top);
  return 0;
}


int importList(char *fileN, List *l, int m)
{
  int i=1;
  char *buffer;
  FILE *dictionary;
  dictionary = fopen(fileN,"r");
  buffer=(char *)malloc(m+2);
  /*assert(fscanf(dictionary,"%s",buffer));
  strcpy(l->s,buffer);
  printf("%s--%s\n",buffer,l->s );
  l->index=i;*/
  while(fscanf(dictionary,"%s",buffer)==1){
    if(l==NULL){AllocateNode(buffer,m);}
    l->next=AllocateNode(buffer,m);
    l=l->next;
  i++;
  }
  printf("%d words read\n",i );
  free(buffer);
  return 0;
}
List *AllocateNode(char *s, int m)
{
   List *p;
   p = (List *)malloc(sizeof(List));
   if(p==NULL){
      printf("Cannot Allocate Node\n");
      return 0;
   }
/*It allocates the largest string's lenght plus 2, for safety*/
   p->s=(char *)malloc(m+2);
   if (p->s==NULL){
     printf("NULL\n" );
     return 0;
   }
   strcpy(p->s, s);
   return p;
}

void listMemFree(List *l)
{
  List *tmp;
  while(l->next!=NULL){
    tmp=l;
    l=l->next;
    free(tmp->s);
	  free(tmp);
  }
  free(l->s); /*frees the last node*/
  free(l);
}

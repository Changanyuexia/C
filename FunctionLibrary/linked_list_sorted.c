#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct llist {
   int num;
   struct llist *next;
};


void printlist(struct llist *t);
struct llist *myalloc(int i);
struct llist *insert(struct llist *t, int i);

int main(void)
{

   int i, j;
   struct llist *top = NULL;

   for(j=0; j<15; j++){
      i = rand()%100;
      top = insert(top, i);
      printlist(top);
   }

   return 0;

}

struct llist *insert(struct llist *t, int i)
{

   struct llist *p;
   struct llist *q;
   /* Empty List */
   if(t == NULL){
      return myalloc(i);
   }

   /* At front */
   if(i < t->num){
      p = myalloc(i);
      p->next = t;
      return p;
   }

   q = t;
   do{

      /* Insert end */
      if(q->next == NULL){
         p = myalloc(i);
         q->next = p;
         return t;
      }

      /* Insert middle */
      if((i >= q->num) && (i <= q->next->num)){
         p = myalloc(i);
         p->next = q->next;
         q->next = p;
         return t;
      }

      q = q->next;
   }while(q != NULL);
   return t;

}

struct llist* myalloc(int i)
{

   struct llist* p = (struct llist *)malloc(sizeof(struct llist));
   if(!p){
      fprintf(stderr, "PANIC\n");
      exit(1);
   }
   p->num = i;
   p->next = NULL;
   return p;

}


void printlist(struct llist* t)
{

   while(t != NULL){
      printf("%d ", t->num);
      t = t->next;
   }
   printf("\n");

}

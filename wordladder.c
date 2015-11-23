/*cat search until cot 
flag cat as parent (depth 0)---->>>pointer
search until dot
flag cot as parent (depth 1)
example in pdf reverse order
 fscan---psakse
*/
/*for you to pass a pointer to the top node to a function called by a funciton 
you have to put double pointer aka **t instead of *t  */


sort/insert
{
struct llist {
   int i;
   struct llist* next;
};

struct llist* myalloc(int i);
struct llist *insert(struct llist *t,int i)
int main (void)
{
   int i;
   struct llist *top = NULL;
   top = insert (top,i);
}
insert(){
/*if empty list*/
if t==NULL

return myalloc(i);
  struct llist *p;
  struct llist *q;
  if(i< t->i){
     p=myalloc(i);
     p->next = t;
     return p;
  }
do{

/*insert end*/
    if (q->next ==NULL){
       p =myalloc(i);
       q->next=p;
}
/* combine  insert end   insert in the middle*/
/*insert in the middle*/
     if (i>= q->i)&& (i,= q->next->i)){
       p =myalloc(i);
       p->next = q-> next;
       q->next =p;

   }
q=q->next;
}while(q!=NULL);
/*end of list*/
return t
}
}


myalloc(int i){
struct llist *p = (struct llist*) malloc(sizeof(struct llist);

}

/*Returns a pointer to the struct that contains char w1*/
Ladder *searchWord(char *w1,Ladder *l);
/*Returns a pointer that contains char w1 and of a certain depth*/
Ladder *searchDepth(int d,Ladder *l);
/*Checks if words are in the list - returns 1 if true*/
int check(char *w1, Ladder *l);

struct ladder{
  struct ladder *parent;
  int depth;
  int index;
  int used;
  char *s;
  struct ladder *next;
};
typedef struct ladder Ladder;

int main(void)
{
  char *w1;
  Ladder *start;
  searchWord(w1, start)
}

Ladder *searchWord(char *w1,Ladder *l)
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
int check(char *w1, Ladder *l)
{
  while(l!=NULL){
    if(strcmp(w1,l->s)==0){
      return 1;
    }
  l=l->next;
  }
  printf("%s is not in the dictionary\n",w1 );
  return 0;
}

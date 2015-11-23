
struct ladder{
  struct ladder *parent;
  int depth;
  int index;
  int used;
  char *s;
  struct ladder *next;
};
typedef struct ladder Ladder;

/*Takes input from file and builds a list using AllocateNode*/
int importList(char *fileN, Ladder *l, int m);
/*Returns a node to the end of the list*/
Ladder *AllocateNode(char *s, int m);

int importList(char *fileN, Ladder *l, int m)
{
  int i=1;
  char *buffer;
  FILE *dictionary;
  dictionary = fopen(fileN,"r");
  buffer=(char *)malloc(m);
  assert(fscanf(dictionary,"%s",buffer));
  strcpy(l->s,buffer);
  l->index=i;
  while(fscanf(dictionary,"%s",buffer)==1){
    l->next=AllocateNode(buffer,m);
    l=l->next;
  i++;
  }
  printf("%d words read\n",i );
  free(buffer);
  return 0;
}
Ladder *AllocateNode(char *s, int m)
{
   Ladder *p;
   p = (Ladder *)malloc(sizeof(Ladder));
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
   p->depth  = 0;
   p->used   = 0;
   p->next   = NULL;
   p->parent = NULL;
   return p;
}

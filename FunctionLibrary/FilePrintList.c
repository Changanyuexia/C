/*Prints list to a file*/
void filePrintList(Ladder *l,FILE *out);

void filePrintList(Ladder *l,FILE *out)
{
  int i=1;
  fprintf(stderr,"file printing\n");
  do{
    fprintf(out,"Word %6d : %10s, used: %d, depth %3d\n",i, l->s,l->used,l->depth);
    if(l->parent!=NULL){
      fprintf(out, "parent: %s\n",l->parent->s );
    }
    else{fprintf(out,"\n");}
    l = l ->next;
    i++;
  }while(l != NULL);
  fprintf(out,"END OF LIST\n");
}

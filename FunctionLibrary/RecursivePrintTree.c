

char* PrintTreeLong(Huf *t)
{
  char *str, *rstr, *lstr;
  str = (char*) calloc(STRSIZE, sizeof(char));
  assert(str != NULL);
  if(t == NULL){
    strcpy(str, "*");
    return str;
  }
    lstr=PrintTreeLong(t->left);
    rstr=PrintTreeLong(t->right);
  if(!isgraph(t->c)){
    sprintf(str, "%d(%s)(%s)", t->c,
    lstr,rstr);
  }
  else{
    sprintf(str, "%c(%s)(%s)", t->c,
    lstr,rstr);
  }
  free(lstr);
  free(rstr);
  return str;
}

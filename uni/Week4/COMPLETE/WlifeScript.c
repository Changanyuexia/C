#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char **argv){
  time_t t;
  FILE *fp;
  char *fName;
  int i,x,y;
  if(argc==2){
     fName=argv[1];
  }
  else{return(0);}
  fp=fopen(fName,"w");
  fprintf(fp, "#Life1.06\n");
  for(i=0;i<99;i++){
      srand((unsigned) time(&t)+i);
      x=rand()%150;
      y=rand()%90;
      fprintf(stderr, "%d %d\n", x, y );
      fprintf(fp, "%d %d\n", x, y );
  }
  fclose(fp);
  printf("%s\n",fName );
  return(0);
}

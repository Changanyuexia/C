#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char **argv){
  FILE *fp;
  char *fName;
  int i, j, x, y;
  if(argc==2){
     fName=argv[1];
  }
  else{return(0);}
  fp=fopen(fName,"w");
fprintf(fp, "#Life1.06\n");
  for(i=0;i<9;i++){
    for(j=0;j<11;j++){
      x=i;
      y=x+j;
      fprintf(stderr, "%d %d\n", x, y );
      fprintf(fp, "%d %d\n", x, y );
    }
  }
  fclose(fp);
  printf("%s\n",fName );
  return(0);
}

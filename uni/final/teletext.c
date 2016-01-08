#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "neillsdl2.h"


#define SUCCESS 0
#define ERROR   1
#define WIDTH  40
#define HEIGHT 25
#define FNTFILENAME "m7fixed.fnt"

enum control {red=129,green,yellow,blue,magenta,cyan,
  singleHeight=140,doubleHeight,blackBack=156,newBack};

unsigned char **fileInput(char *s);
unsigned char **mallocArray(int width ,int height);
CharStyle changeCharStyle(CharStyle style, enum control code);
CharStyle changeGraphStyle(CharStyle style,  enum control code);
CharStyle reset(CharStyle style);
void printArray(unsigned char **A);
void SDL(unsigned char **A);

int main(int argc, char** argv)
{
  unsigned char **A;
  if(argc !=2 ){
    fprintf(stderr, "Bad Arguments\n");
    exit(ERROR);
  }
  A=fileInput(argv[1]);
  /*printArray(A);*/
  SDL(A);
  return SUCCESS;
}
unsigned char **fileInput(char *s)
{
  int i,j;
  FILE *fp;
  unsigned char **A;
  fp = fopen( s ,"rb");
  A = mallocArray( HEIGHT , WIDTH );
  for(i=0; i<HEIGHT;i++ ){
    printf("\n%d. ",i +1);
    for(j=0; j<WIDTH;j++){
      assert(fread(&A[i][j],1,1,fp));
        printf("%hu  ", A[i][j] );

    }
    printf("\n");
  }
  printf("short int :%lu , char, %lu\n",sizeof(short int),sizeof(char) );
  fclose(fp);
  return A;
}
unsigned char **mallocArray(int width ,int height)
{
  int i;
  unsigned char **A;
  A = (unsigned char**) malloc((height)*sizeof(unsigned char*));
  if(A==NULL){
    fprintf(stderr,"Unable to malloc rows\n");
    exit(ERROR);
  }
  for (i = 0; i<height; i++){
    A[i] = (unsigned char*) malloc((width)*sizeof(unsigned char));
    if(A[i]==NULL){
      fprintf(stderr,"Unable to malloc column %d\n",i);
      exit(ERROR);
    }
  }
  return A;
}
void printArray(unsigned char **A)
{
  int i,j;
  for(i=0; i<HEIGHT; i++){
    for(j=0; j<WIDTH;j++){
      printf("%c", A[i][j]-128 );
    }
    printf("\n");
  }
}
CharStyle changeGraphStyle(CharStyle style, enum control code)
{
  switch (code){
    case red:
      style.background.r=255;
      style.background.g=style.background.b=0;
      break;
    case green:
      style.background.g=255;
      style.background.r=style.background.b=0;
      break;
    case yellow:
      style.background.r=style.background.g=255;
      style.background.b=0;
      break;
    case blue:
      style.background.b=255;
      style.background.r=style.background.g=0;
      break;
    case magenta:
      style.background.b=style.background.r=255;
      style.background.g=0;
      break;
    case cyan:
      style.background.b=style.background.g=255;
      style.background.r=0;
      break;
    default:
      style.background.g=style.background.r=style.background.b=0;
      break;
  }
  return style;
}

CharStyle changeCharStyle(CharStyle style, enum control code)
{
  switch (code){
    case red:
      style.character.r=255;
      style.character.g=style.character.b=0;
      break;
    case green:
      style.character.g=255;
      style.character.r=style.character.b=0;
      break;
    case yellow:
      style.character.r=style.character.g=255;
      style.character.b=0;
      break;
    case blue:
      style.character.b=255;
      style.character.r=style.character.g=0;
      break;
    case magenta:
      style.character.b=style.character.r=255;
      style.character.g=0;
      break;
    case cyan:
      style.character.b=style.character.g=255;
      style.character.r=0;
      break;
    case doubleHeight:
      style.height=doubleH1;
      break;
    case singleHeight:
      style.height=singleH;
      break;
    default:
      style.character.g=style.character.r=style.character.b=255;
      break;
  }

  return style;
}
CharStyle reset(CharStyle style)
{
  style.background.r=style.background.g=style.background.b=0;
  style.character.r=style.character.g=style.character.b=255;
  style.height=singleH;
  return style;
}
void SDL(unsigned char **A)
{
  int i,j/*,k=FNT1STCHAR*/;
  CharStyle style, upperStyle;
  enum control ctrl;
  SDL_Simplewin sw;
  fntrow fontdata[FNTCHARS][FNTHEIGHT];
  Neill_SDL_ReadFont(fontdata,(char*) FNTFILENAME);
  Neill_SDL_Init(&sw, WIDTH*FNTWIDTH,HEIGHT*FNTHEIGHT);
  for(i=0;i<HEIGHT;i++){
    style=reset(style);
    for(j=0;j<WIDTH;j++){
      style.ox=j*FNTWIDTH;
      style.oy=i*FNTHEIGHT;
      if(A[i][j]==newBack){
        ctrl= A[i][j-1];
        style = changeGraphStyle(style, ctrl);
        Neill_SDL_DrawChar(&sw, fontdata, ' ', style);
      }
      else if(A[i][j]==blackBack){
        style.background.r=style.background.g=style.background.b=0;
        Neill_SDL_DrawChar(&sw, fontdata, ' ', style);
      }
      else if(128<A[i][j]&& A[i][j]<142){
        ctrl=A[i][j];
        style = changeCharStyle(style, ctrl );
        ctrl=A[i-1][j];
        upperStyle = changeCharStyle(style, ctrl );
        if(style.height==doubleH1&&upperStyle.height==doubleH1)
          style.height=doubleH2;
        Neill_SDL_DrawChar(&sw, fontdata, ' ', style);
      }
switch (style.height) {
  case singleH:
    Neill_SDL_DrawChar(&sw, fontdata, A[i][j]-128, style);
    break;
  case doubleH1:
  case doubleH2:
    Neill_SDL_DrawDoubleChar(&sw, fontdata, A[i][j]-128, style);
    break;
}

    }
  }
  SDL_RenderPresent(sw.renderer);

/*
  SDL_Delay(1000);
  Neill_SDL_SetDrawColour(&sw, 0, 0, 0);
  SDL_RenderClear(sw.renderer);

  for(i=0;i<HEIGHT && k<FNTCHARS+FNT1STCHAR ;i++){
    for(j=0;j<WIDTH ;j++){
    Neill_SDL_DrawChar(&sw, fontdata, k++, FNTWIDTH*j, FNTHEIGHT*i);
    }
  }
  SDL_RenderPresent(sw.renderer);
*/

  SDL_Delay(10000);

  SDL_Quit();
}
/*es para luego experimentos de fonts


fntrow fontDouble[FNTCHARS][2*FNTHEIGHT];
for(i=FNT1STCHAR;i<FNT1STCHAR+20;i++){
  for(j=0;j<FNTWIDTH;j++){
    printf("%hu ",fontdata[i][j]);
  }
  printf("\n");
}*/

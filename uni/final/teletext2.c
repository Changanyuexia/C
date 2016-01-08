/*-------CHECKS TO BE PERFORMED---------
  1.Error messages and printing
  2.Malloc / Free
  3.
  --------TASKS-------------------------
  1. Fix dependencies
*/
/*Message input HERE*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "neillsdl2.h"

void DrawSixel(SDL_Simplewin sw,int graphdata[3][2], CharStyle style);

int main(int argc, char** argv)
{
  CharStyle style[HEIGHT][WIDTH];
  unsigned char **A;
  if(argc !=2 ){
    fprintf(stderr, "Bad Arguments\n");
    exit(ERROR);
  }
  A=fileInput(argv[1]);
  /*printArray(A);*/
  parseForStyle(style,A);
  SDL(style,A);
  return SUCCESS;
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
CharStyle gmodeCheck(CharStyle style,unsigned char ctrl)
{
    switch (ctrl) {
      case contiguousG:
        style.grMode=contiguous;
        break;
      case separetedG:
        style.grMode=seperated;
        break;
    }

  return style;
}
void parseForStyle(CharStyle style[HEIGHT][WIDTH], unsigned char **A)
{
  CharStyle tempStyle;
  int i,j;
  for(i=0;i<HEIGHT;i++){
    tempStyle=reset(tempStyle);
    for(j=0;j<WIDTH;j++){
      if(FRSTCNTRLGRAPH<A[i][j]&&A[i][j]<LSTCNTRLGRAPH){
        tempStyle.dMode=graph;
        if(144<=A[i][j]&&A[i][j]<=151)
        tempStyle.graphics=changeColor(tempStyle.graphics,A[i][j]-16);
         switch (A[i][j]) {
           case contiguousG:
           case separetedG:
             tempStyle=gmodeCheck(tempStyle, A[i][j]);
             break;
           case newBack:
             tempStyle.background = changeColor(tempStyle.background, A[i][j-1]);
             break;
           case blackBack:
             tempStyle.background.r=tempStyle.background.g=tempStyle.background.b=0;
             break;
         }
      }
      if(FRSTCNTRLALPHA<=A[i][j] && A[i][j]<=LSTCNTRLALPHA){
        tempStyle.dMode=alpha;
        if(A[i][j]==singleHeight || A[i][j]==doubleHeight){
          if(i!=0)
            tempStyle.height=changeHeight(tempStyle.height,style[i-1][j].height,A[i][j]);

        }
        tempStyle.character = changeColor(tempStyle.character, A[i][j]);
      }
      if(i!=0 && tempStyle.height!=singleH && style[i-1][j].height==doubleH1){
        tempStyle.height=doubleH2;
      }
      style[i][j]=tempStyle;

    }
  }
}

CharHeight changeHeight(CharHeight height, CharHeight upperHeight, unsigned char code)
{
  switch (code) {
    case singleHeight:
      return singleH;
      break;
    case doubleHeight:
      return doubleH1;
      break;
  }
  return singleH;
}

Color changeColor(Color col, unsigned char code)
{
  switch (code){
    case red:
      col.r=255;
      col.g=col.b=0;
      break;
    case green:
      col.g=255;
      col.r=col.b=0;
      break;
    case yellow:
      col.r=col.g=255;
      col.b=0;
      break;
    case blue:
      col.b=255;
      col.r=col.g=0;
      break;
    case magenta:
      col.b=col.r=255;
      col.g=0;
      break;
    case cyan:
      col.b=col.g=255;
      col.r=0;
      break;
    case white:
      col.g=col.r=col.b=255;
      break;
  }

  return col;
}
CharStyle reset(CharStyle style)
{
  style.background.r=style.background.g=style.background.b=0;
  style.character.r=style.character.g=style.character.b=255;
  style.graphics.r=style.graphics.g=style.graphics.b=255;
  style.height=singleH;
  style.dMode=alpha;
  style.grMode=contiguous;
  return style;
}
void decodeSixels(int dots[3][2], int i)
{
  int a,b;
    for(a=0;a<3;a++){
      for(b=0;b<2;b++){
      dots[a][b]=0;
      }
    }
  if(i>=160){
    i-=160;
  }
  else{
    return;
  }
  if(i>=s_six){
    dots[2][1]=1;
    i-=s_six;
  }
  if(i>=s_five){
    dots[2][0]=1;
    i-=s_five;
  }
  if(i>=s_four){
    dots[1][1]=1;
    i-=s_four;
  }
  if(i>=s_three){
    dots[1][0]=1;
    i-=s_three;
  }
  if(i>=s_two){
    dots[0][1]=1;
    i-=s_two;
  }
  if(i>=s_one){
    dots[0][0]=1;
    i-=s_one;
  }
}
/*
void createGraphFont(short graphdata[GRAPHCHARS][3][2])
{
int i,x,y;
int dots[6];
for (i=0;i<GRAPHCHARS;i++){
decodeSixels(dots,i);
  for (y=0;y<3;y++){
    for (x=0;x<2;x++){

    }
  }
}
}
*/
void DrawSixel(SDL_Simplewin sw, int graphdata[3][2], CharStyle style)
{
  int i,j;
  SDL_Rect rectBack,rectSixel;
  rectBack.h=FNTHEIGHT;
  rectBack.w=FNTWIDTH;
  switch (style.grMode) {
    case contiguous:
      rectSixel.h=6;
      rectSixel.w=8;
      break;
    case seperated:
      rectSixel.h=4;
      rectSixel.w=6;
      break;
  }
  Neill_SDL_SetDrawColour(&sw,style.background.r, style.background.g, style.background.b);
  rectBack.x=style.ox;
  rectBack.y=style.oy;
  SDL_RenderFillRect(sw.renderer,&rectBack );
  for(i=0;i<3;i++){
    for(j=0;j<2;j++){
      if(graphdata[i][j]==1){
        Neill_SDL_SetDrawColour(&sw,style.graphics.r, style.graphics.g, style.graphics.b);
        rectSixel.x=style.ox+j*rectSixel.w;
        rectSixel.y=style.oy+i*rectSixel.h;
        SDL_RenderFillRect(sw.renderer,&rectSixel );
      }
    }
  }

}
void SDL(CharStyle style[HEIGHT][WIDTH], unsigned char **A)
{
  int i,j;
  SDL_Simplewin sw;
  fntrow fontdata[FNTCHARS][FNTHEIGHT];
  int graphdata[3][2];
  Neill_SDL_ReadFont(fontdata,(char*) FNTFILENAME);
  Neill_SDL_Init(&sw, WIDTH*FNTWIDTH,HEIGHT*FNTHEIGHT);
  for(i=0;i<HEIGHT;i++){
    for(j=0;j<WIDTH;j++){
      style[i][j].ox=j*FNTWIDTH;
      style[i][j].oy=i*FNTHEIGHT;
      if(style[i][j].dMode==graph){
        decodeSixels(graphdata,A[i][j]);
        DrawSixel(sw,graphdata,style[i][j]);
      }
      else if(style[i][j].dMode==alpha && (isprint(A[i][j]-128) || A[i][j]==255)){
        switch (style[i][j].height) {
          case singleH:
            Neill_SDL_DrawChar(&sw, fontdata, A[i][j]-128, style[i][j]);
            break;
          case doubleH1:
          case doubleH2:
            Neill_SDL_DrawDoubleChar(&sw, fontdata, A[i][j]-128, style[i][j]);
            break;
        }
      }
      else{  Neill_SDL_DrawChar(&sw, fontdata, ' ', style[i][j]);}
    }
  }
  /*
  SDL_RenderPresent(sw.renderer);


  SDL_Delay(1000);
  Neill_SDL_SetDrawColour(&sw, 0, 0, 0);
  SDL_RenderClear(sw.renderer);

  for(i=0;i<HEIGHT && k<FNTCHARS+FNT1STCHAR ;i++){
    for(j=0;j<WIDTH ;j++){
    Neill_SDL_DrawChar(&sw, fontdata, k++, FNTWIDTH*j, FNTHEIGHT*i);
    }
  }*/
  SDL_RenderPresent(sw.renderer);


  SDL_Delay(5000);

  SDL_FREE(&sw);
}

/*es para luego experimentos de fonts


fntrow fontDouble[FNTCHARS][2*FNTHEIGHT];
for(i=FNT1STCHAR;i<FNT1STCHAR+20;i++){
  for(j=0;j<FNTWIDTH;j++){
    printf("%hu ",fontdata[i][j]);
  }
  printf("\n");
}*/

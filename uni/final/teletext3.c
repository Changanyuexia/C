/*ERROR
  1.New background reads color from previous or next character??
  2.No background color for lfc.m7 or panda.m7 */
/*-------EXTENSION---------------------
  1.IMAGE TO TELETEXT code
  2.IMAGE TO FONT*/
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

void DrawSixel(SDL_Simplewin sw, CharStyle style, int code);
void DrawChar(SDL_Simplewin sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], CharStyle style,unsigned char c);


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
  assert(A!=NULL);
  for(i=0; i<HEIGHT;i++ ){
    printf("\n%d. ",i +1);
    for(j=0; j<WIDTH;j++){
      assert(fread(&A[i][j],1,1,fp));
        printf("%hu  ", A[i][j] );

    }
    printf("\n");
  }
  printf("short int :%lu , char, %lu\n",sizeof(short int),sizeof(unsigned char) );
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
      style.grMode=separated;
      break;
    case holdG:
      style.grMode=hold;
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
        if(FRSTCNTRLGRAPH<=A[i][j]&&A[i][j]<=151){
          tempStyle.graphics=changeColor(tempStyle.graphics,A[i][j]-16);
          if(tempStyle.grMode!=hold){
            tempStyle.grMode=contiguous;
          }
          printf("%d\n",A[i][j] );
          if(style[i][j-1].holdCnt!=0){
          tempStyle.holdCnt=style[i][j-1].holdCnt+1;
          }
        }
         switch (A[i][j]) {
           case holdG:
             tempStyle.holdCnt=1;
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
            tempStyle.height=changeHeight(A[i][j]);

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

CharHeight changeHeight( unsigned char code)
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
  if(code>white){
    code-=16;
  }
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
  style.holdCnt=0;
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
  if(i>=FRSTSIXEL){
    i-=FRSTSIXEL;
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
void renderPattern(SDL_Simplewin *sw, CharStyle style , int graphdata[3][2], SDL_Rect rectSixel, SDL_Rect rectBack)
{
  int i,j;
  rectBack.x=style.ox;
  rectBack.y=style.oy;
  printf("%d  %d  %d\n", style.background.r, style.background.g, style.background.b);
  Neill_SDL_SetDrawColour(sw,style.background.r, style.background.g, style.background.b);
  SDL_RenderFillRect(sw->renderer,&rectBack );
  for(i=0;i<3;i++){
    for(j=0;j<2;j++){
      if(graphdata[i][j]==1){
        Neill_SDL_SetDrawColour(sw,style.graphics.r, style.graphics.g, style.graphics.b);
        switch (style.grMode) {
          case hold:
          case contiguous:
            rectSixel.x=style.ox+j*rectSixel.w;
            rectSixel.y=style.oy+i*rectSixel.h;
            break;
          case separated:
            rectSixel.x=style.ox+j*rectSixel.w+2*j;
            rectSixel.y=style.oy+i*rectSixel.h+2*i;
            break;

        }
        SDL_RenderFillRect(sw->renderer,&rectSixel );
      }
    }
  }
}
void DrawSixel(SDL_Simplewin sw, CharStyle style,int code)
{
  int graphdata[3][2];
  SDL_Rect rectBack,rectSixel;
  rectBack.h=FNTHEIGHT;
  rectBack.w=FNTWIDTH;
  decodeSixels(graphdata, code);
  switch (style.grMode) {
    case hold:
    case contiguous:
      rectSixel.h=FNTHEIGHT/3;
      rectSixel.w=FNTWIDTH/2;
      renderPattern(&sw, style, graphdata, rectSixel,rectBack);
      break;
    case separated:
      rectSixel.h=4;
      rectSixel.w=6;
      renderPattern(&sw, style, graphdata, rectSixel,rectBack);
      break;
  }


}
void DrawChar(SDL_Simplewin sw,fntrow fontdata[FNTCHARS][FNTHEIGHT], CharStyle style, unsigned char c)
{

  switch (style.height) {
    case singleH:
      Neill_SDL_DrawChar(&sw, fontdata, c-128, style);
      break;
    case doubleH1:
    case doubleH2:
      Neill_SDL_DrawDoubleChar(&sw, fontdata, c-128, style);
      break;
  }
}
void SDL(CharStyle style[HEIGHT][WIDTH], unsigned char **A)
{
  int i,j;
  SDL_Simplewin sw;
  fntrow fontdata[FNTCHARS][FNTHEIGHT];
  Neill_SDL_ReadFont(fontdata,(char*) FNTFILENAME);
  Neill_SDL_Init(&sw, WIDTH*FNTWIDTH,HEIGHT*FNTHEIGHT);
  for(i=0;i<HEIGHT;i++){
    for(j=0;j<WIDTH;j++){
      printf("%d\n",0x24 );
      style[i][j].ox=j*FNTWIDTH;
      style[i][j].oy=i*FNTHEIGHT;
      if(style[i][j].dMode==graph && style[i][j].grMode!=hold){
        if(192<=A[i][j]&&A[i][j]<=223){
          style[i][j].character=style[i][j].graphics;
          DrawChar(sw, fontdata, style[i][j], A[i][j]);
        }
        else{
          DrawSixel(sw,style[i][j], A[i][j]);
        }
      }
      else if (style[i][j].dMode==graph && style[i][j].grMode==hold){
        DrawSixel(sw,style[i][j],A[i][j-style[i][j].holdCnt]);
      }
      else if(style[i][j].dMode==alpha && (isprint(A[i][j]-128) || A[i][j]==255)){
        DrawChar(sw, fontdata, style[i][j], A[i][j]);
      }
      else{
        DrawChar(sw, fontdata, style[i][j], SPACE_CHAR );}
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

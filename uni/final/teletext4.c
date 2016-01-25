/*ERROR
  1.New background reads color from previous or next character or ??
  2.No background color for lfc.m7 or panda.m7
  3.new color graphics code implies contiguous????
  4.
   */
/*-------EXTENSION---------------------
  1.IMAGE TO TELETEXT code
  2.IMAGE TO FONT
  ---change font control code
  ---resize image properly*/

/*-------CHECKS TO BE PERFORMED---------
  1.Error messages and printing
  2.Malloc / Free
  3.
  --------TASKS-------------------------
  1. Fix dependencies
*/
/*
This program is a Teletext decoder. Input binary files that
represent Teletext signal values after digitilization.
Output a full 40x25 Teletext screen.                       */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "neillsdl2.h"

int main(int argc, char** argv)
{
  TestResults result;
  CharStyle style[HEIGHT][WIDTH];
  unsigned char **A;
  if(argc !=2 ){
    fprintf(stderr, "Bad Arguments\n");
    exit(ERROR);
  }
  A=fileInput(argv[1]);
  printArray(A);
  parseForStyle(style,A);
  SDL(style,A);
  free(A);
  result = test(argv[1], verbose);
  printf("%d of %d PASSED\n",result.passed, result.total);
  return SUCCESS;
}
unsigned char **mallocArray(int height ,int width)
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
int isCntrlAlhpa(int code)
{
  switch (code) {
    case red:
    case green:
    case yellow:
    case blue:
    case magenta:
    case cyan:
    case white:
     return 1;
     break;
    default:
     return 0;
     break;
  }
}
int isHeight(int code)
{
  switch (code) {
    case singleHeight:
    case doubleHeight:
      return 1;
      break;
    default:
      return 0;
      break;
  }
}
int isCntrlGraph(int code)
{
  switch (code) {
    case grRed:
    case grGreen:
    case grYellow:
    case grBlue:
    case grMagenta:
    case grCyan:
    case grWhite:
     return 1;
     break;
    default:
     return 0;
     break;
  }
}
int isSixel(int code)
{
  if((0xA0<=code&&code<=0xFF)&&!(0xC0<=code&&code<=0xD0)){
    return 1;
  }
  else{
    return 0;
  }
}

int isGraphMode(int code)
{
  switch (code) {
    case contiguousG:
    case separetedG:
    case holdG:
      return 1;
      break;
    default:
      return 0;
      break;
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
  /*  printf("\n%d. ",i +1);*/
    for(j=0; j<WIDTH;j++){
      assert(fread(&A[i][j],1,1,fp));
        /*printf("%hu  ", A[i][j] );*/

    }
    /*printf("\n");*/
  }
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
  Pallete colors;
  colors=setPallete();
  for(i=0;i<HEIGHT;i++){
    tempStyle=reset(tempStyle);
    for(j=0;j<WIDTH;j++){
      tempStyle=setCoordinates(tempStyle, j*FNTWIDTH, i*FNTHEIGHT);
      if(FRSTCNTRLGRAPH<A[i][j]&&A[i][j]<LSTCNTRLGRAPH){
        tempStyle.dMode=graph;
        if(isCntrlGraph(A[i][j])){
          tempStyle.graphics=changeColor(tempStyle.graphics,A[i][j]);
          if(tempStyle.grMode!=hold){
            tempStyle.grMode=contiguous;
          }
          if(style[i][j-1].holdCnt!=0){
          tempStyle.holdCnt=style[i][j-1].holdCnt+1;
          }
        }
         switch (A[i][j]) {
           case releaseG:
             tempStyle=gmodeCheck(tempStyle, A[i][j-style[i][j-1].holdCnt]);
             break;
           case holdG:
             tempStyle.holdCnt=1;
           case contiguousG:
           case separetedG:
             tempStyle=gmodeCheck(tempStyle, A[i][j]);
             break;
           case newBack:
             tempStyle.background = setColor(A[i][j-1]);
             break;
           case blackBack:
             tempStyle.background=setColor(black);
             break;
         }
      }
      if(isCntrlAlhpa(A[i][j]) || isHeight(A[i][j])){
        tempStyle.dMode=alpha;
        if(A[i][j]==singleHeight || A[i][j]==doubleHeight){
          if(i!=0)
            tempStyle.height=changeHeight(A[i][j]);

        }
        tempStyle.character = setColor(A[i][j]);
      }
      if(i!=0 && tempStyle.height!=singleH && style[i-1][j].height==doubleH1){
        tempStyle.height=doubleH2;
      }
      style[i][j]=tempStyle;
    }
  }
}
Pallete setPallete(void)
{
  Pallete p;
  p.red= setColor(red);
  p.green= setColor(green);
  p.yellow= setColor(yellow);
  p.magenta= setColor(magenta);
  p.cyan= setColor(cyan);
  p.blue=setColor(blue);
  p.white=setColor(white);
  p.black=setColor(black);

  return p;
}
Color setColor(int clr)
{
  Color c;
  switch (clr) {
    case red:
      c.r=255;
      c.g=c.b=0;
      return c;
      break;
    case green:
      c.g=255;
      c.r=c.b=0;
      return c;
      break;
    case yellow:
      c.b=0;
      c.g=c.r=255;
      return c;
      break;
    case blue:
      c.b=255;
      c.r=c.g=0;
      return c;
      break;
    case magenta:
      c.g=0;
      c.b=c.r=255;
      return c;
      break;
    case cyan:
      c.r=0;
      c.g=c.b=255;
      return c;
      break;
    case white:
      c.r=c.g=c.b=255;
      return c;
      break;
    case black:
      c.r=c.g=c.b=0;
      return c;
      break;
  }
  return setColor(white);
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
CharStyle setCoordinates(CharStyle style, int x, int y)
{
    style.ox=x;
    style.oy=y;
    return style;
}
Color changeColor(Color col, unsigned char code)
{
  if(code>white){
    code-=16;
  }
  switch (code){
    case red:
      col=setColor(red);
      break;
    case green:
      col=setColor(green);
      break;
    case yellow:
      col=setColor(yellow);
      break;
    case blue:
      col=setColor(blue);
      break;
    case magenta:
      col=setColor(magenta);
      break;
    case cyan:
      col=setColor(cyan);
      break;
    case white:
      col=setColor(white);
      break;
      /*I Belive the default case shouldn't be set to white.
      I'm only including it because in the panda.m7 and lfc.m7
      before the new background code (9D) it doesn't provide with
      a color code so the background stays black instead of white*/
    default:
      col=setColor(white);
  }

  return col;
}
CharStyle reset(CharStyle style)
{
  style.background=setColor(black);
  style.character=setColor(white);
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

void createGraphFont(fntrow graphdata[FNTCHARS][FNTHEIGHT])
{
int i,x=0,y;
int dots[3][2];
for (i=0xA0;i<=0xFF;i++){
decodeSixels(dots,i);
    printf("%#x\n",i );
  for (y=0;y<3;y++){
    if(dots[y][x]==1 && dots[y][x+1]==1){
      graphdata[i-FNT1STCHAR][6*y]=graphdata[i-FNT1STCHAR][6*y+1]=graphdata[i-FNT1STCHAR][6*y+2]=
      graphdata[i-FNT1STCHAR][6*y+3]=graphdata[i-FNT1STCHAR][6*y+4]=
      graphdata[i-FNT1STCHAR][6*y+5]=0xFFFF;
      printf("1111111111111111\n" );
      printf("11111111\n" );
      printf("11111111\n" );
      printf("11111111\n" );
      printf("11111111\n" );
      printf("11111111\n" );
    }
    else if(dots[y][x]==1 && dots[y][x+1]==0){
        graphdata[i-FNT1STCHAR][6*y]=graphdata[i-FNT1STCHAR][6*y+1]=graphdata[i-FNT1STCHAR][6*y+2]=
        graphdata[i-FNT1STCHAR][6*y+3]=graphdata[i-FNT1STCHAR][6*y+4]=
        graphdata[i-FNT1STCHAR][6*y+5]=0xFF00;
      printf("11110000\n" );
      printf("11110000\n" );
      printf("11110000\n" );
      printf("11110000\n" );
      printf("11110000\n" );
      printf("11110000\n" );
    }
    else if(dots[y][x]==0 && dots[y][x+1]==1){
        graphdata[i-FNT1STCHAR][6*y]=graphdata[i-FNT1STCHAR][6*y+1]=graphdata[i-FNT1STCHAR][6*y+2]=
        graphdata[i-FNT1STCHAR][6*y+3]=graphdata[i-FNT1STCHAR][6*y+4]=
        graphdata[i-FNT1STCHAR][6*y+5]=0x00FF;
      printf("0000000011111111\n" );
      printf("0000000011111111\n" );
      printf("0000000011111111\n" );
      printf("0000000011111111\n" );
      printf("0000000011111111\n" );
      printf("0000000011111111\n" );
    }
    else{
      graphdata[i][x]=0x00;
      printf("0000000000000000\n" );
      printf("0000000000000000\n" );
      printf("0000000000000000\n" );
      printf("0000000000000000\n" );
      printf("0000000000000000\n" );
      printf("0000000000000000\n" );
    }
  }
}
}

void SDL(CharStyle style[HEIGHT][WIDTH], unsigned char **A)
{
  int i,j;
  SDL_Simplewin sw;
  fntrow graphdata[FNTCHARS][FNTHEIGHT];
  fntrow fontdata[FNTCHARS][FNTHEIGHT];
  fntrow fontA[FNTCHARS][FNTHEIGHT];
  sw.finished=0;
  Neill_SDL_ReadFont(fontdata,(char*) FNTFILENAME);
  createGraphFont(graphdata);
 /*Neill_SDL_ReadFontChar(fontA,(char *)"font/fontblur.m7");*/
Neill_SDL_ReadFontChar(fontA,(char *)"trebouchet.fnt");
    for(j=0;j<93;j++){
  for(i=0;i<FNTHEIGHT;i++){

    fntrow temp=fontA[j][i]<<8;
   fontdata[j][i]=fontA[j][i]>>8|temp;
    }
  }
  Neill_SDL_Init(&sw, WWIDTH,WHEIGHT);
  for(i=0;i<HEIGHT;i++){
    for(j=0;j<WIDTH;j++){
      if(style[i][j].dMode==graph && style[i][j].grMode!=hold){
        if(192<=A[i][j]&&A[i][j]<=223){
          style[i][j].character=style[i][j].graphics;
          Neill_SDL_DrawChar(&sw, fontdata, A[i][j]-128, style[i][j]);
        }
        else if(isSixel(A[i][j])){
          /*DrawSixel(sw,style[i][j], A[i][j]);*/
          printf("egine I%d j%d\n",i,j );
           Neill_SDL_DrawChar(&sw,graphdata,A[i][j],style[i][j]);

        }
      }
      else if (style[i][j].dMode==graph && style[i][j].grMode==hold){
        DrawSixel(sw,style[i][j],A[i][j-style[i][j].holdCnt]);
      }
      /* else if(A[i][j]-128=='A'){
         Neill_SDL_DrawChar(&sw, fontA, A[i][j]-128, style[i][j]);
       }*/
      else if(style[i][j].dMode==alpha && (isprint(A[i][j]-128)||isprint(A[i][j]) || A[i][j]==255)){
        Neill_SDL_DrawChar(&sw, fontdata, A[i][j]-128, style[i][j]);
      }
      else{
        Neill_SDL_DrawChar(&sw, fontdata, SPACE_CHAR, style[i][j]);
      }
    }
  }
    do{
      SDL_RenderPresent(sw.renderer);
      SDL_Delay(FRAMERATE);
      Neill_SDL_Events(&sw);
    }while(!sw.finished);
  SDL_FREE(&sw);
}

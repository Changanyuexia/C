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
#include "neillsdl2.h"

void printStyle(CharStyle style, unsigned char c);
void printHelp();
int main(int argc, char** argv)
{
  TestResults result;
  CharStyle style[HEIGHT][WIDTH];

  unsigned char **A;
  if(argc !=2 ){
    if(argc==1){
      result = test(verbose);
      fprintf(stdout,"%d of %d PASSED\n",result.passed, result.total);
      return SUCCESS;
    }
    else{
      fprintf(stderr, "Bad Arguments\n");
      printHelp();
      exit(ERROR);
    }
  }
  A=fileInput(argv[1]);
  printArray(A);
  parseForStyle(style,A);
  SDL(style,A);
  return SUCCESS;
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
    for(j=0; j<WIDTH;j++){
      assert(fread(&A[i][j],1,1,fp));
    }
  }
  fclose(fp);
  return A;
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

/*The logic of this function is such:
  it creates a temporary style instance which
  gets passed from function to function so on
  line of TELETEXT can keep previous formats*/
void parseForStyle(CharStyle style[HEIGHT][WIDTH], unsigned char **A)
{
  CharStyle tempStyle;
  int i,j;
  for(i=0;i<HEIGHT;i++){
    tempStyle=reset(tempStyle);
    for(j=0;j<WIDTH;j++){
      /*This is to correct ASCII characters to be TELEXT characters
      *  eg. panda.m7 and lfc.m7                                  */
      if(A[i][j]<TLTXTOFFSET){
        A[i][j]+=TLTXTOFFSET;
      }
      tempStyle=setCoordinates(tempStyle, j*FNTWIDTH, i*FNTHEIGHT);
      if(FRSTCNTRLGRAPH<A[i][j]&&A[i][j]<LSTCNTRLGRAPH){
        tempStyle.dMode=graph;
                asignGraphicsStyle(&tempStyle,style,A);
      }
      asignAlphaStyle(&tempStyle ,style, A[i][j]);
            style[i][j]=tempStyle;
    }
  }
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
void asignGraphicsStyle(CharStyle *tempStyle, CharStyle style[HEIGHT][WIDTH], unsigned char **A )
{
  int i=tempStyle->oy/FNTHEIGHT;
  int j=tempStyle->ox/FNTWIDTH;
  if(isCntrlGraph(A[i][j])){
    tempStyle->graphics=setColor(A[i][j]);
    if(tempStyle->grMode!=hold){
      tempStyle->grMode=contiguous;
    }
    if(style[i][j-1].holdCnt!=0){
    tempStyle->holdCnt=style[i][j-1].holdCnt+1;
    }
  }
  switch (A[i][j]) {
    case releaseG:
      gmodeCheck(tempStyle, A[i][j-style[i][j-1].holdCnt]);
      break;
    case holdG:
      tempStyle->holdCnt=1;
    case contiguousG:
    case separetedG:
      gmodeCheck(tempStyle, A[i][j]);
      break;
    case newBack:
      if(isCntrlAlhpa(A[i][j-1])){
        tempStyle->background = setColor(A[i][j-1]);
      }
      else{
        tempStyle->background = setColor(white);
      }
      break;
    case blackBack:
      tempStyle->background=setColor(black);
      break;
  }
}
void asignAlphaStyle(CharStyle *tempStyle, CharStyle style[HEIGHT][WIDTH], unsigned char code)
{
  int i=tempStyle->oy/FNTHEIGHT;
  int j=tempStyle->ox/FNTWIDTH;
  if(isCntrlAlhpa(code) || isHeight(code)){
    tempStyle->dMode=alpha;
    if(isHeight(code)){
      if(i!=0){
        tempStyle->height=changeHeight(code);
      }
    }
    else{
      tempStyle->character = setColor(code);
    }
  }
  if(i!=0 && tempStyle->height!=singleH && style[i-1][j].height==doubleH1){
    tempStyle->height=doubleH2;
  }
}

Color setColor(int clr)
{
  Color c;
  if(clr>white){
    clr-=ONECOLUMN;
  }
  c.r=c.g=c.b=0;
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
  return c;
}
CharStyle setCoordinates(CharStyle style, int x, int y)
{
    style.ox=x;
    style.oy=y;
    return style;
}
void gmodeCheck(CharStyle *style,unsigned char ctrl)
{
  switch (ctrl) {
    case contiguousG:
      style->grMode=contiguous;
      break;
    case separetedG:
      style->grMode=separated;
      break;
    case holdG:
      style->grMode=hold;
      break;
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
void freeArray(unsigned char **A, int height)
{
  int i;
  for (i=0; i<height; i++){
   free(A[i]);
  }
  free(A);
}
void printArray(unsigned char **A)
{
  int i,j;
  for(i=0; i<HEIGHT; i++){
    for(j=0; j<WIDTH;j++){
      printf("%c", A[i][j]-TLTXTOFFSET );
    }
    printf("\n");
  }
}
void putTLTXTCharWin()
{
  
}
void SDL(CharStyle style[HEIGHT][WIDTH], unsigned char **A)
{
  int i,j;
  SDL_Simplewin sw;
  fntrow fontdata[FNTCHARS][FNTHEIGHT];
  fntrow fontA[FNTCHARS][FNTHEIGHT];
  fntrow graphdata[2][FNTCHARS][FNTHEIGHT];
  sw.finished=0;
  setupSDL(graphdata,fontdata,fontA);
  Neill_SDL_Init(&sw, WWIDTH,WHEIGHT);
  for(i=0;i<HEIGHT;i++){
    for(j=0;j<WIDTH;j++){
      if(isprint(A[i][j]-TLTXTOFFSET)||A[i][j]==0xFF){
        Neill_SDL_DrawChar(&sw, fontA, A[i][j], style[i][j]);
      }
      if((isSixel(A[i][j])&&style[i][j].dMode==graph)||(isCntrlGraph(A[i][j]) && style[i][j].grMode==hold) ){
        switch (style[i][j].grMode) {
          case contiguous:
            Neill_SDL_DrawChar(&sw, graphdata[contiguous], A[i][j], style[i][j]);
            break;
          case separated:
            Neill_SDL_DrawChar(&sw, graphdata[separated], A[i][j], style[i][j]);
            break;
          case hold:
            Neill_SDL_DrawChar(&sw, graphdata[contiguous], A[i][j-style[i][j].holdCnt], style[i][j]);
            break;
        }
      }
     else if((!isgraph(A[i][j]-TLTXTOFFSET) && !isSixel(A[i][j]))){
        Neill_SDL_DrawChar(&sw, fontA, SPACE_CHAR, style[i][j]);
      }
      if(A[i][j]==holdG){
        Neill_SDL_DrawChar(&sw, fontA, 0xFF, style[i][j]);
      }
    }
  }
  do{
    drawFrame(&sw);
  }while(!sw.finished);
  SDL_FREE(&sw);
}
/*The below functions are used to categorize the TELETEXT codes */
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
  if((0xA0<=code&&code<=0xFF)&&!(0xC0<=code&&code<=0xDF)){
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
void printHelp()
{
  FILE *fp;
  char c;
  fp=fopen("ReadMe.txt","r");
  assert(fp!=NULL);
  while ( (c = fgetc(fp) ) != EOF){
    putchar(c);
  }
}
/*this is a auxiliary function to perform visual style check*/
void printStyle(CharStyle style, unsigned char c)
{
  printf("charachter %#x\n",c );
  printf(" background color (RGB)  [%d][%d][%d]\n",
  style.background.r, style.background.g, style.background.b );
  printf(" character color (RGB)  [%d][%d][%d]\n",
  style.character.r, style.character.g, style.character.b );
  printf(" graphics color (RGB)  [%d][%d][%d]\n",
  style.graphics.r, style.graphics.g, style.graphics.b );
  printf("dMode   %d\n",style.dMode );
  printf("grMode  %d\n",style.grMode );
  printf("holdCnt %d\n",style.holdCnt );
}
/*     if(A[i][j]==newBack  || A[i][j]==0xFF){
        Neill_SDL_DrawChar(&sw, fontA, 0xFF, style[i][j]);
      }
      if(style[i][j].dMode==graph && style[i][j].grMode!=hold){
        if(0xC0<=A[i][j]&&A[i][j]<=0xDF){
          style[i][j].character=style[i][j].graphics;
          Neill_SDL_DrawChar(&sw, fontA, A[i][j], style[i][j]);
        }
        else if(isSixel(A[i][j])){
  */  /*       DrawSixel(sw,style[i][j], A[i][j]);
      */
    /*      style[i][j].character=style[i][j].graphics;
          if(style[i][j].grMode==contiguous){
            Neill_SDL_DrawChar(&sw,graphContdata,A[i][j],style[i][j]);
          }
          else{
            Neill_SDL_DrawChar(&sw,graphSepdata,A[i][j],style[i][j]);
          }
        }
        else{
          Neill_SDL_DrawChar(&sw, fontA, SPACE_CHAR, style[i][j]);
        }
      }
      else if (style[i][j].dMode==graph && style[i][j].grMode==hold){
        style[i][j].character=style[i][j].graphics;
        Neill_SDL_DrawChar(&sw,graphContdata,A[i][j-style[i][j].holdCnt],style[i][j]);
      }
      else if(style[i][j].dMode==alpha && (isprint(A[i][j]-TLTXTOFFSET)||isprint(A[i][j]))){
        Neill_SDL_DrawChar(&sw, fontA, A[i][j], style[i][j]);
      }
      else if(A[i][j]!=0xFF){
        Neill_SDL_DrawChar(&sw, fontA, SPACE_CHAR, style[i][j]);
      }*/
      /*  Neill_SDL_ReadFontChar(fontA,(char *)"trebouchet.fnt");
            for(j=0;j<93;j++){
        for(i=0;i<FNTHEIGHT;i++){

          fntrow temp=fontA[j][i]<<8;
         fontdata[j][i]=fontA[j][i]>>8|temp;
          }
        }*/

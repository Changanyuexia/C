#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "teletext.h"
/*#include "neillsdl2.h"
*/
#define LOGNAME "test_log.txt"
#define FORMT "--------------------------"
#define FAIL "\x1B[31mFAILED\x1B[0m"
#define PASS "\x1B[32mPASSED\x1B[0m"

#ifdef __STDC_LIB_EXT1__
  char str[26];
  ctime_s(str,sizeof str,&results);
  printf("%s", str);
#endif


int T_gmodeCheck(int mode);
int T_mallocArray(unsigned char **A, int mode);
int T_parseForStyle(unsigned char **A, char *s, int mode);
int T_reset(int mode);
int T_changeColor(int mode);
int T_SDL(int mode);
int T_changeHeight(int mode);
int T_decodeSixels(int mode);

TestResults test(char *s, int mode)
{
  FILE *fp;
  TestResults result;
  int i=0, cnt[TOT_TESTS];
  unsigned char **A=NULL;
  time_t t = time(NULL);
  result.passed=0;
  fp=fopen(LOGNAME, "w");
  fprintf(fp,"%s%s\n", ctime(&t),FORMT);
  fclose(fp);
  printf("%d.",i+1 );
  cnt[i++] = T_reset(mode);
  printf("%d.",i+1 );
  cnt[i++] = T_gmodeCheck(mode);
  printf("%d.",i+1 );
  cnt[i++] = T_mallocArray(A, mode);
  printf("%d.",i+1 );
  cnt[i++] = T_parseForStyle(A,s, mode);
  printf("%d.",i+1 );
  cnt[i++] = T_changeHeight(mode);
  printf("%d.",i+1 );
  cnt[i++] = T_changeColor(mode);
  printf("%d.",i+1 );
  cnt[i++] = T_decodeSixels(mode);
  printf("%d.",i+1 );
  cnt[i++] = T_SDL(mode);
  result.total = i;
  for(i=0; i<result.total; i++){
    if(cnt[i] == SUCCESS)
    result.passed++;
  }
  return result;
}
int T_decodeSixels(int mode)
{
  int i,j,cnt=0;
  int dots[3][2];
  FILE *fp;
  int testCodeValue=0xB8;
  fp=fopen(LOGNAME,"a");
  fprintf(fp, "%s\nTesting %s %#X\n%s\n",FORMT,__func__,testCodeValue,FORMT );
  decodeSixels(dots,testCodeValue);
  if   (dots[0][0]!=0||dots[0][1]!=0||
        dots[1][0]!=0||dots[1][1]!=1||
        dots[1][0]!=0||dots[1][1]!=1){
    cnt++;
  }
  else{
    for(i=0;i<3;i++){
      for(j=0;j<2;j++){
        fprintf(fp,"%d", dots[i][j]);
      }
      fprintf(fp,"\n");
    }
    fprintf(fp, "Sixel test 0xB8 %s\n","   PASSED" );
  }
  if(mode==verbose &&cnt==0)
    printf("%15s %s\n",__func__, PASS );
  else
    printf("%15s %s\n",__func__, FAIL );
  if(cnt==0)
    return SUCCESS;
  else
    return ERROR;

}
int T_changeHeight(int mode)
{
  int cnt=0;
  CharHeight cHeight=singleH;
  cHeight=changeHeight( 0x8D);
  if(cHeight!=doubleH1){
    cnt++;
  }
  cHeight=changeHeight( 0x8C);
  if(cHeight!=singleH){
    cnt++;
  }
  if(mode==verbose &&cnt==0)
    printf("%15s %s\n",__func__, PASS );
  else
    printf("%15s %s\n",__func__, FAIL );
  if(cnt==0)
    return SUCCESS;
  else
    return ERROR;
}
unsigned char** initA(unsigned char **A)
{
  int i,j,ctrl=0x80;
  A=mallocArray(HEIGHT,WIDTH);
  if(A==NULL)
  printf("null\n" );
  for (i=0;i<HEIGHT;i++){
    for (j=0;j<WIDTH;j++){
     A[i][j]=ctrl;
     ctrl=rand()%256;
   }
  }
  return A;
}
void initStyle(CharStyle style[HEIGHT][WIDTH])
{
  int i,j;
  for (i=0;i<HEIGHT;i++){
    for (j=0;j<WIDTH;j++){
     style[i][j]=reset(style[i][j]);
    }
  }

}
int T_SDL(int mode)
{
  unsigned char **A=NULL;
  CharStyle style[HEIGHT][WIDTH];
  A=initA(A);
  initStyle(style);
  parseForStyle(style,A);
  SDL(style, A);
  if(mode==verbose)
  printf("%15s %s\n",__func__, PASS );
  return SUCCESS;
}
int T_changeColor(int mode)
{
  FILE *fp;
  int ctrl=0x81;
  Color col;
  col.r=col.g=col.b=0;
  fp=fopen(LOGNAME,"a");
  fprintf(fp, "%s\nTesting %s\n%s\n",FORMT,__func__ ,FORMT);
  while(ctrl<=0x87){
    col=changeColor(col, ctrl++);
  }
  if(mode==verbose)
  printf("%15s %s\n",__func__, PASS );
  return SUCCESS;
}
int T_reset(int mode)
{
  int cnt=0;
  FILE *fp;
  CharStyle style;
  fp=fopen(LOGNAME,"a");
  style = reset (style);
  fprintf(fp, "%s\nTesting %s\n%s\n",FORMT,__func__ ,FORMT);
  if(style.background.r!=0 &&
     style.background.g!=0 &&
     style.background.b!=0 ){
    cnt++;
    fprintf(fp,"%18s %s\n","Background Color", "FAILED");
     }
  else{
    fprintf(fp,"%18s %s\n","Background Color", "PASSED");
  }
  if(
     style.character.r!=255 &&
     style.character.g!=255 &&
     style.character.b!=255 ){
       cnt++;
       fprintf(fp,"%18s %s\n","Character Color", "FAILED");
        }
     else{
       fprintf(fp,"%18s %s\n","Character Color", "PASSED");
     }

     if(
     style.dMode!=alpha &&
     style.grMode !=contiguous &&
     style.height!=singleH &&
     style.ox!=0&&
     style.oy!=0 ){
       cnt++;
       fprintf(fp,"%18s %s\n","format ", "FAILED");
     }
     else{
       fprintf(fp,"%18s %s\n","format ", "PASSED");
     }
     fclose(fp);
     if(mode==verbose&&cnt==0)
     printf("%15s %s\n",__func__, PASS );
     else if(mode==verbose){
       printf("%15s %s\n",__func__, FAIL );

     }
     if(cnt!=0)
       return ERROR;
     else
       return SUCCESS;
}
int T_gmodeCheck(int mode)
{
  int cnt=0;
  CharStyle style;
  style=reset(style);
  style=gmodeCheck(style, holdG);
  if(style.grMode!=hold){
    cnt++;
  }
  style=reset(style);
  style=gmodeCheck(style, contiguousG);
  if(style.grMode!=contiguous){
    cnt++;
  }
  style=reset(style);
  style=gmodeCheck(style, separetedG);
  if(style.grMode!=separated){
    cnt++;
  }
  style=reset(style);
  style=gmodeCheck(style, 0xA5);
  if(style.grMode!=contiguous){
    cnt++;
  }
  if(mode==verbose && cnt == 0){
    printf("%15s %s\n",__func__, PASS );
  }
  return cnt;
}
int T_mallocArray(unsigned char **A, int mode)
{
  A=mallocArray(HEIGHT,WIDTH);
  if(A==NULL){
    printf("%15s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    if(mode==verbose){
      printf("%15s %s\n",__func__, PASS );
    }
    return SUCCESS;
  }
}
int T_styleCases(unsigned char ctrl,CharStyle style, int mode)
{
  FILE *fp;
  int cnt=0;
  fp=fopen(LOGNAME,"a");
  switch (ctrl) {
    case red:
      if(style.character.r!=255||style.character.g!=0||style.character.b!=0){
        cnt++;
      }
      else if(mode==verbose){
        fprintf(fp,"%18s %s\n","red character","PASSED");
      }
      break;
    case green:
      if(style.character.r!=0||style.character.g!=255||style.character.b!=0){
        cnt++;
      }
      else if(mode==verbose){
        fprintf(fp,"%18s %s\n","green character","PASSED");
      }
      break;

    case blue:
      if(style.character.r!=0||style.character.g!=0||style.character.b!=255){
        cnt++;
      }
      else if(mode==verbose){
        fprintf(fp,"%18s %s\n","blue character","PASSED");
      }
      break;

    case separetedG:
      if(style.grMode!=separated){
        cnt++;
      }
      else if(mode==verbose){
        fprintf(fp,"%18s %s\n","separated graphics","PASSED");
      }
      break;
    case contiguousG:
      if(style.grMode!=contiguous){
        cnt++;
      }
      else if(mode==verbose){
        fprintf(fp,"%18s %s\n","contiguous graphics","PASSED");
      }
      break;

    case holdG:
      if(style.grMode!=hold){
        cnt++;
      }
      else if(mode==verbose){
        fprintf(fp,"%18s %s\n","hold graphics","PASSED");
      }
      break;
  }
  if(cnt!=0){
    printf("%15s %s\n",__func__, FAIL );
  }
  fclose(fp);
  return  cnt;
}
int T_parseForStyle(unsigned char **A, char *s, int mode)
{
  int i,j,cnt=0;
  FILE *fp;
  CharStyle style[HEIGHT][WIDTH];
  fp=fopen(LOGNAME, "a");
  fprintf(fp, "%s\nTesting %s\n%s\n",FORMT,__func__ ,FORMT);
  fclose(fp);
  A=fileInput(s);
  parseForStyle(style, A);
  for (i=0;i<HEIGHT;i++){
    for (j=0;j<WIDTH;j++){
      if(FRSTCNTRLALPHA<=A[i][j]&&A[i][j]<=LSTCNTRLGRAPH)
       cnt+=T_styleCases(A[i][j],style[i][j], silent);
    }

  }

  if(mode==verbose && cnt==0){
    printf("%15s %s\n",__func__, PASS );
  }
  if(cnt!=0){
    return ERROR;
  }
  return SUCCESS;
}

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "openCV.h"

#define FNTHEIGHT 18
#define FNTWIDTH  16
#define THRESHOLD 220

using namespace cv;
void string2HexBinary(unsigned char totality[10000],char totalString[10000]);
void exportCode(unsigned char totality[10000]);


typedef struct names FileNames;
struct names{
  char *imageName;
  char outputName[30];
  char charFile[30];
  char path[30];
};

typedef struct binPair BinPair;
struct binPair{
  short unsigned int x;
  short unsigned int y;
};
FileNames setFileNames(char* argument, char c)
{
  FileNames names;
  names.imageName=argument;
  strcpy(names.path,"font/");
  if('a'<= c && c <='z'){
    sprintf(names.charFile,"%s%s%c%c.jpg",names.path ,names.imageName,'m',c);
    sprintf(names.outputName,"%s%s%s%c%c.jpg",names.path , "touched",names.imageName,'m',c);
    printf("in %s  out %s  \n",names.charFile,names.outputName );
  }
  else if('A'<= c && c <='Z'){
 sprintf(names.charFile,"%s%s%c.jpg",names.path ,names.imageName,c);
 sprintf(names.outputName,"%s%s%s%c.jpg", names.path , "touched",names.imageName,c);
printf("in %s  out %s  \n",names.charFile,names.outputName );
  }
  else{
    sprintf(names.charFile,"%s%d.jpg", names.path ,c);
    sprintf(names.outputName,"%s%s%d.jpg",names.path, "touched",c);
   printf("in %s  out %s  \n",names.charFile,names.outputName );
  }

  return  names;
}

int main( int argc, char** argv )
{

 // LOADING THE IMAGE
 FileNames names;
 unsigned char totality[10000];
 short unsigned font[FNTHEIGHT];
 char s[FNTHEIGHT][5];
 char totalString[10000];
for(char c=' ';c<=126;c++){
 names=setFileNames(argv[1],c);
 Mat image,outImage;
 image = imread( names.charFile, 1 );
 Size size(FNTWIDTH,FNTHEIGHT);
 Size size2(4,4);
 blur(image,image,size2);
 resize(image, outImage,size);
 cvtColor( outImage, outImage, CV_BGR2GRAY );
 printf("%dx%d\n",outImage.rows, outImage.cols );

 if( argc != 2 || !image.data )
 {
   printf( " No image data \n " );
   return -1;
 }
for(int i=0; i<outImage.rows; i++) {
    if(i==0)
    printf( "    12345678901234567\n\n");
    printf("%2d  ",i );
  for(int j=0; j<=outImage.cols; j++) {
    uchar pixel = outImage.at<uchar>(i,j);
    if(pixel<THRESHOLD){
      printf("%d",1 );
    }
    else{
      printf("%d",0);
    }

  }
  printf("\n" );
}
 imwrite( names.outputName, outImage );

 for(int i=0; i<outImage.rows; i++) {
   font[i]=0;
   for(int j=0; j<=outImage.cols; j++) {
     uchar pixel = outImage.at<uchar>(i,j);
     if(pixel<THRESHOLD)
     font[i]+=pow(2.0,outImage.cols-j+1);
   }
  // printf("%4X--%4hu \n",font[i],font[i] );
   sprintf(s[i],"%4X",font[i]);
 //  printf("%s\n",s[i] );
  }
  for(int i=0;i<FNTHEIGHT;i++){
    for(int j=0;j<4;j++){
      if(s[i][j]==32){
      s[i][j]='0';
      }
    }
strcat(totalString,s[i]);
printf("%2d. %s",i, s[i]);
printf("\n" );
  }
  string2HexBinary(totality,totalString);
  exportCode(totality);
//   int k=0;
//   for(int i=1;i<(int)strlen(totalString);){
//  //   printf("%x %c", totalString[i]-48,totalString[i]);
//     t[k].x=totalString[i++]-48;
//  //   printf("%x %c", totalString[i]-48, totalString[i]);
//     t[k++].y=totalString[i++]-48;
//   }
//   FILE *fout;
//   fout=fopen("letterA.fnt", "wb");
//   int i=0;
//   while(i<30){
//   fwrite(tp++,1,1,fout );
//   i++;
//   }
//
// fclose(fout);
}
// for(int i=1;i<96;i++)
// totalString[i*(4)*(FNTHEIGHT)-1]='0';
// printf("\n%s\n",totalString);
 return 0;
}
void exportCode(unsigned char totality[10000])
{
  FILE *fp;
  fp=fopen("trebouchet.fnt", "wb");
  assert(fp!=NULL);
  fwrite(totality,sizeof(totality)*10000,1,fp );
  fclose(fp);
}
void string2HexBinary(unsigned char totality[10000],char totalString[10000]){
  int i;
  char temporary[3]={0};
  for(i=0;i<10000;i+=2){
    sprintf(temporary,"%c%c",totalString[i],totalString[i+1]);
    totality[i/2]=strtol(temporary,NULL,16);
  //  printf("%d %s %x\n",i,temporary, totality[i/2] );
  }
}

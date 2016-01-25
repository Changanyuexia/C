#include <stdio.h>
#include <string.h>
#include <math.h>
#include "openCV.h"

#define FNTHEIGHT 18
#define FNTWIDTH  16
#define FNTCHARS 96
#define FNT1STCHAR 32
using namespace cv;
typedef struct binPair BinPair;
struct binPair{
  short unsigned int x;
  short unsigned int y;
};

short unsigned int* readChar(short unsigned int *font,Mat outImage, int x, int y)
{
  FILE *fp;
  fp=fopen("helvetica.fnt", "wb");
  for(int i=0; i<FNTHEIGHT; i++) {
    font[i]=0;
    for(int j=0; j<=FNTWIDTH; j++) {
      uchar pixel = outImage.at<uchar>(i+y,j+x);
      if(pixel<20)
      font[i]+=pow(2.0,outImage.cols-j+1);
    }
  //   printf("%4X--%4hu \n",font[i],font[i] );
    fprintf(fp,"%4X",font[i]);
   // printf("%s\n",s[k][i] );
   }
   return font;
}
int main( int argc, char** argv )
{

 // LOADING THE IMAGE
 char* imageName = argv[1];
 char* outputName = argv[2];

 Mat image,outImage;
 image = imread( imageName, 1 );
 Size size(FNTWIDTH*16,FNTHEIGHT*16);
 resize(image, outImage,size);
 cvtColor( outImage, outImage, CV_BGR2GRAY );
 printf("%dx%d\n",outImage.rows, outImage.cols );

 if( argc != 3 || !image.data )
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
    if(j%FNTWIDTH==0)
     printf("\n" );
    if(pixel<20){
      printf("%d",1 );
    }
    else{
      printf("%d",0);
    }

  }
  printf("\n" );
}
//  // THRESHOLD BY LOOPING THROUGH ALL PIXELS
//  // for(int i=0; i<image.rows; i++) {
//  //   for(int j=0; j<image.cols; j++) {
//  //       uchar pixelBlue = image.at<Vec3b>(i,j)[0];
//  //       uchar pixelGreen = image.at<Vec3b>(i,j)[1];
//  //       uchar pixelRed = image.at<Vec3b>(i,j)[2];
//  //   }
//  // }
//  // for(int i=0; i<image.rows; i++) {
//  //   for(int j=0; j<image.cols; j++) {
//  //      Temp[i][j]=image.at<Vec3b>(i,j)[0];
//  //      image.at<Vec3b>(i,j)[0]=image.at<Vec3b>(i,j)[2];
//  //      image.at<Vec3b>(i,j)[2]=image.at<Vec3b>(i,j)[1];
//  //      image.at<Vec3b>(i,j)[1]=Temp[i][j];
//
//
// //red=blue
// //image.at<Vec3b>(i,j)[2]=image.at<Vec3b>(i,j)[0];
//    }
//  }
 imwrite( outputName, outImage );
short unsigned font[FNTCHARS][FNTHEIGHT];
char s[FNTCHARS][FNTHEIGHT][5];
char totalString[10000];
BinPair t[10000];
BinPair *tp=t;
strcpy(totalString, " ");
for(int k=0;k<FNTCHARS;k++){
 readChar(outImage,k&16,k/16);
}
for(int k=0;k<FNTCHARS;k++){
  for(int i=0;i<FNTHEIGHT;i++){
    for(int j=0;j<4;j++){
      if(s[k][i][j]==32){
      s[k][i][j]='0';
      }
    }
strcat(totalString,s[k][i]);
//printf("%3d. %s",i, s[k][i]);
//printf("\n" );
  }
}
  int k=0;
  printf("%hu\n",'0' );
  for(int i=1;i<(int)strlen(totalString);){
  //  printf("%x %c", totalString[i]-48,totalString[i]);
    t[k].x=totalString[i++]-48;
  //  printf("%x %c", totalString[i]-48, totalString[i]);
    t[k++].y=totalString[i++]-48;
  }
//  printf("\n%s\n",totalString );
  FILE *fout;
  fout=fopen("helvetica.fnt", "wb");
  int i=0;
  while(i<30){
  fwrite(tp++,1,1,fout );
  i++;
  }


fclose(fout);
 return 0;
}

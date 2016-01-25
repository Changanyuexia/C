#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "openCV.h"

#define FNTHEIGHT 18
#define FNTWIDTH  16
#define WHEIGHT 25
#define WWIDTH 40
#define THRESHOLD 95
#define OUTPUTFILE "image.m7"

enum sixels {s_one=1,s_two=2,s_three=4,s_four=8,s_five=16,s_six=64};


typedef struct binPair BinPair;
struct binPair{
  unsigned char x;
  unsigned char y;
};

int sixelAssignment(int a, int b);
int encodeSixels(uchar dots[3][2]);

using namespace cv;

int main( int argc, char** argv )
{

// LOADING THE IMAGE

  short unsigned int code[25][40];
  char* imageName = argv[1];
  char outputName[30];
  char charFile[30];
  char folder[10]="photo/";
  char temp[10000];
  char totalString[10000];
  unsigned char totality[10000];
  FILE *fp;
  Mat image,middle,outImage;
  int i,j;
  sprintf(charFile,"%s%s",folder,imageName);
  sprintf(outputName,"%s%s%s",folder,"touched",imageName);
  image = imread( charFile, -1 );
  Size size(FNTHEIGHT*WHEIGHT,FNTWIDTH*WWIDTH);
  Size k_size(5,5);
  Size size3(FNTWIDTH*WWIDTH/8,FNTHEIGHT*WHEIGHT/6-18);
  resize(image, middle,size);
  blur(middle,middle,k_size);
  cvtColor( middle, middle, CV_BGR2GRAY );
  resize( middle, outImage,size3);
  printf("%dx%d\n",outImage.rows, outImage.cols );
  printf("%dx%d\n",middle.rows, middle.cols );

  if( argc != 2 || !image.data ){
    printf( " No image data \n " );
    return -1;
  }
  for(i=0; i<outImage.rows; i++) {
    for(j=0; j<=outImage.cols; j++) {
      uchar pixel = outImage.at<uchar>(i,j);
      if(pixel<THRESHOLD){
        outImage.at<uchar>(i,j)=0;
      }
      else{
        outImage.at<uchar>(i,j)=255;
      }
    }
  }
  imshow("icona",outImage);
  cvWaitKey();
  // for(i=0;i<40*25;i++){
  //   totalString[i]=' ';
  // }
  // totalString[39*5]='\0';
  //totalString[0]='\0';
  imwrite( outputName, outImage );
  for(i=0; i<outImage.rows; i+=3) {
    for(j=0; j<outImage.cols; j+=2) {
      uchar pixel[3][2];
      pixel[0][0] = outImage.at<uchar>(i,j);
      pixel[0][1] = outImage.at<uchar>(i,j+1);
      pixel[1][0] = outImage.at<uchar>(i+1,j);
      pixel[1][1] = outImage.at<uchar>(i+1,j+1);
      pixel[2][0] = outImage.at<uchar>(i+2,j);
      pixel[2][1] = outImage.at<uchar>(i+2,j+1);
      code[i/3][j/2]=encodeSixels(pixel);
      printf("%d--%d  -- %x\n",i,j,code[i/3][j/2] );
      sprintf(temp,"%2x",code[i/3][j/2]+0xA0);
      assert(strcat(totalString,temp ));
    }
  }
    for(i=0;i<(int)strlen(totalString);i++){
      if(totalString[i]==' '){
        totalString[i]='0';
      }
      if(i%40==0){
        totalString[i]='9';
        totalString[i+1]='7';
      }
    }
  printf("%s\n",totalString );
  for(i=0;i<1000;i+=2){
    char temporary[3];
    sprintf(temporary,"%c%c",totalString[i],totalString[i+1]);
    totality[i/2]=strtol(temporary,NULL,16);
    printf("%s %x\n",temporary, totality[i/2] );
  }


  // for(i=0;i<1000;i++){
  //   printf("%d-%c  ",i,totalString[i] );
  // }
  // printf("\n" );
  fp=fopen(OUTPUTFILE, "wb");

  fwrite(totality,sizeof(totality),1,fp );
  fclose(fp);
  return 0;
}

int sixelAssignment(int a, int b)
{
  switch (a) {
    case 0:
    if(b==0){
      return s_one;
    }
    else {
      return s_two;
    }
    break;
    case 1:
    if(b==0){
      return s_three;
    }
    else {
      return s_four;
    }
    break;
    case 2:
    if(b==0){
      return s_five;
    }
    else {
      return s_six;
    }
    break;
  }
  return 10;
}
int encodeSixels(uchar dots[3][2])
{
  int a,b,code=0;
  for(a=0;a<3;a++){
    for(b=0;b<2;b++){
      if(dots[a][b]==0) {
        code+=sixelAssignment(a,b);
      }
    }
  }
  return code;
}

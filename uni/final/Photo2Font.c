/*
* This program takes as input a series of photos
* named properly as the example "FONT" folder and makes a
* bitmap font file named
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "openCV.h"

#define FNTHEIGHT 18
#define FNTWIDTH  16
#define THRESHOLD 220
#define FNTCHARS  96
#define KERNELSIZE 4
#define TOTALCHARFONT FNTHEIGHT*FNTCHARS*4
#define OUTFNTFILE "trebouchet.fnt"
using namespace cv;



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

FileNames setFileNames(char* argument, char c);
void string2HexBinary(unsigned char totality[10000],char totalString[10000]);
void exportCode(unsigned char totality[TOTALCHARFONT]);


int main( int argc, char** argv )
{
  int i,j,k;
  char temp[4];
  FileNames names;
  unsigned char totality[TOTALCHARFONT];
  short unsigned font[FNTHEIGHT];
  char s[FNTHEIGHT][5];
  char totalString[10000];
  int counter=0;
  for(char c=' ';counter<FNTCHARS;c++){
    counter++;
    names=setFileNames(argv[1],c);
    Mat image,outImage;
    image = imread( names.charFile, 1 );
    Size size(FNTWIDTH,FNTHEIGHT);
    Size size2(KERNELSIZE,KERNELSIZE);
    blur(image,image,size2);
    resize(image, outImage,size);
    /*image mode conversion RGB to GRAY*/
    cvtColor( outImage, outImage, CV_BGR2GRAY );
    if( argc != 2 || !image.data ){
      printf( " No image data \n " );
      return -1;
    }
    imwrite( names.outputName, outImage );
    for(i=0; i<outImage.rows; i++) {
      font[i]=0;
      for(j=1; j<=outImage.cols; j++) {
        uchar pixel = outImage.at<uchar>(i,j);
        if(pixel<THRESHOLD){
          font[i]+=pow(2.0,outImage.cols-j);
        }
      }
      sprintf(s[i],"%4X",font[i]);
    }
    for(i=0;i<FNTHEIGHT;i++){
      for(j=0;j<5;j++){
        if(s[i][j]==32){
          s[i][j]='0';
        }
        for(k=0;k<4;k++){
          temp[k]=s[i][k];
        }
        s[i][0]=temp[2];
        s[i][1]=temp[3];
        s[i][2]=temp[0];
        s[i][3]=temp[1];
      }
      if(c==' ' && i==0){
        strcpy(totalString,s[i]);
      }
      else{
        strcat(totalString,s[i]);
      }
    }
  }
  for(i=0;i<(int)sizeof(totalString);i++){
    if(totalString[i]==32){
      totalString[i]='0';
    }
  }
  string2HexBinary(totality,totalString);
  exportCode(totality);
  return 0;
}

FileNames setFileNames(char* argument, char c)
{
  FileNames names;
  names.imageName=argument;
  strcpy(names.path,"font/");
  if('a'<= c && c <='z'){
    sprintf(names.charFile,"%s%s%c%c.jpg",names.path ,names.imageName,'m',c);
    sprintf(names.outputName,"%s%s%s%c%c.jpg",names.path , "touched",names.imageName,'m',c);
  }
  else if('A'<= c && c <='Z'){
    sprintf(names.charFile,"%s%s%c.jpg",names.path ,names.imageName,c);
    sprintf(names.outputName,"%s%s%s%c.jpg", names.path , "touched",names.imageName,c);
  }
  else{
    sprintf(names.charFile,"%s%d.jpg", names.path ,c);
    sprintf(names.outputName,"%s%s%d.jpg",names.path, "touched",c);
  }
  return  names;
}

void exportCode(unsigned char totality[TOTALCHARFONT])
{
  FILE *fp;
  fp=fopen(OUTFNTFILE, "wb");
  assert(fp!=NULL);
  fwrite(totality,sizeof(totality)*TOTALCHARFONT,1,fp );
  fclose(fp);
}
void string2HexBinary(unsigned char totality[TOTALCHARFONT],char totalString[10000]){
  int i;
  char temporary[3]={0};
  for(i=0;i<=TOTALCHARFONT;i+=2){
    sprintf(temporary,"%c%c",totalString[i],totalString[i+1]);
    totality[i/2]=strtol(temporary,NULL,16);
  }
}

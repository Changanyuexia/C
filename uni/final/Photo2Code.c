#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "openCV.h"

#define FNTHEIGHT 18
#define FNTWIDTH  16
#define WHEIGHT 25
#define WWIDTH 40
#define THRESHOLD 66
#define OUTPUTFILE "image.m7"
#define BLUR_KERNELSIZE 5

enum sixels {s_one=1,s_two=2,s_three=4,s_four=8,s_five=16,s_six=64};

typedef struct names FileNames;
struct names{
  char *imageName;
  char outputName[30];
  char charFile[30];
  char path[30];
};

typedef struct binPair BinPair;
struct binPair{
  unsigned char x;
  unsigned char y;
};

using namespace cv;

FileNames setFileNames(char* argument);
int sixelAssignment(int a, int b);
int encodeSixels(uchar dots[3][2]);
void parseImage(char totalString[10000], Mat outImage);
void addControlCodes(char totalString[10000]);
Mat imageProcess(Mat image, Mat middle);
void string2HexBinary(unsigned char totality[10000],char totalString[10000]);
void exportCode(unsigned char totality[10000]);
int argumentCheck(int argcnt,char *arg1);
void addTitle(char totalString[10000]);

int main( int argc, char** argv )
{

// LOADING THE IMAGE

  FileNames names;
  char totalString[10000];
  unsigned char totality[10000];
  Mat image,middle,outImage;
  names = setFileNames(argv[1]);
  if(argumentCheck(argc,argv[1])!=0){
    return 0;
  }
  image = imread( names.charFile, -1 );
  if(!image.data){
   fprintf(stderr, "No Image Data\n");
  }
  outImage=imageProcess(image,middle);
  imshow("icona",outImage);
  cvWaitKey();
  imwrite( names.outputName, outImage );
  parseImage(totalString,outImage);
  addControlCodes(totalString);
  addTitle(totalString);
  string2HexBinary(totality,totalString);
  exportCode(totality);
  return 0;
}
int argumentCheck(int argcnt, char *arg1)
{
  if( argcnt != 2){
    printf( "Run $./Photo2Code with options\
     %c-h%c or %c--help%c for use \n ",'"','"','"','"' );
    return -1;
  }
  if(strcmp(arg1,"--help")==0 || strcmp(arg1,"-h")==0){
    printf("./Photo2Code %cphoto file path%c\n",'"','"' );
    return -1;
  }
  return 0;
}
void addTitle(char totalString[10000])
{
  char tot[WWIDTH];
  char temp[2*WWIDTH];
  int i=0,j;
  strcpy(tot,"           THE BRISTOL TOWER      \0");
  for (j=0;j<(int)strlen(tot);j++){
    sprintf(temp,"%2x",tot[j]);
    totalString[i++]=temp[0];
    totalString[i++]=temp[1];
  }
}
FileNames setFileNames(char* argument)
{
  FileNames names;
  names.imageName=argument;
  strcpy(names.path,"photo/");
  sprintf(names.charFile,"%s%s",names.path,names.imageName);
  sprintf(names.outputName,"%s%s%s",names.path,"touched",names.imageName);

  return  names;
}
void exportCode(unsigned char totality[10000])
{
  FILE *fp;
  fp=fopen(OUTPUTFILE, "wb");
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
void addControlCodes(char totalString[10000])
{
  int i;
  for(i=0;i<10000;i++){
  if(totalString[i]==' '){
    totalString[i]='0';
  }
  if(i%(sizeof(short)*WWIDTH)==0){
    /*adding the white graphics control code to every line
    with 0x97 being the control code for white graphics*/
    totalString[i]='9';
    totalString[i+1]='7';
  }
}
printf("%s\n",totalString );

}
Mat threshold(Mat outImage)
{
  int i,j;
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
  return outImage;
}
Mat imageProcess(Mat image, Mat middle)
{
  Mat outImage;
  Size size(FNTHEIGHT*WHEIGHT,FNTWIDTH*WWIDTH);
  Size k_size(BLUR_KERNELSIZE,BLUR_KERNELSIZE);
  Size size3(FNTWIDTH*WWIDTH/8,FNTHEIGHT*(WHEIGHT-1)/6);
  resize(image, middle,size);
  blur(middle,middle,k_size);
  cvtColor( middle, middle, CV_BGR2GRAY );
  resize( middle, outImage,size3);
  printf("%dx%d\n",image.rows, image.cols );
  printf("%dx%d\n",outImage.rows, outImage.cols );
  printf("%dx%d\n",middle.rows, middle.cols );
  outImage=threshold(outImage);
  return outImage;
}
void parseImage(char totalString[10000], Mat outImage)
{
  int i,j;
  short unsigned int code[WHEIGHT][WWIDTH];
  char temp[10000]={0};
  for(i=0;i<WWIDTH*(int)sizeof(short)*2;i++){
    strcat(totalString," ");
  }
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
     //printf("%d--%d  -- %x\n",i,j,code[i/3][j/2] );
      sprintf(temp,"%2x",code[i/3][j/2]+0xA0);
      assert(strcat(totalString,temp ));
    }
  }
  //printf("%s\n",totalString );
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

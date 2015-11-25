#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 4
#define ITERATIONS 10000

void fillArray(int a[LENGTH]);
void printArray(int a[LENGTH]);
int  isAscending(int a[LENGTH]);

int main(void)
{
  int i,cnt=0;
  float ascending;
  int a[LENGTH];
  srand((unsigned) time(NULL));
  for(i=0;i<ITERATIONS;i++){
  fillArray(a);
  printArray(a);
  if(isAscending(a)){
    printf("is ascending\n");
    cnt++;
  }
  else{printf("is not ascending\n");}
  }
  ascending=(float)cnt/ITERATIONS*100.0;
  printf("ascending: %f\n",ascending);
  return 0;
}
int isAscending(int a[LENGTH])
{
  int i,watermark=1;
  for(i=0;i<LENGTH-1;i++){
    if(a[i+1]<a[i]){
      watermark--;
    }
  }
  return watermark;
}

void fillArray(int a[LENGTH])
{
  int i;
  for(i=0;i<LENGTH;i++){
    a[i]=rand()%10;
  }
}
void printArray(int a[LENGTH])
{
  int i;
  for(i=0;i<LENGTH;i++){
    printf("%d ",a[i]);
  }
  printf("\n");
}

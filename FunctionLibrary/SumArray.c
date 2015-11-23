#define W 10
#define H 10
int SumArray(int A[H]);
int SumArray2(int A[H][W]);

int SumArray(int A[H])
{
  int i,sum=0;
  for(i=0;i<H;i++){
    sum+=A[i];
  }
  return sum;
}

int SumArray2(int A[H][W])
{
  int i,j,sum=0;
  for(i=0;i<H;i++){
    for(i=0;i<H;i++){
      sum+=A[i][j];
    }
  }
  return sum;
}

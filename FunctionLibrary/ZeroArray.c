#define W 10
#define H 10
void ZerpArray(int A[H]);
void Zerorray2(int A[H][W]);

void ZeroArray(int A[H])
{
  int i,sum=0;
  for(i=0;i<H;i++){
    A[i]=0;
  }
  return sum;
}

void ZeroArray2(int A[H][W])
{
  int i,j,sum=0;
  for(i=0;i<H;i++){
    for(i=0;i<H;i++){
      A[i][j]=0;
    }
  }
}

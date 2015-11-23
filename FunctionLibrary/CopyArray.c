#define W 10
#define H 10
void CopyArray(int A[H], int B[H]);
void Copyrray2(int A[H][W], int B[H][W]);

void CopyArray(int A[H], int B[H])
{
  int i,sum=0;
  for(i=0;i<H;i++){
    A[i]=B[i];
  }
  return sum;
}

void CopyArray2(int A[H][W], int B[H][W])
{
  int i,j,sum=0;
  for(i=0;i<H;i++){
    for(i=0;i<H;i++){
      A[i][j]=B[i][j];
    }
  }
}

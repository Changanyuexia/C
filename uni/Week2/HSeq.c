/*Hailstone Sequence*/
/*Checks for the initial number <50000
that creates the longest Sequence
Answer---n0=35655--in 205-steps*/
/*Checks for the initial number
that provokes the largest number
in the Sequence initials<50000
Answer---max=121012864          */

#include <stdio.h>

int hSeq (int n);
void maxSeq (void);
int maxNum (int n, int max, int cnt);

int main(void)
{
      maxSeq();
      return(0);
}

int hSeq (int n)
{
  int i=0,max;
    printf("%3d---%3d\n",i,n);
      while(n>2){
        i++;
        if(n%2 == 0){n=n/2;  printf("%3d---%3d\n",i,n);}
        if(n%2 == 1){n=3*n+1; printf("%3d---%3d\n",i,n);}
        max=maxNum(n, max ,i);
      }
    i++;
    n=1;
    printf("%3d---%3d\n",i,n);
    printf("%d----------%d\n", max, i );
    return(i);
}
int maxNum(int n, int max, int cnt)
{
    if(n>(max)){
      printf("currentmax=%d i=%d\n",n,cnt);
      return(n);
    }
    else{return(max);}
}
void maxSeq(void)
{
  int i, fin=0, temp=0, num=0;
     for(i=2;i<=50000;i++){
       temp=hSeq(i);
       if (temp>fin){
         fin=temp;
         num=i;
       }
        printf("%d\n",temp);
     }
     printf("%d---%d\n",num,fin);
}

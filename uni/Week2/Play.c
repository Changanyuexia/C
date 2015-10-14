#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

void randswap(int b[], int i,int songs);
void randswap2(int b[], int i);
void change(int b[],int i,int songs);

int main(void)
{
   int i, songs;
   int play[MAX];
   printf("How many songs required  ?\n" );
   scanf("%d",&songs );
      for (i=1;i<=songs;i++){
         play[i]=i;
         printf("Play[%d]=%d\n", i, play[i]);
      }
      for(i=1;i<=songs;i++){
      randswap(play,i,songs);
      }
      for (i=1;i<=songs;i++){
   printf("Play[%2d ] = %2d\n", i, play[i]);
 }
   return(0);
}

void randswap(int b[], int i, int songs)
{
   time_t t;
   int temp, buffer;
   srand((unsigned) i*time(&t));
   temp=1+rand()%(songs-1);
   buffer=b[i];
   b[i]=b[temp];
   b[temp]=buffer;

}

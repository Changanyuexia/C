#include <stdlib.h>
#include <time.h>

/*Swaps  b[i] with b[rand] */
void randswap(int b[], int i, int songs);

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

#include <stdio.h>
#define MAX 255
/*check if it can be replaced by a % sign */
int overspill(int coordinate, int max);

int main(void)
{
  int i1=500;
  int i2=255;
  int i3=0;
  int i4=-10;


  printf("%4d-OS %4d --- %c %d\n",i1,overspill(i1,MAX),'%',i1%MAX );
  printf("%4d-OS %4d --- %c %d\n",i2,overspill(i2,MAX),'%',i2%MAX );
  printf("%4d-OS %4d --- %c %d\n",i3,overspill(i3,MAX),'%',i3%MAX );
  printf("%4d-OS %4d --- %c %d\n",i4,overspill(i4,MAX),'%',i4%MAX );

  return 0;
}
int overspill(int coordinate, int max)
{
   int division;
   if (coordinate>(max-1)){
      division = coordinate/(max-1);
      coordinate -= (division*(max));
   }
   if (coordinate < 0){
     coordinate += (max);
   }
   return (coordinate);
}

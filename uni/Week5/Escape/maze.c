#include <stdio.h>
#define  HEIGHT  3
#define  WIDTH   3

void nextStepH(int x, int y, int *p, int maze[HEIGHT][WIDTH]);

int main(void)
{
   int i,x,y;
   int maze[HEIGHT][WIDTH];
   int pattern[HEIGHT][WIDTH];
   int *p;
   p=*maze;
   for(i=1;i<=9;i++){
     *p=i;
     printf("%d\n", *p++);
   }
   x=y=0;
   pattern[y][x]=maze[0][0];
 p=*pattern;
   nextStepH(x, y, p, maze);
   p=*pattern;
   for(i=1;i<=9;i++){
     printf("%d\n", *p++);
   }
   return(0);
}
void nextStepH(int x, int y, int *p, int maze[HEIGHT][WIDTH])
{
  int i;
   for(i=0;x<WIDTH;i++){
     if(x==WIDTH-1 &&y<HEIGHT){
      *++p=maze[y][x];

     }
      x++;
   }
   for(i=0;y<HEIGHT;i++){
     if(x<WIDTH &&y==HEIGHT){
      *++p=maze[y][x];

     }
      y++;
   }
}

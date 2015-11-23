#include <stdio.h>
#include <ctype.h>
#define  HEIGHT  5
#define  WIDTH   5
#define  AREA   11


struct position{
  int x;
  int y;
};
int nextStep(struct position *en, char maze[HEIGHT][WIDTH], char *r);
int goRight(struct position *en, char maze[HEIGHT][WIDTH]);
int goDown(struct position *en);
int goLeft(struct position *en);
int goUp(struct position *en);
void printB(int x,int y, char maze[HEIGHT][WIDTH],char rmaze[AREA]);
void fillB(char maze[HEIGHT][WIDTH]);

int main(void)
{
   struct position entity;
   struct position *en;
   char maze[HEIGHT][WIDTH]= {"#####","#123#","#456#","#789#","#####"};
   char rmaze[AREA]= {"#1#########"};
   char *r;
   r=rmaze+2;
   entity.x=1;
   entity.y=1;
   en=&entity;
   printB(en->x,en->y,maze,rmaze);
   nextStep(en,maze,r);
   printB(en->x,en->y,maze,rmaze);
   fillB(maze);
   printB(en->x,en->y,maze,rmaze);
   entity.y=1;
   entity.x=2;
   r=rmaze+3;
   nextStep(en,maze,r);
   printB(en->x,en->y,maze,rmaze);
   return(0);
}
int nextStep(struct position *en, char maze[HEIGHT][WIDTH], char *r)
{
   int a=goRight(en,maze);
   if(a>0){
      *r++=maze[en->y][en->x];
      return(nextStep(en,maze,r)+a);
   }
   else{
      return(0);
   }
}

int goRight(struct position *en, char maze[HEIGHT][WIDTH])
{
   if(isdigit(maze[en->y][en->x+1])){
      maze[en->y][en->x]='*';
      en->x++;
      return(1);
   }
   else if(isdigit(maze[en->y+1][en->x])){
      maze[en->y][en->x]='*';
      return(goDown(en));
   }
   else if(isdigit(maze[en->y][en->x-1])){
      maze[en->y][en->x]='*';
      return(goLeft(en));
   }
   else if(isdigit(maze[en->y-1][en->x])){
      maze[en->y][en->x]='*';
      return(goUp(en));
   }
   return(0);
}
int goDown(struct position *en)
{
    en->y++;
    return(2);
}
int goLeft(struct position *en)
{
    en->x--;
    return(3);
}
int goUp(struct position *en)
{
    en->y--;
    return(3);
}
void fillB(char maze[HEIGHT][WIDTH])
{
  int i,j;
  for (i=1;i<HEIGHT-1;i++){
    for(j=1;j<WIDTH-1;j++){
      maze[i][j]=j+3*(i-1)+48;
    }
  }
}
void printB(int x,int y,char maze[HEIGHT][WIDTH],char rmaze[AREA])
{
  int i,j;
  /*print board and player*/
     for(i=0;i<HEIGHT;i++){
        for(j=0;j<WIDTH;j++){
          if(i==y&&j==x){
            printf("@" );
          }
          else{
           printf("%c",maze[i][j] );
          }
        }
        printf("\n");
      }
      /*print step array*/
      for(i=0;i<11;i++){
            printf("%c",rmaze[i]);
         }
         printf("\n");
}

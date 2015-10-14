#include <stdio.h>

int devision(int sec,int i, int a);

int main(void)
{
   int a[3]={600, 60, 10};
   int times[3];
   int i,sec;
      for (i=0;i<3;i++)
      {printf("%d\n",a[i]);}
   printf("Type the time required\n");
   scanf("%d",&sec);
      for(i=0;i<3;i++){
         times[i]=devision(sec, 0, a[i]);
         sec =sec-a[i]*times[i];
      }
   printf("Number of button presses = %d\n",times[0]+times[1]+times[2]);
   return(0);
}

int devision(int sec, int i,int a)
{
  int div,rest;
   if(sec>=a){
     div=sec/a;
     rest=sec%a;
     printf("%3d--%d--time needed yet %d sec\n",a,div,rest);
     if(a==10&&rest>0)
     {div++;}
   return(div);
   }
   return(0);
}

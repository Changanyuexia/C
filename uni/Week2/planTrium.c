#include <stdio.h>

#define NUM 97
#define MAX_ALPHA 26

int main(void)
{
    int cnt, i, j, k;

    char c1='a',c2='a',c3='a';

    cnt=0;
      for(k=0;k<MAX_ALPHA;k++){
         for(j=0;j<MAX_ALPHA;j++){
            for(i=0;i<MAX_ALPHA;i++){
              if(c3!='a' && c3!='e' && c3!='i' && c3!='o' && c3!='u'){
                 if(c2=='a' || c2=='e' || c2=='i' || c2=='o' || c2=='u'){
                    if(c1!='a' && c1!='e' && c1!='i' && c1!='o' && c1!='u'){
                    cnt++;
                    printf("%6d %4c%c%c\n",cnt, c1 , c2, c3);
                    }
                 }
             }
            c3++;
            }
           c3='a';
          c2++;
         }
        c2='a';
        c1++;
      }
      c1='a';
    return 0;
}

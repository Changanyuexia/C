/* The Secret Codes Program gets a character
and decrypts it through a secret formula  */
#include <stdio.h>

int scodes(int a);

int main(void)
{
   char c;
   while ((c = getchar())!=EOF){
     c = scodes(c);
       printf("%c",c );
   }
   return(0);
}
/* Scrumbling up the letters*/
int scodes(int a)
{
    if(a>='a'&& a<='z'){
      /*---[ a+('z'-a)-(a-'a') ]--- Equivalent*/
       return('z'-(a-'a'));
    }
    else if(a>='A'&& a<='Z'){
      /*---[ a+('Z'-a)-(a-'A') ]--- Equivalent*/
           return('Z'-(a-'A'));
        }
    else{return(a);}
}

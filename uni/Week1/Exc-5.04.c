#include <stdio.h>

#define CAPS ('A' - 'a')

int isVowel(int c);

int main(void)
{
   int c;

   while ((c = getchar())  != EOF){
      
     if(isVowel(c)==1 && c>='a'&& c<='z'){
       putchar(c+CAPS);
     }
     else if(isVowel(c)==0 && c>='A' && c<='Z'){
       putchar(c-CAPS);
     }
     else{
       putchar(c);
     }
   }
   return(0);
}

int isVowel(int c)
{
   if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||
      c=='A'||c=='E'||c=='I'||c=='O'||c=='U'){
     return(1);
   }
   else{return(0);}
}

#define CAPS ('A' - 'a')

/*returns 1 if true 0 if false*/
int isVowel(int c);


int isVowel(int c)
{
   if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||
      c=='A'||c=='E'||c=='I'||c=='O'||c=='U'){
     return(1);
   }
   else{return(0);}
}

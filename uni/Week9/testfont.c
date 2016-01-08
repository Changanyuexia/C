#include "neillsdl2.h"

/* NB not all symbols present, not guaranteed to be ASCII.
Letters & Numbers all OK */

#define FNTFILENAME "m7fixed.fnt"

int main(int argc, char *argv[])
{

   SDL_Simplewin sw;
   fntrow fontdata[FNTCHARS][FNTHEIGHT];

   if(argc != 1){
      fprintf(stderr, "Usage : %s\n", argv[0]);
      exit(1);
   }

   Neill_SDL_Init(&sw, 800 , 600);
   Neill_SDL_ReadFont(fontdata, FNTFILENAME);
   Neill_SDL_DrawString(&sw, fontdata, "Lorem ipsum dolor sit amet, consectetur", 1, 200);
   Neill_SDL_DrawString(&sw, fontdata, "The Quick Brown Fox Jumps over the Lazy Dogs.", 1, 200+2*FNTHEIGHT);

   SDL_RenderPresent(sw.renderer);
   SDL_UpdateWindowSurface(sw.win);
   SDL_WaitEvent(SDL_Event event);

   SDL_Quit();

   return(EXIT_SUCCESS);

}

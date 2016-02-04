#include <SDL2/SDL.h>
#include <math.h>
#include "teletext.h"      

#define WWIDTH WIDTH*FNTWIDTH
#define WHEIGHT HEIGHT*FNTHEIGHT

#define SDL_8BITCOLOUR 256

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

/* All info required for windows / renderer & event loop */
struct SDL_Simplewin {
   int finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
};
typedef struct SDL_Simplewin SDL_Simplewin;

void Neill_SDL_Init(SDL_Simplewin *sw, int width, int height);
void Neill_SDL_ReadFont(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *fname);
void Neill_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b);
unsigned setYCoord(CharStyle style, unsigned y , unsigned* oy, unsigned *fntIndex);
void Neill_SDL_DrawChar(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, CharStyle style);
void Neill_SDL_Events(SDL_Simplewin *sw);
void SDL_FREE(SDL_Simplewin *sw);
void createGraphFont(fntrow graphdata[FNTCHARS][FNTHEIGHT], int mode);
void setupSDL(fntrow graphdata[2][FNTCHARS][FNTHEIGHT],fntrow fontdata[FNTCHARS][FNTHEIGHT],fntrow fontA[FNTCHARS][FNTHEIGHT]);
void drawFrame(SDL_Simplewin *sw);
/*void DrawSixel(SDL_Simplewin sw, CharStyle style, int code);
void Neill_SDL_ReadFontChar(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *fname);
void Neill_SDL_DrawString(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], char *str, int ox, int oy);
*/

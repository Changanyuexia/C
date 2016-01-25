#include "neillsdl2.h"

/*  Set up a simple (WIDTH, HEIGHT) window.
   Attempt to hide the renderer etc. from user. */
void Neill_SDL_Init(SDL_Simplewin *sw, int width, int height)
{


   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   sw->finished = 0;

   sw->win= SDL_CreateWindow("SDL Window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          width, height,
                          SDL_WINDOW_SHOWN);
   if(sw->win == NULL){
      fprintf(stderr, "\nUnable to initialize SDL Window:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   sw->renderer = SDL_CreateRenderer(sw->win, -1, 0);
   if(sw->renderer == NULL){
      fprintf(stderr, "\nUnable to initialize SDL Renderer:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   /* Set screen to black */
   Neill_SDL_SetDrawColour(sw, 0, 0, 0);
   SDL_RenderClear(sw->renderer);
   SDL_RenderPresent(sw->renderer);

}

/* Trivial wrapper to avoid complexities of renderer & alpha channels */
void Neill_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b)
{

   SDL_SetRenderDrawColor(sw->renderer, r, g, b, SDL_ALPHA_OPAQUE);

}

void Neill_SDL_DrawChar(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, CharStyle style)
{

   unsigned x, y,oy=0,index_y=0;
   /*if(chr>128){
    chr-=128;
  } CUIDAAAAOOOO*/

   for(y = 0; y < FNTHEIGHT; y++){
      for(x = 0; x < FNTWIDTH; x++){
        index_y=y;
   switch (style.height) {
     case singleH:
       oy=y+style.oy;
       break;
     case doubleH1:
       oy=2*y+style.oy;
       break;
     case doubleH2:
       oy=2*y+style.oy;
       index_y=y+FNTHEIGHT/2;
       break;
   }
         if(fontdata[chr-FNT1STCHAR][index_y] >> (FNTWIDTH - 1 - x) & 1){
            /*printf("*");*/
            /* White Ink */
            Neill_SDL_SetDrawColour(sw, style.character.r, style.character.g, style.character.b);
            SDL_RenderDrawPoint(sw->renderer, x + style.ox, oy++);
            if(style.height!=singleH){
              SDL_RenderDrawPoint(sw->renderer, x + style.ox, oy);
            }
         }
         else{
            /*printf(".");*/
            /* Black Ink */
            Neill_SDL_SetDrawColour(sw, style.background.r, style.background.g, style.background.b);
            SDL_RenderDrawPoint(sw->renderer, x + style.ox, oy++);
            if(style.height!=singleH){
              SDL_RenderDrawPoint(sw->renderer, x + style.ox, oy);
            }
         }
      }
   }

}
void renderPattern(SDL_Simplewin *sw, CharStyle style , int graphdata[3][2], SDL_Rect rectSixel, SDL_Rect rectBack)
{
  int i,j;
  rectBack.x=style.ox;
  rectBack.y=style.oy;
  Neill_SDL_SetDrawColour(sw,style.background.r, style.background.g, style.background.b);
  SDL_RenderFillRect(sw->renderer,&rectBack );
  for(i=0;i<3;i++){
    for(j=0;j<2;j++){
      if(graphdata[i][j]==1){
        Neill_SDL_SetDrawColour(sw,style.graphics.r, style.graphics.g, style.graphics.b);
        switch (style.grMode) {
          case hold:
          case contiguous:
            rectSixel.x=style.ox+j*rectSixel.w;
            rectSixel.y=style.oy+i*rectSixel.h;
            break;
          case separated:
            rectSixel.x=style.ox+j*rectSixel.w+2*j;
            rectSixel.y=style.oy+i*rectSixel.h+2*i;
            break;

        }
        SDL_RenderFillRect(sw->renderer,&rectSixel );
      }
    }
  }
}

void DrawSixel(SDL_Simplewin sw, CharStyle style,int code)
{
  int graphdata[3][2];
  SDL_Rect rectBack,rectSixel;
  rectBack.h=FNTHEIGHT;
  rectBack.w=FNTWIDTH;
  decodeSixels(graphdata, code);
  switch (style.grMode) {
    case hold:
    case contiguous:
      rectSixel.h=FNTHEIGHT/3;
      rectSixel.w=FNTWIDTH/2;
      renderPattern(&sw, style, graphdata, rectSixel,rectBack);
      break;
    case separated:
      rectSixel.h=4;
      rectSixel.w=6;
      renderPattern(&sw, style, graphdata, rectSixel,rectBack);
      break;
  }

}


void Neill_SDL_ReadFont(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *fname)
{

    FILE *fp = fopen(fname, "rb");
    size_t itms;
    if(!fp){
       fprintf(stderr, "Can't open Font file %s\n", fname);
       exit(1);
   }
   itms = fread(fontdata, sizeof(fntrow), (FNTCHARS)*FNTHEIGHT, fp);
   if(itms != (FNTCHARS)*FNTHEIGHT){
       fprintf(stderr, "Can't read all Font file %s (%d) \n", fname, (int)itms);
       exit(1);
   }
   fclose(fp);

}
void Neill_SDL_ReadFontChar(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *fname)
{

    FILE *fp = fopen(fname, "rb");
    size_t itms;
    if(!fp){
       fprintf(stderr, "Can't open Font file %s\n", fname);
       exit(1);
   }
 itms = fread(fontdata, sizeof(fntrow), 93*FNTHEIGHT, fp);
   if(itms != 93*FNTHEIGHT){
       fprintf(stderr, "Can't read all Font file %s (%d) \n", fname, (int)itms);
       exit(1);
   }
   fclose(fp);

}
/* Gobble all events & ignore most */
void Neill_SDL_Events(SDL_Simplewin *sw)
{
   SDL_Event event;
   while(SDL_PollEvent(&event))
   {
       switch (event.type){
          case SDL_QUIT:
          case SDL_MOUSEBUTTONDOWN:
          case SDL_KEYDOWN:
             sw->finished =1;
       }
    }
}

void SDL_FREE(SDL_Simplewin *sw)
{
  SDL_RenderClear(sw->renderer);
  SDL_DestroyRenderer(sw->renderer);
  SDL_DestroyWindow(sw->win);
  sw->renderer=NULL;
  sw->win=NULL;
  SDL_Quit();
}

#include "SDL2/SDL.h"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_ttf.h"

#define RATIO 576/720
#define SWIDTH 2000
int handle_event()
{
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return -1;
    }
  }
  return 0;
}

int main()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();

  SDL_Window *window = SDL_CreateWindow("test", 100, 100, 720, 576, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  TTF_Font *font = TTF_OpenFont("/home/np15685/Downloads/Software/arduino-1.6.5-r5/java/lib/fonts/LucidaSansRegular.ttf", 200);
  if (font == NULL)
    printf("null font\n");

  SDL_Color color = {40, 100, 255,0};
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Lucida San", color);
  if (textSurface == NULL)
    printf("null text surface\n");

  SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
  if (textTexture == NULL)
    printf("null text texture\n");

  SDL_Rect src = { 0, 0,SWIDTH , SWIDTH*RATIO };
SDL_Rect dest = { 0, 0, 720-150 , (750-150)*RATIO };


  while (handle_event() == 0) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textTexture, &src, &dest);
    SDL_RenderPresent(renderer);
   
  }
textSurface = TTF_RenderText_Solid(font, "niko rul", color);
textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
 while (handle_event() == 0) {
     
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
   
  }
  return 0;
}


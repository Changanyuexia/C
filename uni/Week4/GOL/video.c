#include <SDL/SDL.h>
/*This pointer will reference the backbuffer*/
SDL_Surface *screen;
/*This pointer will reference our bitmap sprite*/
SDL_Surface *image;
/*This pointer will temporarily reference our bitmap sprite*/
SDL_Surface *temp;
/*These rectangles will describe the source and destination regions of our blit*/
	SDL_Rect src, dest;
/*diko mou-telos*/
void demo_init(int x, int y);
/* Types */
typedef struct
{
	int red,green; /* The shade of color in red,green. blue is always 0 since we're using it as the background */
	float x,y; /* Current position of particle */
}dot;
/* Initialize SDL */
if(SDL_Init(SDL_INIT_VIDEO) != 0)
    fprintf(stderr,"Could not initialize SDL: %s\n",SDL_GetError());
/* Open main window */
screen = SDL_SetVideoMode(WIDTH,HEIGHT,0,SDL_HWSURFACE|SDL_DOUBLEBUF);
  SDL_FillRect(screen,NULL,SDL_MapRGBA(screen->format,255,255,255,255));
if(!screen)
    fprintf(stderr,"Could not set video mode: %s\n",SDL_GetError());
    /* Initialize dots */
    void demo_init(int x, int y)
    {
    	int i;


    	{
    		demo_dots[i].red = rand()%255;
    		demo_dots[i].green = rand()%255;
    		demo_dots[i].x = x;
    		demo_dots[i].y = y;
    	}
    }

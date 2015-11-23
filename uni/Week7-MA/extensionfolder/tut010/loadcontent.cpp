#include"game.h"

bool game::LoadContent()
{
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"background.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rectBackground.x = 0; rectBackground.y = 0; rectBackground.w = 256; rectBackground.h = h;
    SDL_GetRendererOutputSize(renderer,&screenWidth,&screenHeight);
    displayRect.w=screenWidth;displayRect.h=screenHeight;displayRect.x=displayRect.y=0;

    font = TTF_OpenFont( "Tahoma.ttf", 20 );
    if( font == NULL )
    {
        return false;
    }


    message = TTF_RenderText_Solid( font, "This is just a short sentence.", textColor );
    text = SDL_CreateTextureFromSurface(renderer,message);
    SDL_QueryTexture(text, NULL, NULL, &w, &h);
    textRect.x=50;textRect.y=50;textRect.w=w;textRect.h=h;

    return 1;
}

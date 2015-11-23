#include"game.h"
void game::OnRender()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, &rectBackground, &displayRect);
    //if(data!=""){
    SDL_RenderCopy(renderer, text, NULL, &textRect);
    //}

    SDL_RenderPresent(renderer);
}

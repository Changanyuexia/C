#include"game.h"

void game::Cleanup()
{
    SDL_FreeSurface(message);
    SDL_DestroyTexture(text);
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

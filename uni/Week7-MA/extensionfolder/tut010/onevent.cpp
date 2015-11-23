#include"game.h"

void game::OnEvent(SDL_Event* Event) {
    //handle window close
    if(Event->type == SDL_QUIT) {
        Running = false;
    }
    //handle screen resize
    if( Event->type == SDL_WINDOWEVENT )
    {
        switch (Event->window.event){
        case SDL_WINDOWEVENT_RESIZED:
            SDL_GetRendererOutputSize(renderer,&screenWidth,&screenHeight);
            displayRect.w=screenWidth;displayRect.h=screenHeight;displayRect.x=displayRect.y=0;
            break;
        }
    }
    //handle key press
    //int w=0,h=0;
    if(Event->type == SDL_KEYDOWN)
    {
        /*
        data = data + SDL_GetScancodeName(Event->key.keysym.scancode);
        std::cout<<data<<std::endl;
        message = TTF_RenderText_Solid( font, data.c_str(), textColor );
        text = SDL_CreateTextureFromSurface(renderer,message);
        SDL_QueryTexture(text, NULL, NULL, &w, &h);
        textRect.x=0;textRect.y=50;textRect.w=w;textRect.h=h;
        */
        switch(Event->key.keysym.sym)
        {
            case SDLK_d: /*do some thing*/;break;
            case SDLK_a: /*do some thing*/;break;
            case SDLK_ESCAPE: Running=false;break;
        }
    }
    //handle key release
    if(Event->type == SDL_KEYUP)
    {
        switch(Event->key.keysym.sym)
        {
            case SDLK_d: /*do some thing*/;break;
            case SDLK_a: /*do some thing*/;break;

        }
    }
}

//
//  main.cpp
//  GPC_Ch01
//
//  Created by Inoue Shinichi on 2022/03/02.
//

#include "Game.hpp"

#include "SDL2/SDL.h"
#include <cstdio>

int main(int argc, const char * argv[])
{
    Game game;
    bool success = game.Initialize();
    if (success)
    {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;

//    // SDL2の動作チェック
//    {
//        SDL_Init(SDL_INIT_VIDEO);
//
//        SDL_Window* window = SDL_CreateWindow(
//                                              "SDL2 window title",
//                                              SDL_WINDOWPOS_UNDEFINED,
//                                              SDL_WINDOWPOS_UNDEFINED,
//                                              640,
//                                              480,
//                                              SDL_WINDOW_OPENGL);
//
//        if (window == NULL)
//        {
//            std::printf("Could not create window: %s\n", SDL_GetError());
//            return 1;
//        }
//
//        SDL_Event event;
//        while (SDL_PollEvent(&event))
//        {
//            if (event.type == SDL_QUIT)
//            {
//                SDL_DestroyWindow(window);
//                SDL_Quit();
//                return 0;
//            }
//        }
//
//        SDL_Delay(5000);
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return 0;
//    }

}


//#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
//int main(){
//SDL_Surface *text,*screen; SDL_Window *window;
//SDL_Rect scr_rect;
//SDL_Color white = {255, 255, 255}; TTF_Font* font;
//SDL_Init(SDL_INIT_EVERYTHING);
//TTF_Init();
//window = SDL_CreateWindow("test",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN); screen = SDL_GetWindowSurface(window);
//font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 30);
//text = TTF_RenderUTF8_Blended(font, "Hello Xcode and SDL2", white); scr_rect.x = 60;
//scr_rect.y = 200;
//
//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,1,1,1)); SDL_BlitSurface(text, NULL, screen, &scr_rect); SDL_UpdateWindowSurface(window); SDL_Delay(10000);
//SDL_FreeSurface(text); TTF_CloseFont(font); TTF_Quit(); SDL_Quit();
//return 0; }

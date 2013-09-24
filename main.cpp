#include "Sprite.hpp"
#include "util.hpp"
#include "Game.hpp"
#include "Menu.hpp"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

bool inMenu = true;

int main()
{
    SDL_Window *win = SDL_CreateWindow("TicTacToe - Press R to restart.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 400, SDL_WINDOW_SHOWN);
    tictac_assert(win, SDL_GetError());
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    tictac_assert(ren, SDL_GetError());

    tictac_assert(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG, IMG_GetError());

    Game game(ren);
    Menu menu(ren);

    bool is_running = true;
    while (is_running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                is_running = false;
                break;
            default:
                ;
            }

            if (!inMenu)
                game.onEvent(event);
            else
                menu.onEvent(event);
        }

        if (!inMenu)
        {
            game.update();
        }
        else
        {
            menu.update();
        }

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    SDL_Quit();
}

#include "Sprite.hpp"
#include "util.hpp"
#include "Game.hpp"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

bool menu = true;

int main()
{
    SDL_Window *win = SDL_CreateWindow("TicTacToe - Press R to restart.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 400, SDL_WINDOW_SHOWN);
    tictac_assert(win, SDL_GetError());
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    tictac_assert(ren, SDL_GetError());

    tictac_assert(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG, IMG_GetError());

    Sprite spr_menuBg(loadTexture(ren, "res/bg_menu.bmp"));
    Sprite spr_playButton(loadTexture(ren, "res/button_play.bmp"), 75, 100);
    Sprite spr_selectionArrow(loadTexture(ren, "res/selectionarrow.bmp"), 65, 100);
    Sprite spr_exitButton(loadTexture(ren, "res/button_exit.bmp"), 75, 200);

    Game game(ren);

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

            if (!menu)
                game.onEvent(event);
        }

        if (!menu)
        {
            game.update();
        }
        else
        {
            spr_menuBg.draw(ren);
            spr_playButton.draw(ren);
            spr_exitButton.draw(ren);

            if (pointIsInRect({event.motion.x, event.motion.y}, spr_playButton.getRect()))
            {
                spr_selectionArrow.draw(ren);
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    menu = false;
                }
            }
            if (pointIsInRect({event.motion.x, event.motion.y}, spr_exitButton.getRect()))
            {
                spr_selectionArrow.move(0, 100);
                spr_selectionArrow.draw(ren);
                spr_selectionArrow.move(0, -100);

                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    is_running = false;
                }
            }
        }

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    SDL_Quit();
}

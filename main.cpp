#include "Sprite.hpp"
#include "util.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "driver.hpp"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

int main()
{
    driver::init();

    Game game;
    Menu menu;

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

            if (!driver::menu)
                game.onEvent(event);
            else
                menu.onEvent(event);
        }

        if (!driver::menu)
        {
            game.onUpdate();
        }
        else
        {
            menu.onUpdate();
        }

        SDL_RenderPresent(driver::renderer);
        SDL_Delay(16);
    }

    SDL_Quit();
}

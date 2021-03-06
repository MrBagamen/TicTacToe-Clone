#include "driver.hpp"
#include "util.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>

using namespace util;

namespace driver
{

SDL_Renderer *renderer;
bool running;

std::map<std::string, State *> m_states;
State *m_state;
SDL_Window *win;

void init()
{
    win = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 400, SDL_WINDOW_SHOWN);
    tictac_assert(win, SDL_GetError());
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    tictac_assert(renderer, SDL_GetError());

    tictac_assert(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG, IMG_GetError());
    tictac_assert(SDLNet_Init() == 0, SDLNet_GetError());
    running = true;
}

void addState(const std::string &name, State *state)
{
    m_states[name] = state;
}

void setState(const std::string &name)
{
    m_state = m_states[name];
}

void update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        default:
            ;
        }

        m_state->onEvent(event);
    }

    m_state->onUpdate();

    SDL_RenderPresent(driver::renderer);
    SDL_Delay(16);
}

void quit()
{
    for (auto pair : m_states)
    {
        delete pair.second;
    }

    SDLNet_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

}

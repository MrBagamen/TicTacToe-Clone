#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <SDL2/SDL.h>

namespace driver
{

void init();

extern SDL_Renderer *renderer;
extern bool menu;

}

#endif // DRIVER_HPP

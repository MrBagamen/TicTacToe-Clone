#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "State.hpp"

#include <string>
#include <map>
#include <SDL2/SDL.h>

namespace driver
{

void init();
void addState(const std::string& name, State *state);
void setState(const std::string& name);
void update();
void quit();

extern SDL_Renderer *renderer;
extern bool running;

}

#endif // DRIVER_HPP

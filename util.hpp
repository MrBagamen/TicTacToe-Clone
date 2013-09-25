#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

#include <SDL2/SDL.h>

namespace util
{

void tictac_assert(bool expr, const std::string &message);
bool pointIsInRect(SDL_Point p, SDL_Rect r);

}

#endif // UTIL_HPP

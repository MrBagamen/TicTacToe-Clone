#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

#include <SDL2/SDL.h>

void tictac_assert(bool expr, const std::string &message);
bool pointIsInRect(SDL_Point p, SDL_Rect r);
SDL_Texture *loadTexture(const std::string &filename);

#endif // UTIL_HPP

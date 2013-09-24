#include "util.hpp"

#include <iostream>
#include <SDL2/SDL_image.h>

using namespace std;

void tictac_assert(bool expr, const string &message)
{
    if (!expr)
    {
        cerr << message << endl;
        exit(1);
    }
}

bool pointIsInRect(SDL_Point p, SDL_Rect r)
{
    return p.x > r.x && p.x < r.x + r.w && p.y > r.y && p.y < r.y + r.h;
}

// Load a texture assertively
SDL_Texture *loadTexture(SDL_Renderer *renderer, const string &filename)
{
    auto tex = IMG_LoadTexture(renderer, filename.c_str());
    tictac_assert(tex, IMG_GetError());
    return tex;
}

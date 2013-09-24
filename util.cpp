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

bool checkWinrar(char *a, int p, bool &ended)
{
    //1 = X, 2 = O
    if (((a[0] == p) && (a[1] == p) && (a[2] == p)) ||
            ((a[0] == p) && (a[4] == p) && (a[8] == p)) ||
            ((a[0] == p) && (a[3] == p) && (a[6] == p)) ||
            ((a[1] == p) && (a[4] == p) && (a[7] == p)) ||
            ((a[2] == p) && (a[4] == p) && (a[6] == p)) ||
            ((a[2] == p) && (a[5] == p) && (a[8] == p)) ||
            ((a[3] == p) && (a[4] == p) && (a[5] == p)) ||
            ((a[6] == p) && (a[7] == p) && (a[8] == p)))
    {
        ended = true;
        return true;
    }
    return false;
}

bool pointIsInRect(SDL_Point p, SDL_Rect r)
{
    return p.x > r.x && p.x < r.x + r.w && p.y > r.y && p.y < r.y + r.h;
}

// Load a texture assertively
SDL_Texture* loadTexture(SDL_Renderer* renderer, const string& filename)
{
    auto tex = IMG_LoadTexture(renderer, filename.c_str());
    tictac_assert(tex, IMG_GetError());
    return tex;
}

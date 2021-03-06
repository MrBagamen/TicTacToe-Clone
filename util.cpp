#include "util.hpp"
#include "driver.hpp"

#include <iostream>
#include <SDL2/SDL_image.h>

using namespace std;

namespace util
{

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

}

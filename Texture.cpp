#include "Texture.hpp"

#include "driver.hpp"
#include "util.hpp"
#include <SDL2/SDL_image.h>

void Texture::loadFromFile(const std::string &filename)
{
    sdltex = IMG_LoadTexture(driver::renderer, filename.c_str());
    util::tictac_assert(sdltex, IMG_GetError());
}

Texture::~Texture()
{
    SDL_DestroyTexture(sdltex);
}

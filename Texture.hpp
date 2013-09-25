#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <SDL2/SDL.h>

class Texture
{
public:
    void loadFromFile(const std::string &filename);
    ~Texture();
    operator SDL_Texture *() const
    {
        return sdltex;
    }

private:
    SDL_Texture *sdltex;
};

#endif // TEXTURE_HPP

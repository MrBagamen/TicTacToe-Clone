#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>

#include "Texture.hpp"

class Sprite
{
public:
    Sprite(int x = 0, int y = 0);
    void draw() const;
    void move(int xOff, int yOff);
    SDL_Rect getRect() const;
    void setPosition(int x, int y);
    void setTexture(const Texture &texture);
private:
    const Texture *m_texture;
    SDL_Rect m_rect;
};

#endif // SPRITE_HPP

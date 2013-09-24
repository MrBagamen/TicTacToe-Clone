#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>

class Sprite
{
public:
    Sprite(SDL_Texture *texture, int x = 0, int y = 0);
    void draw(SDL_Renderer *renderer) const;
    void move(int xOff, int yOff);
    SDL_Rect getRect() const;
    void setPosition(int x, int y);
private:
    SDL_Texture *m_texture;
    SDL_Rect m_rect;
};

#endif // SPRITE_HPP

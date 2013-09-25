#include "Sprite.hpp"
#include "driver.hpp"

Sprite::Sprite(int x, int y)
{
    m_rect.x = x;
    m_rect.y = y;
}

void Sprite::draw() const
{
    SDL_RenderCopy(driver::renderer, *m_texture, nullptr, &m_rect);
}

void Sprite::move(int xOff, int yOff)
{
    m_rect.x += xOff;
    m_rect.y += yOff;
}

SDL_Rect Sprite::getRect() const
{
    return m_rect;
}

void Sprite::setPosition(int x, int y)
{
    m_rect.x = x;
    m_rect.y = y;
}

void Sprite::setTexture(const Texture &texture)
{
    m_texture = &texture;
    SDL_QueryTexture(*m_texture, nullptr, nullptr, &m_rect.w, &m_rect.h);
}

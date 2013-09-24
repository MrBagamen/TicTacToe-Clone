#ifndef MENU_HPP
#define MENU_HPP

#include "Sprite.hpp"

class Menu
{
public:
    Menu(SDL_Renderer *renderer);
    void update();
    void onEvent(SDL_Event &event);
private:
    SDL_Renderer *m_renderer;
    Sprite spr_menuBg;
    Sprite spr_playButton;
    Sprite spr_selectionArrow;
    Sprite spr_exitButton;
    int m_selectedItem;
};

#endif // MENU_HPP

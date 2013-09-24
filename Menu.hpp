#ifndef MENU_HPP
#define MENU_HPP

#include "Sprite.hpp"

class Menu
{
public:
    Menu();
    void update();
    void onEvent(SDL_Event &event);
private:
    Sprite spr_menuBg;
    Sprite spr_playButton;
    Sprite spr_selectionArrow;
    Sprite spr_exitButton;
    int m_selectedItem;
};

#endif // MENU_HPP

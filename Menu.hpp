#ifndef MENU_HPP
#define MENU_HPP

#include "Sprite.hpp"
#include "State.hpp"

class Menu : public State
{
public:
    Menu();
    virtual void onUpdate();
    virtual void onEvent(const SDL_Event &event);
private:
    Sprite spr_menuBg;
    Sprite spr_singleplayerButton;
    Sprite spr_netplayButton;
    Sprite spr_exitButton;
    Sprite spr_shine;
    int m_selectedItem;
};

#endif // MENU_HPP

#include "Menu.hpp"

#include "util.hpp"
#include "driver.hpp"

using namespace util;

Menu::Menu() :
    spr_menuBg(),
    spr_singleplayerButton(75, 150),
    spr_netplayButton(75, 220),
    spr_exitButton(75, 290),
    spr_shine(),
    m_selectedItem(-1)
{
    tex_menuBg.loadFromFile("res/bg_menu.png");
    tex_singlePlayerButton.loadFromFile("res/button_singleplayer.png");
    tex_netplayButton.loadFromFile("res/button_netplay.png");
    tex_exitButton.loadFromFile("res/button_exit.png");
    tex_shine.loadFromFile("res/shine.png");
    spr_menuBg.setTexture(tex_menuBg);
    spr_singleplayerButton.setTexture(tex_singlePlayerButton);
    spr_netplayButton.setTexture(tex_netplayButton);
    spr_exitButton.setTexture(tex_exitButton);
    spr_shine.setTexture(tex_shine);
}

void Menu::onUpdate()
{
    spr_menuBg.draw();
    spr_singleplayerButton.draw();
    spr_netplayButton.draw();
    spr_exitButton.draw();

    if (m_selectedItem == 0)
    {
        spr_shine.setPosition(75, 150);
    }
    else if (m_selectedItem == 1)
    {
        spr_shine.setPosition(75, 220);
    }
    else if (m_selectedItem == 2)
    {
        spr_shine.setPosition(75, 290);
    }
    else
    {
        return;
    }

    spr_shine.draw();
}

void Menu::onEvent(const SDL_Event &event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        if (pointIsInRect({event.button.x, event.button.y}, spr_singleplayerButton.getRect()))
        {
            driver::setState("game");
        }
        if (pointIsInRect({event.button.x, event.button.y}, spr_exitButton.getRect()))
        {
            driver::running = false;
        }
    }
    else if (event.type == SDL_MOUSEMOTION)
    {
        if (pointIsInRect({event.motion.x, event.motion.y}, spr_singleplayerButton.getRect()))
        {
            m_selectedItem = 0;
        }
        else if (pointIsInRect({event.motion.x, event.motion.y}, spr_netplayButton.getRect()))
        {
            m_selectedItem = 1;
        }
        else if (pointIsInRect({event.motion.x, event.motion.y}, spr_exitButton.getRect()))
        {
            m_selectedItem = 2;
        }
        else
        {
            m_selectedItem = -1;
        }
    }
}

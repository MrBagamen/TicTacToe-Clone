#include "Menu.hpp"

#include "util.hpp"
#include "driver.hpp"

using namespace util;

Menu::Menu() :
    spr_menuBg(loadTexture("res/bg_menu.bmp")),
    spr_playButton(loadTexture("res/button_play.bmp"), 75, 100),
    spr_shine(loadTexture("res/shine.png"), 65, 100),
    spr_exitButton(loadTexture("res/button_exit.bmp"), 75, 200),
    m_selectedItem(0)
{

}

void Menu::onUpdate()
{
    spr_menuBg.draw();
    spr_playButton.draw();
    spr_exitButton.draw();

    if (m_selectedItem == 0)
    {
        spr_shine.setPosition(75, 100);
    }
    else if (m_selectedItem == 1)
    {
        spr_shine.setPosition(75, 200);
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
        if (pointIsInRect({event.button.x, event.button.y}, spr_playButton.getRect()))
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
        if (pointIsInRect({event.motion.x, event.motion.y}, spr_playButton.getRect()))
        {
            m_selectedItem = 0;
        }
        else if (pointIsInRect({event.motion.x, event.motion.y}, spr_exitButton.getRect()))
        {
            m_selectedItem = 1;
        }
        else
        {
            m_selectedItem = -1;
        }
    }
}

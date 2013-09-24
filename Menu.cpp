#include "Menu.hpp"

#include "util.hpp"

Menu::Menu(SDL_Renderer *renderer) :
    m_renderer(renderer),
    spr_menuBg(loadTexture(m_renderer, "res/bg_menu.bmp")),
    spr_playButton(loadTexture(m_renderer, "res/button_play.bmp"), 75, 100),
    spr_selectionArrow(loadTexture(m_renderer, "res/selectionarrow.bmp"), 65, 100),
    spr_exitButton(loadTexture(m_renderer, "res/button_exit.bmp"), 75, 200),
    m_selectedItem(0)
{

}

void Menu::update()
{
    spr_menuBg.draw(m_renderer);
    spr_playButton.draw(m_renderer);
    spr_exitButton.draw(m_renderer);

    if (m_selectedItem == 0)
    {
        spr_selectionArrow.setPosition(65, 100);
    }
    else if (m_selectedItem == 1)
    {
        spr_selectionArrow.setPosition(65, 200);
    }
    else
    {
        return;
    }

    spr_selectionArrow.draw(m_renderer);
}

void Menu::onEvent(SDL_Event &event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        if (pointIsInRect({event.button.x, event.button.y}, spr_playButton.getRect()))
        {
            extern bool inMenu;
            inMenu = false;
        }
        if (pointIsInRect({event.button.x, event.button.y}, spr_exitButton.getRect()))
        {
            // TODO: quit
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

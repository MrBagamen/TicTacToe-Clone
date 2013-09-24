#include "Game.hpp"
#include "util.hpp"

#include "driver.hpp"

#include <cstring>
#include <iostream>

using namespace std;
using namespace util;

Game::Game() :
    spr_gameBg(loadTexture("res/bg_game.bmp")),
    tex_field_empty(loadTexture("res/field_empty.bmp")),
    tex_field_highlighted(loadTexture("res/field_highlighted.bmp")),
    tex_field_x(loadTexture("res/field_x.bmp")),
    tex_field_o(loadTexture("res/field_o.bmp"))
{
    memset(board, 0, 9);
    m_highlightedTile = -1;
}

void Game::onUpdate()
{
    const Uint8 *keyDown = SDL_GetKeyboardState(nullptr);

    if (keyDown[SDL_SCANCODE_ESCAPE])
    {
        driver::menu = true;
    }
    //Draw background
    spr_gameBg.draw();
    //Draw fields
    SDL_Rect rect {FIELD_START.x, FIELD_START.y, FIELD_SIZE.x, FIELD_SIZE.y};
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 0)
        {
            SDL_RenderCopy(driver::renderer, tex_field_empty, nullptr, &rect);

            if (m_highlightedTile == i)
                SDL_RenderCopy(driver::renderer, tex_field_highlighted, nullptr, &rect);
        }
        if (board[i] == 1)
        {
            SDL_RenderCopy(driver::renderer, tex_field_x, nullptr, &rect);
        }
        if (board[i] == 2)
        {
            SDL_RenderCopy(driver::renderer, tex_field_o, nullptr, &rect);
        }
        rect.x += FIELD_SIZE.x + FIELD_GAP.x;
        if (i == 2 || i == 5)
        {
            rect.y += rect.h + FIELD_GAP.y;
            rect.x = FIELD_START.x;
        }
    }
    //Check who won
    if (!ended)
    {
        if (checkWinrar(1))
        {
            cout << "Winrar is X\n";
        }
        else if (checkWinrar(2))
        {
            cout << "Winrar is O\n";
        }
    }
    if (keyDown[SDL_SCANCODE_R])
    {
        ended = false;
        memset(board, 0, 9);
        turn = 0;
        m_highlightedTile = -1;
    }
}

void Game::onEvent(const SDL_Event &event)
{
    if (ended)
        return;

    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        int index = tileIndexFromPoint({event.button.x, event.button.y});

        if (board[index] == 0)
        {
            if (turn == 0)
            {
                board[index] = 1;
                turn = 1;
            }
            else if (turn == 1)
            {
                board[index] = 2;
                turn = 0;
            }
        }
    }
    else if (event.type == SDL_MOUSEMOTION)
    {
        m_highlightedTile = tileIndexFromPoint({event.motion.x, event.motion.y});
    }
}

int Game::tileIndexFromPoint(SDL_Point p)
{
    SDL_Rect rect {FIELD_START.x, FIELD_START.y, FIELD_SIZE.x, FIELD_SIZE.y};

    for (int i = 0; i < 9; ++i)
    {

        if (pointIsInRect(p, rect))
            return i;

        rect.x += FIELD_SIZE.x + FIELD_GAP.x;

        if (i == 2 || i == 5)
        {
            rect.y += rect.h + FIELD_GAP.y;
            rect.x = FIELD_START.x;
        }
    }

    return -1;
}

bool Game::checkWinrar(int player)
{
    //1 = X, 2 = O
    if (((board[0] == player) && (board[1] == player) && (board[2] == player)) ||
            ((board[0] == player) && (board[4] == player) && (board[8] == player)) ||
            ((board[0] == player) && (board[3] == player) && (board[6] == player)) ||
            ((board[1] == player) && (board[4] == player) && (board[7] == player)) ||
            ((board[2] == player) && (board[4] == player) && (board[6] == player)) ||
            ((board[2] == player) && (board[5] == player) && (board[8] == player)) ||
            ((board[3] == player) && (board[4] == player) && (board[5] == player)) ||
            ((board[6] == player) && (board[7] == player) && (board[8] == player)))
    {
        ended = true;
        return true;
    }
    return false;
}

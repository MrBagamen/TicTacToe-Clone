#include "Sprite.hpp"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

namespace
{

void tictac_assert(bool expr, const string &message)
{
    if (!expr)
    {
        cerr << message << endl;
        exit(1);
    }
}

bool checkWinrar(char *a, int p, bool &ended)
{
    //1 = X, 2 = O
    if (((a[0] == p) && (a[1] == p) && (a[2] == p)) ||
            ((a[0] == p) && (a[4] == p) && (a[8] == p)) ||
            ((a[0] == p) && (a[3] == p) && (a[6] == p)) ||
            ((a[1] == p) && (a[4] == p) && (a[7] == p)) ||
            ((a[2] == p) && (a[4] == p) && (a[6] == p)) ||
            ((a[2] == p) && (a[5] == p) && (a[8] == p)) ||
            ((a[3] == p) && (a[4] == p) && (a[5] == p)) ||
            ((a[6] == p) && (a[7] == p) && (a[8] == p)))
    {
        ended = true;
        return true;
    }
    return false;
}

bool pointIsInRect(SDL_Point p, SDL_Rect r)
{
    return p.x > r.x && p.x < r.x + r.w && p.y > r.y && p.y < r.y + r.h;
}

// Load a texture assertively
SDL_Texture* loadTexture(SDL_Renderer* renderer, const string& filename)
{
    auto tex = IMG_LoadTexture(renderer, filename.c_str());
    tictac_assert(tex, IMG_GetError());
    return tex;
}

}

int main()
{
    SDL_Window *win = SDL_CreateWindow("TicTacToe - Press R to restart.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 400, SDL_WINDOW_SHOWN);
    tictac_assert(win, SDL_GetError());
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    tictac_assert(ren, SDL_GetError());
    const Uint8 *keyDown = SDL_GetKeyboardState(nullptr);
    tictac_assert(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG, IMG_GetError());

    int turn = 0;
    bool ended = false;
    bool menu = true;

    Sprite spr_menuBg(loadTexture(ren, "res/bg_menu.bmp"));
    Sprite spr_playButton(loadTexture(ren, "res/button_play.bmp"), 75, 100);
    Sprite spr_selectionArrow(loadTexture(ren, "res/selectionarrow.bmp"), 65, 100);
    Sprite spr_exitButton(loadTexture(ren, "res/button_exit.bmp"), 75, 200);
    Sprite spr_gameBg(loadTexture(ren, "res/bg_game.bmp"), 0, 3);

    SDL_Texture *efTexture = loadTexture(ren, "res/empty.bmp");
    SDL_Rect efData;
    SDL_QueryTexture(efTexture, nullptr, nullptr, &efData.w, &efData.h);
    efData.x = 0;
    efData.y = 13;

    SDL_Texture *moTexture = loadTexture(ren, "res/collision.bmp");
    SDL_Texture *xTexture = loadTexture(ren, "res/x.bmp");
    SDL_Texture *oTexture = loadTexture(ren, "res/o.bmp");

    char board[9];
    memset(board, 0, 9);

    bool is_running = true;
    while (is_running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                is_running = false;
                break;
            default:
                ;
            }
        }
        SDL_RenderClear(ren);

        if (!menu)
        {
            if (keyDown[SDL_SCANCODE_ESCAPE])
            {
                menu = true;
            }
            //Draw background
            spr_gameBg.draw(ren);
            //Draw fields
            for (int i = 0; i < 9; i++)
            {
                efData.x += 15;

                if (board[i] == 0)
                {
                    SDL_RenderCopy(ren, efTexture, nullptr, &efData);
                }
                if (!ended)
                {
                    if (pointIsInRect({event.motion.x, event.motion.y}, efData))
                    {
                        SDL_RenderCopy(ren, moTexture, nullptr, &efData);
                        if (event.button.button == SDL_BUTTON_LEFT)
                        {
                            if (board[i] == 0)
                            {
                                if (turn == 0)
                                {
                                    board[i] = 1;
                                    turn = 1;
                                }
                                else if (turn == 1)
                                {
                                    board[i] = 2;
                                    turn = 0;
                                }
                            }
                        }
                    }
                }
                if (board[i] == 1)
                {
                    SDL_RenderCopy(ren, xTexture, nullptr, &efData);
                }
                if (board[i] == 2)
                {
                    SDL_RenderCopy(ren, oTexture, nullptr, &efData);
                }
                efData.x += efData.w + 3;
                if (i == 2 || i == 5)
                {
                    efData.y += efData.h + 15;
                    efData.x = 0;
                }
            }
            efData.x = 0;
            efData.y = 13;
            //Check who won
            if (!ended)
            {
                if (checkWinrar(board, 1, ended))
                {
                    cout << "Winrar is X\n";
                }
                else if (checkWinrar(board, 2, ended))
                {
                    cout << "Winrar is O\n";
                }
            }
            if (keyDown[SDL_SCANCODE_R])
            {
                ended = false;
                memset(board, 0, 9);
                turn = 0;
            }
        }
        else
        {
            spr_menuBg.draw(ren);
            spr_playButton.draw(ren);
            spr_exitButton.draw(ren);

            if (pointIsInRect({event.motion.x, event.motion.y}, spr_playButton.getRect()))
            {
                spr_selectionArrow.draw(ren);
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    menu = false;
                }
            }
            if (pointIsInRect({event.motion.x, event.motion.y}, spr_exitButton.getRect()))
            {
                spr_selectionArrow.move(0, 100);
                spr_selectionArrow.draw(ren);
                spr_selectionArrow.move(0, -100);

                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    is_running = false;
                }
            }
        }

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    SDL_Quit();
}

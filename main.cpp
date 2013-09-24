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

bool checkWinrar(int *a, int p, bool &ended)
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

    Sprite mbgSprite(loadTexture(ren, "res/Menubg.bmp"));
    Sprite pbSprite(loadTexture(ren, "res/pb.bmp"), 75, 100);
    Sprite selSprite(loadTexture(ren, "res/selection.bmp"), 65, 100);
    Sprite ebSprite(loadTexture(ren, "res/eb.bmp"), 75, 200);
    Sprite bgSprite(loadTexture(ren, "res/bg.bmp"), 0, 3);

    SDL_Texture *efTexture = loadTexture(ren, "res/empty.bmp");
    SDL_Rect efData;
    SDL_QueryTexture(efTexture, nullptr, nullptr, &efData.w, &efData.h);
    efData.x = 0;
    efData.y = 13;

    SDL_Texture *moTexture = loadTexture(ren, "res/collision.bmp");
    SDL_Texture *xTexture = loadTexture(ren, "res/x.bmp");
    SDL_Texture *oTexture = loadTexture(ren, "res/o.bmp");

    //Test shit
    int fArray[9] = {   0, 0, 0,
                        0, 0, 0,
                        0, 0, 0
                    };

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
            bgSprite.draw(ren);
            //Draw fields
            for (int i = 0; i < 9; i++)
            {
                efData.x += 15;

                if (fArray[i] == 0)
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
                            if (fArray[i] == 0)
                            {
                                if (turn == 0)
                                {
                                    fArray[i] = 1;
                                    turn = 1;
                                }
                                else if (turn == 1)
                                {
                                    fArray[i] = 2;
                                    turn = 0;
                                }
                            }
                        }
                    }
                }
                if (fArray[i] == 1)
                {
                    SDL_RenderCopy(ren, xTexture, nullptr, &efData);
                }
                if (fArray[i] == 2)
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
                if (checkWinrar(fArray, 1, ended))
                {
                    cout << "Winrar is X\n";
                }
                else if (checkWinrar(fArray, 2, ended))
                {
                    cout << "Winrar is O\n";
                }
            }
            if (keyDown[SDL_SCANCODE_R])
            {
                ended = false;
                memset(fArray, 0, 9 * sizeof(int));
                turn = 0;
            }
        }
        else
        {
            mbgSprite.draw(ren);
            pbSprite.draw(ren);
            ebSprite.draw(ren);

            if (pointIsInRect({event.motion.x, event.motion.y}, pbSprite.getRect()))
            {
                selSprite.draw(ren);
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    menu = false;
                }
            }
            if (pointIsInRect({event.motion.x, event.motion.y}, ebSprite.getRect()))
            {
                selSprite.move(0, 100);
                selSprite.draw(ren);
                selSprite.move(0, -100);

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

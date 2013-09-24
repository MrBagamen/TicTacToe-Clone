#include <iostream>
#include <SDL2/SDL.h>

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

}

int main()
{
    SDL_Surface *img;
    SDL_Window *win = SDL_CreateWindow("TicTacToe - Press R to restart.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 400, SDL_WINDOW_SHOWN);
    tictac_assert(win, SDL_GetError());
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    tictac_assert(ren, SDL_GetError());
    const Uint8 *keyDown = SDL_GetKeyboardState(nullptr);

    int turn = 0;
    bool ended = false;
    bool menu = true;

    //Menu Background
    img = SDL_LoadBMP("res/Menubg.bmp");
    tictac_assert(img, SDL_GetError());
    SDL_Rect mbgData;
    mbgData.x = 0;
    mbgData.y = 0;
    mbgData.w = img->w;
    mbgData.h = img->h;
    SDL_Texture *mbgTexture = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);

    //Play Button
    img = SDL_LoadBMP("res/pb.bmp");
    tictac_assert(img, SDL_GetError());
    SDL_Rect pbData;
    pbData.x = 75;
    pbData.y = 100;
    pbData.w = img->w;
    pbData.h = img->h;
    SDL_Texture *pbTexture = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);

    //Selection arrow
    img = SDL_LoadBMP("res/selection.bmp");
    tictac_assert(img, SDL_GetError());
    SDL_Rect selData;
    selData.x = 65;
    selData.y = 100;
    selData.w = img->w;
    selData.h = img->h;
    SDL_Texture *selTexture = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);

    //Exit
    img = SDL_LoadBMP("res/eb.bmp");
    tictac_assert(img, SDL_GetError());
    SDL_Rect ebData;
    ebData.x = 75;
    ebData.y = 200;
    ebData.w = img->w;
    ebData.h = img->h;
    SDL_Texture *ebTexture = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);

    //Background
    img = SDL_LoadBMP("res/bg.bmp");
    tictac_assert(img, SDL_GetError());
    SDL_Rect bgData;
    bgData.x = 0;
    bgData.y = 3;
    bgData.w = img->w;
    bgData.h = img->h;
    SDL_Texture *bgTexture = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);

    //Empty Field
    img = SDL_LoadBMP("res/empty.bmp");
    tictac_assert(img, SDL_GetError());
    SDL_Rect efData;
    efData.x = 0;
    efData.y = 13;
    efData.w = img->w;
    efData.h = img->h;
    SDL_Texture *efTexture = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);

    //Mouseover Field
    img = SDL_LoadBMP("res/collision.bmp");
    tictac_assert(img, SDL_GetError());
    SDL_Texture *moTexture = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);

    //X Field
    img = SDL_LoadBMP("res/x.bmp");
    tictac_assert(img, SDL_GetError());
    SDL_Texture *xTexture = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);

    //O Field
    img = SDL_LoadBMP("res/o.bmp");
    tictac_assert(img, SDL_GetError());
    SDL_Texture *oTexture = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);

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
            SDL_RenderCopy(ren, bgTexture, nullptr, &bgData);
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
            //MENU BG
            SDL_RenderCopy(ren, mbgTexture, nullptr, &mbgData);

            //Play button
            SDL_RenderCopy(ren, pbTexture, nullptr, &pbData);

            //Exit button
            SDL_RenderCopy(ren, ebTexture, nullptr, &ebData);

            if (pointIsInRect({event.motion.x, event.motion.y}, pbData))
            {
                SDL_RenderCopy(ren, selTexture, nullptr, &selData);
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    menu = false;
                }
            }
            if (pointIsInRect({event.motion.x, event.motion.y}, ebData))
            {
                selData.y += 100;
                SDL_RenderCopy(ren, selTexture, nullptr, &selData);
                selData.y -= 100;
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

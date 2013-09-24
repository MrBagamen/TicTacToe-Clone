#ifndef GAME_HPP
#define GAME_HPP

#include "Sprite.hpp"

class Game
{
public:
    Game(SDL_Renderer *ren);
    void update();
    void onEvent(SDL_Event& event);
private:
    char board[9];
    int turn = 0;
    bool ended = false;

    SDL_Renderer *m_renderer;

    Sprite spr_gameBg;

    SDL_Texture *tex_field_empty;
    SDL_Texture *tex_field_highlighted;
    SDL_Texture *tex_field_x;
    SDL_Texture *tex_field_o;

    static constexpr SDL_Point FIELD_SIZE  = {85, 85};
    static constexpr SDL_Point FIELD_START = {15, 10};
    static constexpr SDL_Point FIELD_GAP   = {18, 15};
    int m_highlightedTile;

    int tileIndexFromPoint(SDL_Point p);
};

#endif // GAME_HPP

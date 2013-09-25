#ifndef GAME_HPP
#define GAME_HPP

#include "Sprite.hpp"
#include "State.hpp"
#include "Texture.hpp"

class Game : public State
{
public:
    Game();
    virtual void onUpdate();
    virtual void onEvent(const SDL_Event &event);
private:
    char board[9];
    int turn = 0;
    bool ended = false;

    Sprite spr_gameBg;

    Texture tex_gameBg;
    Texture tex_field_empty;
    Texture tex_field_highlighted;
    Texture tex_field_x;
    Texture tex_field_o;

    static constexpr SDL_Point FIELD_SIZE  = {85, 85};
    static constexpr SDL_Point FIELD_START = {15, 10};
    static constexpr SDL_Point FIELD_GAP   = {18, 15};
    int m_highlightedTile;

    static int tileIndexFromPoint(SDL_Point p);
    bool checkWinrar(int player);
};

#endif // GAME_HPP

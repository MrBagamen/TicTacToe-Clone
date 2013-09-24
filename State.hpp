#ifndef STATE_HPP
#define STATE_HPP

#include <SDL2/SDL.h>

class State
{
public:
    virtual void onEvent(const SDL_Event &/*event*/) {}
    virtual void onUpdate() {}
    virtual ~State() {}
};

#endif // STATE_HPP

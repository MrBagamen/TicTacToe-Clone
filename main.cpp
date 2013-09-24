#include "Sprite.hpp"
#include "util.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "driver.hpp"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

int main()
{
    driver::init();

    driver::addState("menu", new Menu);
    driver::addState("game", new Game);

    driver::setState("menu");

    while (driver::running)
        driver::update();

    driver::quit();
}

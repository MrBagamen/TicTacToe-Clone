#include "Game.hpp"
#include "Menu.hpp"
#include "driver.hpp"

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

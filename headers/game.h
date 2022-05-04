#ifndef GAME_H_
#define GAME_H_

#include <optional>
#include <SFML/Graphics.hpp>
#include <optional>
#include "menu.h"

namespace Tanks {

std::optional<Menu::ButtonType> startGame(sf::RenderWindow &window,
                                          int level = 1);

}

#endif  // GAME_H_

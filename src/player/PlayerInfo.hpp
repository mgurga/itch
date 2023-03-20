#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>

struct PlayerInfo {
    std::vector<std::string>& pressed;
    sf::Vector2i mouse_pos;
};
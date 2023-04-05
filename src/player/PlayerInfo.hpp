#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>

struct PlayerInfo {
    std::vector<std::string>& pressed;
    sf::Vector2i mouse_pos;
    bool mouse_down;

    static PlayerInfo get_empty_player_info() {
        std::vector<std::string> inputs;
        sf::Vector2i m(0, 0);
        PlayerInfo pi = {inputs, m, false};
        return pi;
    }
};
#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>

struct PlayerInfo {
    std::vector<std::string>& pressed;
    std::vector<std::string>& keys_down;
    sf::Vector2i mouse_pos;
    bool mouse_down;

    static PlayerInfo get_empty_player_info() {
        std::vector<std::string> inputs;
        std::vector<std::string> keys_down;
        sf::Vector2i m(0, 0);
        PlayerInfo pi = {inputs, keys_down, m, false};
        return pi;
    }
};
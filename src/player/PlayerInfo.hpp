#pragma once

#include <vector>
#include <string>

struct PlayerInfo {
    std::vector<std::string>& pressed;
    std::vector<std::string>& keys_down;
    int mouse_x;
    int mouse_y;
    bool mouse_down;

    static PlayerInfo get_empty_player_info() {
        std::vector<std::string> inputs;
        std::vector<std::string> keys_down;
        PlayerInfo pi = {inputs, keys_down, 0, 0, false};
        return pi;
    }
};
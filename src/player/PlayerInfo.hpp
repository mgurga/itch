#pragma once

#include <string>
#include <vector>

struct PlayerInfo {
    std::vector<std::string>& pressed;
    std::vector<std::string>& keys_down;
    int mouse_x;
    int mouse_y;
    bool mouse_down;
};

// creates an empty player info struct with the provided name
// workaround to support the MSVC compiler
#define EMPTY_PLAYER_INFO(VARNAME)      \
    std::vector<std::string> inputs;    \
    std::vector<std::string> keys_down; \
    int mouse_x = 0;                    \
    int mouse_y = 0;                    \
    PlayerInfo VARNAME = {inputs, keys_down, mouse_x, mouse_y, false};
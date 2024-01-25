#pragma once

#include <string>
#include <vector>

struct PlayerInfo {
    std::vector<std::string>& pressed;
    std::vector<std::string>& keys_down;
    std::vector<std::string>& clicked_sprites;
    std::vector<std::string>& hovered_sprites;
    int mouse_x;
    int mouse_y;
    bool mouse_down;
    bool mouse_pressed;
};

// creates an empty player info struct with the provided name
// workaround to support the MSVC compiler
#define EMPTY_PLAYER_INFO(VARNAME)            \
    std::vector<std::string> inputs;          \
    std::vector<std::string> keys_down;       \
    std::vector<std::string> clicked_sprites; \
    std::vector<std::string> hovered_sprites; \
    PlayerInfo VARNAME = {inputs, keys_down, clicked_sprites, hovered_sprites, 0, 0, false, false};

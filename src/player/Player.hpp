#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "../Project.hpp"
#include "PlayerInfo.hpp"

class Player {
public:
    Player(bool& running);
    ~Player() { delete window; }
    void draw();
    void paint(Project& project);
    PlayerInfo get_player_info() {
        return {pressed, keys_down, mouse_pos.x, mouse_pos.y, mouse_pressed};
    }

    bool& running;

private:
    void paint_sprite(ScratchSprite& sprite);
    void paint_monitor(ScratchMonitor& monitor);
    void paint_default_monitor(ScratchMonitor& monitor);
    void paint_large_monitor(ScratchMonitor& monitor);
    void paint_slider_monitor(ScratchMonitor& monitor);

    unsigned int ww, wh;

    sf::Font font;
    const unsigned MONITOR_FONT_SIZE = 11;
    std::vector<std::string> pressed;
    std::vector<std::string> keys_down;
    sf::Vector2i mouse_pos;
    bool mouse_pressed = false;
    sf::RenderWindow* window;
};
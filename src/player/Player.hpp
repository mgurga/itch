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
    PlayerInfo get_player_info();

    bool& running;

private:
    void paint_sprite(ScratchSprite& sprite);

    unsigned int ww, wh;

    std::vector<std::string> pressed;
    std::vector<std::string> keys_down;
    sf::Vector2i mouse_pos;
    bool mouse_pressed = false;
    sf::RenderWindow* window;
};
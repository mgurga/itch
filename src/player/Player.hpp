#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <iostream>
#include <vector>

#include "PlayerInfo.hpp"
#include "../Project.hpp"

class Player {
public:
    Player(bool& running);
    ~Player() {
        delete window;
    }
    void draw();
    void paint(Project& project);
    PlayerInfo get_player_info();

    bool& running;
private:
    std::vector<std::string> pressed;
    sf::Vector2i mouse_pos;
    sf::RenderWindow* window;
};
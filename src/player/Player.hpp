#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "../Project.hpp"

class Player {
public:
    Player(bool& running);
    ~Player() {
        delete window;
    }
    void draw();
    void paint(Project& project);

    std::vector<std::string> pressed;
    bool& running;
private:
    sf::RenderWindow* window;
};
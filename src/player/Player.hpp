#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <vector>

class Player {
public:
    Player(bool& running);
    ~Player() {
        delete window;
    }
    void draw();

    std::vector<std::string> pressed;
    bool& running;
private:
    sf::Window* window;
};
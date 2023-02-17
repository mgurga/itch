#include <SFML/Window.hpp>

class Player {
public:
    Player();
    void draw();

private:
    sf::Window* window;
};
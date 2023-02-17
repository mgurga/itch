#include "Player.hpp"

Player::Player() {
    sf::Window window(sf::VideoMode(800, 600), "Itch");
    this->window = &window;
}

void Player::draw() {
    if (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
    }
}
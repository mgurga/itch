#include "Player.hpp"

Player::Player(bool& r):
    running(r)
{
    window = new sf::Window(sf::VideoMode(514, 386), "Itch");
    window->setKeyRepeatEnabled(false);
}

void Player::draw() {
    if (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                running = false;
            }

            if (event.type == sf::Event::KeyPressed) {
                pressed.push_back("any");
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) pressed.push_back("right arrow");
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) pressed.push_back("left arrow");
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) pressed.push_back("up arrow");
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) pressed.push_back("down arrow");
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) pressed.push_back("space");
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    pressed.push_back(std::string(1, static_cast<char>(event.text.unicode)));
                }
            }
        }
    }
}
#include "Player.hpp"

Player::Player(bool& r):
    running(r)
{
    window = new sf::RenderWindow(sf::VideoMode(480, 360), "Itch");
    window->setKeyRepeatEnabled(false);
    // sf::View v = sf::View();
    // v.setCenter(float(window->getSize().x) / 2.0, float(window->getSize().y) / 2.0);
    // v.setSize(window->getSize().x, window->getSize().y);
    // window->setView(v);
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

            mouse_pos = sf::Mouse::getPosition(*window);
            mouse_pos.x -= 240;
            mouse_pos.y = -mouse_pos.y + 180;
        }
    }
}

void Player::paint(Project& project) {
    unsigned int ww = window->getSize().x; // window width
    unsigned int wh = window->getSize().y; // window height

    window->clear(sf::Color(255, 255, 255));

    sf::Sprite stagesprite;
    stagesprite.setTexture(project.stage.costumes[project.stage.currentCostume].texture);
    stagesprite.setPosition(0, 0);
    window->draw(stagesprite);

    for (ScratchSprite sprite : project.sprites) {
        if (sprite.visible) {
            sf::Sprite out;
            sf::Texture& st = sprite.costumes[sprite.currentCostume].texture;
            sf::Vector2u ss = st.getSize(); // sprite size

            // draw sprite
            out.setTexture(st, true);
            out.setPosition(float(sprite.x) + (ww / 2.0), float(-sprite.y) + (wh / 2.0));
            out.setOrigin(float(ss.x) / 2.0, float(ss.y) / 2.0);
            out.setRotation(sprite.direction - 90);
            window->draw(out);

            // draw dot at center the center of sprite
            // sf::CircleShape cs(3);
            // cs.setPosition(out.getPosition().x, out.getPosition().y);
            // cs.setFillColor(sf::Color(255, 0, 0));
            // window->draw(cs);
        }
    }

    window->display();
}

PlayerInfo Player::get_player_info() {
    return {pressed, mouse_pos};
}
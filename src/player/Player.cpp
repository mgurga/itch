#include "Player.hpp"

#include <math.h>

Player::Player(bool& r) : running(r) {
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

            // add to pressed vector (only reads held keys once)
            if (event.type == sf::Event::KeyPressed) {
                pressed.push_back(
                    "any");  // should be removed, just check if pressed vector is not empty
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    pressed.push_back("right arrow");
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

            // add to keys_down vector (held keys always in this vector)
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) keys_down.push_back("right arrow");
                if (event.key.code == sf::Keyboard::Left) keys_down.push_back("left arrow");
                if (event.key.code == sf::Keyboard::Up) keys_down.push_back("up arrow");
                if (event.key.code == sf::Keyboard::Down) keys_down.push_back("down arrow");
                if (event.key.code == sf::Keyboard::Space) keys_down.push_back("space");
                if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
                    char chr = static_cast<char>(event.key.code - sf::Keyboard::A + 'a');
                    keys_down.push_back(std::string(1, chr));
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                std::string toremove;

                if (event.key.code == sf::Keyboard::Right) toremove = "right arrow";
                if (event.key.code == sf::Keyboard::Left) toremove = "left arrow";
                if (event.key.code == sf::Keyboard::Up) toremove = "up arrow";
                if (event.key.code == sf::Keyboard::Down) toremove = "down arrow";
                if (event.key.code == sf::Keyboard::Space) toremove = "space";
                if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
                    char chr = static_cast<char>(event.key.code - sf::Keyboard::A + 'a');
                    toremove = std::string(1, chr);
                }

                if (!toremove.empty())
                    keys_down.erase(std::remove(keys_down.begin(), keys_down.end(), toremove),
                                    keys_down.end());
            }

            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left && mouse_pressed != true)
                    mouse_pressed = true;

            if (event.type == sf::Event::MouseButtonReleased)
                if (event.mouseButton.button == sf::Mouse::Left) mouse_pressed = false;

            mouse_pos = sf::Mouse::getPosition(*window);
            mouse_pos.x -= 240;
            mouse_pos.y = -mouse_pos.y + 180;
        }
    }
}

void Player::paint(Project& project) {
    ww = window->getSize().x;  // window width
    wh = window->getSize().y;  // window height
    window->clear(sf::Color(255, 255, 255));

    sf::Sprite stagesprite;
    stagesprite.setTexture(project.stage.costumes[project.stage.currentCostume()].texture);
    stagesprite.setPosition(0, 0);
    window->draw(stagesprite);

    for (ScratchSprite sprite : project.clones) { paint_sprite(sprite); }
    for (ScratchSprite sprite : project.sprites) { paint_sprite(sprite); }

    window->display();
}

void Player::paint_sprite(ScratchSprite& sprite) {
    if (sprite.get_visible() && sprite.effects()["GHOST"] != 100.0) {
        sf::Sprite out;
        sf::Texture& st = sprite.costumes[sprite.currentCostume()].texture;
        // sf::Vector2u ss = st.getSize(); // sprite size

        // draw sprite
        out.setTexture(st, true);
        out.setPosition(float(sprite.get_x()) + (ww / 2.0), float(-sprite.get_y()) + (wh / 2.0));
        out.setOrigin(sprite.costumes[sprite.currentCostume()].rotationCenterX,
                      sprite.costumes[sprite.currentCostume()].rotationCenterY);
        out.setRotation(sprite.get_direction() - 90.0f);

        double ghost = sprite.effects()["GHOST"];
        if (ghost < 0) ghost = 0;
        out.setColor(sf::Color(255, 255, 255, floor(abs(100 - ghost)) * 2.55));
        out.setScale(static_cast<float>(sprite.get_size()) / 100,
                     static_cast<float>(sprite.get_size()) / 100);
        out.setScale(out.getScale().x / sprite.costumes[sprite.currentCostume()].bitmapResolution,
                     out.getScale().y / sprite.costumes[sprite.currentCostume()].bitmapResolution);
        window->draw(out);

        // draw dot at center the center of sprite
        // sf::CircleShape cs(3);
        // cs.setPosition(out.getPosition().x, out.getPosition().y);
        // cs.setFillColor(sf::Color(255, 0, 0));
        // window->draw(cs);
    }
}

PlayerInfo Player::get_player_info() {
    return {pressed, keys_down, mouse_pos.x, mouse_pos.y, mouse_pressed};
}
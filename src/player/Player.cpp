#include "Player.hpp"

Player::Player(bool& r) : running(r) {
    window = new sf::RenderWindow(sf::VideoMode(480, 360), "Itch",
                                  sf::Style::Titlebar | sf::Style::Close);
    window->setKeyRepeatEnabled(false);
    // sf::View v = sf::View();
    // v.setCenter(float(window->getSize().x) / 2.0, float(window->getSize().y) / 2.0);
    // v.setSize(window->getSize().x, window->getSize().y);
    // window->setView(v);
    if (!font.loadFromFile("NotoSans-Regular.ttf")) {
        std::cout << "font not found" << std::endl;
        exit(1);
    }
    pen_layer.create(480, 360, sf::Color(255, 255, 255, 0));
}

sf::Vector2i Player::get_raw_mouse_pos() {
    // ensures mouse position is always 0 <= x <= 480 and 0 <= y <= 360
    sf::Vector2i mp = sf::Mouse::getPosition(*window);
    mp.x /= scale;
    mp.y /= scale;
    return mp;
}

void Player::set_scale(float s) {
    window->setSize(sf::Vector2u(480 * s, 360 * s));
    scale = s;
}

void Player::draw() {
    if (window->isOpen()) {
        sf::Event event;
        mouse_pressed = false;
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

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && mouse_down != true)
                    mouse_down = true;
                mouse_pressed = true;
            }

            if (event.type == sf::Event::MouseButtonReleased)
                if (event.mouseButton.button == sf::Mouse::Left) mouse_down = false;

            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
                    set_scale(scale + 0.5);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen))
                    if (scale > 1) set_scale(scale - 0.5);
            }
            // results in window flickering and not preserving aspect ratio
            if (event.type == sf::Event::Resized) {
                int new_width = event.size.width;

                float new_scale = floor((new_width / 480.0) * 100 + 0.5) / 100;
                set_scale(new_scale);
            }

            mouse_pos = get_raw_mouse_pos();
            mouse_pos.x -= ww / 2.0;
            mouse_pos.y = -mouse_pos.y + (wh / 2.0);
        }
    }
}

void Player::paint(DrawOrderList& draw_orders) {
    ww = 480;  // window width
    wh = 360;  // window height
    window->clear(sf::Color(255, 255, 255));

    clicked_sprites.clear();
    hovered_sprites.clear();

    paint_stage(
        *window,
        dynamic_cast<StageDrawOrder*>(draw_orders.get_draw_order_list().at(0).get())->get_stage());

    sf::Texture pentex;
    pentex.loadFromImage(pen_layer);
    sf::Sprite penspr;
    penspr.setPosition(0, 0);
    penspr.setTexture(pentex, true);
    window->draw(penspr);

    for (std::unique_ptr<DrawOrder>& dw : draw_orders.get_draw_order_list()) {
        switch (dw->get_type()) {
        case DrawOrder::DrawObject::NONE: break;
        case DrawOrder::DrawObject::SPRITE:
            paint_sprite(*window, dynamic_cast<SpriteDrawOrder*>(dw.get())->get_sprite());
            break;
        case DrawOrder::DrawObject::MONITOR:
            paint_monitor(dynamic_cast<MonitorDrawOrder*>(dw.get())->get_monitor());
            break;
        case DrawOrder::DrawObject::PEN_LINE:
            paint_pen_line(*dynamic_cast<PenDrawOrder*>(dw.get()));
            break;
        case DrawOrder::DrawObject::PEN_CLEAR:
            pen_layer.create(480, 360, sf::Color(255, 255, 255, 0));
            break;
        case DrawOrder::DrawObject::PEN_STAMP:
            paint_pen_stamp(*dynamic_cast<StampDrawOrder*>(dw.get()));
            break;
        }
    }

    window->display();
}

void Player::paint_pen_stamp(StampDrawOrder& dw) {
    sf::RenderTexture rt;
    rt.create(pen_layer.getSize().x, pen_layer.getSize().y);

    sf::Sprite bg;
    sf::Texture bgtex;
    auto plf = pen_layer;
    plf.flipVertically();
    bgtex.loadFromImage(plf);
    bgtex.setSmooth(false);
    bg.setTexture(bgtex);
    bg.setPosition(0, 0);
    rt.draw(bg);

    sf::Sprite ss;
    sf::Texture sstex;
    auto ssimg = dw.get_sprite().costume().get_image_resource().get_texture().copyToImage();
    ssimg.flipVertically();
    sstex.loadFromImage(ssimg);
    sstex.setSmooth(true);
    ss.setTexture(sstex);
    ss.setPosition(float(dw.get_x()) + (ww / 2.0), float(dw.get_y()) + (wh / 2.0));
    ss.setOrigin(dw.get_sprite().costume().get_rot_center_x(),
                 dw.get_sprite().costume().get_rot_center_y());
    ss.setRotation(360.0f - (dw.get_sprite().get_direction() - 90.0f));
    rt.draw(ss);

    rt.display();

    auto rtimg = rt.getTexture().copyToImage();
    rtimg.flipVertically();
    pen_layer = rtimg;
}

void Player::paint_pen_line(PenDrawOrder& dw) {
    dw.set_x(dw.get_x() + (ww / 2.0));
    dw.set_y(-dw.get_y() + (wh / 2.0));
    dw.set_x2(dw.get_x2() + (ww / 2.0));
    dw.set_y2(-dw.get_y2() + (wh / 2.0));

    if (dw.get_x() == dw.get_x2() && dw.get_y() == dw.get_y2()) {
        auto s = dw.get_pen_settings();
        paint_pen_point(dw.get_x(), dw.get_y(), s);
        return;
    }

    double xdiff = dw.get_x2() - dw.get_x();
    double ydiff = dw.get_y2() - dw.get_y();

    double steps = std::max(std::abs(xdiff), std::abs(ydiff));

    double xinc = xdiff / steps;
    double yinc = ydiff / steps;
    double penx = dw.get_x();
    double peny = dw.get_y();

    auto s = dw.get_pen_settings();
    for (int i = 0; i < steps; i++) {
        penx += xinc;
        peny += yinc;
        paint_pen_point(penx, peny, s);
    }
}

void Player::paint_pen_point(double x, double y, EngineFunctions::PenSettings& s) {
    sf::Color c = sf::Color(static_cast<int>(s.pen_rgb.r), static_cast<int>(s.pen_rgb.g),
                            static_cast<int>(s.pen_rgb.b));

    if (s.pen_size == 1) {
        pen_layer.setPixel(x, y, c);
        return;
    }

    double radius = s.pen_size / 2.0;
    double radius_sqr = radius * radius;
    for (int cx = -radius; cx < radius; cx++) {
        int hh = (int)std::sqrt(radius_sqr - cx * cx);
        int rx = x + cx;
        int ph = y + hh;

        for (int cy = y - hh; cy < ph; cy++) {
            if (rx <= 0 || rx >= ww) continue;
            if (cy <= 0 || cy >= wh) continue;
            pen_layer.setPixel(rx, cy, c);
        }
    }
}

void Player::paint_stage(sf::RenderTarget& rt, ScratchStage& stage) {
    sf::Sprite out;
    sf::Texture& st = stage.costume().get_image_resource().get_texture();

    out.setTexture(st, true);
    out.setPosition(stage.get_x(), stage.get_y());

    // apply effects
    double ghost = stage.get_effect("GHOST");
    if (ghost < 0) ghost = 0;
    out.setColor(sf::Color(255, 255, 255, floor(std::abs(100 - ghost)) * 2.55));

    // apply size
    out.setScale(static_cast<float>(stage.get_size()) / 100,
                 static_cast<float>(stage.get_size()) / 100);
    out.setScale(out.getScale().x / stage.costume().get_bitmap_res(),
                 out.getScale().y / stage.costume().get_bitmap_res());

    rt.draw(out);
}

void Player::paint_sprite(sf::RenderTarget& rt, ScratchSprite& sprite) {
    if (sprite.get_visible() && sprite.get_effect("GHOST") != 100.0) {
        sf::Sprite out;
        sf::Texture& st = sprite.costume().get_image_resource().get_texture();
        // sf::Vector2u ss = st.getSize(); // sprite size

        // draw sprite
        out.setTexture(st, true);
        out.setPosition(float(sprite.get_x()) + (ww / 2.0), float(-sprite.get_y()) + (wh / 2.0));
        out.setOrigin(sprite.costume().get_rot_center_x(), sprite.costume().get_rot_center_y());
        out.setRotation(sprite.get_direction() - 90.0f);

        // check if mouse is over a sprite and if clicked
        sf::Vector2i mousevec = get_raw_mouse_pos();
        if (out.getGlobalBounds().contains(mousevec.x, mousevec.y))
            hovered_sprites.push_back(sprite.get_name());
        if (out.getGlobalBounds().contains(mousevec.x, mousevec.y) && mouse_pressed)
            clicked_sprites.push_back(sprite.get_name());

        // apply effects
        double ghost = sprite.get_effect("GHOST");
        if (ghost < 0) ghost = 0;
        out.setColor(sf::Color(255, 255, 255, floor(std::abs(100 - ghost)) * 2.55));

        // apply size
        out.setScale(static_cast<float>(sprite.get_size()) / 100,
                     static_cast<float>(sprite.get_size()) / 100);
        out.setScale(out.getScale().x / sprite.costume().get_bitmap_res(),
                     out.getScale().y / sprite.costume().get_bitmap_res());
        rt.draw(out);

        // draw dot at center the center of sprite
        // sf::CircleShape cs(3);
        // cs.setPosition(sprite.get_x(), sprite.get_y());
        // cs.setFillColor(sf::Color(255, 0, 0));
        // window->draw(cs);
    }
}

void Player::paint_monitor(ScratchMonitor& monitor) {
    if (!monitor.visible) return;
    switch (monitor.mode) {
    case MonitorMode::DEFAULT: paint_default_monitor(monitor); return;
    case MonitorMode::LARGE: paint_large_monitor(monitor); return;
    case MonitorMode::SLIDER: paint_slider_monitor(monitor); return;
    case MonitorMode::LIST: paint_list_monitor(monitor); return;
    default: return;
    }
}

void Player::paint_default_monitor(ScratchMonitor& monitor) {
    float monitor_width = 8;
    sf::Text display_name_text;
    display_name_text.setString(monitor.display_name);
    display_name_text.setFont(font);
    display_name_text.setCharacterSize(MONITOR_FONT_SIZE);
    display_name_text.setFillColor(sf::Color::Black);
    display_name_text.setOutlineThickness(0.3);
    display_name_text.setPosition(monitor.x + monitor_width, monitor.y + 3);
    monitor_width += display_name_text.getGlobalBounds().width;
    monitor_width += 10;

    sf::Text value_text;
    value_text.setString(monitor.values.at(0).get_string());
    value_text.setFont(font);
    value_text.setCharacterSize(MONITOR_FONT_SIZE);
    value_text.setFillColor(sf::Color::White);
    value_text.setOutlineColor(sf::Color::White);
    value_text.setOutlineThickness(0.2);
    value_text.setPosition(monitor.x + monitor_width +
                               (std::max(40.0f, value_text.getGlobalBounds().width) / 2) -
                               (value_text.getGlobalBounds().width / 2),
                           monitor.y + 3.5);
    monitor_width += std::max(40.0f, value_text.getGlobalBounds().width);
    monitor_width += 10;

    sf::RectangleShape background;
    background.setSize({monitor_width, 20.0});
    background.setPosition({static_cast<float>(monitor.x), static_cast<float>(monitor.y)});
    background.setFillColor(sf::Color(220, 220, 220));

    sf::RectangleShape value_background;
    value_background.setSize({std::max(40.0f, value_text.getGlobalBounds().width), 14.0});
    value_background.setPosition(
        {monitor.x + monitor_width - (std::max(40.0f, value_text.getGlobalBounds().width) + 10),
         monitor.y + 3.0f});
    if (monitor.opcode.substr(0, 5) == "data_")
        value_background.setFillColor(sf::Color(255, 140, 26));
    else if (monitor.opcode.substr(0, 8) == "sensing_")
        value_background.setFillColor(sf::Color(92, 177, 214));
    else if (monitor.opcode.substr(0, 7) == "motion_")
        value_background.setFillColor(sf::Color(76, 151, 255));
    else if (monitor.opcode.substr(0, 6) == "looks_")
        value_background.setFillColor(sf::Color(153, 102, 255));
    else if (monitor.opcode.substr(0, 6) == "sound_")
        value_background.setFillColor(sf::Color(207, 99, 207));
    else
        value_background.setFillColor(sf::Color::Red);

    window->draw(background);
    window->draw(value_background);
    window->draw(display_name_text);
    window->draw(value_text);
}

void Player::paint_large_monitor(ScratchMonitor& monitor) {
    sf::Text value_text;
    value_text.setString(monitor.values.at(0).get_string());
    value_text.setFont(font);
    value_text.setCharacterSize(MONITOR_FONT_SIZE + 2);
    value_text.setFillColor(sf::Color::White);
    value_text.setOutlineColor(sf::Color::White);
    value_text.setOutlineThickness(0.2);
    value_text.setPosition(monitor.x + (std::max(40.0f, value_text.getGlobalBounds().width) / 2) -
                               (value_text.getGlobalBounds().width / 2),
                           monitor.y + 1);

    sf::RectangleShape value_background;
    value_background.setSize({std::max(40.0f, value_text.getGlobalBounds().width), 20.0});
    value_background.setPosition({static_cast<float>(monitor.x), static_cast<float>(monitor.y)});
    if (monitor.opcode.substr(0, 5) == "data_")
        value_background.setFillColor(sf::Color(255, 140, 26));
    else if (monitor.opcode.substr(0, 8) == "sensing_")
        value_background.setFillColor(sf::Color(92, 177, 214));
    else if (monitor.opcode.substr(0, 7) == "motion_")
        value_background.setFillColor(sf::Color(76, 151, 255));
    else if (monitor.opcode.substr(0, 6) == "looks_")
        value_background.setFillColor(sf::Color(153, 102, 255));
    else if (monitor.opcode.substr(0, 6) == "sound_")
        value_background.setFillColor(sf::Color(207, 99, 207));
    else
        value_background.setFillColor(sf::Color::Red);

    window->draw(value_background);
    window->draw(value_text);
}

void Player::paint_slider_monitor(ScratchMonitor& monitor) {
    float monitor_width = 8;
    sf::Text display_name_text;
    display_name_text.setString(monitor.display_name);
    display_name_text.setFont(font);
    display_name_text.setCharacterSize(MONITOR_FONT_SIZE);
    display_name_text.setFillColor(sf::Color::Black);
    display_name_text.setOutlineThickness(0.3);
    display_name_text.setPosition(monitor.x + monitor_width, monitor.y + 3);
    monitor_width += display_name_text.getGlobalBounds().width;
    monitor_width += 10;

    sf::Text value_text;
    value_text.setString(monitor.values.at(0).get_string());
    value_text.setFont(font);
    value_text.setCharacterSize(MONITOR_FONT_SIZE);
    value_text.setFillColor(sf::Color::White);
    value_text.setOutlineColor(sf::Color::White);
    value_text.setOutlineThickness(0.2);
    value_text.setPosition(monitor.x + monitor_width +
                               (std::max(40.0f, value_text.getGlobalBounds().width) / 2) -
                               (value_text.getGlobalBounds().width / 2),
                           monitor.y + 3.5);
    monitor_width += std::max(40.0f, value_text.getGlobalBounds().width);
    monitor_width += 10;

    sf::RectangleShape background;
    background.setSize({monitor_width, 40.0});
    background.setPosition({static_cast<float>(monitor.x), static_cast<float>(monitor.y)});
    background.setFillColor(sf::Color(220, 220, 220));

    sf::RectangleShape value_background;
    value_background.setSize({std::max(40.0f, value_text.getGlobalBounds().width), 14.0});
    value_background.setPosition(
        {monitor.x + monitor_width - (std::max(40.0f, value_text.getGlobalBounds().width) + 10),
         monitor.y + 3.0f});
    if (monitor.opcode.substr(0, 5) == "data_")
        value_background.setFillColor(sf::Color(255, 140, 26));
    else if (monitor.opcode.substr(0, 8) == "sensing_")
        value_background.setFillColor(sf::Color(92, 177, 214));
    else if (monitor.opcode.substr(0, 7) == "motion_")
        value_background.setFillColor(sf::Color(76, 151, 255));
    else if (monitor.opcode.substr(0, 6) == "looks_")
        value_background.setFillColor(sf::Color(153, 102, 255));
    else if (monitor.opcode.substr(0, 6) == "sound_")
        value_background.setFillColor(sf::Color(207, 99, 207));
    else
        value_background.setFillColor(sf::Color::Red);

    sf::RectangleShape slider_background;
    slider_background.setSize({monitor_width - 20, 5});
    slider_background.setPosition({monitor.x + 10.0f, monitor.y + 25.0f});
    slider_background.setFillColor(sf::Color(229, 229, 229));

    sf::RectangleShape slider_handle;
    float handle_x = 0;
    handle_x += (monitor.values.at(0).get_number() * (monitor_width - 20)) /
                (monitor.sliderMax - monitor.sliderMin);
    handle_x = std::max(0.0f, handle_x);
    handle_x = std::min(handle_x, (monitor_width - 20));
    slider_handle.setSize({10.0f, 10.0f});
    slider_handle.setPosition({monitor.x + 5.0f + handle_x, monitor.y + 22.5f});
    slider_handle.setFillColor(sf::Color(0, 92, 200));

    sf::RectangleShape slider_progress_background;
    slider_progress_background.setSize({handle_x, 5});
    slider_progress_background.setPosition({monitor.x + 10.0f, monitor.y + 25.0f});
    slider_progress_background.setFillColor(sf::Color(0, 92, 200));

    window->draw(background);
    window->draw(value_background);
    window->draw(display_name_text);
    window->draw(value_text);
    window->draw(slider_background);
    window->draw(slider_progress_background);
    window->draw(slider_handle);
}

void Player::paint_list_monitor(ScratchMonitor& monitor) {
    sf::RectangleShape background;
    background.setPosition({static_cast<float>(monitor.x), static_cast<float>(monitor.y)});
    background.setSize({static_cast<float>(monitor.width), static_cast<float>(monitor.height)});
    background.setFillColor(sf::Color(220, 220, 220));

    sf::RectangleShape list_name_background;
    list_name_background.setPosition(
        {static_cast<float>(monitor.x) + 1, static_cast<float>(monitor.y) + 1});
    list_name_background.setSize({static_cast<float>(monitor.width) - 2, 20.0f});
    list_name_background.setFillColor(sf::Color::White);

    sf::Text list_name_text;
    list_name_text.setString(monitor.display_name);
    list_name_text.setFont(font);
    list_name_text.setCharacterSize(MONITOR_FONT_SIZE);
    list_name_text.setFillColor(sf::Color::Black);
    list_name_text.setOutlineThickness(0.3);
    list_name_text.setPosition(
        monitor.x + (monitor.width / 2.0f) - (list_name_text.getGlobalBounds().width / 2.0f),
        monitor.y + 4);

    window->draw(background);
    window->draw(list_name_background);
    window->draw(list_name_text);

    float item_y = 3;
    int index = 1;
    for (std::string s : monitor.values) {
        if (item_y > monitor.height - 40) break;

        sf::RectangleShape item_background;
        item_background.setFillColor(sf::Color(252, 102, 44));
        item_background.setPosition(monitor.x + 20.0f, monitor.y + 20 + item_y);
        item_background.setSize({monitor.width - 23.0f, 20});

        sf::Text item_text;
        item_text.setString(s);
        item_text.setFont(font);
        item_text.setCharacterSize(MONITOR_FONT_SIZE + 2);
        item_text.setFillColor(sf::Color::White);
        item_text.setOutlineColor(sf::Color::White);
        item_text.setOutlineThickness(0.2);
        item_text.setPosition(monitor.x + 25.0f, monitor.y + 22 + item_y);

        sf::Text item_index_text;
        item_index_text.setString(std::to_string(index));
        item_index_text.setFont(font);
        item_index_text.setCharacterSize(MONITOR_FONT_SIZE + 2);
        item_index_text.setFillColor(sf::Color::Black);
        item_index_text.setOutlineColor(sf::Color::Black);
        item_index_text.setOutlineThickness(0.2);
        item_index_text.setPosition(
            monitor.x + 8.0f - (item_index_text.getGlobalBounds().width / 2.0f),
            monitor.y + 22 + item_y);

        index++;
        item_y += 22;
        window->draw(item_background);
        window->draw(item_index_text);
        window->draw(item_text);
    }

    sf::RectangleShape list_length_background;
    list_length_background.setPosition({static_cast<float>(monitor.x) + 1,
                                        static_cast<float>(monitor.y) + monitor.height - 21.0f});
    list_length_background.setSize({static_cast<float>(monitor.width) - 2, 20.0f});
    list_length_background.setFillColor(sf::Color::White);

    sf::Text list_length_text;
    list_length_text.setString("length " + std::to_string(monitor.values.size()));
    list_length_text.setFont(font);
    list_length_text.setCharacterSize(MONITOR_FONT_SIZE);
    list_length_text.setFillColor(sf::Color::Black);
    list_length_text.setOutlineThickness(0.3);
    list_length_text.setPosition(
        monitor.x + (monitor.width / 2.0f) - (list_length_text.getGlobalBounds().width / 2.0f),
        monitor.y + monitor.height - 18.0f);

    window->draw(list_length_background);
    window->draw(list_length_text);
}
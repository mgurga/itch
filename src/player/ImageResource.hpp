#pragma once

#include <SFML/Graphics.hpp>

class ImageResource {
public:
    ImageResource() { tex.setSmooth(true); };

    void load_from_rgba_data(uint8_t* data, int width, int height) {
        sf::Image img;
        img.create(width, height, data);
        tex.loadFromImage(img);
    }
    void load_from_file(std::filesystem::path tempdir) { tex.loadFromFile(tempdir.string()); }

    sf::Texture& get_texture() { return tex; }

private:
    sf::Texture tex;
};
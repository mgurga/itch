#pragma once

#include <SFML/Audio.hpp>
#include <filesystem>

class SoundResource {
public:
    SoundResource() {}

    void load_from_file(std::filesystem::path tempdir) {
        if (!sound.loadFromFile(tempdir.string()))
            std::cout << "could not load sound file: " << tempdir << std::endl;
    }

    sf::SoundBuffer& get_sound() { return sound; };
    float get_length() { return sound.getDuration().asSeconds(); }

private:
    sf::SoundBuffer sound;
};
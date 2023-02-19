#pragma once

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <SFML/Audio.hpp>

#include "ScratchAsset.hpp"

using json = nlohmann::json;

class ScratchSound : ScratchAsset {
public:
    ScratchSound(json ss);
    void load_sound(std::string tempdir);

    double rate;
    double sampleCount;

    sf::SoundBuffer sound;
};
#pragma once

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include "ScratchAsset.hpp"

using json = nlohmann::json;

class ScratchCostume : ScratchAsset {
public:
    ScratchCostume(json sc);
    void load_image(std::string tempdir);

    int bitmapResolution;
    float rotationCenterX;
    float rotationCenterY;

    sf::Texture texture;
};
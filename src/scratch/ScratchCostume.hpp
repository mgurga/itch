#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include "ScratchAsset.hpp"

using json = nlohmann::json;

class ScratchCostume : public ScratchAsset {
public:
    ScratchCostume(json sc);
    void load_image(std::filesystem::path tempdir);

    int bitmapResolution;
    float rotationCenterX;
    float rotationCenterY;

    sf::Texture texture;
};
#pragma once

#include <lunasvg.h>

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "ScratchAsset.hpp"

using namespace lunasvg;
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
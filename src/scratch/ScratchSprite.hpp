#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "ScratchStage.hpp"
#include "ScratchTarget.hpp"

enum RotationStyle { ALL_AROUND, LEFT_RIGHT, DONT_ROTATE };

class ScratchSprite : public ScratchTarget {
public:
    ScratchSprite(json ss, std::filesystem::path temp_dir, bool heavyload = true);
    ScratchSprite(ScratchStage& st);

    bool visible;
    double x, y, size, direction;
    bool draggable;
    RotationStyle rotationStyle;
    std::unordered_map<std::string, double> effects = {
        {"COLOR", 0},  {"FISHEYE", 0},    {"WHIRL", 0}, {"PIXELATE", 0},
        {"MOSAIC", 0}, {"BRIGHTNESS", 0}, {"GHOST", 0}};
};
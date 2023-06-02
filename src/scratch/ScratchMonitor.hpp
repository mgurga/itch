#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

enum MonitorMode { DEFAULT, LARGE, SLIDER, LIST };

class ScratchMonitor {
public:
    ScratchMonitor(json sm);

    std::string id;
    MonitorMode mode;
    std::string opcode;
    std::string variable;
    std::string spriteName;
    int height, width;
    int x, y;
    bool visible;

    std::string display_name;
    std::string value;

    // monitors that are NOT lists have these variables
    int sliderMin, sliderMax;
    bool isDiscrete;
};
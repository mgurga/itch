#pragma once

#include <string>
#include <iostream>
#include <stdlib.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum MonitorMode {
    DEFAULT,
    LARGE,
    SLIDER,
    LIST
};

class ScratchMonitor {
public:
    ScratchMonitor(json sm);

    std::string id;
    MonitorMode mode;
    std::string opcode;
    std::string variable;
    std::string spriteName;
    std::string value;
    int height, width;
    int x, y;
    bool visible;

    // monitors that are NOT lists have these variables
    int sliderMin, sliderMax;
    bool isDiscrete;
};
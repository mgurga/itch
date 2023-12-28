#pragma once

#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../engine/Value.hpp"

using json = nlohmann::json;

enum class MonitorMode { DEFAULT, LARGE, SLIDER, LIST };

class ScratchMonitor {
public:
    ScratchMonitor(json sm);

    std::string id;
    MonitorMode mode;
    std::string opcode;
    std::string spriteName;
    int height, width;
    int x, y;
    bool visible;
    std::map<std::string, std::string> params;

    std::string display_name;
    std::vector<Value> values;

    // monitors that are NOT lists have these variables
    int sliderMin, sliderMax;
    bool isDiscrete;
};
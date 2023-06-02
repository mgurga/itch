#include "ScratchMonitor.hpp"

ScratchMonitor::ScratchMonitor(json sm) :
    id(sm["id"]),
    opcode(sm["opcode"]),
    spriteName(sm["spriteName"].is_null() ? "" : sm["spriteName"]),
    value(sm["value"].dump()),
    width(sm["width"]),
    height(sm["height"]),
    x(sm["x"]),
    y(sm["y"]),
    visible(sm["visible"]) {
    if (sm["mode"] == "default") {
        mode = DEFAULT;
    } else if (sm["mode"] == "large") {
        mode = LARGE;
    } else if (sm["mode"] == "slider") {
        mode = SLIDER;
    } else if (sm["mode"] == "list") {
        mode = LIST;
    } else {
        mode = DEFAULT;
    }

    if (sm["params"].empty()) {
        variable = "";
    } else if (!sm["params"]["VARIABLE"].is_null()) {
        variable = sm["params"]["VARIABLE"];
    } else if (!sm["params"]["LIST"].is_null()) {
        variable = sm["params"]["LIST"];
    } else {
        variable = "";
    }

    if (mode != LIST) {
        sliderMin = sm["sliderMin"];
        sliderMax = sm["sliderMax"];
        isDiscrete = sm["isDiscrete"];
    }
}
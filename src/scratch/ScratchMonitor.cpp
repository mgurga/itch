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

    for (auto p : sm["params"].items()) params[p.key()] = p.value();

    if (mode != LIST) {
        sliderMin = sm["sliderMin"];
        sliderMax = sm["sliderMax"];
        isDiscrete = sm["isDiscrete"];
    }
}
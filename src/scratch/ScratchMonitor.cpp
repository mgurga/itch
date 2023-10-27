#include "ScratchMonitor.hpp"

ScratchMonitor::ScratchMonitor(json sm) :
    id(sm["id"]),
    opcode(sm["opcode"]),
    spriteName(sm["spriteName"].is_null() ? "" : sm["spriteName"]),
    width(sm["width"]),
    height(sm["height"]),
    x(sm["x"]),
    y(sm["y"]),
    visible(sm["visible"]) {
    if (!(sm["mode"] == "list")) {
        values.push_back(sm["value"].dump());
    } else {
        for (auto v : sm["value"]) {
            if (v.type() == nlohmann::detail::value_t::string)
                values.push_back(v.get<std::string>());
            else
                values.push_back(v.dump());
        }
    }

    if (sm["mode"] == "default") {
        mode = MonitorMode::DEFAULT;
    } else if (sm["mode"] == "large") {
        mode = MonitorMode::LARGE;
    } else if (sm["mode"] == "slider") {
        mode = MonitorMode::SLIDER;
    } else if (sm["mode"] == "list") {
        mode = MonitorMode::LIST;
    } else {
        mode = MonitorMode::DEFAULT;
    }

    for (auto p : sm["params"].items()) params[p.key()] = p.value();

    if (mode != MonitorMode::LIST) {
        sliderMin = sm["sliderMin"];
        sliderMax = sm["sliderMax"];
        isDiscrete = sm["isDiscrete"];
    }
}
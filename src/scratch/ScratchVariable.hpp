#pragma once

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ScratchVariable {
public:
    ScratchVariable(json sv):
        name(to_string(sv[0])),
        value(to_string(sv[1])),
        isCloud(sv.size() == 3)
    {};

    std::string name;
    std::string value;
    bool isCloud;
};
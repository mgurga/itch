#pragma once

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ScratchVariable {
public:
    ScratchVariable(json sv);

    std::string name;
    std::string value;
    bool isCloud;
};
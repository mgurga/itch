#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "ScratchVariable.hpp"

using json = nlohmann::json;

class ScratchTarget
{
public:
    ScratchTarget(json st);

    bool isStage;
    std::string name;
    std::vector<ScratchVariable> variables;
    int volume;
    int layerOrder;
};
